//https://blynk.hackster.io/josie99/smart-trash-bin-automation-7c8dea
#define BLYNK_PRINT Serial          // Blynk 
#include <ESP8266WiFi.h>            // WIFI
#include <BlynkSimpleEsp8266.h>     
#include<Servo.h>                 //Servo SG90
char auth[] = "483e2a27dc3b4fdcb5108b*******";   // token
char ssid[] = "Adsl momo";  // SSID WIFI
char pass[] = "9155253009";   // PASSWORD WIFI
Servo servo;
#define trigPin D1 //Ultrasonic1
#define echoPin D2 //Ultrasonic1
#define trigPin2 D3 //Ultrasonic2
#define echoPin2 D4 //Ultrasonic2
#define Servo_pin D5   //14
#define LED 16 //LED WIFI 
#define BLYNK_MAX_SENDBYTES 256 //256 Bytes

long duration, distance; 
long duration2, distance2; 
int t=0;
int L=0;
float prencent=0;
float distance_old=0;
void setup() 
{
  Serial.begin (9600);
  pinMode(trigPin, OUTPUT);     //Ultrasonic1
  pinMode(echoPin, INPUT);      //Ultrasonic1
  pinMode(trigPin2, OUTPUT);    //Ultrasonic2
  pinMode(echoPin2, INPUT);     //Ultrasonic2 
  pinMode(LED, OUTPUT);         //LED
  servo.attach(Servo_pin);       //Servo
//  Blynk.begin(auth, ssid, pass); 
//  Blynk.email("josie**************@gmail.com", "TrashBin", "Online."); // Test Online Email Sent
//  Blynk.notify("Tong Sampah Sudah Online"); //Notify Trash Online
  servo.write(210); // Starting Position Servo
}

void Blink() {
  int i=0;
  while (i=5){
    i=i+1;
  digitalWrite(LED, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(50);                       // wait for a second
  digitalWrite(LED, LOW);    // turn the LED off by making the voltage LOW
  delay(50); 
//
//  //Ultrasonic2                                    
////  long duration2, distance2;        
//  digitalWrite(trigPin2, LOW);        
//  delayMicroseconds(2);              
//  digitalWrite(trigPin2, HIGH);
//  delayMicroseconds(10);           
//  digitalWrite(trigPin2, LOW);
//  duration2 = pulseIn(echoPin2, HIGH);
//  distance2 = (duration2/2) / 29.1;
////  distance2= duration2*0.034/2;
//
//      Serial.print("The ");
//      Serial.print((23-distance2)/23);
//      Serial.println(" %  Percentage of the Trash bin is full. ");
//      Serial.print("The distance measured by second sensor is ");
//      Serial.print(distance2);
//      Serial.println(" cm ");
//      // wait for a second

 //Ultrasonic2                                    
//  long duration2, distance2;        
  digitalWrite(trigPin2, LOW);        
  delayMicroseconds(2);              
  digitalWrite(trigPin2, HIGH);
  delayMicroseconds(10);           
  digitalWrite(trigPin2, LOW);
  duration2 = pulseIn(echoPin2, HIGH);
//  distance2 = (duration2/2) / 29.1;
  distance2= (duration2*0.034)/2;

      prencent=((26-distance2)/26);
      Serial.print("The ");
      Serial.print(prencent);
      Serial.println(" %  Percentage of the Trash bin is full. ");
      Serial.println("The distance measured by second sensor by second method:  ");
      Serial.print(" duration2*0.034 is :");
      Serial.print(distance2);
      Serial.println(" cm ");
      // wait for a second
}
}
void loop() 
{
//  Blynk.run();
  
   //Ultrasonic1
//  long duration, distance;       
  digitalWrite(trigPin, LOW);        
  delayMicroseconds(2);              
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);           
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
//  distance = (duration/2) / 29.1;
  distance= duration*0.034/2;
//  Blynk.virtualWrite(V1, distance); //Level
  //Ultrasonic1
                                  
  //Ultrasonic2                                    
  long duration2, distance2;        
  digitalWrite(trigPin2, LOW);        
  delayMicroseconds(2);              
  digitalWrite(trigPin2, HIGH);
  delayMicroseconds(10);           
  digitalWrite(trigPin2, LOW);
  duration2 = pulseIn(echoPin2, HIGH);
//  distance2 = (duration2/2) / 29.1;
  distance2= (duration2*0.034)/2;
//  Blynk.virtualWrite(V2, distance2); //Level   
  //Ultrasonic2
 
  // Open Automation
  
  if (distance >= 25 || distance <0)    //Condition when trash open and close automatically
  {
    
    Serial.println("User is Out of range");
    
    if (L<1){
      servo.write(210);  //menutup
      t=0;
    }
    else{
       L=L+1;
    }
    if (distance2 >= 6 || distance2 <= 0)  //Condition When Trash close reading full or not 
    {

      digitalWrite(trigPin2, LOW);        
      delayMicroseconds(2);              
      digitalWrite(trigPin2, HIGH);
      delayMicroseconds(10);           
      digitalWrite(trigPin2, LOW);
      duration2 = pulseIn(echoPin2, HIGH);
    distance2 = (duration2/2) / 29.1;
//      distance2= (duration2*0.034)/2;

      prencent=((26-distance2)/26);
      Serial.print("The ");
      Serial.print(prencent);
      Serial.println(" %  Percentage of the Trash bin is full. ");
      Serial.println("The distance measured by second sensor by second method:  ");
      Serial.print(" (duration2*0.034)/2 is :");
      Serial.print(distance2);
      Serial.println(" cm ");
    Serial.print("Sensor 1 actviated by Distace of: ");
    Serial.print(distance2);
    Serial.println("  cm");
      // wait for a second
      
      digitalWrite(LED, HIGH);
//      delay(500);
    }
    else
    {
//      digitalWrite(LED, LOW);
//      delay(3000);
      Serial.println("Trash bin is FULL");
      Blink();
//      Blynk.email("jo********@gmail.com", "Subject: TrashBin", "Full"); //if trash full will sending you email every 15minutes 
//      Blynk.notify("Hey, Tong Sampah Penuh Segera Dikosongkan"); //Notify if trash full with blynk
    }
  }
  else 
  {
      t=t+1;
      
      digitalWrite(trigPin2, LOW);        
      delayMicroseconds(2);              
      digitalWrite(trigPin2, HIGH);
      delayMicroseconds(10);           
      digitalWrite(trigPin2, LOW);
      duration2 = pulseIn(echoPin2, HIGH);
//    distance2 = (duration2/2) / 29.1;
      distance2= (duration2*0.034)/2;

      prencent=((26-distance2)/26);
      Serial.print("The ");
      Serial.print(prencent);
      Serial.println(" %  Percentage of the Trash bin is full. ");
      Serial.println("The distance measured by second sensor by second method:  ");
      Serial.print(" (duration2*0.034)/2 is :");
      Serial.print(distance2);
      Serial.println(" cm ");
    Serial.print("Sensor 1 actviated by Distace of: ");
    Serial.print(distance2);
    Serial.println("  cm");
    if (t>1 && t<20){
     delay(1);      //Delay open trash 
     
    }
    else{
      servo.write(60);      //Open trash 
      L=0;
      
    }
    
  }
//  delay(50); //Reading hands
}
//Open Automation

  //Open Manually 
//  BLYNK_WRITE(V3)
//  {
//  servo.write(param.asInt());//open
//  delay(5000);
//  }
////  BLYNK_WRITE(V5)
//  {
//   servo.write(param.asInt());
//   delay(5000);
//  }
  //Open Manually
