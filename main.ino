//190201069-Esra Dinc
//190201084-Rana Dudu Kabak
#include<EEPROM.h>

#include <Wire.h>

#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C ekran(0x27, 16, 2);
int kopuk = 0;
int yika = 0;
int kurula = 0;
int cilala = 0;

int bes = 0;
int on = 0;
int yirmi = 0;
int elli = 0;
int yuz = 0;

int adres = 0;

int sayac;

int bestlsay = 20;
int ontlsay = 20;
int yirmitlsay = 10;
int ellitlsay = 30;
int yuztlsay = 5;

int parasayisi[5] = {bestlsay, ontlsay, yirmitlsay, ellitlsay, yuztlsay};

int yeniparasayisi[5];

int matris[4][3];

int kopuklemesay = 30;
int yikamasay = 50;
int kurulamasay = 100;
int cilalamasay = 20;

int hizmetid[4] = {1, 2, 3, 4};
int kalanhizmet[4] = {kopuklemesay, yikamasay, kurulamasay, cilalamasay};
int ucret[4] = {15, 10, 5, 50};
int hizmetson[4];

int bitis = 9;

int yesil = 8;
int kirmizi = 7;

int reset = 6;

int cilalamabutonu = 5;
int kurulamabutonu = 4;
int yikamabutonu = 3;
int kopuklemebutonu = 2;

int para = 0;
int harcanan = 0;
int paraustu;

int buton5 = A1;
int buton10 = 13;
int buton20 = 12;
int buton50 = 11;
int buton100 = 10;

void setup() {
  //butonlar ve ledler icin

  //paralar
  pinMode(buton5, INPUT);
  pinMode(buton10, INPUT);
  pinMode(buton20, INPUT);
  pinMode(buton50, INPUT);
  pinMode(buton100, INPUT);

  //ledler
  pinMode(yesil, OUTPUT);
  pinMode(kirmizi, OUTPUT);

  //bitis reset
  pinMode(bitis, INPUT);
  pinMode(reset, INPUT);

  //hizmetler
  pinMode(cilalamabutonu, INPUT);
  pinMode(kurulamabutonu, INPUT);
  pinMode(yikamabutonu, INPUT);
  pinMode(kopuklemebutonu, INPUT);

  ekran.init();
  ekran.backlight();

  Serial.begin(9600);
  
  //dosyanin ilk satiri yazma
  for (int i = 0; i < 5; i++) {
    EEPROM.write(adres, parasayisi[i]);
    adres++;
  }
  //dosyanin ilk satiri okuma
  adres = 0;
  for (int i = 0; i < 5; i++) {
    Serial.print( EEPROM.read(adres));
    if (i != 4) {
      Serial.print( ",");
    }
    adres++;
  }
  Serial.println();

  //Dosyanin devami
  //matrisi tanımladım
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 3; j++) {
      if (j == 0) {
        matris[i][j] = hizmetid[i];
      }
      else if (j == 1) {
        matris[i][j] = kalanhizmet[i];
      }
      else if (j == 2) {
        matris[i][j] = ucret[i];
      }
    }
  }
  
  //eeproma yazma ikinci kisim icin
  adres = 5;

  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 3; j++) {
      EEPROM.write(adres, matris[i][j]);
      adres++;
    }
  }
  
  //ikinci kismi okuma
  int b = 0;
  adres = 5;
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 3; j++) {
      if (j == 1) {
        if (b == 0) {
          Serial.print("Kopukleme");
          Serial.print("\t");
          Serial.print(EEPROM.read(adres));
          adres++;
        }
        else if (b == 1) {
          Serial.print("Yikama");
          Serial.print("\t\t");
          Serial.print(EEPROM.read(adres));
          adres++;
        }
        else if (b == 2) {
          Serial.print("Kurulama");
          Serial.print("\t");
          Serial.print(EEPROM.read(adres));
          adres++;
        }
        else if (b == 3) {
          Serial.print("Cilalama");
          Serial.print("\t");
          Serial.print(EEPROM.read(adres));
          adres++;
        }
      }
      else if (j == 2) {
        Serial.print(EEPROM.read(adres));
        Serial.print(" TL");
        adres++;
      }
      else {

        Serial.print(EEPROM.read(adres));
        adres++;
      }

      Serial.print("\t");
    }
    b++;
    Serial.print("\n");
  }

  ekran.setCursor(0, 0);
  ekran.print("Hosgeldiniz.");
  ekran.setCursor(0, 1);
  ekran.print("Para atiniz.");
  delay(2000);
  ekran.clear();
}

void loop() {
  //para ekleme butonlari icin

  //5 TL butonunna basinca
  if (digitalRead(buton5) == HIGH) {
    bes++;
    para += 5;
    sayac = 0;
    adres = 0;
    bestlsay++;
    EEPROM.update(adres, bestlsay);

    delay(1000);
  }

  //10 Tl butonuna basinca
  if (digitalRead(buton10) == HIGH) {
    on++;
    para += 10;
    sayac = 0;
    adres = 1;
    ontlsay++;
    EEPROM.update(adres, ontlsay);
    
    delay(1000);
  }

  //20 Tl butonuna basinca
  if (digitalRead(buton20) == HIGH) {
    yirmi++;
    para += 20;
    sayac = 0;
    adres = 2;
    yirmitlsay++;
    EEPROM.update(adres, yirmitlsay);

    delay(1000);
  }

  //50 Tl butonuna basinca
  if (digitalRead(buton50) == HIGH) {
    elli++;
    para += 50;
    sayac = 0;
    adres = 3;
    ellitlsay++;
    EEPROM.update(adres, ellitlsay);

    delay(1000);
  }

  //100 Tl butonuna basinca
  if (digitalRead(buton100) == HIGH) {
    yuz++;
    para += 100;
    sayac = 0;
    adres = 4;
    yuztlsay++;
    EEPROM.update(adres, yuztlsay);

    delay(1000);
  }

  //Hizmet butonlari icin

  //Kopukleme butonu icin
  if (digitalRead(kopuklemebutonu) == HIGH) {
    sayac = 1;
    if (kopuklemesay <= 0) {
      ekran.setCursor(0, 0);
      ekran.print("Kopukleme");
      ekran.setCursor(0, 1);
      ekran.print("yapamazsiniz ");
      Serial.println("Kopukleme hizmetimiz kalmamistir. Kopukleme yapamazsiniz.");
      delay(1000);
    }
    else {
      kopuk++;

      harcanan += 15;
      adres = 6;

      kopuklemesay--;
      EEPROM.update(adres, kopuklemesay);

      ekran.setCursor(0, 0);
      ekran.print("Kalan kopukleme");
      ekran.setCursor(0, 1);
      ekran.print("adedi: ");
      ekran.print(kopuklemesay);
      ekran.setCursor(0, 1);
      delay(2000);
      ekran.clear();

    }
  }

  //Yikama butonu icin
  if (digitalRead(yikamabutonu) == HIGH) {
    sayac = 1;
    if (yikamasay <= 0) {
      ekran.setCursor(0, 0);
      ekran.print("Yikama");
      ekran.setCursor(0, 1);
      ekran.print("yapamazsiniz ");
      Serial.println("Yikama hizmetimiz kalmamistir. yikama yapamazsiniz.");
      delay(1000);
    }
    else {
      yika++;

      harcanan += 10;
      adres = 9;

      yikamasay--;
      EEPROM.update(adres, yikamasay);
      ekran.setCursor(0, 0);
      ekran.print("Kalan yikama");
      ekran.setCursor(0, 1);
      ekran.print("adedi: ");
      ekran.print(yikamasay);
      ekran.setCursor(0, 1);
      delay(3000);
      ekran.clear();
    }
  }

  //Kurulama butonu icin
  if (digitalRead(kurulamabutonu) == HIGH) {
    sayac = 1;
    if (kurulamasay <= 0) {
      ekran.setCursor(0, 0);
      ekran.print("Kurulama");
      ekran.setCursor(0, 1);
      ekran.print("yapamazsiniz ");
      Serial.println("Kurulama hizmetimiz kalmamistir. Kurulama yapamazsiniz.");
      delay(1000);
    }
    else {
      kurula++;

      harcanan += 5;
      adres = 12;

      kurulamasay--;

      EEPROM.update(adres, kurulamasay);
      ekran.setCursor(0, 0);
      ekran.print("Kalan kurulama");
      ekran.setCursor(0, 1);
      ekran.print("adedi: ");
      ekran.print(kurulamasay);
      ekran.setCursor(0, 1);
      delay(3000);
      ekran.clear();
    }
  }


  //Cilalama butonu icin
  if (digitalRead(cilalamabutonu) == HIGH) {
    sayac = 1;
    if (cilalamasay <= 0) {
      ekran.setCursor(0, 0);
      ekran.print("Cilalama");
      ekran.setCursor(0, 1);
      ekran.print("yapamazsiniz ");
      Serial.println("Cilalama hizmetimiz kalmamistir.Cilalama yapamazsiniz.");
      delay(1000);
    }
    else {
      cilala++;
      harcanan += 50;
      adres = 15;
      cilalamasay--;
      EEPROM.update(adres, cilalamasay);
      ekran.setCursor(0, 0);
      ekran.print("Kalan cilalama");
      ekran.setCursor(0, 1);
      ekran.print("adedi: ");
      ekran.print(cilalamasay);
      ekran.setCursor(0, 1);
      delay(3000);
      ekran.clear();
    }
  }


  if (digitalRead(bitis) == HIGH) {
    if (sayac == 0) {
      ekran.setCursor(0, 0);
      ekran.print(para);
      ekran.print(" TL para");
      ekran.setCursor(0, 1);
      ekran.print("attiniz.");
      delay(3000);
      ekran.clear();

      Serial.print(para);
      Serial.println("TL para attiniz.");
      Serial.println("Hizmet seciniz.");

      ekran.setCursor(0, 0);
      ekran.print("Hizmet secin.");
      delay(3000);
      ekran.clear();
    }


    if (sayac == 1) {
      //sikismayi kontrol ediyor
      int sikisma = millis() % 4 + 1;
      if (sikisma == 2 ) {
       
        Serial.println("Para sikisti.");
        Serial.print(para);
        Serial.println(" TL geri verildi.");
        Serial.println("Para atiniz.");
        
        digitalWrite(kirmizi, HIGH);
        ekran.setCursor(0, 0);
        ekran.print("Para sikisti");
        delay(3000);
        digitalWrite(kirmizi, LOW);
        delay(1000);

        ekran.clear();

        ekran.setCursor(0, 0);
        ekran.print(para);
        ekran.print(" TL geri");
        ekran.setCursor(0, 1);
        ekran.print("verildi.");
        delay(3000);
        ekran.clear();
        ekran.setCursor(0, 0);
        ekran.print("Para atiniz.");
        delay(3000);
        ekran.clear();

        bestlsay = bestlsay - bes;
        ontlsay = ontlsay - on;
        yirmitlsay = yirmitlsay - yirmi;
        ellitlsay = ellitlsay - elli;
        yuztlsay = yuztlsay - yuz;

        EEPROM.update(0, bestlsay);
        EEPROM.update(1, ontlsay);
        EEPROM.update(2, yirmitlsay);
        EEPROM.update(3, ellitlsay);
        EEPROM.update(4, yuztlsay);

        kopuklemesay = kopuklemesay + kopuk;
        yikamasay = yikamasay + yika;
        kurulamasay = kurulamasay + kurula;
        cilalamasay = cilalamasay + cilala;

        EEPROM.update(6, kopuklemesay);
        EEPROM.update(9, yikamasay);
        EEPROM.update(12, kurulamasay);
        EEPROM.update(15, cilalamasay);

        para = 0;

        harcanan = 0;

        kopuk = 0;
        yika = 0;
        kurula = 0;
        cilala = 0;

        bes = 0;
        on = 0;
        yirmi = 0;
        elli = 0;
        yuz = 0;

        ekran.clear();
        Serial.println();
        Serial.println("GUNCEL");
        adres = 0;
        for (int i = 0; i < 5; i++) {
          Serial.print( EEPROM.read(adres));
          if (i != 4) {
            Serial.print(",");
          }
          adres++;
        }

        Serial.println();

        int f = 0;
        adres = 5;
        for (int i = 0; i < 4; i++) {
          for (int j = 0; j < 3; j++) {
            if (j == 1) {
              if (f == 0) {
                Serial.print("Kopukleme");
                Serial.print("\t");
                Serial.print(EEPROM.read(adres));
                adres++;
              }
              else if (f == 1) {
                Serial.print("Yikama");
                Serial.print("\t\t");
                Serial.print(EEPROM.read(adres));
                adres++;
              }
              else if (f == 2) {
                Serial.print("Kurulama");
                Serial.print("\t");
                Serial.print(EEPROM.read(adres));
                adres++;
              }
              else if (f == 3) {
                Serial.print("Cilalama");
                Serial.print("\t");
                Serial.print(EEPROM.read(adres));
                adres++;
              }
            }
            else if (j == 2) {
              Serial.print(EEPROM.read(adres));
              Serial.print(" TL");
              adres++;
            }
            else {

              Serial.print(EEPROM.read(adres));
              adres++;
            }

            Serial.print("\t");
          }
          f++;
          Serial.print("\n");
        }
        Serial.println();
      }
      else {

        paraustu = para - harcanan;

        if (paraustu < 0) {
          Serial.println("Yetersiz bakiye!");
          Serial.println("Lutfen reset tusuna basarak islemlerinizi tekrarlayin");
          ekran.setCursor(0, 0);
          ekran.print("Yetersiz bakiye");
          ekran.clear();
          delay(1000);

        }

        else {
          Serial.print("Harcadiginiz tutar:");
          Serial.println(harcanan);

          ekran.setCursor(0, 0);
          ekran.print("Para ustunuz:");
          ekran.setCursor(0, 1);
          ekran.print(paraustu);
          ekran.print("TL");

          Serial.print("Verilecek para ustu:");
          Serial.println(paraustu);

          digitalWrite(yesil, HIGH);
          delay(2000);
          digitalWrite(yesil, LOW);
          delay(1000);

          Serial.println("Para ustu veriliyor..");

          int temp;
          temp = paraustu;
          int a, b, c, d, e;
          a = temp / 100;
          if (a <= yuztlsay) {
            temp = temp - (a * 100);
            yuztlsay = yuztlsay - a;
            EEPROM.update(4, yuztlsay);

          }
          else {
            a =  yuztlsay;
            temp = temp - ( yuztlsay * 100);
            yuztlsay = yuztlsay - a;
            EEPROM.update(4, yuztlsay);
          }

          b = temp / 50;
          if (b <= ellitlsay) {
            temp = temp - (b * 50);
            ellitlsay = ellitlsay - b;
            EEPROM.update(3, ellitlsay);

          }
          else {
            b = ellitlsay;
            temp = temp - (ellitlsay * 50);
            ellitlsay = ellitlsay - b;
            EEPROM.update(3, ellitlsay);
          }

          c = temp / 20;
          if (c <= yirmitlsay) {
            temp = temp - (c * 20);
            yirmitlsay = yirmitlsay - c;
            EEPROM.update(2, yirmitlsay);

          }
          else {
            c = yirmitlsay;
            temp = temp - (yirmitlsay * 20);
            yirmitlsay = yirmitlsay - c;
            EEPROM.update(2, yirmitlsay);
          }

          d = temp / 10;
          if (d <= ontlsay) {
            temp = temp - (d * 10);
            ontlsay = ontlsay - d;
            EEPROM.update(1, ontlsay);
          }
          else {
            d = ontlsay;
            temp = temp - (ontlsay * 10);
            ontlsay = ontlsay - d;
            EEPROM.update(1, ontlsay);
          }

          e = temp / 5;
          if (e <= bestlsay) {
            temp = temp - (e * 5);
            bestlsay = bestlsay - e;
            EEPROM.update(0, bestlsay);

          }
          else {
            e = bestlsay;
            temp = temp - (bestlsay * 5);
            bestlsay = bestlsay - e;
            EEPROM.update(0, bestlsay);
          }

          int verilen = e * 5 + d * 10 + c * 20 + b * 50 + a * 100;

          if (verilen != paraustu) {
            Serial.println("Gerekli banknotlar mevcut degil.Para ustu verilemiyor.");
            Serial.print(para);
            Serial.println(" TL geri veriliyor. Lutfen islemlerinizi tekrarlayiniz. ");
            yuztlsay += a;
            ellitlsay += b;
            yirmitlsay += c;
            ontlsay += d;
            bestlsay += e;
            EEPROM.update(0, bestlsay);
            EEPROM.update(1, ontlsay);
            EEPROM.update(2, yirmitlsay);
            EEPROM.update(3, ellitlsay);
            EEPROM.update(4, yuztlsay);

            bestlsay = bestlsay - bes;
            ontlsay = ontlsay - on;
            yirmitlsay = yirmitlsay - yirmi;
            ellitlsay = ellitlsay - elli;
            yuztlsay = yuztlsay - yuz;

            EEPROM.update(0, bestlsay);
            EEPROM.update(1, ontlsay);
            EEPROM.update(2, yirmitlsay);
            EEPROM.update(3, ellitlsay);
            EEPROM.update(4, yuztlsay);

            kopuklemesay = kopuklemesay + kopuk;
            yikamasay = yikamasay + yika;
            kurulamasay = kurulamasay + kurula;
            cilalamasay = cilalamasay + cilala;

            EEPROM.update(6, kopuklemesay);
            EEPROM.update(9, yikamasay);
            EEPROM.update(12, kurulamasay);
            EEPROM.update(15, cilalamasay);
          }
          else {
            Serial.print("Para ustu olarak verilen 100 TL sayisi:");
            Serial.println(a);
            Serial.print("Para ustu olarak verilen 50 TL sayisi: ");
            Serial.println(b);
            Serial.print("Para ustu olarak verilen 20 TL sayisi:");
            Serial.println(c);
            Serial.print("Para ustu olarak verilen 10 TL sayisi: ");
            Serial.println(d);
            Serial.print("Para ustu olarak verilen 5 TL sayisi: " );
            Serial.println(e);
          }

          ekran.clear();

          Serial.println();
          Serial.println("GUNCEL");
          adres = 0;
          for (int i = 0; i < 5; i++) {
            Serial.print( EEPROM.read(adres));
            if (i != 4) {
              Serial.print(",");
            }
            adres++;
          }

          Serial.println();

          int f = 0;
          adres = 5;
          for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 3; j++) {
              if (j == 1) {
                if (f == 0) {
                  Serial.print("Kopukleme");
                  Serial.print("\t");
                  Serial.print(EEPROM.read(adres));
                  adres++;
                }
                else if (f == 1) {
                  Serial.print("Yikama");
                  Serial.print("\t\t");
                  Serial.print(EEPROM.read(adres));
                  adres++;
                }
                else if (f == 2) {
                  Serial.print("Kurulama");
                  Serial.print("\t");
                  Serial.print(EEPROM.read(adres));
                  adres++;
                }
                else if (f == 3) {
                  Serial.print("Cilalama");
                  Serial.print("\t");
                  Serial.print(EEPROM.read(adres));
                  adres++;
                }
              }
              else if (j == 2) {
                Serial.print(EEPROM.read(adres));
                Serial.print(" TL");
                adres++;
              }
              else {

                Serial.print(EEPROM.read(adres));
                adres++;
              }

              Serial.print("\t");
            }
            f++;
            Serial.print("\n");
          }
          Serial.println();
          para = 0;
          harcanan = 0;

          kopuk = 0;
          kurula = 0;
          yika = 0;
          cilala = 0;

          bes = 0;
          on = 0;
          yirmi = 0;
          elli = 0;
          yuz = 0;

          Serial.println("Hosgeldiniz."); 
          Serial.println("Para atiniz.");
          
          ekran.setCursor(0, 0);
          ekran.print("Hosgeldiniz");
          ekran.setCursor(0, 1);
          ekran.print("Para atiniz.");
          delay(2000);
          ekran.clear();
          delay(1000);
        }
      }
    }
  }
  
  // reset butonu icin
  if (digitalRead(reset) == HIGH) {
    Serial.println("Resetlendi");
    Serial.print(para);
    Serial.println(" TL geri verildi.");
    ekran.setCursor(0, 0);
    ekran.print("Resetlendi.");
    delay(3000);
    ekran.clear();
    ekran.setCursor(0, 0);
    ekran.print(para);
    ekran.print(" TL geri");
    ekran.setCursor(0, 1);
    ekran.print("verildi.");
    delay(3000);
    ekran.clear();
    ekran.setCursor(0, 0);
    ekran.print("Para atiniz.");
    delay(3000);
    ekran.clear();

    bestlsay = bestlsay - bes;
    ontlsay = ontlsay - on;
    yirmitlsay = yirmitlsay - yirmi;
    ellitlsay = ellitlsay - elli;
    yuztlsay = yuztlsay - yuz;

    EEPROM.update(0, bestlsay);
    EEPROM.update(1, ontlsay);
    EEPROM.update(2, yirmitlsay);
    EEPROM.update(3, ellitlsay);
    EEPROM.update(4, yuztlsay);

    kopuklemesay = kopuklemesay + kopuk;
    yikamasay = yikamasay + yika;
    kurulamasay = kurulamasay + kurula;
    cilalamasay = cilalamasay + cilala;

    EEPROM.update(6, kopuklemesay);
    EEPROM.update(9, yikamasay);
    EEPROM.update(12, kurulamasay);
    EEPROM.update(15, cilalamasay);

    para = 0;
    harcanan = 0;

    kopuk = 0;
    yika = 0;
    kurula = 0;
    cilala = 0;

    bes = 0;
    on = 0;
    yirmi = 0;
    elli = 0;
    yuz = 0;

    Serial.println();
    Serial.println("GUNCEL");
    adres = 0;
    for (int i = 0; i < 5; i++) {
      Serial.print( EEPROM.read(adres));
      if (i != 4) {
        Serial.print(",");
      }
      adres++;
    }

    Serial.println();

    int f = 0;
    adres = 5;
    for (int i = 0; i < 4; i++) {
      for (int j = 0; j < 3; j++) {
        if (j == 1) {
          if (f == 0) {
            Serial.print("Kopukleme");
            Serial.print("\t");
            Serial.print(EEPROM.read(adres));
            adres++;
          }
          else if (f == 1) {
            Serial.print("Yikama");
            Serial.print("\t\t");
            Serial.print(EEPROM.read(adres));
            adres++;
          }
          else if (f == 2) {
            Serial.print("Kurulama");
            Serial.print("\t");
            Serial.print(EEPROM.read(adres));
            adres++;
          }
          else if (f == 3) {
            Serial.print("Cilalama");
            Serial.print("\t");
            Serial.print(EEPROM.read(adres));
            adres++;
          }
        }
        else if (j == 2) {
          Serial.print(EEPROM.read(adres));
          Serial.print(" TL");
          adres++;
        }
        else {

          Serial.print(EEPROM.read(adres));
          adres++;
        }

        Serial.print("\t");
      }
      f++;
      Serial.print("\n");
    }
    Serial.println("Para atiniz.");
  }
}
