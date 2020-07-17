#include <SoftwareSerial.h>
SoftwareSerial SIM900A(6,7);

float temp;
int LEDR = 11;
int LEDG = 10;
int Buzzer = 13;

void setup() {
  SIM900A.begin(9600); 
  Serial.begin(9600);
  pinMode(LEDR,OUTPUT);
  pinMode(LEDG,OUTPUT);
  pinMode(Buzzer,OUTPUT);

}

void loop() {
 temp = analogRead(A0);
 temp = temp * 0.48828125;

 if(temp>34)
 {
  Serial.println();
  	Serial.print("** Fire Alert **");
  	Serial.println();
 	Serial.println();
  digitalWrite(LEDR,HIGH);
  digitalWrite(LEDG,LOW);
  digitalWrite(Buzzer,HIGH);
  
  	Serial.print("Temperature :");
  	Serial.print(temp);
  	Serial.print("*c");
  	Serial.println();
  delay(1000);
  SendMessage();
  }
 else {

  digitalWrite(LEDG,HIGH);
  digitalWrite(LEDR,LOW);
  digitalWrite(Buzzer,LOW);
  	Serial.print("Temperature :");
  	Serial.print(temp);
  	Serial.print("*c");
  	Serial.println();
  delay(1000);  
 }
}
 void SendMessage()
{
  if (SIM900A.available()>0)
  	Serial.write(SIM900A.read());

  	Serial.println ("Making a Call");
  	SIM900A.println("ATD+8801633325120;");
  delay(1000);
  	Serial.println ("Sending Message");
 	 SIM900A.println("AT+CMGF=1");   
  delay(1000);
 	 Serial.println ("Set SMS Number");
 	 SIM900A.println("AT+CMGS=\"+8801633325120\"\r"); 
  delay(1000);
  	Serial.println ("Set SMS Content");
  	SIM900A.println("2ndfloor,Science Building JKKNIU");
  delay(100);
  	Serial.println ("Finish");
  	SIM900A.println((char)26);
  delay(1000);
  	Serial.println ("Message has been sent");
  delay(5000);
}
