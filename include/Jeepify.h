#ifndef JEEPIFY_H
#define JEEPIFY_H
#include <Arduino.h>

#define SEND_CMD_STAY_ALIVE        1
#define SEND_CMD_SLEEPMODE_ON      2
#define SEND_CMD_SLEEPMODE_OFF     3
#define SEND_CMD_SLEEPMODE_TOGGLE  4
#define SEND_CMD_DEBUGMODE_ON      5
#define SEND_CMD_DEBUGMODE_OFF     6
#define SEND_CMD_DEBUGMODE_TOGGLE  7
#define SEND_CMD_DEMOMODE_ON       8
#define SEND_CMD_DEMOMODE_OFF      9
#define SEND_CMD_DEMOMODE_TOGGLE  10
#define SEND_CMD_PAIRMODE_ON      11
#define SEND_CMD_PAIRMODE_OFF     12
#define SEND_CMD_PAIRMODE_TOGGLE  13
#define SEND_CMD_SWITCH_ON        14
#define SEND_CMD_SWITCH_OFF       15
#define SEND_CMD_SWITCH_TOGGLE    16
#define SEND_CMD_CURRENT_CALIB    30
#define SEND_CMD_VOLTAGE_CALIB    31
#define SEND_CMD_UPDATE_NAME      40
#define SEND_CMD_RESET            50
#define SEND_CMD_RESTART          51


#define MAX_PERIPHERALS 5
#define MAX_PEERS       10
#define MAX_STATUS      10
#define SCHWELLE        0.0005

#define MSG_CHANGED_SWITCH     10 // Payload PeriphId
#define MSG_CHANGED_SENSOR     20 // Payload PeriphId
#define MSG_CHANGED_PEERNAME   30 // Payload PeerID
#define MSG_CHANGED_AVAIL      40 // Payload PeerId

// Module-Types
#define SWITCH_1_WAY        1
#define SWITCH_2_WAY        2
#define SWITCH_4_WAY        4
#define SWITCH_8_WAY        8
#define PDC                 9
#define PDC_SENSOR_MIX      10
#define BATTERY_SENSOR      20
#define MONITOR_ROUND       30
#define MONITOR_BIG         31
#define MODULE_ALL          99
#define RELAY_REVERSED      -1
#define RELAY_NORMAL        1

// Sensor-Types
#define SENS_TYPE_SWITCH  101
#define SENS_TYPE_AMP     102
#define SENS_TYPE_VOLT    103
#define SENS_TYPE_SENS    104
#define SENS_TYPE_EQUAL   105
#define SENS_TYPE_ALL     106
#define NOT_FOUND         199

// Intervals
#define MSGLIGHT_INTERVAL 300
#define PING_INTERVAL     1000
#define MSG_INTERVAL      1000
#define LOGO_INTERVAL     3000
#define OFFLINE_INTERVAL  20000
#define PAIR_INTERVAL     30000
#define SLEEP_INTERVAL    5000

// Round-Monitor Touch
const int I2C_SDA  = 4;
const int I2C_SCL  = 5;
const int TP_INT   = 0;
const int TP_RST   = 1;
const int Rotation = 0;

// ESP32-3248S035 Touch
#define TOUCH_SDA  33
#define TOUCH_SCL  32
#define TOUCH_INT  21
#define TOUCH_RST 25
#define TOUCH_WIDTH  480
#define TOUCH_HEIGHT 320

#define MULTI_SCREENS 4
#define MULTI_SCREEN_ROWS 2
#define MULTI_SCREEN_COLS 2
#define PERIPH_PER_SCREEN 4

extern uint8_t broadcastAddressAll[6];
#endif