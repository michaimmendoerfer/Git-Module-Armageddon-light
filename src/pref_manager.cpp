#include <Arduino.h>
#include "PeerClass.h"
#include <Preferences.h>
#ifdef ESP32
    #include <esp_now.h>
    #include <WiFi.h>
    #include <nvs_flash.h>
#elif defined(ESP8266)
    #include <ESP8266WiFi.h>
    #include <espnow.h>
#endif 
#include <pref_manager.h>

extern Preferences preferences;

void   PrintMAC(const uint8_t * mac_addr);

MultiMonitorClass Screen[MULTI_SCREENS];

char ScreenExportImportBuffer[300];

int  MultiMonitorClass::_ClassId = 1;

MultiMonitorClass::MultiMonitorClass() 
{ 
    _Id = _ClassId;
    _ClassId++;
    
    sprintf(_Name, "Screen-%d", _Id);
    _Changed = false;
    
    for (int i=0; i<PERIPH_PER_SCREEN; i++)
    {
        _Peer[i] = NULL;
        _PeerId[i] = 0;
        _Periph[i] = NULL;
        _PeriphId[i] = 0;
        _Component[i] = NULL;
    }
    _Used = false;
}
char* MultiMonitorClass::Export() 
// fills ScreenExportImportBuffer with "Name;PeriphId0;PeriphId1;PeriphId2;PeriphId3"
{
    char ReturnBufferScreen[50];

    strcpy(ScreenExportImportBuffer, _Name);
                        
    for (int Si=0; Si<PERIPH_PER_SCREEN; Si++)
    {   
        sprintf(ReturnBufferScreen, ";%d",_PeriphId[Si]);
        strcat(ScreenExportImportBuffer, ReturnBufferScreen);
    }

    return ScreenExportImportBuffer;
}
void MultiMonitorClass::Import(char *Buf) 
// import from Buf with "Name;PeriphId0;PeriphId1;PeriphId2;PeriphId3"
{
    strcpy(_Name, strtok(Buf, ";"));
    
    for (int Si=0; Si<PERIPH_PER_SCREEN; Si++)
    {  
        _PeriphId[Si] = atoi(strtok(NULL, ";"));
        if (_PeriphId[Si] > 0)
        {
            _Periph[Si]   = FindPeriphById(_PeriphId[Si]);
            _PeerId[Si]   = _Periph[Si]->GetPeerId();
            _Peer[Si]     = FindPeerById(_PeerId[Si]);
        }
        else
        {
            _Periph[Si]   = NULL;
            _PeerId[Si]   = 0;
            _Peer[Si]     = NULL;
        }
    }

}
void SavePeers() 
// writes [Peer-0] - [Name;Type;BroadcastAddress[0-5];SleepMode;DebugMode;DemoMode;Periph0Name;Periph0Type;Periph0Pos;Periph0PeerId...]
{
    PeerClass *P;
    
    char Buf[10];
    char ExportBuffer[50];
    String ExportStringMulti;
    String ExportStringPeer;

    preferences.begin("JeepifyPeers", false);
    
    preferences.putInt("PeerCount", PeerList.size());
    Serial.printf("PeerList.size() = %d, gelesenes PeerCount = %d\n\r", PeerList.size(), preferences.getInt("PeerCount"));

    for(int i = 0; i < PeerList.size(); i++){
      P = PeerList.get(i);
      sprintf(Buf, "Peer-%d", i);

      ExportStringPeer = P->Export();

      Serial.printf("putSring = %d", preferences.putString(Buf, ExportStringPeer));
      Serial.printf("schreibe: [%s]: %s", Buf, ExportStringPeer.c_str());
      Serial.println();
    }
  
    Serial.println("jetzt kommt Multi");

    for (int s=0; s<MULTI_SCREENS; s++) {
      snprintf(Buf, sizeof(Buf), "Screen-%d", s);
      
      ExportStringMulti = Screen[s].Export();

      preferences.putString(Buf, ExportStringMulti);
      Serial.printf("schreibe: [%s]: %s", Buf, ExportStringMulti.c_str());
      Serial.println();
    }
    preferences.end();
}
int GetPeers() 
{
    PeerClass *P;
    
    char Buf[10];
    String ImportStringMulti;
    String ImportStringPeer;

    preferences.begin("JeepifyPeers", true);

    PeerList.clear();

    int PeerCount = preferences.getInt("PeerCount");
    Serial.printf("Peercount = %d", PeerCount);
    
    for (int Pi=0 ; Pi<PeerCount; Pi++)
    {
        sprintf(Buf, "Peer-%d", Pi);
        ImportStringPeer = preferences.getString(Buf, "");
        strcpy(ScreenExportImportBuffer, ImportStringPeer.c_str());
        Serial.printf("gelesen: [%s]: %s\n", Buf, ScreenExportImportBuffer);

        P = new PeerClass();
        P->Import(ScreenExportImportBuffer);
        
        PeerList.add(P);
        for (int Si=0; Si<MAX_PERIPHERALS; Si++) PeriphList.add(P->GetPeriphPtr(Si));
    }
  
    Serial.println("jetzt kommt Multi");

    for (int s=0; s<MULTI_SCREENS; s++) 
    {
        snprintf(Buf, sizeof(Buf), "Screen-%d", s);
        
        ImportStringMulti = preferences.getString(Buf, "nix");
        if (ImportStringMulti != "nix") 
        {   
            Serial.printf("%s - %d Bytes gelesen: %s\n\r", Buf, sizeof(ImportStringMulti), ImportStringMulti);
            strcpy(ScreenExportImportBuffer, ImportStringMulti.c_str());
            
            ReportAll();
            
            Serial.println("jetzt kommt import");
            Screen[s].Import(ScreenExportImportBuffer);
        }
    }
    ReportAll();
    preferences.end();

    return PeerCount;
}
void ClearPeers() 
{
  preferences.begin("JeepifyPeers", false);
    preferences.clear();
    Serial.println("JeepifyPeers cleared...");
  preferences.end();
}
void ClearInit() 
{
  preferences.begin("JeepifyInit", false);
    preferences.clear();
    Serial.println("JeepifyInit cleared...");
  preferences.end();
}
void DeletePeer(PeerClass *P) 
{
    PeriphClass *Periph;
    
    for (int s=0; s<MULTI_SCREENS; s++) {
      for (int Si=0; Si<PERIPH_PER_SCREEN; Si++)
      {
          if (Screen[s].GetPeerId(Si) == P->GetId())
          {
              Screen[s].SetPeerId(Si, -1);
              Screen[s].SetPeer(Si, NULL);
              Screen[s].SetPeriphId(Si, -1);
              Screen[s].SetPeer(Si, NULL);
              Screen[s].SetChanged(true);
          }
      }
    }

    for (int Si=PeriphList.size()-1; Si>=0; Si--)
    {
        Periph = PeriphList.get(Si);
        if (Periph->GetPeerId() == P->GetId()) PeriphList.remove(Si);
    }

    for(int i = 0; i < PeerList.size(); i++){
        if (PeerList.get(i) == P) 
        {
            PeerList.remove(i);
            Serial.printf("Peer: %s deleted and removed from list.", P->GetName());
            delete P;
            P = NULL;
        }
    }
}
void RegisterPeers() 
{
  PeerClass *P;

  #ifdef ESP32
        esp_now_peer_info_t peerInfo;
        peerInfo.channel = 1;
        peerInfo.encrypt = false;
        memset(&peerInfo, 0, sizeof(peerInfo));

        // Register BROADCAST
        for (int b=0; b<6; b++) peerInfo.peer_addr[b] = 0xff;
            if (esp_now_add_peer(&peerInfo) != ESP_OK) {
            PrintMAC(peerInfo.peer_addr); Serial.println(": Failed to add peer");
            }
            else {
            Serial.print (" ("); PrintMAC(peerInfo.peer_addr);  Serial.println(") added...");
            }

        // Register Peers
        for (int i=0; i<PeerList.size(); i++) 
        {
            P = PeerList.get(i);
            memcpy(peerInfo.peer_addr, P->GetBroadcastAddress(), 6);

            if (esp_now_add_peer(&peerInfo) != 0) 
            {
                PrintMAC(peerInfo.peer_addr); Serial.println(": Failed to add peer");
            }
            else {
                Serial.print("Peer: "); Serial.print(P->GetName()); 
                Serial.print (" ("); PrintMAC(peerInfo.peer_addr); Serial.println(") added...");
            }
        }
  #elif defined(ESP8266)
        if (esp_now_add_peer(broadcastAddressAll, ESP_NOW_ROLE_SLAVE, 1, NULL, 0) != 0) {
        PrintMAC(broadcastAddressAll); Serial.println(": Failed to add peer");
        }
        else {
        Serial.print (" ("); PrintMAC(broadcastAddressAll);  Serial.println(") added...");
        }

        for (int i=0; i<PeerList.size(); i++) 
        {
            P = PeerList.get(i);
            
            if (esp_now_add_peer(P->GetBroadcastAddress(), ESP_NOW_ROLE_SLAVE, 1, NULL, 0) != 0) 
            {
                PrintMAC(P->GetBroadcastAddress()); Serial.println(": Failed to add peer");
            }
            else {
                Serial.print("Peer: "); Serial.print(P->GetName()); 
                Serial.print (" ("); PrintMAC(P->GetBroadcastAddress()); Serial.println(") added...");
            }
        }
  #endif  // ESP8266
}
void ReportAll()
{
    PeerClass *P;
    Serial.printf("REPORT: PeerList.size() = %d\n\r", PeerList.size());

    for(int i=0; i < PeerList.size(); i++)
    {
      P = PeerList.get(i);
      Serial.printf("[%d] %s, Type:%d, MAC:", P->GetId(), P->GetName(), P->GetType());
      PrintMAC(P->GetBroadcastAddress());
      Serial.println();
      for (int Si=0; Si<MAX_PERIPHERALS; Si++)
      {
          if (P->GetPeriphType(Si) > 0)
          {
              Serial.printf("    %d: %s(%d) at position %d", P->GetPeriphId(Si), P->GetPeriphName(Si), P->GetPeriphType(Si), P->GetPeriphPos(Si));
              Serial.println();
          }
      }

      for (int s=0; s<MULTI_SCREENS; s++) {
          //Serial.printf("Screen[%d]: %s", s, Screen[s].GetName());
          for (int Si=0; Si<PERIPH_PER_SCREEN; Si++)
          {
              if (Screen[s].GetPeriphId(Si))
              {
                Serial.printf("    %d: %s(%d) at position %d", Screen[s].GetPeriph(Si)->GetId(), Screen[s].GetPeriph(Si)->GetName(), Screen[s].GetPeriph(Si)->GetType(), Si);
                Serial.println();
              }
          }
      }
    }
}