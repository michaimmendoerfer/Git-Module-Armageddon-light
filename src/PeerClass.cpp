//Version 1.01
#include <Arduino.h>
#include "PeerClass.h"
#include "LinkedList.h"

PeerClass   *ActivePeer;
PeriphClass *ActivePeriph;

LinkedList<PeerClass*> PeerList = LinkedList<PeerClass*>();
LinkedList<PeriphClass*> PeriphList = LinkedList<PeriphClass*>();

int  PeriphClass::_ClassId = 1;
int  PeerClass::_ClassId = 1;

char ExportImportBuffer[300];

extern void PrintMAC(const uint8_t * mac_addr);

#pragma region PeriphClass::Declaration
PeriphClass::PeriphClass()
{
    _Id = _ClassId;
    _ClassId++;

    strcpy(_Name, "n.n.");
    _Type = 0;  
    _Pos = 0;       
    _isADS = false;
    _IOPort = 0;
    _Nullwert = 0;
    _VperAmp = 0;
    _Vin = 0;
    _Value = 0;
    _OldValue = 0;
    _Changed = false;
    _PeerId = 0;
    memset(_UId, 0, 7);
}
void  PeriphClass::Setup(const char* Name, int Type, bool isADS, int IOPort, 
                         float Nullwert, float VperAmp, int Vin, int PeerId, uint8_t *UId)
{
    strcpy(_Name, Name);
    _Type = Type;
    _isADS = isADS;
    _IOPort = IOPort;
    _Nullwert = Nullwert;
    _VperAmp = VperAmp;
    _PeerId = PeerId;
    memcpy(_UId, UId, 7);
}
bool PeriphClass::IsType(int Type)
{
    switch (Type) { 
                case SENS_TYPE_ALL:                                                                return true; break;
                case SENS_TYPE_SENS:    if ((_Type == SENS_TYPE_VOLT) or (_Type == SENS_TYPE_AMP)) return true; break;
                case SENS_TYPE_VOLT:    if  (_Type == SENS_TYPE_VOLT)                              return true; break;
                case SENS_TYPE_AMP:     if  (_Type == SENS_TYPE_AMP)                               return true; break;
                case SENS_TYPE_SWITCH:  if  (_Type == SENS_TYPE_SWITCH)                            return true; break;
            }
    return false;
}
#pragma endregion PeriphClass::Declaration
#pragma region PeerClass::Declaration
PeerClass::PeerClass()
{
    _Id = _ClassId;
    _ClassId++;

    strcpy(_Name, "n.n.") ;
    _Type = 0;  
    _SleepMode = false;
    _DebugMode = false;
    _DemoMode = false;
    _PairMode = false;
    _Changed = false;
    _TSLastSeen = 0;
    memset(_BroadcastAddress, 0, 6);
}
void  PeerClass::Setup(const char* Name, int Type, const char *Version, const uint8_t *BroadcastAddress, 
                       bool SleepMode, bool DebugMode, bool DemoMode, bool PairMode)
{
    strcpy(_Name, Name);
    _Type = Type;
    strcpy(_Version, Version);
    memcpy(_BroadcastAddress, BroadcastAddress, 6);
    _SleepMode = SleepMode;
    _DebugMode = DebugMode;
    _DemoMode  = DemoMode;
    _PairMode  = PairMode;
    
    for (int Si=0; Si<MAX_PERIPHERALS; Si++) Periph[Si].SetPos(Si);
}     
void  PeerClass::Setup(const char* Name, int Type, const char *Version, const uint8_t *BroadcastAddress, 
                    bool SleepMode, bool DebugMode, bool DemoMode, bool PairMode,
                    int VoltageMon, int RelayType, int ADCPort1, int ADCPort2, float VoltageDevider)
{
    strcpy(_Name, Name);
    _Type = Type;
    strcpy(_Version, Version);
    if (BroadcastAddress) memcpy(_BroadcastAddress, BroadcastAddress, 6);
    _SleepMode = SleepMode;
    _DebugMode = DebugMode;
    _DemoMode  = DemoMode;
    _PairMode  = PairMode;

    _VoltageMon     = VoltageMon;
    _RelayType      = RelayType;
    _ADCPort1       = ADCPort1;
    _ADCPort2       = ADCPort2;
    _VoltageDevider = VoltageDevider;
    
    for (int Si=0; Si<MAX_PERIPHERALS; Si++) 
    {
        Periph[Si].SetPos(Si);
    }
}      
char* PeerClass::Export() 
{
    char ReturnBufferPeriph[40];

    snprintf(ExportImportBuffer, sizeof(ExportImportBuffer), "%s;%d;%d;%d;%d;%d;%d;%d;%d;%d;%d", 
                        _Name, _Type, 
                        _BroadcastAddress[0], _BroadcastAddress[1], _BroadcastAddress[2],
                        _BroadcastAddress[3], _BroadcastAddress[4], _BroadcastAddress[5],
                        _SleepMode, _DebugMode, _DemoMode);
                        
    for (int Si=0; Si<MAX_PERIPHERALS; Si++)
    { 
        snprintf(ReturnBufferPeriph, sizeof(ReturnBufferPeriph), ";%s;%d",
                 Periph[Si].GetName(), Periph[Si].GetType());

        strcat(ExportImportBuffer, ReturnBufferPeriph);
    }

    return ExportImportBuffer;
}
void PeerClass::Import(char *Buf) 
{
    strcpy(_Name, strtok(Buf, ";"));
    _Type = atoi(strtok(NULL, ";"));
    
    _BroadcastAddress[0] = (byte) atoi(strtok(NULL, ";"));
    _BroadcastAddress[1] = (byte) atoi(strtok(NULL, ";"));
    _BroadcastAddress[2] = (byte) atoi(strtok(NULL, ";"));
    _BroadcastAddress[3] = (byte) atoi(strtok(NULL, ";"));
    _BroadcastAddress[4] = (byte) atoi(strtok(NULL, ";"));
    _BroadcastAddress[5] = (byte) atoi(strtok(NULL, ";"));
    //PrintMAC(_BroadcastAddress);

    _SleepMode = (bool) atoi(strtok(NULL, ";"));
    _DebugMode = (bool) atoi(strtok(NULL, ";"));
    _DemoMode  = (bool) atoi(strtok(NULL, ";"));

    for (int Si=0; Si<MAX_PERIPHERALS; Si++)
    {
        Periph[Si].SetName(strtok(NULL, ";"));
        Periph[Si].SetType(atoi(strtok(NULL, ";")));
        Periph[Si].SetPos(Si);
        Periph[Si].SetPeerId(_Id);
    }
    //Serial.println("ende import");
}
        
void  PeerClass::PeriphSetup(int Pos, const char* Name, int Type, bool isADS, int IOPort, 
                             float Nullwert, float VperAmp, int Vin, int PeerId)
{
    uint8_t UId[7];
    byte PosByte = Pos;

    memcpy(UId, _BroadcastAddress, 6);
    UId[6] = PosByte;

    Periph[Pos].Setup(Name, Type, isADS, IOPort, Nullwert, VperAmp, Vin, PeerId, UId);
}
int   PeerClass::GetPeriphId(char *Name)
{
    for (int P=0; P<MAX_PERIPHERALS; P++)
    {   
        if (strcmp(Name, Periph[P].GetName()) == 0) return Periph[P].GetId();
    }
    return -1;
}
void  PeerClass::SetPeriphValue(char *Name, float Value)
{
   for (int P=0; P<MAX_PERIPHERALS; P++)
    {   
        if (strcmp(Name, Periph[P].GetName()) == 0) Periph[P].SetValue(Value); 
    }    
}
float PeerClass::GetPeriphValue(char *Name)
{
   for (int P=0; P<MAX_PERIPHERALS; P++)
    {   
        if (strcmp(Name, Periph[P].GetName()) == 0) return Periph[P].GetValue(); 
    }    

    return -1;
}
float PeerClass::GetPeriphNullwert(char *Name) 
{
    for (int P=0; P<MAX_PERIPHERALS; P++)
    {   
        if (strcmp(Name, Periph[P].GetName()) == 0) return Periph[P].GetNullwert(); 
    }    

    return -1;
}
void  PeerClass::SetPeriphNullwert(char *Name, float Nullwert)
{
    for (int P=0; P<MAX_PERIPHERALS; P++)
    {   
        if (strcmp(Name, Periph[P].GetName()) == 0) Periph[P].SetNullwert(Nullwert);
    }    
}
PeriphClass *PeerClass::GetPeriphPtr(char *Name)
{
    for (int P=0; P<MAX_PERIPHERALS; P++)
    {
        if (strcpy(Periph[P].GetName(), Name) == 0) return &Periph[P];
    }
    return NULL;
}
#pragma endregion PeerClass::Declaration
#pragma region MAC-Things
PeerClass *FindPeerByMAC(const uint8_t *BroadcastAddress)
{
    PeerClass *Peer;
    for(int i = 0; i < PeerList.size(); i++){

		Peer = PeerList.get(i);

		if (memcmp(Peer->GetBroadcastAddress(), BroadcastAddress, 6) == 0) return Peer;
	}
    return NULL;
}
PeerClass *FindPeerById(int Id)
{
    PeerClass *Peer;
    for(int i = 0; i < PeerList.size(); i++){

		Peer = PeerList.get(i);

		if (Peer->GetId() == Id) return Peer;
    }
    return NULL;
}
PeerClass *FindPeerByName(char *Name)
{
    PeerClass *Peer;
    for(int i = 0; i < PeerList.size(); i++) 
    {   
        Peer = PeerList.get(i);
        if (strcmp(Peer->GetName(), Name) == 0) return Peer;
    }
    return NULL;
}
PeerClass *FindFirstPeer(int Type)
// returns first Peer with Type, otherwise NULL
{
    for(int i = 0; i < PeerList.size(); i++) 
    {   
        if ((PeerList.get(i)->GetType() == Type) or (Type == MODULE_ALL)) return PeerList.get(i);
    }
    return NULL;
}
PeerClass *FindNextPeer(PeerClass *P, int Type, bool circular)
// returns next Peer, tries PeerList.size() times, otherwise returns NULL
{
    PeerClass *Peer;
    int ActualPeerIndex;

    //Get PeerIndex in List
    for(int i = 0; i < PeerList.size(); i++) 
    {   
        if (PeerList.get(i) == P) ActualPeerIndex = i;
    }

    for (int i=0; i<PeerList.size(); i++)
    {       
        ActualPeerIndex++;
        if (ActualPeerIndex == PeerList.size()) 
        {   
            if (!circular) return NULL;
            ActualPeerIndex = 0;
        }

        Peer = PeerList.get(ActualPeerIndex);
        
        if (Type == MODULE_ALL) return Peer;
        if (Type == Peer->GetType()) return Peer;
    }
    return NULL;
}
PeerClass *FindPrevPeer(PeerClass *P, int Type, bool circular)
// returns previous Peer, tries PeerList.size() times, otherwise returns NULL
{
    PeerClass *Peer;
    int ActualPeerIndex;

    //Get PeerIndex in List
    for(int i = 0; i < PeerList.size(); i++) 
    {   
        if (PeerList.get(i) == P) ActualPeerIndex = i;
    }

    for (int i=0; i<PeerList.size(); i++)
    {       
        ActualPeerIndex--;
        if (ActualPeerIndex == -1) 
        {   
            if (!circular) return NULL;
            ActualPeerIndex = PeerList.size()-1;
        }

        Peer = PeerList.get(ActualPeerIndex);
        
        if (Type == MODULE_ALL) return Peer;
        if (Type == Peer->GetType()) return Peer;
    }
    return NULL;
}

PeriphClass *FindPeriphById(int Id)
{
    for(int i = 0; i < PeriphList.size(); i++) 
    {   
        if (PeriphList.get(i)->GetId() == Id) return PeriphList.get(i);
    }
    return NULL;
}
PeriphClass *FindFirstPeriph(PeerClass *P, int Type)
// return first Periph of Type. If Peer=NULL Peer is ignored
{
    PeriphClass *Periph;

    if (PeriphList.size() == 0) return NULL;
    Serial.printf("PeriphList.size() = %d",PeriphList.size());

    for(int i = 0; i < PeriphList.size(); i++) 
    {   
        Periph = PeriphList.get(i);
        Serial.printf("Checke %s, PeriphId:%d\n\r", Periph->GetName(), Periph->GetId());
        
        if ((P == NULL) or (P->GetId() == Periph->GetPeerId()))
        // Peer fits
        {
            if (Periph->IsType(Type)) return Periph;
        }
    }
    return NULL;
}
PeriphClass *FindLastPeriph(PeerClass *P, int Type)
// return last Periph of Type. If Peer=NULL Peer is ignored, otherwise NULL
{
    PeriphClass *Periph;

    if (PeriphList.size() == 0) return NULL;
    
    for(int i = PeriphList.size()-1; i>=0; i--) 
    {   
        Periph = PeriphList.get(i);

        if ((P == NULL) or (P->GetId() == Periph->GetPeerId()))
        // Peer fits
        {
            if (Periph->IsType(Type)) return Periph;
        }
    }
    return NULL;
}
int FindPeriphListPos(PeriphClass *Periph)
{
    if (PeriphList.size() == 0) return -1;

    if (Periph != NULL)
    {
        for(int i = 0; i < PeriphList.size(); i++) 
        {   
            if (PeriphList.get(i) == Periph) return i;
        }
    }
    return -1;
}
int FindPeerListPos(PeerClass *P)
{
    if (PeerList.size() == 0) return -1;

    if (P != NULL)
    {
        for(int i = 0; i < PeerList.size(); i++) 
        {   
            if (PeerList.get(i) == P) return i;
        }
    }
    return -1;
}
PeriphClass *FindNextPeriph(PeerClass *P, PeriphClass *Periph, int Type, bool circular)
// return next Periph of Type. If Peer=NULL Peer is ignored, otherwise NULL, circular...
{
    PeriphClass *TPeriph;
    
    if (PeriphList.size() == 0) return NULL;

    int PeriphPos = FindPeriphListPos(Periph);
    
    if (P == NULL) circular = true;  // if Peer doesnt matter, always search circular

    for(int i = 0; i < PeriphList.size(); i++) 
    {
        PeriphPos++;
        if (PeriphPos == PeriphList.size())
        {
            if (!circular) return NULL;
            PeriphPos = 0;
        }
        TPeriph = PeriphList.get(PeriphPos);

        if ((P == NULL) or (P->GetId() == TPeriph->GetPeerId()))
        // Peer fits
        {
            if (TPeriph->IsType(Type)) return TPeriph;
        }
    }
    return NULL;
}
PeriphClass *FindPrevPeriph(PeerClass *P, PeriphClass *Periph, int Type, bool circular)
// return previous Periph of Type. If Peer=NULL Peer is ignored, otherwise NULL, circular...
{
    PeriphClass *TPeriph;

    if (PeriphList.size() == 0) return NULL;
    
    int PeriphPos = FindPeriphListPos(Periph);
    if (PeriphPos == -1) PeriphPos--; // if not found prev will start at last element
    
    if (P == NULL) circular = true;   // if Peer doesnt matter, always search circular

    for(int i = 0; i < PeriphList.size(); i++) 
    {
        PeriphPos--;
        if (PeriphPos == -1)
        {
            if (!circular) return NULL;
            PeriphPos = PeriphList.size()-1;
        }
        TPeriph = PeriphList.get(PeriphPos);

        if ((P == NULL) or (P->GetId() == TPeriph->GetPeerId()))
        // Peer fits
        {
            if (TPeriph->IsType(Type)) return TPeriph;
        }
    }
    return NULL;
}
#pragma endregion MAC-Things

char *TypeInText(int Type)
{
    switch (Type)
    {
        case SENS_TYPE_VOLT:    return "Voltage-Sensor";
        case SENS_TYPE_AMP:     return "Current-Sensor";
        case SENS_TYPE_SWITCH:  return "Switch";
        case SWITCH_1_WAY:      return "1-way Switch";
        case SWITCH_2_WAY:      return "2-Way Switch";
        case SWITCH_4_WAY:      return "4-way Switch";
        case SWITCH_8_WAY:      return "8-Way Switch";
        case PDC:               return "Power distributor";
        case PDC_SENSOR_MIX:    return "Mixed Device";
        case BATTERY_SENSOR:    return "Battery-Sensor";
        case MONITOR_ROUND:     return "Round Monitor";
        case MONITOR_BIG:       return "3.5' Monitor";
    }
    return "not known";
}