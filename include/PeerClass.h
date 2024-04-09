/*
include PeerList and PeriphList
Version 2.01
*/

#ifndef PEERCLASS_H
#define PEERCLASS_H

#include <Arduino.h>
#include "Jeepify.h"
#include "LinkedList.h"

class PeriphClass {
    static int  _ClassId;

    private:
        char        _Name[20];
        int         _Id;
        int         _Type;      //1=Switch, 2=Amp, 3=Volt
        int         _Pos;       //Periph 1..4.. from one peer
        bool        _isADS;
        int         _IOPort;
        float       _Nullwert;
        float       _VperAmp;
        int         _Vin;
        volatile float       _Value;
        float       _OldValue;
        bool        _Changed;
        int         _PeerId;
        
    public:
        PeriphClass();
        void  Setup(const char* Name, int Type, bool isADS, int IOPort, float Nullwert, float VperAmp, int Vin, int PeerId);
        
        bool  SetName(const char* Name) { strcpy(_Name, Name); return true; }
        char *GetName(){ return (_Name); }
        int   GetId() { return _Id; }
        void  SetId(int Id) { _Id = Id; }
        int   GetType() { return _Type; }
        void  SetType(int Type) { _Type = Type; }
        bool  IsType(int Type);
        int   GetPos() { return _Pos; }
        void  SetPos(int Pos) {_Pos = Pos; }
        bool  isADS() { return _isADS; }
        bool  GetADS() { return _isADS; }
        void  SetADS(bool isADS) { _isADS = isADS; }
        int   GetIOPort() { return _IOPort; }
        void  SetIOPort(int IOPort) { _IOPort = IOPort; }
        float GetNullwert() { return _Nullwert; }
        void  SetNullwert(float Nullwert) { _Nullwert = Nullwert; }
        float GetVperAmp() { return _VperAmp; }
        void  SetVperAmp(float VperAmp) { _VperAmp = VperAmp; }
        int   GetVin() { return _Vin; }
        void  SetVin(int Vin) { _Vin = Vin; }
        float GetValue() { return _Value; }
        void  SetValue(float Value) { _Value = Value; }
        float GetOldValue() { return _OldValue; }
        void  SetOldValue(float OldValue) { _OldValue = OldValue; }
        bool  hasChanged() { return _Changed; }
        bool  GetChanged() { return _Changed; }
        void  SetChanged(bool Changed) { _Changed = Changed; }
        int   GetPeerId() { return _PeerId; }
        void  SetPeerId(int PeerId) { _PeerId = PeerId; }
        bool  IsSensor() { return ((_Type == SENS_TYPE_VOLT) or (_Type == SENS_TYPE_AMP)); }
        bool  IsSwitch() { return ( _Type == SENS_TYPE_SWITCH) ; }
        bool  isEmpty() { return (_Type == 0); }
        
        PeriphClass *GetPtrToSelf() { return this; }
};

class PeerClass 
{
    static int _ClassId;

    private:
        char       _Name[20];
        int        _Id;
        int        _Type;  
        char       _Version[10];
        u_int8_t   _BroadcastAddress[6];
        bool       _SleepMode;
        bool       _DebugMode;
        bool       _DemoMode;
        bool       _PairMode;
        bool       _Changed;
        PeriphClass Periph[MAX_PERIPHERALS]; 
        uint32_t   _TSLastSeen;
        int        _VoltageMon;
        int        _RelayType;
        int        _ADCPort1;
        int        _ADCPort2;
        float      _VoltageDevider;
        uint32_t   _LastContact;
        int        _Brightness;
        
    public:
        PeerClass();
        void  Setup(const char* Name, int Type, const char *Version, const uint8_t *BroadcastAddress, 
                    bool SleepMode, bool DebugMode, bool DemoMode, bool PairMode);
        void  Setup(const char* Name, int Type, const char *Version, const uint8_t *BroadcastAddress, 
                    bool SleepMode, bool DebugMode, bool DemoMode, bool PairMode,
                    int VoltageMon, int RelayType, int ADCPort1, int ADCPort2, float VoltageDevider);
        char* Export();
        void  Import(const char *Buf);

        void  SetName(const char *Name) { strcpy(_Name, Name); }
        char *GetName() { return (_Name); }
        void  SetVersion(const char *Version) { strcpy(_Version, Version); }
        char *GetVersion() { return (_Version); }
        int   GetId() { return _Id; }
        void  SetId(int Id) { _Id = Id; }
        int   GetType() { return _Type; }
        void  SetType(int Type) { _Type = Type; }
        uint8_t *GetBroadcastAddress() { return _BroadcastAddress; }
        void     SetBroadcastAddress(const uint8_t *BroadcastAddress) { memcpy(_BroadcastAddress, BroadcastAddress, 6); }
        uint32_t GetTSLastSeen() { return _TSLastSeen; }
        void     SetTSLastSeen(uint32_t TSLastSeen) { _TSLastSeen = TSLastSeen; }
        bool  GetSleepMode() { return _SleepMode; }
        void  SetSleepMode(bool SleepMode) { _SleepMode = SleepMode; }
        bool  GetDebugMode() { return _DebugMode; }
        void  SetDebugMode(bool DebugMode) { _DebugMode = DebugMode; }
        bool  GetDemoMode() { return _DemoMode; }
        void  SetDemoMode(bool DemoMode) { _DemoMode = DemoMode; }
        bool  GetPairMode() { return _PairMode; }
        void  SetPairMode(bool PairMode) { _PairMode = PairMode; }
        bool  GetChanged() { return _Changed; }
        void  SetChanged(bool Changed) { _Changed = Changed; }
        int   GetVoltageMon() { return _VoltageMon; }
        void  SetVoltageMon(int VoltageMon) { _VoltageMon = VoltageMon; }
        int   GetRelayType() { return _RelayType; }
        void  SetRelayType(int RelayType) { _RelayType = RelayType; }
        int   GetADCPort1() { return _ADCPort1; }
        void  SetADCPort1(int ADCPort1) { _ADCPort1 = ADCPort1; }
        int   GetADCPort2() { return _ADCPort2; }
        void  SetADCPort2(int ADCPort2) { _ADCPort2 = ADCPort2; }
        int   GetVoltageDevider() { return _VoltageDevider; }
        void  SetVoltageDevider(int VoltageDevider) { _VoltageDevider = VoltageDevider; }
        int32_t   GetLastContact() { return _LastContact; }
        void      SetLastContact(uint32_t LastContact) { _LastContact = LastContact; }
        
        bool  TogglePairMode() { _PairMode = !_PairMode; return _PairMode; }
    
        int   GetBrightness() { return _Brightness; }
        void  SetBrightness(int Brightness) {_Brightness = Brightness; }
        
        void  PeriphSetup(int Pos, const char* Name, int Type, bool isADS, int IOPort, float Nullwert, float VperAmp, int Vin, int PeerId);
        
        char *GetPeriphName(int P) { return Periph[P].GetName(); }
        bool  SetPeriphName(int P, const char *Name) { Periph[P].SetName(Name); return true; }
        
        int   GetPeriphId(char *Name);
        int   GetPeriphId(int PosPeriph) { return Periph[PosPeriph].GetId(); }
        
        void  SetPeriphPeerId(int P, int PeerId) { Periph[P].SetPeerId(PeerId); }
        int   GetPeriphPeerId(int P) { return Periph[P].GetPeerId(); }

        int   GetPeriphPos(int P) { return Periph[P].GetPos(); }

        float GetPeriphValue(char *Name);
        float GetPeriphValue(int P) { return Periph[P].GetValue(); }
        void  SetPeriphValue(int P, float Value) { Periph[P].SetValue(Value); }
        void  SetPeriphValue(char *Name, float Value);
        
        float GetPeriphOldValue(int P) { return Periph[P].GetOldValue(); }
        void  SetPeriphOldValue(int P, float Value) { Periph[P].SetOldValue(Value); }
        
        void  SetPeriphChanged(int P, bool Changed) { Periph[P].SetChanged(Changed); }
        bool  GetPeriphChanged(int P) { return Periph[P].GetChanged(); }
        bool  PeriphChanged(int P) { return Periph[P].GetChanged(); }
        
        bool  PeriphHasADS(int P) { return Periph[P].GetADS(); }
        bool  GetPeriphADS(int P) { return Periph[P].GetADS(); }
        
        int   GetPeriphType(int P) { return Periph[P].GetType(); }
        
        int   GetPeriphVin(int P) { return Periph[P].GetVin(); }
        void  SetPeriphVin(int P, float Vin) { Periph[P].SetVin(Vin); }
        
        float GetPeriphVperAmp(int P){ return Periph[P].GetVperAmp(); }
        void  SetPeriphVperAmp(int P, float VperAmp) { return Periph[P].SetVperAmp(VperAmp); }
        
        int   GetPeriphIOPort(int P) { return Periph[P].GetIOPort(); }

        float GetPeriphNullwert(int P) { return Periph[P].GetNullwert(); }
        float GetPeriphNullwert(char *Name);
        void  SetPeriphNullwert(int P, float Nullwert) { Periph[P].SetNullwert(Nullwert); }
        void  SetPeriphNullwert(char *Name, float Nullwert);

        PeriphClass *GetPeriphPtr(int P) { return &Periph[P]; }
        PeriphClass *GetPeriphPtr(char *Name);
        
        bool isEmpty() { return (_Type == 0); }
        bool isPeriphEmpty(int SNr) { return Periph[SNr].isEmpty(); }
        bool isPeriphSensor(int SNr) { return Periph[SNr].IsSensor(); }
        bool isPeriphSwitch(int SNr) { return Periph[SNr].IsSwitch(); }
};

PeerClass *FindPeerByMAC(const uint8_t *BroadcastAddress);
PeerClass *FindPeerById(int Id);
PeerClass *FindPeerByName(char *Name);

PeerClass *FindFirstPeer(int Type);
PeerClass *FindNextPeer(PeerClass *P, int Type, bool circular);
PeerClass *FindPrevPeer(PeerClass *P, int Type, bool circular);
PeriphClass *FindPeriphById(int Id);
PeriphClass *FindFirstPeriph(PeerClass *P, int Type);
PeriphClass *FindLastPeriph (PeerClass *P, int Type);
PeriphClass *FindPrevPeriph(PeerClass *P, PeriphClass *Periph, int Type, bool circular);
PeriphClass *FindNextPeriph(PeerClass *P, PeriphClass *Periph, int Type, bool circular);

extern LinkedList<PeerClass*>   PeerList;
extern LinkedList<PeriphClass*> PeriphList;

char *TypeInText(int Type);
extern PeerClass *ActivePeer;
extern PeriphClass *ActivePeriph;

extern char ExportImportBuffer[300];

char *TypeInText(int Type);

#endif