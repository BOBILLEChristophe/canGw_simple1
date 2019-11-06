/*
   Config.h

*/


#ifndef __config_H__
#define __config_H__


#define DEBUG                       


// Selection des redirections souhaitees
#define SEND_TO_SERIAL              false           
#define SEND_TO_CAN                 false
#define SEND_TO_TCP                 false

#define RECEIVE_FROM_SERIAL         false           
#define RECEIVE_FROM_CAN            true
#define RECEIVE_FROM_TCP            false


// WIFI
#define WIFI_SSID                "Freebox-750000"
#define WIFI_PSW                 "FLAVY24175"

#define MDNS_NAME                "cangw"

#define OTAName                  "cangw"           
#define OTAPassword              "FLAVY24175"

#define TPC_PORT                  12560


// SERIAL
#define dbg_output                Serial1
#define SERIAL_BAUDRATE           115200
#define DBG_RX_PIN_ID             GPIO_NUM_15                 // GPIO15
#define DBG_TX_PIN_ID             GPIO_NUM_2                  // GPIO2

// CAN
#define CAN_TX_PIN_ID             GPIO_NUM_5                  // GPI05
#define CAN_RX_PIN_ID             GPIO_NUM_4                  // GPI04
#define CAN_BAUDRATE              CAN_SPEED_500KBPS



#endif
