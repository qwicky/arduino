#include <SoftwareSerial.h>

#include <SD.h>                      // need to include the SD library
#define SD_ChipSelectPin 53  //using digital pin 4 on arduino nano 328
#include <TMRpcm.h>           //  also need to include this library...
#include <SPI.h>

TMRpcm tmrpcm;   // create an object for use in this sketch
 
  

#define NUM_OF_LEDS 5
int led[NUM_OF_LEDS];

int socketIn1 = 6;
int socketIn2 = 5;
int socketIn3 = 7;
int counter = 0;

void setup()

{
  Serial.begin(9600);  
  Serial.println("Setup begin");
  for(int i = 0; i<NUM_OF_LEDS;i++)
  {
    if(i+8<11)
    {
      led[i] = i+8;
    }
    else
    {
      led[i] = i+9;
    }
    pinMode(led[i], OUTPUT);
  }  
  pinMode(socketIn1,INPUT);
  pinMode(socketIn2,INPUT);
  pinMode(socketIn3,INPUT);


  tmrpcm.speakerPin = 11; //11 on Mega, 9 on Uno, Nano, etc
 
  if (!SD.begin(SD_ChipSelectPin)) {  // see if the card is present and can be initialized:
    Serial.println("no sd");
  //return;   // don't do anything more if not
  }
 tmrpcm.volume(40);

    for(int i = 0; i<NUM_OF_LEDS;i++)
    {
      digitalWrite(led[i], HIGH);
    }
   // delay(2000);

pinMode(A0,INPUT);
Serial.println("Setup end");
}

int play_mode = 0;

void loop()

{
/*
    for(int i = 0; i<NUM_OF_LEDS;i++)
    {
       {
        digitalWrite(led[i], HIGH);
       }
    }  
  */
  
  Serial.println("LOOP");
  int val1 = digitalRead(socketIn1);
  int val2 = digitalRead(socketIn2);
  int val3 = digitalRead(socketIn3);
  if(val1 == HIGH )
  {
    if(play_mode == 0)
    {
      play_mode = 1;
      tmrpcm.play("1.wav");
                                                                 
    } 

    Serial.println("CONNECT");
  }
  else
  {
    if(play_mode == 1)
    {
      play_mode = 0;              
      tmrpcm.disable();                                             
    }
  }
  {
    for(int i = 0; i<NUM_OF_LEDS;i++)
    {
       if(!((i==1 && val1 == HIGH) || (i==2 && val2 == HIGH) || (i==3 && val3 == HIGH)) )
       {
        digitalWrite(led[i], LOW);
       }
       else
       {
        digitalWrite(led[i], HIGH);
       }
    }  

    //delay(1000);

    for(int i = 0; i<NUM_OF_LEDS;i++)
    {
      if((counter%NUM_OF_LEDS)==i)
      {
      //  digitalWrite(led[i], HIGH);
      }
    }
    //delay(1000);
  }
  counter++;
  
/*
int val = digitalRead(inpin);  // read input value
  if (val == HIGH) {         // check if the input is HIGH (button released)
    digitalWrite(led2, LOW);  // turn LED OFF
  } else {
    digitalWrite(led2, HIGH);  // turn LED ON
  }

*/
  int val = analogRead(A0);
  Serial.println(val);             // debug value

}
