#include <Sim800L.h>
#include <SoftwareSerial.h>

#include "RTClib.h"
#include <SPI.h>
#include <MFRC522.h>
#include <LiquidCrystal_I2C.h>


#define RST_PIN         5           // Configurable, see typical pin layout above
#define SS_PIN          53          // Configurable, see typical pin layout above


Sim800L Sim800L;
//*****************************************************************************************//
RTC_DS3231 rtc;
//*****************************************************************************************//
LiquidCrystal_I2C lcd(0x27, 16, 4);
//*****************************************************************************************//
MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance
MFRC522::MIFARE_Key key;
MFRC522::StatusCode status;


//*****************************************************************************************// 
char daysOfTheWeek[7][12] = {"minggu", "Senin", "Selasa", "Rabu", "Kamis", "Jumat", "Sabtu"};
int tahun, bulan, hari, jam, menit, detik = 0;
//*****************************************************************************************//

void setup() {
  Serial.begin(9600);
   Serial.println("LABEL,Date,Time,Nama");
  SPI.begin();     
mfrc522.PCD_Init();                                             
//Serial.println(F("Read personal data on a MIFARE PICC:"));    
//*****************************************************************************************//
lcd.begin();
lcd.backlight();
      DateTime now = rtc.now();
lcd.setCursor(0, 0);hari = now.day();lcd.print(daysOfTheWeek[now.dayOfTheWeek()]); lcd.setCursor(0, 1);hari = now.day();lcd.print(now.day());
      lcd.setCursor(2,1);lcd.print(':');
lcd.setCursor(3, 1);bulan = now.month();lcd.print(bulan,DEC);
      lcd.setCursor(5,1);lcd.print(':');
lcd.setCursor(6, 1);tahun = now.year();lcd.print(tahun,DEC);

Serial.begin(9600);


delay(2000); 
      if (! rtc.begin()) {
        Serial.println("Couldn't find RTC");  
        while (1);
        }
      if (rtc.lostPower()) {
         Serial.println("RTC lost power, lets set the time!"); rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
        }
 //*****************************************************************************************/
 
lcd.clear();

}

void loop() {
   
  DateTime now = rtc.now();
  lcd.setCursor(0,1);
  jam = now.hour();lcd.print(now.hour());
  lcd.setCursor(2,1);
  lcd.print(':');
  lcd.setCursor(3,1);
  menit = now.minute();
  lcd.print(now.minute());
  lcd.setCursor(5,1);
  lcd.print(':');
  lcd.setCursor(6,1);
  detik = now.second();
  lcd.print(now.second());
  lcd.setCursor(0,2);
  lcd.print("Selamat Datang ");
  lcd.setCursor(0,3);
  lcd.print("Absensi Sekolah");
  delay(500);lcd.clear();
//-------------------------------------------
// Prepare key - all keys are set to FFFFFFFFFFFFh at chip delivery from the factory.

for (byte i = 0; i < 6; i++) key.keyByte[i] = 0xFF;
byte block;
byte len;

//-------------------------------------------
// Reset the loop if no new card present on the sensor/reader. This saves the entire process when idle.

if ( ! mfrc522.PICC_IsNewCardPresent()) {
return;
}
// Select one of the cards
if ( ! mfrc522.PICC_ReadCardSerial()) {
return;
}
Serial.println(F("**Card Detected:**"));
byte buffer1[18];
block = 4;
len = 18;
status = mfrc522.PCD_Authenticate(MFRC522::PICC_CMD_MF_AUTH_KEY_A, 4, &key, &(mfrc522.uid));
if (status != MFRC522::STATUS_OK) {
//Serial.print(F("Authentication failed: "));
//Serial.println(mfrc522.GetStatusCodeName(status));
return;
}
status = mfrc522.MIFARE_Read(block, buffer1, &len);
if (status != MFRC522::STATUS_OK) {
//Serial.print(F("Reading failed: "));
//Serial.println(mfrc522.GetStatusCodeName(status));
return;
}
String value = "";
for (uint8_t i = 0; i < 16; i++)
{
value += (char)buffer1[i];
}
value.trim();
//Serial.print(value);
//Serial.println(F("\n**End Reading**\n"));
mfrc522.PICC_HaltA();
mfrc522.PCD_StopCrypto1();



 
    //-------------------------------------------
lcd.setCursor(0,0);lcd.print(value);delay(500);lcd.clear();
//-------------------------------------------
lcd.setCursor(0,0);lcd.print("success");delay(500);lcd.clear();
//-------------------------------------------
 
   Serial.println( (String) "DATA,DATE,TIME," + value + ",AUTOSCROLL_20" );



  
 if(value=="sutran"){
  Serial.println('\1');

    char* text;
    char* number;
    bool sender;
    Sim800L.begin(9600); 
    while(!Serial);
		text="Testing Sms";
		number="082331490525";
		sender=Sim800L.sendSms(number,text);             
    }
	
if(value=="widhi"){
    Serial.println('\0');
    char* text;
    char* number;
    bool sender;
    Sim800L.begin(9600); 
    while(!Serial);
    text="hello world";
    number="083846144706";
    sender=Sim800L.sendSms(number,text);
                  
    }



}
