int led = 13; //Led pin tanımlanıyor. En kullanılabilir led piniymiş GND ye yakın olmasından galiba :D
int gelen;
int dijital_deger, analog_deger, gonderilecekSicaklik;
int buzzerPin=2; // Buzzer'in + bacağının bnağlı olduğu pin

// Gas sensor analog ve dijital Pinler
int pin_gas_a = 7; // Gas sensor arduino dijital pin 7
int pin_gas_b = A2; // Gas sensor arduino analog pin A2

int gas_sensor = 220; // Sensor degeri serial monitorden okuyup istediğiniz degeri verebilirsiniz
float olculendeger;
int lm35Pin = A1;
float sicaklik;

void setup() {                
  pinMode(led, OUTPUT);   
  Serial.begin(9600); // 9600 Baud ile haberleşmeye başla
  pinMode(buzzerPin,OUTPUT); // Buzzer'in bağlı olduğu pini çıkış olarak ayarladık.
  // Gas sensor analog ve dijital Pinler
  pinMode(pin_gas_a, INPUT);
  pinMode(pin_gas_b, INPUT);
 
}
void loop() {
  delay(1000);
  if(Serial.available()>0){ // Haberleşme kullanılabilir durumda ise
    gelen=Serial.read(); // Java kodundan geleni oku
    if(gelen==1){ 
      digitalWrite(led, HIGH);  // 1 ise yak
      digitalWrite(buzzerPin, HIGH);
    }
    if(gelen==0){
      digitalWrite(led, LOW);  // 0 ise söndür
      digitalWrite(buzzerPin, HIGH);
    }
    Serial.write(gelen);
    Serial.write(dijital_deger);
    Serial.write(gonderilecekSicaklik);
  }
  dijital_deger = digitalRead(pin_gas_a);
   // Gas sensor analog pin A2
  analog_deger = analogRead(pin_gas_b);
  // Serial monitor
  if(dijital_deger != 0){
     Serial.print("Gaz Algılanıyor :");
     Serial.println(analog_deger);
  }
  else if(dijital_deger == 0){
    Serial.print("Gaz Algılanmıyor");
  }
 //   Serial.print(dijital_deger);
 //   Serial.print(" Pin Gas B : ");
 //   Serial.println(analog_deger);
  if (analog_deger > gas_sensor)
  {
    digitalWrite(buzzerPin, HIGH);
  }
  else
  {
    digitalWrite(buzzerPin, LOW);
  }
  delay(100);
  
  olculendeger = analogRead(lm35Pin); 
  olculendeger = (olculendeger/1023)*5000;//değeri mV'a dönüştürecek 
  sicaklik = olculendeger /10,0; // mV'u sicakliğa dönüştürecek
  gonderilecekSicaklik = (int)sicaklik;
   if (sicaklik > 70)
  {
    Serial.print("Duman sensörü devre dışı, Oda Sıcaklık :");
    Serial.println(sicaklik);
    digitalWrite(buzzerPin, HIGH);
  }
  else
  {
    Serial.print("Oda Sıcaklığı :");
    Serial.println(sicaklik);
    digitalWrite(buzzerPin, LOW);
  }
  delay(1000); 
}



