#define sensor_pin A0
#define buzzer_pin 2
//RGB LED'imizin çıkış pinlerini tanımlıyoruz:
#define led_r 3
#define led_g 4
//#define led_b 7
//Sensörün çalışması için gerekli ön ısıtma süresini 5sn olarak belirliyoruz
#define preheat_time 5000
//Alarmın çalması için gerekli eşik değerini 300 olarak belirliyoruz.
#define threshold 300

#include <LiquidCrystal.h>
LiquidCrystal lcd (9,10,11,12,13,5);


const int in1=8;
const int in2 =7; 


void setup() {

  lcd.begin(16,2);
  
  // put your setup code here, to run once:
pinMode(buzzer_pin, OUTPUT);
pinMode(led_r, OUTPUT);
pinMode(led_g, OUTPUT);
//pinMode(led_b, OUTPUT);
//Varsayılan olarak LED'in sönük kalmasını sağlıyoruz
digitalWrite(led_r, HIGH);
digitalWrite(led_g, HIGH);
//digitalWrite(led_b, HIGH);
//Sensör değerini seri monitörden görebilmemiz için seri haberleşmeyi başlatıyoruz:
Serial.begin(9600);
//İlk 5sn boyunca sensörün ısınmasını bekliyoruz. Bu esnada LED mavi renkte yanıyor:
Serial.println("Sensor isitiliyor...");
//digitalWrite(led_b, LOW);
delay(preheat_time);
//Isıma işlemi için gereken 5sn süre tamamlandığında mavi LED'i söndürüyoruz:
//digitalWrite(led_b, HIGH);
delay(1000);
}

void loop() {
  // put your main code here, to run repeatedly:
//analogRead() fonksiyonu ile sensör değerini ölçüyoruz ve bir değişken içerisinde tutuyoruz:
int sensorValue = analogRead(sensor_pin);
//Sensör değeri belirlediğimiz eşik değerinden yüksek ise alarm() fonksiyonunu çağırıyoruz:

lcd.clear();
lcd.home();
lcd.print("   GYC CLEAN");
lcd.setCursor(1,1);
lcd.print( sensorValue);
//lcd.print("sensorValue");
delay(1000);


if (sensorValue >= threshold)
{
digitalWrite (in1,HIGH);
digitalWrite(in2,LOW);

}
else {
digitalWrite (in1,LOW);
digitalWrite(in2,LOW);
}

//Alarmın çalmadığı durumda LED'in yeşil yanmasını istiyoruz:
if (sensorValue >= threshold) {

alarm(100);

}
else {
digitalWrite(led_g, LOW);
//Sensör değerini bilgisayarımızdan görebilmek için seri monitöre yazıyoruz:
Serial.println(sensorValue);
delay(1);


}


}
//Alarm fonksiyonumuzu tanımlıyoruz. Bu fonksiyon parametre olarak buzzerın ötüp ve LED'in yanıp söneceği süreyi almakta.

void alarm(unsigned int duration)
{
//Buzzer'ın 440Hz'te (la notası) ses üretmesini istiyoruz:
tone(buzzer_pin, 440);
//Normal durumda yeşil yanmakta olan LED'i söndürüp kırmızı renkte yakıyoruz:
digitalWrite(led_r, LOW);
digitalWrite(led_g, HIGH);
delay(duration);
noTone(buzzer_pin);
digitalWrite(led_r, HIGH);
digitalWrite(led_g, HIGH);
delay(duration);
}
