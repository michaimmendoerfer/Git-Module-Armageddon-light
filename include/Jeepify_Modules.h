#ifndef JEEPIFY_MODULES_H
#define JEEPIFY_MODULES_H
#endif
/*
const int SWITCHES_PER_SCREEN = 4;

void InitModule(int ModuleType)
{
    /*
    ESP32 DevKit:
    possible Inputs:  4,13,16,17,18,19,21,22,23,25,26,27,(ADC1:32,33,34,35,36,39)
    possible Outputs: 4,13,16,17,18,19,21,22,23,25,26,27,32,33
    SPI-Flash:        6,7,8,9,10,11 (don´t use)
    ADC2 (when Wifi): 32,33,34,35,36,39

    
    //uint8_t MacUId[7];
    switch (ModuleType)
    {
        case ESP8266_4_SWITCHES_1_VOLT_NOADC_NO_PORT:
        {
            //                Name        Type       Version  Address   sleep  debug  demo  pair  vMon RelayType    adc1 adc2 voltagedevier 
            Module.Setup(_ModuleName, SWITCH_4_WAY, _Version, NULL,     false, true,  true, false, -1, RELAY_NORMAL, -1,  -1,     1);

            //                      Name     Type             ADS  IO  NULL   VpA   Vin  PeerID
            Module.PeriphSetup(0, "Sw-1",   SENS_TYPE_SWITCH,  0,  25,   0,    0,    0,    0);
            Module.PeriphSetup(1, "Sw-2",   SENS_TYPE_SWITCH,  0,  26,   0,    0,    0,    0);
            Module.PeriphSetup(2, "Sw-3",   SENS_TYPE_SWITCH,  0,  32,   0,    0,    0,    0);
            Module.PeriphSetup(3, "Sw-4",   SENS_TYPE_SWITCH,  0,  33,   0,    0,    0,    0);
            Module.PeriphSetup(4, "Volt-1", SENS_TYPE_VOLT,    0,  39,   0,    0,   200,   0); 

            break;
        }
        case ESP8266_4_SWITCHES_1_VOLT_ADC_NO_PORT:     
        {

            //                Name        Type         Version  Address   sleep  debug  demo  pair  vMon RelayType   adc1 adc2 voltagedevier 
            Module.Setup(_ModuleName, SWITCH_4_WAY, _Version,    NULL,    false, true,  true, false, 1,  RELAY_NORMAL, -1,  -1,     1);

            //                      Name     Type             ADS  IO  NULL   VpA   Vin  PeerID
            Module.PeriphSetup(0, "Extern", SENS_TYPE_SWITCH,  0,  25,   0,    0,    0,    0);
            Module.PeriphSetup(1, "In-Car", SENS_TYPE_SWITCH,  0,  26,   0,    0,    0,    0);
            Module.PeriphSetup(2, "Solar",  SENS_TYPE_SWITCH,  0,  32,   0,    0,    0,    0);
            Module.PeriphSetup(3, "Load",   SENS_TYPE_SWITCH,  0,  33,   0,    0,    0,    0);
            Module.PeriphSetup(4, "Lipo",   SENS_TYPE_VOLT,    0,  39,   0,    0,   200,   0); 
    }
    #ifdef MODULE_4S_1V_NOADC   // 4-Way Switch with Voltage-Monitor #################################################################
      const int SWITCHES_PER_SCREEN = 4;

      //                Name        Type       Version  Address   sleep  debug  demo  pair  vMon RelayType    adc1 adc2 voltagedevier 
      Module.Setup(_ModuleName, SWITCH_4_WAY, _Version, NULL,     false, true,  true, false, -1, RELAY_NORMAL, -1,  -1,     1);

      //                      Name     Type             ADS  IO  NULL   VpA   Vin  PeerID
      Module.PeriphSetup(0, "Extern", SENS_TYPE_SWITCH,  0,  25,   0,    0,    0,    0);
      Module.PeriphSetup(1, "In-Car", SENS_TYPE_SWITCH,  0,  26,   0,    0,    0,    0);
      Module.PeriphSetup(2, "Solar",  SENS_TYPE_SWITCH,  0,  32,   0,    0,    0,    0);
      Module.PeriphSetup(3, "Load",   SENS_TYPE_SWITCH,  0,  33,   0,    0,    0,    0);
      Module.PeriphSetup(4, "Lipo",   SENS_TYPE_VOLT,    0,  39,   0,    0,   200,   0); 
    #endif
    #ifdef MODULE_4S_1V_ADC     // 4-Way Switch no Voltage-Monitor ###################################################################
      #define SWITCHES_PER_SCREEN 4

      //                Name        Type         Version  Address   sleep  debug  demo  pair  vMon RelayType    adc1 adc2 voltagedevier 
      Module.Setup(_ModuleName, BATTERY_SENSOR, _Version, NULL,     false, true,  true, false, 1,  RELAY_NORMAL, -1,  -1,     1);

      //                      Name     Type             ADS  IO  NULL   VpA   Vin  PeerID
      Module.PeriphSetup(0, "Extern", SENS_TYPE_SWITCH,  0,  25,   0,    0,    0,    0);
      Module.PeriphSetup(1, "In-Car", SENS_TYPE_SWITCH,  0,  26,   0,    0,    0,    0);
      Module.PeriphSetup(2, "Solar",  SENS_TYPE_SWITCH,  0,  32,   0,    0,    0,    0);
      Module.PeriphSetup(3, "Load",   SENS_TYPE_SWITCH,  0,  33,   0,    0,    0,    0);
      Module.PeriphSetup(4, "Lipo",   SENS_TYPE_VOLT,    0,  39,   0,    0,   200,   0); 
    #endif
    #ifdef MODULE_1S            // 1-Way Switch ######################################################################################
      #define SWITCHES_PER_SCREEN 1
      //                Name        Type       Version  Address   sleep  debug  demo   pair  vMon RelayType      adc1 adc2 voltagedevier 
      Module.Setup(_ModuleName, SWITCH_1_WAY, _Version, NULL,     false, true,  false, false, -1, RELAY_REVERSED, -1,  -1,     1);

      //                      Name     Type             ADS    IO  NULL   VpA   Vin  PeerID
      Module.PeriphSetup(0, "Switch_1", SENS_TYPE_SWITCH,  0,  25,   0,    0,    0,    0);
    #endif
    #ifdef MODULE_2S            // 2-Way Switch ######################################################################################
      #define SWITCHES_PER_SCREEN 2

      //                Name        Type       Version  Address   sleep  debug  demo   pair  vMon RelayType      adc1 adc2 voltagedevier 
      Module.Setup(_ModuleName, SWITCH_2_WAY, _Version, NULL,     false, true,  false, false, -1, RELAY_REVERSED, -1,  -1,     1);
      
      //                      Name     Type             ADS    IO  NULL   VpA   Vin  PeerID
      Module.PeriphSetup(0, "Switch_1", SENS_TYPE_SWITCH,  0,  25,   0,    0,    0,    0);
      Module.PeriphSetup(0, "Switch_2", SENS_TYPE_SWITCH,  0,  26,   0,    0,    0,    0);
    #endif
    #ifdef MODULE_4A_1V_ADC     // 4-way Battery-Sensor with ADC and VMon ############################################################
      #define SWITCHES_PER_SCREEN 4
      
      //                Name        Type         Version  Address   sleep  debug  demo  pair  vMon RelayType    adc1 adc2 voltagedevier 
      Module.Setup(_ModuleName, BATTERY_SENSOR, _Version, NULL,     false, true,  true, false, 1,  RELAY_NORMAL, 14,  15,     1);

      //                      Name     Type             ADS  IO  NULL   VpA   Vin  PeerID
      Module.PeriphSetup(0, "Sensor_1", SENS_TYPE_AMP,  1,    1,   0,  0.066,  0,    0);
      Module.PeriphSetup(1, "Sensor_2", SENS_TYPE_AMP,  1,    2,   0,  0.066,  0,    0);
      Module.PeriphSe_ModuleNametup(2, "Sensor_3", SENS_TYPE_AMP,  1,    3,   0,  0.066,  0,    0);
      Module.PeriphSetup(3, "Sensor_4", SENS_TYPE_AMP,  1,    4,   0,  0.066,  0,    0);
      Module.PeriphSetup(4, "VMon",     SENS_TYPE_VOLT, 0,   39,   0,    0,   200,   0); 
    #endif
    #ifdef MODULE_4A_1V_NOADC   // 4-way Battery-Sensor no ADC and VMon ##############################################################
      #define SWITCHES_PER_SCREEN 4

      //                Name        Type         Version  Address   sleep  debug  demo  pair  vMon RelayType    adc1 adc2 voltagedevier 
      Module.Setup(_ModuleName, BATTERY_SENSOR, _Version, NULL,     false, true,  true, false, 1,  RELAY_NORMAL, -1,  -1,     1.5);

      //                      Name     Type             ADS  IO  NULL   VpA   Vin  PeerID
      Module.PeriphSetup(0, "Amp 1",  SENS_TYPE_AMP,     0,  25,   0,    0,    0,    0);
      Module.PeriphSetup(1, "Amp 2",  SENS_TYPE_AMP,     0,  26,   0,    0,    0,    0);
      Module.PeriphSetup(2, "Amp 3",  SENS_TYPE_AMP,     0,  32,   0,    0,    0,    0);
      Module.PeriphSetup(3, "Amp 4",  SENS_TYPE_AMP,     0,  33,   0,    0,    0,    0);
      Module.PeriphSetup(4, "V-Sens", SENS_TYPE_VOLT,    0,  39,   0,    0,   200,   0); 
    #endif
    #ifdef MODULE_8266_4S_NO_PORT_NO_ADC   // 4-way Battery-Sensor no ADC and VMon ##############################################################
      #define SWITCHES_PER_SCREEN 4
       Serial.println("vor Module.Setup");
      Module.Setup(_ModuleName, SWITCH_4_WAY, _Version, NULL,     false, true,  false, false, -1,  RELAY_NORMAL, -1,  -1,     1);
        Serial.println("nach Module.Setup");
      //                      Name     Type             ADS     IO  NULL   VpA   Vin  PeerID
      Module.PeriphSetup(0, "Rel_1", SENS_TYPE_SWITCH,  false,  04,   0,    0,    0,    0);
      Module.PeriphSetup(1, "Rel_2", SENS_TYPE_SWITCH,  false,  14,   0,    0,    0,    0);
      Module.PeriphSetup(2, "Rel_3", SENS_TYPE_SWITCH,  false,  12,   0,    0,    0,    0);
      Module.PeriphSetup(3, "Rel_4", SENS_TYPE_SWITCH,  false,  13,   0,    0,    0,    0);
    #endif
    #ifdef MODULE_2A_2S_1V_NOADC   // 4-way Battery-Sensor no ADC and VMon ##############################################################
      #define SWITCHES_PER_SCREEN 2

      //                Name        Type         Version  Address   sleep  debug  demo  pair  vMon RelayType    adc1 adc2 voltagedevier 
      Module.Setup(_ModuleName, PDC_SENSOR_MIX, _Version, NULL,     false, true,  true, false, 1,  RELAY_NORMAL, -1,  -1,     1.5);

      //                      Name     Type             ADS  IO  NULL   VpA   Vin  PeerID
      Module.PeriphSetup(0, "Amp 1",  SENS_TYPE_AMP,     0,  25,   0,    0,    0,    0);
      Module.PeriphSetup(1, "Amp 2",  SENS_TYPE_AMP,     0,  26,   0,    0,    0,    0);
      Module.PeriphSetup(2, "Sw 1",   SENS_TYPE_SWITCH,  0,  32,   0,    0,    0,    0);
      Module.PeriphSetup(3, "Sw 2 ",  SENS_TYPE_SWITCH,  0,  33,   0,    0,    0,    0);
      Module.PeriphSetup(4, "V-Sens", SENS_TYPE_VOLT,    0,  39,   0,    0,   200,   0); 
    #endif

    for (int SNr=0; SNr<MAX_PERIPHERALS; SNr++)
    {
        if (Module.isPeriphSensor(SNr)) 
        {
            SensorList.add(Module.GetPeriphPtr(SNr));
            PeriphList.add(Module.GetPeriphPtr(SNr));
        }
        else if (Module.isPeriphSwitch(SNr)) 
        {
            SwitchList.add(Module.GetPeriphPtr(SNr));
            PeriphList.add(Module.GetPeriphPtr(SNr));
        }
    }
}
*/
