int led = 8; 
int gelen;
int dijital_deger, analog_deger, gonderilecekSicaklik;
int buzzerPin=2; // Buzzer'in + bacağının bağlı olduğu pin

// Gas sensor analog ve dijital Pinler
int pin_gas_a = 7; // Gas sensor arduino dijital pin 7
int pin_gas_b = A2; // Gas sensor arduino analog pin A2

int gas_sensor = 300; // Sensor degeri serial monitorden okuyup istediğiniz degeri verebilirsiniz
float olculendeger;
int lm35Pin = A1;
float sicaklik;
int buzzerDurum=0;
void setup() {                
  pinMode(led, OUTPUT);   
  Serial.begin(9600); // 9600 Baud ile haberleşmeye başla.
  pinMode(buzzerPin,OUTPUT); // Buzzer'in bağlı olduğu pini çıkış olarak ayarladık.
  // Gas sensor analog ve dijital Pinler
  pinMode(pin_gas_a, INPUT);
  pinMode(pin_gas_b, INPUT);
 
}
void loop() {
  delay(1000);
  if(Serial.available()>0){ // Haberleşme kullanılabilir durumda ise
    gelen=Serial.read(); // Java kodundan geleni oku
    if(gelen==65){ 
      digitalWrite(led, HIGH);  // 1 ise yak
      digitalWrite(buzzerPin, LOW);
      buzzerDurum = 0;
    }
    if(gelen==66){ 
      digitalWrite(led, LOW);  // 1 ise yak
      digitalWrite(buzzerPin, HIGH);
      buzzerDurum = 1;
    }
    if(gelen==67){
      digitalWrite(led, LOW);  // 0 ise söndür
      digitalWrite(buzzerPin, LOW);
      buzzerDurum = 0;
    }
    Serial.write(gelen);
    Serial.write(dijital_deger);
    Serial.write(gonderilecekSicaklik);
  }
  dijital_deger = digitalRead(pin_gas_a);
   // Gas sensor analog pin A2
  analog_deger = analogRead(pin_gas_b);
  // Serial monitor
  Serial.print("Pin Gas_A : ");
  Serial.print(dijital_deger);
  Serial.print(" Pin Gas_B : ");
  Serial.println(analog_deger);
  if (analog_deger > gas_sensor)
  {

    digitalWrite(buzzerPin, HIGH);

  }
  else
  {
    if(buzzerDurum != 1){
      digitalWrite(buzzerPin, LOW);
    }
    
  }
  delay(100);
  //sicakliksensoru
  int sicaklikVolt = analogRead(lm35Pin);
  float sicaklikC = sicaklikC = sicaklikVolt / 9.31; 
  Serial.print("Sıcaklık: ");
  Serial.println(sicaklikC);
}
