/**
 * Author GTIS69
 *
 */
 
#include <Arduino.h>
#include "Api.h"

int intChecksum;
char chrChecksumLinky;
String Ligne_Lu;
String Etiquette;
String Donnee;
String strHoro;

String strMqtt[3][94];
String strMemDonnee[94];

uint32_t tpsDernier;
uint32_t tpsPeriodeRaf;

void setup() {  
  Serial.begin(9600);  
  Serial.print("start...");
  Api_setup();
}

void loop() {
  int numUnread = Serial.available();
  
  Api_loop();
  
  if (numUnread > 0) {
    int intCaractere_Lu = Serial.read() & 0x7F;
    char chrCaractere_Lu = (char)intCaractere_Lu;
    
    if (intCaractere_Lu == 0x0A) { // Caractere de debut de ligne
      intChecksum = 0;
      Ligne_Lu = "";
      Etiquette = "";
      Donnee = "";
    }
    else if (intCaractere_Lu == 0x0D) { // Caractere de fin de ligne
      
      // calcul du checksum
      chrChecksumLinky = Ligne_Lu.charAt(Ligne_Lu.length() - 1);
      for(int i=0; i<Ligne_Lu.length() - 1; i++){
        intChecksum += Ligne_Lu.charAt(i);
      }
      
      intChecksum = (intChecksum & 0x3F) + 0x20;
      
      if ((char)intChecksum == chrChecksumLinky) {
        Etiquette = Ligne_Lu.substring(0, Ligne_Lu.indexOf(0x09));
        Ligne_Lu = Ligne_Lu.substring(Ligne_Lu.indexOf(0x09) + 1);
        Donnee = Ligne_Lu.substring(0, Ligne_Lu.indexOf(0x09));
        
        if (Etiquette == "ADSC") {
          strMqtt[0][0] = "1";
          strMqtt[1][0] = "Linky/ADSC/Value";
          strMqtt[2][0] = Donnee;
          
        }
        else if (Etiquette == "VTIC") {
          strMqtt[0][1] = "1";
          strMqtt[1][1] = "Linky/VTIC/Value";
          strMqtt[2][1] = Donnee;
        }
        else if (Etiquette == "DATE") {
          strMqtt[0][2] = "1";
          strMqtt[1][2] = "Linky/DATE/Value";
          strMqtt[2][2] = "20" + Donnee.substring(1, 3) + "-" + Donnee.substring(3, 5) + "-" + Donnee.substring(5, 7) + "T" + Donnee.substring(7, 9) + ":" + Donnee.substring(9, 11) + ":" + Donnee.substring(11, 13) + ".000Z";
        }
        else if (Etiquette == "NGTF") {
          strMqtt[0][3] = "1";
          strMqtt[1][3] = "Linky/NGTF/Value";
          strMqtt[2][3] = Donnee;
        }
        else if (Etiquette == "LTARF") {
          strMqtt[0][4] = "1";
          strMqtt[1][4] = "Linky/LTARF/Value";
          strMqtt[2][4] = Donnee;
        }
        else if (Etiquette == "EAST") {
          strMqtt[0][5] = "1";
          strMqtt[1][5] = "Linky/EAST/Value";
          strMqtt[2][5] = Donnee;
        }
        else if (Etiquette == "EASF01") {
          strMqtt[0][6] = "1";
          strMqtt[1][6] = "Linky/EASF01/Value";
          strMqtt[2][6] = Donnee;
        }
        else if (Etiquette == "EASF02") {
          strMqtt[0][7] = "1";
          strMqtt[1][7] = "Linky/EASF02/Value";
          strMqtt[2][7] = Donnee;
        }
        else if (Etiquette == "EASF03") {
          strMqtt[0][8] = "1";
          strMqtt[1][8] = "Linky/EASF03/Value";
          strMqtt[2][8] = Donnee;
        }
        else if (Etiquette == "EASF04") {
          strMqtt[0][9] = "1";
          strMqtt[1][9] = "Linky/EASF04/Value";
          strMqtt[2][9] = Donnee;
        }
        else if (Etiquette == "EASF05") {
          strMqtt[0][10] = "1";
          strMqtt[1][10] = "Linky/EASF05/Value";
          strMqtt[2][10] = Donnee;
        }
        else if (Etiquette == "EASF06") {
          strMqtt[0][11] = "1";
          strMqtt[1][11] = "Linky/EASF06/Value";
          strMqtt[2][11] = Donnee;
        }
        else if (Etiquette == "EASF07") {
          strMqtt[0][12] = "1";
          strMqtt[1][12] = "Linky/EASF07/Value";
          strMqtt[2][12] = Donnee;
        }
        else if (Etiquette == "EASF08") {
          strMqtt[0][13] = "1";
          strMqtt[1][13] = "Linky/EASF08/Value";
          strMqtt[2][13] = Donnee;
        }
        else if (Etiquette == "EASF09") {
          strMqtt[0][14] = "1";
          strMqtt[1][14] = "Linky/EASF09/Value";
          strMqtt[2][14] = Donnee;
        }
        else if (Etiquette == "EASF10") {
          strMqtt[0][15] = "1";
          strMqtt[1][15] = "Linky/EASF10/Value";
          strMqtt[2][15] = Donnee;
        }
        else if (Etiquette == "EASD01") {
          strMqtt[0][16] = "1";
          strMqtt[1][16] = "Linky/EASD01/Value";
          strMqtt[2][16] = Donnee;
        }
        else if (Etiquette == "EASD02") {
          strMqtt[0][17] = "1";
          strMqtt[1][17] = "Linky/EASD02/Value";
          strMqtt[2][17] = Donnee;
        }
        else if (Etiquette == "EASD03") {
          strMqtt[0][18] = "1";
          strMqtt[1][18] = "Linky/EASD03/Value";
          strMqtt[2][18] = Donnee;
        }
        else if (Etiquette == "EASD04") {
          strMqtt[0][19] = "1";
          strMqtt[1][19] = "Linky/EASD04/Value";
          strMqtt[2][19] = Donnee;
        }
        else if (Etiquette == "EAIT") {
          strMqtt[0][20] = "1";
          strMqtt[1][20] = "Linky/EAIT/Value";
          strMqtt[2][20] = Donnee;
        }
        else if (Etiquette == "ERQ1") {
          strMqtt[0][21] = "1";
          strMqtt[1][21] = "Linky/ERQ1/Value";
          strMqtt[2][21] = Donnee;
        }
        else if (Etiquette == "ERQ2") {
          strMqtt[0][22] = "1";
          strMqtt[1][22] = "Linky/ERQ2/Value";
          strMqtt[2][22] = Donnee;
        }
        else if (Etiquette == "ERQ3") {
          strMqtt[0][23] = "1";
          strMqtt[1][23] = "Linky/ERQ3/Value";
          strMqtt[2][23] = Donnee;
        }
        else if (Etiquette == "ERQ4") {
          strMqtt[0][24] = "1";
          strMqtt[1][24] = "Linky/ERQ4/Value";
          strMqtt[2][24] = Donnee;
        }
        else if (Etiquette == "IRMS1") {
          strMqtt[0][25] = "1";
          strMqtt[1][25] = "Linky/IRMS1/Value";
          strMqtt[2][25] = Donnee;
        }
        else if (Etiquette == "IRMS2") {
          strMqtt[0][26] = "1";
          strMqtt[1][26] = "Linky/IRMS2/Value";
          strMqtt[2][26] = Donnee;
        }
        else if (Etiquette == "IRMS3") {
          strMqtt[0][27] = "1";
          strMqtt[1][27] = "Linky/IRMS3/Value";
          strMqtt[2][27] = Donnee;
        }
        else if (Etiquette == "URMS1") {
          strMqtt[0][28] = "1";
          strMqtt[1][28] = "Linky/URMS1/Value";
          strMqtt[2][28] = Donnee;
        }
        else if (Etiquette == "URMS2") {
          strMqtt[0][29] = "1";
          strMqtt[1][29] = "Linky/URMS2/Value";
          strMqtt[2][29] = Donnee;
        }
        else if (Etiquette == "URMS3") {
          strMqtt[0][30] = "1";
          strMqtt[1][30] = "Linky/URMS3/Value";
          strMqtt[2][30] = Donnee;
        }
        else if (Etiquette == "PREF") {
          strMqtt[0][31] = "1";
          strMqtt[1][31] = "Linky/PREF/Value";
          strMqtt[2][31] = Donnee;
        }
        else if (Etiquette == "PCOUP") {
          strMqtt[0][32] = "1";
          strMqtt[1][32] = "Linky/PCOUP/Value";
          strMqtt[2][32] = Donnee;
        }
        else if (Etiquette == "SINSTS") {
          strMqtt[0][33] = "1";
          strMqtt[1][33] = "Linky/SINSTS/Value";
          strMqtt[2][33] = Donnee;
        }
        else if (Etiquette == "SINSTS1") {
          strMqtt[0][34] = "1";
          strMqtt[1][34] = "Linky/SINSTS1/Value";
          strMqtt[2][34] = Donnee;
        }
        else if (Etiquette == "SINSTS2") {
          strMqtt[0][35] = "1";
          strMqtt[1][35] = "Linky/SINSTS2/Value";
          strMqtt[2][35] = Donnee;
        }
        else if (Etiquette == "SINSTS3") {
          strMqtt[0][36] = "1";
          strMqtt[1][36] = "Linky/SINSTS3/Value";
          strMqtt[2][36] = Donnee;
        }
        else if (Etiquette == "SMAXSN") {
          strHoro = "20" + Donnee.substring(1, 3) + "-" + Donnee.substring(3, 5) + "-" + Donnee.substring(5, 7) + "T" + Donnee.substring(7, 9) + ":" + Donnee.substring(9, 11) + ":" + Donnee.substring(11, 13) + ".000Z";
          Ligne_Lu = Ligne_Lu.substring(Ligne_Lu.indexOf(0x09) + 1);
          Donnee = Ligne_Lu.substring(0, Ligne_Lu.indexOf(0x09));

          strMqtt[0][37] = "1";
          strMqtt[1][37] = "Linky/SMAXSN/Value";
          strMqtt[2][37] = Donnee;
          
          strMqtt[0][38] = "1";
          strMqtt[1][38] = "Linky/SMAXSN/Horo";
          strMqtt[2][38] = strHoro;
        }
        else if (Etiquette == "SMAXSN1") {
          strHoro = "20" + Donnee.substring(1, 3) + "-" + Donnee.substring(3, 5) + "-" + Donnee.substring(5, 7) + "T" + Donnee.substring(7, 9) + ":" + Donnee.substring(9, 11) + ":" + Donnee.substring(11, 13) + ".000Z";
          Ligne_Lu = Ligne_Lu.substring(Ligne_Lu.indexOf(0x09) + 1);
          Donnee = Ligne_Lu.substring(0, Ligne_Lu.indexOf(0x09));

          strMqtt[0][39] = "1";
          strMqtt[1][39] = "Linky/SMAXSN1/Value";
          strMqtt[2][39] = Donnee;
          
          strMqtt[0][40] = "1";
          strMqtt[1][40] = "Linky/SMAXSN1/Horo";
          strMqtt[2][40] = strHoro;
        }
        else if (Etiquette == "SMAXSN2") {
          strHoro = "20" + Donnee.substring(1, 3) + "-" + Donnee.substring(3, 5) + "-" + Donnee.substring(5, 7) + "T" + Donnee.substring(7, 9) + ":" + Donnee.substring(9, 11) + ":" + Donnee.substring(11, 13) + ".000Z";
          Ligne_Lu = Ligne_Lu.substring(Ligne_Lu.indexOf(0x09) + 1);
          Donnee = Ligne_Lu.substring(0, Ligne_Lu.indexOf(0x09));

          strMqtt[0][41] = "1";
          strMqtt[1][41] = "Linky/SMAXSN2/Value";
          strMqtt[2][41] = Donnee;
          
          strMqtt[0][42] = "1";
          strMqtt[1][42] = "Linky/SMAXSN2/Horo";
          strMqtt[2][42] = strHoro;
        }
        else if (Etiquette == "SMAXSN3") {
          strHoro = "20" + Donnee.substring(1, 3) + "-" + Donnee.substring(3, 5) + "-" + Donnee.substring(5, 7) + "T" + Donnee.substring(7, 9) + ":" + Donnee.substring(9, 11) + ":" + Donnee.substring(11, 13) + ".000Z";
          Ligne_Lu = Ligne_Lu.substring(Ligne_Lu.indexOf(0x09) + 1);
          Donnee = Ligne_Lu.substring(0, Ligne_Lu.indexOf(0x09));

          strMqtt[0][43] = "1";
          strMqtt[1][43] = "Linky/SMAXSN3/Value";
          strMqtt[2][43] = Donnee;
          
          strMqtt[0][44] = "1";
          strMqtt[1][44] = "Linky/SMAXSN3/Horo";
          strMqtt[2][44] = strHoro;
        }
        else if (Etiquette == "SMAXSN-1") {
          strHoro = "20" + Donnee.substring(1, 3) + "-" + Donnee.substring(3, 5) + "-" + Donnee.substring(5, 7) + "T" + Donnee.substring(7, 9) + ":" + Donnee.substring(9, 11) + ":" + Donnee.substring(11, 13) + ".000Z";
          Ligne_Lu = Ligne_Lu.substring(Ligne_Lu.indexOf(0x09) + 1);
          Donnee = Ligne_Lu.substring(0, Ligne_Lu.indexOf(0x09));
          
          strMqtt[0][45] = "1";
          strMqtt[1][45] = "Linky/SMAXSN-1/Value";
          strMqtt[2][45] = Donnee;
          
          strMqtt[0][46] = "1";
          strMqtt[1][46] = "Linky/SMAXSN-1/Horo";
          strMqtt[2][46] = strHoro;
        }
        else if (Etiquette == "SMAXSN1-1") {
          strHoro = "20" + Donnee.substring(1, 3) + "-" + Donnee.substring(3, 5) + "-" + Donnee.substring(5, 7) + "T" + Donnee.substring(7, 9) + ":" + Donnee.substring(9, 11) + ":" + Donnee.substring(11, 13) + ".000Z";
          Ligne_Lu = Ligne_Lu.substring(Ligne_Lu.indexOf(0x09) + 1);
          Donnee = Ligne_Lu.substring(0, Ligne_Lu.indexOf(0x09));
          
          strMqtt[0][47] = "1";
          strMqtt[1][47] = "Linky/SMAXSN1-1/Value";
          strMqtt[2][47] = Donnee;
          
          strMqtt[0][48] = "1";
          strMqtt[1][48] = "Linky/SMAXSN1-1/Horo";
          strMqtt[2][48] = strHoro;
        }
        else if (Etiquette == "SMAXSN2-1") {
          strHoro = "20" + Donnee.substring(1, 3) + "-" + Donnee.substring(3, 5) + "-" + Donnee.substring(5, 7) + "T" + Donnee.substring(7, 9) + ":" + Donnee.substring(9, 11) + ":" + Donnee.substring(11, 13) + ".000Z";
          Ligne_Lu = Ligne_Lu.substring(Ligne_Lu.indexOf(0x09) + 1);
          Donnee = Ligne_Lu.substring(0, Ligne_Lu.indexOf(0x09));
          
          strMqtt[0][49] = "1";
          strMqtt[1][49] = "Linky/SMAXSN2-1/Value";
          strMqtt[2][49] = Donnee;
          
          strMqtt[0][50] = "1";
          strMqtt[1][50] = "Linky/SMAXSN2-1/Horo";
          strMqtt[2][50] = strHoro;
        }
        else if (Etiquette == "SMAXSN3-1") {
          strHoro = "20" + Donnee.substring(1, 3) + "-" + Donnee.substring(3, 5) + "-" + Donnee.substring(5, 7) + "T" + Donnee.substring(7, 9) + ":" + Donnee.substring(9, 11) + ":" + Donnee.substring(11, 13) + ".000Z";
          Ligne_Lu = Ligne_Lu.substring(Ligne_Lu.indexOf(0x09) + 1);
          Donnee = Ligne_Lu.substring(0, Ligne_Lu.indexOf(0x09));
          
          strMqtt[0][51] = "1";
          strMqtt[1][51] = "Linky/SMAXSN3-1/Value";
          strMqtt[2][51] = Donnee;
          
          strMqtt[0][52] = "1";
          strMqtt[1][52] = "Linky/SMAXSN3-1/Horo";
          strMqtt[2][52] = strHoro;
        }
        else if (Etiquette == "SINSTI") {
          strMqtt[0][53] = "1";
          strMqtt[1][53] = "Linky/SINSTI/Value";
          strMqtt[2][53] = Donnee;
        }
        else if (Etiquette == "SMAXIN") {
          strHoro = "20" + Donnee.substring(1, 3) + "-" + Donnee.substring(3, 5) + "-" + Donnee.substring(5, 7) + "T" + Donnee.substring(7, 9) + ":" + Donnee.substring(9, 11) + ":" + Donnee.substring(11, 13) + ".000Z";
          Ligne_Lu = Ligne_Lu.substring(Ligne_Lu.indexOf(0x09) + 1);
          Donnee = Ligne_Lu.substring(0, Ligne_Lu.indexOf(0x09));
          
          strMqtt[0][54] = "1";
          strMqtt[1][54] = "Linky/SMAXIN/Value";
          strMqtt[2][54] = Donnee;
          
          strMqtt[0][55] = "1";
          strMqtt[1][55] = "Linky/SMAXIN/Horo";
          strMqtt[2][55] = strHoro;
        }
        else if (Etiquette == "SMAXIN-1") {
          strHoro = "20" + Donnee.substring(1, 3) + "-" + Donnee.substring(3, 5) + "-" + Donnee.substring(5, 7) + "T" + Donnee.substring(7, 9) + ":" + Donnee.substring(9, 11) + ":" + Donnee.substring(11, 13) + ".000Z";
          Ligne_Lu = Ligne_Lu.substring(Ligne_Lu.indexOf(0x09) + 1);
          Donnee = Ligne_Lu.substring(0, Ligne_Lu.indexOf(0x09));
          
          strMqtt[0][56] = "1";
          strMqtt[1][56] = "Linky/SMAXIN-1/Value";
          strMqtt[2][56] = Donnee;
          
          strMqtt[0][57] = "1";
          strMqtt[1][57] = "Linky/SMAXIN-1/Horo";
          strMqtt[2][57] = strHoro;
        }
        else if (Etiquette == "CCASN") {
          strHoro = "20" + Donnee.substring(1, 3) + "-" + Donnee.substring(3, 5) + "-" + Donnee.substring(5, 7) + "T" + Donnee.substring(7, 9) + ":" + Donnee.substring(9, 11) + ":" + Donnee.substring(11, 13) + ".000Z";
          Ligne_Lu = Ligne_Lu.substring(Ligne_Lu.indexOf(0x09) + 1);
          Donnee = Ligne_Lu.substring(0, Ligne_Lu.indexOf(0x09));
          
          strMqtt[0][58] = "1";
          strMqtt[1][58] = "Linky/CCASN/Value";
          strMqtt[2][58] = Donnee;
          
          strMqtt[0][59] = "1";
          strMqtt[1][59] = "Linky/CCASN/Horo";
          strMqtt[2][59] = strHoro;
        }
        else if (Etiquette == "CCASN-1") {
          strHoro = "20" + Donnee.substring(1, 3) + "-" + Donnee.substring(3, 5) + "-" + Donnee.substring(5, 7) + "T" + Donnee.substring(7, 9) + ":" + Donnee.substring(9, 11) + ":" + Donnee.substring(11, 13) + ".000Z";
          Ligne_Lu = Ligne_Lu.substring(Ligne_Lu.indexOf(0x09) + 1);
          Donnee = Ligne_Lu.substring(0, Ligne_Lu.indexOf(0x09));
          
          strMqtt[0][60] = "1";
          strMqtt[1][60] = "Linky/CCASN-1/Value";
          strMqtt[2][60] = Donnee;
          
          strMqtt[0][61] = "1";
          strMqtt[1][61] = "Linky/CCASN-1/Horo";
          strMqtt[2][61] = strHoro;
        }
        else if (Etiquette == "CCAIN") {
          strHoro = "20" + Donnee.substring(1, 3) + "-" + Donnee.substring(3, 5) + "-" + Donnee.substring(5, 7) + "T" + Donnee.substring(7, 9) + ":" + Donnee.substring(9, 11) + ":" + Donnee.substring(11, 13) + ".000Z";
          Ligne_Lu = Ligne_Lu.substring(Ligne_Lu.indexOf(0x09) + 1);
          Donnee = Ligne_Lu.substring(0, Ligne_Lu.indexOf(0x09));
          
          strMqtt[0][62] = "1";
          strMqtt[1][62] = "Linky/CCAIN/Value";
          strMqtt[2][62] = Donnee;
          
          strMqtt[0][63] = "1";
          strMqtt[1][63] = "Linky/CCAIN/Horo";
          strMqtt[2][63] = strHoro;
        }
        else if (Etiquette == "CCAIN-1") {
          strHoro = "20" + Donnee.substring(1, 3) + "-" + Donnee.substring(3, 5) + "-" + Donnee.substring(5, 7) + "T" + Donnee.substring(7, 9) + ":" + Donnee.substring(9, 11) + ":" + Donnee.substring(11, 13) + ".000Z";
          Ligne_Lu = Ligne_Lu.substring(Ligne_Lu.indexOf(0x09) + 1);
          Donnee = Ligne_Lu.substring(0, Ligne_Lu.indexOf(0x09));
          
          strMqtt[0][64] = "1";
          strMqtt[1][64] = "Linky/CCAIN-1/Value";
          strMqtt[2][64] = Donnee;
          
          strMqtt[0][65] = "1";
          strMqtt[1][65] = "Linky/CCAIN-1/Horo";
          strMqtt[2][65] = strHoro;
        }
        else if (Etiquette == "UMOY1") {
          strHoro = "20" + Donnee.substring(1, 3) + "-" + Donnee.substring(3, 5) + "-" + Donnee.substring(5, 7) + "T" + Donnee.substring(7, 9) + ":" + Donnee.substring(9, 11) + ":" + Donnee.substring(11, 13) + ".000Z";
          Ligne_Lu = Ligne_Lu.substring(Ligne_Lu.indexOf(0x09) + 1);
          Donnee = Ligne_Lu.substring(0, Ligne_Lu.indexOf(0x09));
          
          strMqtt[0][66] = "1";
          strMqtt[1][66] = "Linky/UMOY1/Value";
          strMqtt[2][66] = Donnee;
          
          strMqtt[0][67] = "1";
          strMqtt[1][67] = "Linky/UMOY1/Horo";
          strMqtt[2][67] = strHoro;
        }
        else if (Etiquette == "UMOY2") {
          strHoro = "20" + Donnee.substring(1, 3) + "-" + Donnee.substring(3, 5) + "-" + Donnee.substring(5, 7) + "T" + Donnee.substring(7, 9) + ":" + Donnee.substring(9, 11) + ":" + Donnee.substring(11, 13) + ".000Z";
          Ligne_Lu = Ligne_Lu.substring(Ligne_Lu.indexOf(0x09) + 1);
          Donnee = Ligne_Lu.substring(0, Ligne_Lu.indexOf(0x09));
          
          strMqtt[0][68] = "1";
          strMqtt[0][68] = "Linky/UMOY2/Value";
          strMqtt[2][68] = Donnee;
          
          strMqtt[0][69] = "1";
          strMqtt[1][69] = "Linky/UMOY2/Horo";
          strMqtt[2][69] = strHoro;
        }
        else if (Etiquette == "UMOY3") {
          strHoro = "20" + Donnee.substring(1, 3) + "-" + Donnee.substring(3, 5) + "-" + Donnee.substring(5, 7) + "T" + Donnee.substring(7, 9) + ":" + Donnee.substring(9, 11) + ":" + Donnee.substring(11, 13) + ".000Z";
          Ligne_Lu = Ligne_Lu.substring(Ligne_Lu.indexOf(0x09) + 1);
          Donnee = Ligne_Lu.substring(0, Ligne_Lu.indexOf(0x09));
          
          strMqtt[0][70] = "1";
          strMqtt[1][70] = "Linky/UMOY3/Value";
          strMqtt[2][70] = Donnee;
          
          strMqtt[0][71] = "1";
          strMqtt[1][71] = "Linky/UMOY3/Horo";
          strMqtt[2][71] = strHoro;
        }
        else if (Etiquette == "STGE") {
          strMqtt[0][72] = "1";
          strMqtt[1][72] = "Linky/STGE/Value";
          strMqtt[2][72] = Donnee;
        }
        else if (Etiquette == "DPM1") {
          strHoro = "20" + Donnee.substring(1, 3) + "-" + Donnee.substring(3, 5) + "-" + Donnee.substring(5, 7) + "T" + Donnee.substring(7, 9) + ":" + Donnee.substring(9, 11) + ":" + Donnee.substring(11, 13) + ".000Z";
          Ligne_Lu = Ligne_Lu.substring(Ligne_Lu.indexOf(0x09) + 1);
          Donnee = Ligne_Lu.substring(0, Ligne_Lu.indexOf(0x09));
          
          strMqtt[0][73] = "1";
          strMqtt[1][73] = "Linky/DPM1/Value";
          strMqtt[2][73] = Donnee;
          
          strMqtt[0][74] = "1";
          strMqtt[1][74] = "Linky/DPM1/Horo";
          strMqtt[2][74] = strHoro;
        }
        else if (Etiquette == "FPM1") {
          strHoro = "20" + Donnee.substring(1, 3) + "-" + Donnee.substring(3, 5) + "-" + Donnee.substring(5, 7) + "T" + Donnee.substring(7, 9) + ":" + Donnee.substring(9, 11) + ":" + Donnee.substring(11, 13) + ".000Z";
          Ligne_Lu = Ligne_Lu.substring(Ligne_Lu.indexOf(0x09) + 1);
          Donnee = Ligne_Lu.substring(0, Ligne_Lu.indexOf(0x09));
          
          strMqtt[0][75] = "1";
          strMqtt[1][75] = "Linky/FPM1/Value";
          strMqtt[2][75] = Donnee;
          
          strMqtt[0][76] = "1";
          strMqtt[1][76] = "Linky/FPM1/Horo";
          strMqtt[2][76] = strHoro;
        }
        else if (Etiquette == "DPM2") {
          strHoro = "20" + Donnee.substring(1, 3) + "-" + Donnee.substring(3, 5) + "-" + Donnee.substring(5, 7) + "T" + Donnee.substring(7, 9) + ":" + Donnee.substring(9, 11) + ":" + Donnee.substring(11, 13) + ".000Z";
          Ligne_Lu = Ligne_Lu.substring(Ligne_Lu.indexOf(0x09) + 1);
          Donnee = Ligne_Lu.substring(0, Ligne_Lu.indexOf(0x09));
          
          strMqtt[0][77] = "1";
          strMqtt[1][77] = "Linky/DPM2/Value";
          strMqtt[2][77] = Donnee;
          
          strMqtt[0][78] = "1";
          strMqtt[1][78] = "Linky/DPM2/Horo";
          strMqtt[2][78] = strHoro;
        }
        else if (Etiquette == "FPM2") {
          strHoro = "20" + Donnee.substring(1, 3) + "-" + Donnee.substring(3, 5) + "-" + Donnee.substring(5, 7) + "T" + Donnee.substring(7, 9) + ":" + Donnee.substring(9, 11) + ":" + Donnee.substring(11, 13) + ".000Z";
          Ligne_Lu = Ligne_Lu.substring(Ligne_Lu.indexOf(0x09) + 1);
          Donnee = Ligne_Lu.substring(0, Ligne_Lu.indexOf(0x09));
          
          strMqtt[0][79] = "1";
          strMqtt[1][79] = "Linky/FPM2/Value";
          strMqtt[2][79] = Donnee;
          
          strMqtt[0][80] = "1";
          strMqtt[1][80] = "Linky/FPM2/Horo";
          strMqtt[2][80] = strHoro;
        }
        else if (Etiquette == "DPM3") {
          strHoro = "20" + Donnee.substring(1, 3) + "-" + Donnee.substring(3, 5) + "-" + Donnee.substring(5, 7) + "T" + Donnee.substring(7, 9) + ":" + Donnee.substring(9, 11) + ":" + Donnee.substring(11, 13) + ".000Z";
          Ligne_Lu = Ligne_Lu.substring(Ligne_Lu.indexOf(0x09) + 1);
          Donnee = Ligne_Lu.substring(0, Ligne_Lu.indexOf(0x09));
          
          strMqtt[0][81] = "1";
          strMqtt[1][81] = "Linky/DPM3/Value";
          strMqtt[2][81] = Donnee;
          
          strMqtt[0][82] = "1";
          strMqtt[1][82] = "Linky/DPM3/Horo";
          strMqtt[2][82] = strHoro;
        }
        else if (Etiquette == "FPM3") {
          strHoro = "20" + Donnee.substring(1, 3) + "-" + Donnee.substring(3, 5) + "-" + Donnee.substring(5, 7) + "T" + Donnee.substring(7, 9) + ":" + Donnee.substring(9, 11) + ":" + Donnee.substring(11, 13) + ".000Z";
          Ligne_Lu = Ligne_Lu.substring(Ligne_Lu.indexOf(0x09) + 1);
          Donnee = Ligne_Lu.substring(0, Ligne_Lu.indexOf(0x09));
          
          strMqtt[0][83] = "1";
          strMqtt[1][83] = "Linky/FPM3/Value";
          strMqtt[2][83] = Donnee;
          
          strMqtt[0][84] = "1";
          strMqtt[1][84] = "Linky/FPM3/Horo";
          strMqtt[2][84] = strHoro;
        }
        else if (Etiquette == "MSG1") {
          strMqtt[0][85] = "1";
          strMqtt[1][85] = "Linky/MSG1/Value";
          strMqtt[2][85] = Donnee;
        }
        else if (Etiquette == "MSG2") {
          strMqtt[0][86] = "1";
          strMqtt[1][86] = "Linky/MSG2/Value";
          strMqtt[2][86] = Donnee;
        }
        else if (Etiquette == "PRM") {
          strMqtt[0][87] = "1";
          strMqtt[1][87] = "Linky/PRM/Value";
          strMqtt[2][87] = Donnee;
        }
        else if (Etiquette == "RELAIS") {
          strMqtt[0][88] = "1";
          strMqtt[1][88] = "Linky/RELAIS/Value";
          strMqtt[2][88] = Donnee;
        }
        else if (Etiquette == "NTARF") {
          strMqtt[0][89] = "1";
          strMqtt[1][89] = "Linky/NTARF/Value";
          strMqtt[2][89] = Donnee;
        }
        else if (Etiquette == "NJOURF") {
          strMqtt[0][90] = "1";
          strMqtt[1][90] = "Linky/NJOURF/Value";
          strMqtt[2][90] = Donnee;
        }
        else if (Etiquette == "NJOURF+1") {
          strMqtt[0][91] = "1";
          strMqtt[1][91] = "Linky/NJOURF+1/Value";
          strMqtt[2][91] = Donnee;
        }
        else if (Etiquette == "PPOINTE") {
          strMqtt[0][93] = "1";
          strMqtt[1][93] = "Linky/PPOINTE/Value";
          strMqtt[2][93] = Donnee;
        }
        else if (Etiquette == "PJOURF+1") {
          strMqtt[0][92] = "1";
          strMqtt[1][92] = "Linky/PJOURF+1/Value";
          strMqtt[2][92] = Donnee;

          if (micros() >= (tpsPeriodeRaf + tpsDernier)) {
            for(int i = 0; i < 85 ; i++){
              if (strMqtt[1][i] != "") {
                Api_Send(strMqtt[1][i], strMqtt[2][i]);
                strMemDonnee[i] = strMqtt[2][i];
                strMqtt[0][i] = "0";
              }
            }
          }
          else {
            for(int i = 0; i < 85 ; i++){
              if (strMqtt[0][i] == "1" && strMemDonnee[i] != strMqtt[2][i]) {
                Api_Send(strMqtt[1][i], strMqtt[2][i]);
                strMemDonnee[i] = strMqtt[2][i];
                strMqtt[0][i] = "0";
              }
            }
          }
        }
      }
      else {
      }
        Ligne_Lu = "";
    }
    else {
      Ligne_Lu += chrCaractere_Lu;
    }
  }
}
