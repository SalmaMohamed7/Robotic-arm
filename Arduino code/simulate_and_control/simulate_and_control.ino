#include <Firebase.h>
#include <FirebaseArduino.h>
#include <FirebaseCloudMessaging.h>
#include <FirebaseError.h>
#include <FirebaseHttpClient.h>
#include <FirebaseObject.h>

#include <ESP8266WiFi.h>
#include <ArduinoJson.h>
#include <FirebaseArduino.h>
#include <Servo.h>
 
#define FIREBASE_HOST "car-dt.firebaseio.com" 
#define FIREBASE_AUTH "QdjvffipvUgkhPl679Fs3BfCw2JErfkxNZLKIsXv" 
#define WIFI_SSID "Ulm" 
#define WIFI_PASSWORD "1471998ss" 

int ledPin = 13;
Servo servoA0;
Servo servoA1;
Servo servoA2;
 
void setup() { 
  Serial.begin(9600); 
  pinMode(ledPin,OUTPUT);
 digitalWrite(ledPin,LOW);  
  servoA0.attach(0);  //pinD3
  servoA1.attach(2);  //PIN D4
  servoA2.attach(5);  //PIN D1
  servoA0.write(90);
  servoA1.write(90);
  servoA2.write(90);

  // connect to wifi. 
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD); 
  Serial.print("connecting"); 
  while (WiFi.status() != WL_CONNECTED) { 
    Serial.print("."); 
    delay(500); 
  } 
  Serial.println(); 
  Serial.print("connected: "); 
  Serial.println(WiFi.localIP()); 
   
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH); 
} 
 
int n = 0; 
int a0=0;
int a1=0;
int a2=0;
int moveA0 = 0;
int moveA1 = 0;
int moveA2 = 0;
int servA0 = 0;
int servA1 = 0;
int servA2 = 0;
String aaa = "a0";
String st = "";
int a0Read = 0;
int a1Read = 0; 
int a2Read = 0;
boolean a0Changed = false;
 
void loop() { 
//  set value 
if(WiFi.status() != WL_CONNECTED){
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD); 
  Serial.print("connecting"); 
  while (WiFi.status() != WL_CONNECTED) { 
    Serial.print("."); 
    delay(500); 
  } 
  Serial.println(); 
  Serial.print("connected: "); 
  Serial.println(WiFi.localIP()); 
   
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
}

  if(Firebase.getFloat("test")==0){
    Serial.print("facing problem with firebase please wait!");
    ESP.restart();
     }
if(Serial.available()>0){
  st = Serial.readString();
  Serial.println(st);
}
if(st.substring(0,2)=="a0"){
  String num = st.substring(3);
  Serial.println(num);
  moveA0 = num.toInt();
  st="";
}
if(st.substring(0,2)=="a1"){
  String num = st.substring(3);
  Serial.println(num);
  moveA1 = num.toInt();
  st="";

}
if(st.substring(0,2)=="a2"){
  String num = st.substring(3);
  Serial.println(num);
  moveA2 = num.toInt();
  st="";
}

//A0
if(moveA0<0){ 
  //servoA0 moves anti-clockwise
  servA0 = moveA0*-4.5;
  servoA0.write(85); //Anti-Clockwise from 98 to 85
  delay(servA0);
  servoA0.write(90); //Stop
  //delay(2000);  
    int x = 0;
  while(moveA0<0){
      x = Firebase.getFloat("angles/A0");
      if(moveA0<=-10){
        x=x-10;  
        moveA0+=10;  
      }
      else{
        x = x + moveA0;
        moveA0=0;
      }
  Firebase.setFloat("angles/A0", x); 
    
  delay(100);
  Serial.print("MOVEA0 = ");
  Serial.println(moveA0);  
}
  Firebase.setFloat("read/a0", x);
  Serial.print("ZEROOOOOO");
}

if(moveA0>0){
  //move servoA0 clockwise
  servA0 = moveA0*2.5;
  servoA0.write(99); //Clockwise  vv
  delay(servA0);
  servoA0.write(90); //Stop
  //delay(2000);  
    int x = 0;
  while(moveA0>0){
  x = Firebase.getFloat("angles/A0");
  if(moveA0>=10){
    x=x+10;  
    moveA0-=10;  
  }
  else{
    x = x + moveA0;
    moveA0=0;
  }
  Firebase.setFloat("angles/A0", x); 
  delay(100);
  Serial.print("MOVEA0 = ");
  Serial.println(moveA0);  
}
 Firebase.setFloat("read/a0", x);
 Serial.print("ZEROOOOOO");
}

//A1
if(moveA1<0){
  //move servoA1 anti-clockwise
  servA1 = moveA1;
  servA1 = servA1*-4.3;  //4.1
  servoA1.write(84); 
  delay(servA1);
  servoA1.write(90); //Stop
  //delay(2000); 
  int x = 0;
  while(moveA1<0){
  x = Firebase.getFloat("angles/A1");
  if(moveA1<=-10){
    x=x-10;  
    moveA1+=10;  
  }
  else{
    x = x - (moveA1*-1);
    moveA1=0;
  }
  Firebase.setFloat("angles/A1", x); 
  delay(100);
  Serial.print("MOVEA1 = ");
  Serial.println(moveA1);  
}
 Firebase.setFloat("read/a1", x);
  Serial.print("ZEROOOOOO");

}

if(moveA1>0){
  servA1 = moveA1*2.8;//2.5
  servoA1.write(99); //Anti-Clockwise
  delay(servA1);
  servoA1.write(90); //Stop
  //delay(2000);  
  int x = 0;
  while(moveA1>0){
  x = Firebase.getFloat("angles/A1");
  if(moveA1>=10){
    x=x+10;  
    moveA1-=10;  
  }
  else{
    x = x + moveA1;
    moveA1=0;
    Firebase.setFloat("read/a1", x);
  }
  Firebase.setFloat("angles/A1", x); 
  delay(100);
  Serial.print("MOVEA1 = ");
  Serial.println(moveA1);  
}
Firebase.setFloat("read/a1", x);
 Serial.print("ZEROOOOOO");
}

//A2
if(moveA2<0){
  //move servoA2 anti clockwise
  servA2 = moveA2*-3.1;  //2.5 2.7 2.9
  servoA2.write(99); //Clockwise
  delay(servA2);
  servoA2.write(90); //Stop
  //delay(2000);  
  int x = 0;
  while(moveA2<0){
  x = Firebase.getFloat("angles/A2");
  if(moveA2<=-10){
    x=x-10;  
    moveA2+=10;  
  }
  else{
    x = x - (moveA2*-1);
    moveA2=0;
    

  }
  Firebase.setFloat("angles/A2", x); 
  delay(100);
  Serial.print("MOVEA2 = ");
  Serial.println(moveA2);  
}
Firebase.setFloat("read/a2", x);
 Serial.print("ZEROOOOOO");

}

if(moveA2>0){
  //move servoA2 clockwise
//  servA2 = moveA2*2.5;
//  servoA2.write(99); //Clockwise
  servA2 = moveA2*3.8; // 4.5 == 3.8
  servoA2.write(85); 
  delay(servA2);
  servoA2.write(90); //Stop
  //delay(2000);  
  int x = 0;
  while(moveA2>0){
  x = Firebase.getFloat("angles/A2");
  if(moveA2>=10){
    x=x+10;  
    moveA2-=10;  
  }
  else{
    x = x + moveA2;
    moveA2=0;
  }
  Firebase.setFloat("angles/A2", x); 
  delay(100);
  Serial.print("MOVEA2 = ");
  Serial.println(moveA2);  
}
 Firebase.setFloat("read/a2", x);
 Serial.print("ZEROOOOOO");
}


  a0Read = Firebase.getFloat("read/a0"); 
  a1Read = Firebase.getFloat("read/a1"); 
  a2Read = Firebase.getFloat("read/a2"); 
  // get value  
  int a0Before = Firebase.getFloat("angles/A0");
  int a1Before = Firebase.getFloat("angles/A1");
  int a2Before = Firebase.getFloat("angles/A2");

  //A0
  if(a0Before>a0Read){
    a0 = a0Before - a0Read;
      Serial.print("A0 moved "); 
      Serial.print(a0); 
      Serial.println(" degrees clockwise"); 
      a0=a0*2.6; //2.5
      servoA0.write(99); //Clockwise
      delay(a0);
      servoA0.write(90); //Stop
      delay(2000);   
  }
  if(a0Before<a0Read){
    a0 = a0Read - a0Before;
      Serial.print("A0 moved "); 
      Serial.print(a0); 
      Serial.println(" degrees anti-clockwise"); 
      a0=a0*4.5;
      servoA0.write(85); //Anti-Clockwise
      delay(a0);
      servoA0.write(90); //Stop
      delay(2000);   
  }
  //A1
  if(a1Before>a1Read){
    a1 = a1Before - a1Read;
      Serial.print("A1 moved "); 
      Serial.print(a1); 
      Serial.println(" degrees clockwise"); 
//      a1=a1*4;
//      servoA1.write(85); //Clockwise
      a1=a1*3; //2.5  2.8
      servoA1.write(99); //Anti-Clockwise
      delay(a1);
      servoA1.write(90); //Stop
      delay(2000);   
  }
  if(a1Before<a1Read){
    a1 = a1Read - a1Before;
      Serial.print("A1 moved "); 
      Serial.print(a1); 
      Serial.println(" degrees anti-clockwise"); 
        a1=a1*4; //3.8
      servoA1.write(84); //Clockwise
//      a1=a1*5;
//      servoA1.write(99); //Anti-Clockwise
      delay(a1);
      servoA1.write(90); //Stop
      delay(2000);   
  }
  //A2
  if(a2Before>a2Read){
    a2 = a2Before - a2Read;
      Serial.print("A2 moved "); 
      Serial.print(a2); 
      Serial.println(" degrees clockwise"); 
//       a2=a2*2.5;
//      servoA2.write(99); //Anti-Clockwise
      a2=a2*4; //4.5
      servoA2.write(85); //Clockwise
      delay(a2);
      servoA2.write(90); //Stop
      delay(2000);   
  }
  if(a2Before<a2Read){
    a2 = a2Read - a2Before;
      Serial.print("A2 moved "); 
      Serial.print(a2); 
      Serial.println(" degrees anti-clockwise"); 
//      a2=a2*4;
//      servoA2.write(85); //Clockwise
      a2=a2*2.5;
      servoA2.write(99); //Anti-Clockwise
      delay(a2);
      servoA2.write(90); //Stop
      delay(2000);   
  }
  delay(3000);
  int a0After = Firebase.getFloat("angles/A0");
  int a1After = Firebase.getFloat("angles/A1");
  int a2After = Firebase.getFloat("angles/A2");
  delay(200);
  Firebase.setFloat("read/a0", a0After);
  Firebase.setFloat("read/a1", a1After); 
  Firebase.setFloat("read/a2", a2After); 

//A0
    
  if(a0Before<a0After){
    a0 = a0After - a0Before;
      Serial.print("A0 moved "); 
      Serial.print(a0); 
      Serial.println(" degrees clockwise");  
      a0=a0*2.5;
      servoA0.write(99); //Clockwise
      delay(a0);
      servoA0.write(90); //Stop
      delay(2000);     
  }
  if(a0Before>a0After){
    Serial.print("A0 moved "); 
      a0 = a0Before - a0After;
      Serial.print(a0); 
      Serial.println(" degrees anticlockwise"); 
      a0=a0*4.6; //4.5
      servoA0.write(85); // Anti-Clockwise
      delay(a0);
      servoA0.write(90); //Stop
      delay(2000);   
  }
  if(a0Before == a0After){
   // a0Changed = false;
    Serial.print("A0:");
  Serial.println(a0After); 
  a0=0;
  }
  
//A1
  
  if(a1Before<a1After){
      Serial.print("A1 moved "); 
      a1 = a1After - a1Before;
      Serial.print(a1); 
      Serial.println(" degrees clockwise");   
      a1=a1*3; //2.5  2.8
      servoA1.write(99); //Anti-Clockwise
      delay(a1);
      servoA1.write(90); //Stop
      delay(2000);       
  }
  if(a1Before>a1After){
    Serial.print("A1 moved "); 
      a1 = a1Before - a1After;
      Serial.print(a1); 
      Serial.println(" degrees anticlockwise"); 
      a1=a1*4; //3.8
      servoA1.write(84);
//      a1=a1*5;
//      servoA1.write(98); //Anti-Clockwise
      delay(a1);
      servoA1.write(90); //Stop
      delay(2000);   
  }
  if(a1Before == a1After){
    Serial.print("A1:");
  Serial.println(a1After); 
  a1=0;
  }
//A2  

if(a2Before<a2After){
      Serial.print("A2 moved "); 
      a2 = a2After - a2Before;
      Serial.print(a2); 
      Serial.println(" degrees clockwise");     
      a2=a2*4; // 4.5 --- 3.8
      servoA2.write(85); //Clockwise
//      a2=a2*2.5;
//      servoA2.write(99); //Anti-Clockwise
      delay(a2);
      servoA2.write(90); //Stop
      delay(2000);     
  }
  if(a2Before>a2After){
    Serial.print("A2 moved "); 
      a2 = a2Before - a2After;
      Serial.print(a2); 
      Serial.println(" degrees anticlockwise");
//      a2=a2*4;
//      servoA2.write(85); 
       a2=a2*2.9; // 2.5 TP 2.7 TO 2.8
      servoA2.write(99); //Anti-Clockwise
      delay(a2);
      servoA2.write(90); //Stop
      delay(2000);   
  }
  if(a2Before == a2After){
    Serial.print("A2:");
  Serial.println(a2After); 
  a2=0;
  }
 
}
