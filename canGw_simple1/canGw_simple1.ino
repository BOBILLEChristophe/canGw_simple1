/*


    Passerelle Wifi/CAN avec un ESP32 et un module SN65HVD230 CAN Bus Transceiver https://www.ebay.fr/itm/1pcs-SN65HVD230-CAN-bus-transceiver

    Ce projet est une passerelle simple entre un reseau ETHERNET/WiFi et un bus CAN en simplex. Pour les besoins en communication bi-directionnelle,
    une seconde passerelle similaire a celle-ci pourra etre utilisee.

    Christophe BOBILLE sept 2018 - nov 2019
    christophe.bobille@gmail.com

    Les messages echanges sont de type  : unsigned char mInputMsg[]  = "0x25 0 3 0x93 0x00  0x9F";
    ou avec identifiant long : unsigned char mInputMsg[]  = "0xFF00112 1 3 0x93 0x00  0x9F";

    avec des champs d'arbitrage sur 11 ou 29 bits
    le champ de donnees peut varier de 0 (trame de requete) a 8 octets.

    Bibliotheques :
    - <ESP32CAN.h> @ https://github.com/nhatuan84/esp32-can-protocol-demo
*/

#define VERSION  "1.0"
#define PROJECT  "canGw_simple1"

#include <Arduino.h>
#include <HardwareSerial.h>
#include "Config.h"
#include "CanCtrl.h"
#include <WiFi.h>

const char* ssid     = WIFI_SSID;
const char* password = WIFI_PSW;

WiFiServer server(12560);

GW_Can canCtrl;                     // Instance de GW_Can


/*__________________________________________________________SETUP__________________________________________________________*/

void setup() {

  
  // Port serie pour debug
  dbg_output.begin(SERIAL_BAUDRATE, SERIAL_8N1, DBG_RX_PIN_ID, DBG_TX_PIN_ID);

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    dbg_output.print(".");
  }
  server.begin();
  dbg_output.println("");
  dbg_output.println("WiFi connected.");
  dbg_output.println("IP address: ");
  dbg_output.println(WiFi.localIP());

  dbg_output.setDebugOutput(true); // Debug + complet
  // Infos du projet
  dbg_output.print("\n\n\n");
  dbg_output.print("Project :      ");
  dbg_output.print(PROJECT);
  dbg_output.print("\nVersion :      ");
  dbg_output.print(VERSION);
  dbg_output.print("\nCompiled :     ");
  dbg_output.print(__DATE__);
  dbg_output.print(" ");
  dbg_output.print(__TIME__);
  dbg_output.print("\n\n");

  //Bus CAN
  int err = canCtrl.begin();
  switch (err) {
    case 0 :
      dbg_output.print("CAN ok !\n\n");
      break;
    case -1 :
      dbg_output.print("Probleme de connexion CAN !\n");
      dbg_output.print("Programme interrompu.");
      return;
  }
  dbg_output.print("End of setup.\n\n");

} // End setup


/*__________________________________________________________LOOP__________________________________________________________*/

void loop() {

  static int err = 1;

  WiFiClient client = server.available();
  if (client) {
    dbg_output.print("New Client.\n");
    while (client.connected()) {

      //if (RECEIVE_FROM_CAN) { //INCOMING messages sur le bus CAN et envoi sur le port Serial et wifi
      err = canCtrl.msgRx();
      switch (err) {
        case 0 :
          client.print(canCtrl.getInputMsg());
      }
      //} // -> end RECEIVE_FROM_CAN
      delay(1);
    }
  }
} // End loop
