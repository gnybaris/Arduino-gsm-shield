// https://github.com/gnybaris
// IG @gnybaris



#include <GSM.h> // gsm kütüphanesini dahil ediyoruz
#define PINNUMBER "" // Sim kartın pin numarası var ise tırnak içinde ("0000") yazınız. Sim kartın girişinde pin numarası yok ise boş bırakınız.

GSM gsmAccess;
GSM_SMS sms;

boolean halleffect = false;
int led_sure = 0; //ledi yakma suresi icin degisken
unsigned long oncekiZaman = 0; //onceki zamani tuttugumuz degisken

void setup() {
  Serial.begin(9600); // serial bağlantıyı oluşturuyoruz

  while (!Serial) { ; }
  Serial.println("SMS Gondermek Icin Hazirlaniyor..! \nGSM Sinyalleri Aranıyor..!\n"); // Serial port ekranından aşamaları izleyebilmemiz için uyarı metini.
  boolean notConnected = true; // bağlantı kontrolleri
  while (notConnected) {
      if (gsmAccess.begin(PINNUMBER) == GSM_READY) {
           notConnected = false; // bağlantı oluşmazsa
    } 
      else {
    Serial.println("Baglanti Kurulamadi... \nTekran Baglanti Araniyor..!\n"); // Serial port ekranından aşamaları izleyebilmemiz için uyarı metini.
    delay(1000);
    }
    }
  
  Serial.println("GSM Baslatildi. Sistem Sorunsuz Calisiyor. :)"); // Serial port ekranından aşamaları izleyebilmemiz için uyarı metini.

       pinMode(13, OUTPUT);

  sms.beginSMS("+905"); // sms gönderilecek telefon numarasını başında ülke alan kodu olacak şekilde yazınız.
  sms.print("Sistem Acildi \nGSM Sorunsuz Calisiyor :)\n "); // Gönderliecek ilk sms gsm çalıştığını haberini verecektir
  sms.endSMS();
    Serial.println("\nSISTEM MESAJI ATILDI -1\n"); // Serial port ekranından aşamaları izleyebilmemiz için uyarı metini.
    
  // ikinci veya daha fazla telefon numarası eklenebilir ve her telefon için ayrı ayrı metin düzenlenmesi yapılabilir.
//  sms.beginSMS("+905"); // sms gönderilecek telefon numarasını başında ülke alan kodu olacak şekilde yazınız.
//  sms.print("Sistem Acildi \nGSM Sorunsuz Calisiyor :)\n ");// Gönderliecek ilk sms gsm çalıştığını haberini verecektir
//  sms.endSMS();
//  Serial.println("\nSISTEM MESAJI ATILDI -2\n"); // Serial port ekranından aşamaları izleyebilmemiz için uyarı metini. 

}

void loop() {

          //sensor için
      if (digitalRead(4) == HIGH && !halleffect) { 
        led_sure = 1; // ledi 1 saniye yak
        halleffect = true; // basildimi true olsun ki buraya bir daha bakmasin
      }     
      else if (digitalRead(4) == LOW) {
        halleffect = false;
      }
        //sensor için son

      if (millis() - oncekiZaman > 1000) { // su anki zamandan onceki zamani cikardigimizda kalan fark 1000ms ise

      //led için
      if (led_sure > 0) { //ledi yakma suresi 0 dan buyukse bunu buton basildiginda aliyor
        digitalWrite(13, HIGH); //ledi yak
        led_sure--; // her seferinde ledi yakma suresini 1 eksik yapiyoruz
        
        sms.beginSMS("+905"); // sms gönderilecek telefon numarasını başında ülke alan kodu olacak şekilde yazınız.
        sms.print("!! GUVENLIK PROBLEMI !! \nKAPI ACILDI \n \nDIKKAT !!\n "); // uyarı sms metini 
        sms.endSMS();
        Serial.println("\nMANYETİK ALAN DİSİ - ISLEM BASARILI!-1\n"); // Serial port ekranından aşamaları izleyebilmemiz için uyarı metini. 

//        sms.beginSMS("+905"); // sms gönderilecek telefon numarasını başında ülke alan kodu olacak şekilde yazınız.
//        sms.print("!! GUVENLIK PROBLEMI !! \nKAPI ACILDI \n \nDIKKAT !!\n "); // uyarı sms metini 
//        sms.endSMS();
//        Serial.println("\nMANYETİK ALAN DİSİ - ISLEM BASARILI!-2\n"); // Serial port ekranından aşamaları izleyebilmemiz için uyarı metini. 
      
      } else {
        digitalWrite(13, LOW); //ledi sondur
      }
       //led için son

  oncekiZaman = millis();
    }
    }
