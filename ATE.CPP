
/*************************************************************************
Title:    Automated Testpoints
Authors:  Futturman<Futturman@yahoo.com>
File:     $Id: $
License:  GNU General Public License v3

LICENSE:
    Copyright (C) 2020 J1Futturman
    #include <Relay16.h>

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

*************************************************************************/
#include <Wire.h>
//#include <LiquidCrystal_I2C.h>
#include <Relay16.h>
#define TCAADDR1 0x70
#define TCAADDR2 0x71
#define TCAADDR3 0x72
Relay16 relayBoard;
int resetPin = 12;

/**************************************/
String inputString = "";              // a string to hold incoming data
boolean stringComplete = false;       // whether the string is complete
String commandString = "";
/**************************************/


void tcaselect(uint8_t sensor,uint8_t module)
{

  if (module==TCAADDR1){ //0x70
 Wire.beginTransmission(TCAADDR2);
 Wire.write(0);
 Wire.endTransmission();

 //Wire.beginTransmission(TCAADDR3);
 //Wire.write(0);
 //Wire.endTransmission();

  }
 else if (module==TCAADDR2){ //0x71
  Wire.beginTransmission(TCAADDR1);
  Wire.write(0);
  Wire.endTransmission();

 // Wire.beginTransmission(TCAADDR3);
// Wire.write(0);
// Wire.endTransmission();

}

 if (module==TCAADDR3){ //0x73
  Wire.beginTransmission(TCAADDR1);
  Wire.write(0);
  Wire.endTransmission();

  Wire.beginTransmission(TCAADDR2);
  Wire.write(0);
  Wire.endTransmission();

}

 Wire.beginTransmission(module);
 Wire.write(1<<sensor);
 Wire.endTransmission();

}

void loop()
{

if(stringComplete)
{
  stringComplete = false;
  getCommand();

  if(commandString.equals("STAR"))

    {
      starttest();
    }
   inputString = "";
 if(commandString.equals("CON1"))

    {
      s1Off();

    }
inputString = "";
     if(commandString.equals("CON2"))

    {
      s2On();

    }
inputString = "";
     if(commandString.equals("CON3"))

    {
      s2Off();

    }
inputString = "";
     if(commandString.equals("CON4"))

    {
      s3On();

    }
inputString = "";
     if(commandString.equals("CON5"))

    {
      s3Off();

    }
inputString = "";
     if(commandString.equals("CON6"))

    {
      s4On();

    }
inputString = "";
     if(commandString.equals("CON7"))

    {
      s4Off();

    }

inputString = "";
   
    if(commandString.equals("RESE"))

    {
      ArduinoReset();

     }

    inputString = "";
 }

}


void setup() {


  //////////////////RESET/////////////////
  digitalWrite(resetPin, HIGH);
  delay(200);
  // initialize the digital pin as an output.

  pinMode(resetPin, OUTPUT);
  Serial.begin(9600);

  delay(200);
  ////////////////////////////////////////////

 pinMode(LED_BUILTIN, OUTPUT);

 Serial.println("=============================================================");
 Serial.println("                   \nAUTOMATIC BREAKOUT BOX TEST                   ");
 Serial.println("==============================================================");
 Serial.println("Test in progress");
 Serial.read();
 }

void ArduinoReset()
{

 delay(100); // wait
 Serial.println("resetting");
 delay(300);

 /**Starts the I2C**/
/**Wire.begin();**/

/**STACK 0**/
//relayBoard.begin(LOW, LOW, LOW, 4);
//tcaselect(0, TCAADDR1);

//relayBoard.relayOn(9);
//relayBoard.relayOn(8);


//    relayBoard.relayOff(9);
//    relayBoard.relayOff(8);
//   delay(100);
}




void con_ohm()

{

  /**Starts the I2C**/
 Wire.begin();

/**STACK 0**/
relayBoard.begin(LOW, LOW, LOW, 4);
tcaselect(0, TCAADDR1);

relayBoard.relayOn(9);
relayBoard.relayOn(8);

}

void SoloOn()
{
Wire.begin();
Serial.println("Initiating switch Bulbs Test");

relayBoard.begin(HIGH, LOW, HIGH, 4);
tcaselect(0, TCAADDR1);

relayBoard.relayOn(9);
relayBoard.relayOn(8);
}

void Soloff()
{
Wire.begin();
Serial.println("Terminating switch Bulbs Test");

relayBoard.begin(HIGH, LOW, HIGH, 4);
tcaselect(0, TCAADDR1);

relayBoard.relayOff(9);
relayBoard.relayOff(8);


}

void starttest()
{

Wire.begin();
Serial.println("S1 ON Test");
Serial.println("Press S1  ON on the UUT");
Serial.println("Press ENTER when ready.");
////////////;

//**************J2-6(14) and J2-12(5)**************//

//*******************RELAY 14*********************//
relayBoard.begin(LOW, LOW, LOW, 4);
tcaselect(6, TCAADDR1);
relayBoard.relayOn(14);

//*********************RELAY 5*******************//
relayBoard.begin(LOW, LOW, HIGH, 4);
tcaselect(6, TCAADDR1);
relayBoard.relayOn(5);
delay(5);
Serial.println("\n");
Serial.println("Testing J2-6 and J2-12 ");
Cont();
delay(5);

//******************OFF the relays****************//
relayBoard.begin(LOW, LOW, LOW, 4);
tcaselect(6, TCAADDR1);
relayBoard.relayOff(14);
relayBoard.begin(LOW, LOW, HIGH, 4);
tcaselect(6, TCAADDR1);
relayBoard.relayOff(5);
delay(5);
Serial.println("\n");

//**************J2-15(15) to J2-14(3)**************//
Serial.println("Testing J2-15 and J2-14 ");

//******************ON the relays******************//
relayBoard.begin(LOW, LOW, HIGH, 4);
tcaselect(6, TCAADDR1);
relayBoard.relayOn(15);
relayBoard.relayOn(3);
delay(5);
Cont();
delay(5);

//******************OFF the relays******************//
relayBoard.begin(LOW, LOW, HIGH, 4);
tcaselect(6, TCAADDR1);
relayBoard.relayOff(15);
relayBoard.relayOff(3);
delay(5);
Serial.println("\n");

//****************J2-15(15) to J2-13(4)****************//
Serial.println("Testing J2-15 and J2-13 ");

//******************ON the relays******************//
relayBoard.begin(LOW, LOW, HIGH, 4);
tcaselect(6, TCAADDR1);
relayBoard.relayOn(15);
relayBoard.relayOn(4);
delay(5);
NoCon();
Serial.println("\n");
delay(5);

//******************OFF the relays******************//
relayBoard.begin(LOW, LOW, HIGH, 4);
tcaselect(6, TCAADDR1);
relayBoard.relayOff(15);
relayBoard.relayOff(4);
delay(5);
//****************************************************//
Serial.println("\n");
Serial.println("S1 ON test completed");
////////////;

}
//****************************************************//
//*****************END OF S1 ON TEST*****************//
//***************************************************//



//**************************************************//
//*****************START S1 OFF TEST****************//
//**************************************************//

void s1Off()
{
Wire.begin();
Serial.println("\n");
Serial.println("S1 OFF TEST");
//*************J2-6(14) and J2-12(5)*************//

//*************RELAY 14*************//
relayBoard.begin(LOW, LOW, LOW, 4);
tcaselect(6, TCAADDR1);
relayBoard.relayOn(14);
//*************RELAY 5*************//
relayBoard.begin(LOW, LOW, HIGH, 4);
tcaselect(6, TCAADDR1);
relayBoard.relayOn(5);
delay(5);
Serial.println("Testing J2-6 and J2-12 ");
NoCon();
delay(5);

//*****************OFF the relays*****************//
relayBoard.begin(LOW, LOW, LOW, 4);
tcaselect(6, TCAADDR1);
relayBoard.relayOff(14);
relayBoard.begin(LOW, LOW, HIGH, 4);
tcaselect(6, TCAADDR1);
relayBoard.relayOff(5);
delay(5);
///**********************************************//

Serial.println("\n");
//*************J2-15(15) to J2-14(3)*************//
Serial.println("Testing J2-15 and J2-14 ");
relayBoard.begin(LOW, LOW, HIGH, 4);
tcaselect(6, TCAADDR1);
relayBoard.relayOn(15);
relayBoard.relayOn(3);
delay(5);
NoCon();
delay(5);
//*****************OFF the relays*****************//
relayBoard.begin(LOW, LOW, HIGH, 4);
tcaselect(6, TCAADDR1);
relayBoard.relayOff(15);
relayBoard.relayOff(3);
delay(5);
Serial.println("\n");
//**********************************************//

//*************J2-15(15) to J2-13(4)*************//
Serial.println("Testing J2-15 and J2-13 ");
relayBoard.begin(LOW, LOW, HIGH, 4);
tcaselect(6, TCAADDR1);
relayBoard.relayOn(15);
relayBoard.relayOn(4);
delay(5);
Cont();
Serial.println("\n");
delay(500);
//*****************OFF the relays*****************//
relayBoard.begin(LOW, LOW, HIGH, 4);
tcaselect(2, TCAADDR1);
relayBoard.relayOff(15);
//relayBoard.begin(LOW, LOW, HIGH, 4);
tcaselect(2, TCAADDR1);
relayBoard.relayOff(4);
delay(5);
Serial.println("\n");
Serial.println("S1 OFF Test completed");
Serial.read();
}
//****************************************************//
//*****************END OF S1 OFF TEST*****************//
//***************************************************//



//**************************************************//
//*****************START S2 ON TEST*****************//
//**************************************************//

void s2On()
{
Wire.begin();
Serial.println("\n");
Serial.println("S2 ON TEST");
//*************J3-6(14) and J3-13(4)*************/
relayBoard.begin(LOW, LOW, LOW, 4);
tcaselect(7, TCAADDR1);
relayBoard.relayOn(14);
relayBoard.relayOn(4);
delay(5);
Serial.println("Testing J3-6 and J3-13 ");
Cont();
delay(5);

//*****************OFF the relays*****************//
relayBoard.begin(LOW, LOW, LOW, 4);
tcaselect(7, TCAADDR1);
relayBoard.relayOff(14);
relayBoard.relayOff(4);
delay(5);
//************************************************//

//*****************J3-21 to J3-20*****************//
Serial.println("\n");
Serial.println("Testing J3-21 and J3-20 ");

//***************ON RELAY 13 and 5 ***************//
relayBoard.begin(LOW, HIGH,LOW, 4);
tcaselect(7, TCAADDR1);
relayBoard.relayOn(13);
relayBoard.relayOn(5);
delay(5);
Cont();
delay(5);
//*****************OFF the relays*****************//
relayBoard.begin(LOW, HIGH,LOW, 4);
tcaselect(7, TCAADDR1);
relayBoard.relayOff(13);
relayBoard.relayOff(5);
delay(5);
//*********************************************//

//*****************J3-21 to J3-7***************//
Serial.println("\n");
Serial.println("Testing J3-21 and J3-7");
//*****************ON RELAY 13****************//
relayBoard.begin(LOW,HIGH,LOW ,4);
tcaselect(7, TCAADDR1);
relayBoard.relayOn(13);
//*****************RELAY 2*****************//
relayBoard.begin(LOW,LOW,LOW ,4);
tcaselect(7, TCAADDR1);
relayBoard.relayOn(2);
delay(5);
NoCon();
Serial.println("\n");
delay(5);
//*****************Off the relays*****************//
relayBoard.begin(LOW,HIGH,LOW ,4);
tcaselect(7, TCAADDR1);
relayBoard.relayOff(13);
relayBoard.begin(LOW,LOW,LOW, 4);
tcaselect(7, TCAADDR1);
relayBoard.relayOff(2);
delay(5);
Serial.println("\n");
Serial.println("S2 ON test completed");

}
//****************************************************//
//*****************END OF S2 ON TEST*****************//
//***************************************************//




//**************************************************//
//*****************START S2 OFF TEST*****************//
//**************************************************//
void s2Off()
{
Wire.begin();
Serial.println("\n");
Serial.println("S2 OFF TEST");
//*****************J3-6(14) and J3-13(4)*****************//
//*****************RELAY 14 and 4*****************//
relayBoard.begin(LOW, LOW, LOW, 4);
tcaselect(7, TCAADDR1);
relayBoard.relayOn(14);
relayBoard.relayOn(4);
delay(5);
Serial.println("Testing J3-6 and J3-13 ");
NoCon();
delay(5);
//*****************Off the relays*****************//
relayBoard.begin(LOW, LOW, LOW, 4);
tcaselect(7, TCAADDR1);
relayBoard.relayOff(14);
relayBoard.relayOff(4);
delay(5);
//**********************************************//

//*************J3-21(13) to J3-20(5)*************//
Serial.println("\n");
Serial.println("Testing J3-21 and J3-20 ");

//**************ON RELAY 13 and 5 **************//
relayBoard.begin(LOW, HIGH,LOW, 4);
tcaselect(7, TCAADDR1);
relayBoard.relayOn(13);
relayBoard.relayOn(5);
delay(5);
NoCon();
delay(5);
//*****************Off the relays*****************//
relayBoard.begin(LOW, HIGH,LOW, 4);
tcaselect(7, TCAADDR1);
relayBoard.relayOff(13);
relayBoard.relayOff(5);
delay(5);
//***********************************************//

//**************J3-21(13) to J3-7(2)*************//
Serial.println("\n");
Serial.println("Testing J3-21 and J3-7");

//****************ON RELAY 13*******************//
relayBoard.begin(LOW,HIGH,LOW ,4);
tcaselect(7, TCAADDR1);
relayBoard.relayOn(13);
//****************ON RELAY 2*******************//
relayBoard.begin(LOW,LOW,LOW ,4);
tcaselect(7, TCAADDR1);
relayBoard.relayOn(2);
delay(5);
Cont();
Serial.println("\n");
delay(5);
//*****************Off the relays*****************//
relayBoard.begin(LOW,HIGH,LOW ,4);
tcaselect(7, TCAADDR1);
relayBoard.relayOff(13);

relayBoard.begin(LOW,LOW,LOW ,4);
tcaselect(7, TCAADDR1);
relayBoard.relayOff(2);

delay(5);
Serial.println("\n");
Serial.println("S2 OFF test completed");  
////////////
}
//****************************************************//
//*****************END OF S2 OFF TEST*****************//
//***************************************************//



//**************************************************//
//*****************START S3 ON TEST*****************//
//**************************************************//

void s3On()
{
Wire.begin();
Serial.println("\n");
Serial.println("S3 ON TEST");
Serial.println("\n");

//***************J2-5(13) and J2-11(6)***************//
//**********************RELAY 13********************//
relayBoard.begin(LOW, LOW, LOW, 4);
tcaselect(6, TCAADDR1);
relayBoard.relayOn(13);
//********************RELAY 6*********************//
relayBoard.begin(LOW, LOW, HIGH, 4);
tcaselect(6, TCAADDR1);
relayBoard.relayOn(6);
delay(5);
Serial.println("Testing J2-5 and J2-11 ");
Cont();
delay(5);

//***************OFF THE RELAYS***************//
relayBoard.begin(LOW, LOW, LOW, 4);
tcaselect(6, TCAADDR1);
relayBoard.relayOff(13);
relayBoard.begin(LOW, LOW, HIGH, 4);
tcaselect(7, TCAADDR1);
relayBoard.relayOff(6);
delay(5);
//********************************************//


//*************J2-18(10) to J2-17(8)**********//
Serial.println("\n");
Serial.println("Testing J2-18 and J2-17 ");
//*************ON RELAY 10 and 8*************//
relayBoard.begin(LOW,HIGH, LOW, 4);
tcaselect(6, TCAADDR1);
relayBoard.relayOn(10);
relayBoard.relayOn(8);
delay(5);
Cont();
delay(5);
//***************OFF the relays***************//
relayBoard.begin(LOW,HIGH, LOW, 4);
tcaselect(6, TCAADDR1);
relayBoard.relayOff(10);
relayBoard.relayOff(8);
delay(5);

//********************************************//
//************J2-18(10) to J2-16(1)************//
Serial.println("\n");
Serial.println("Testing J2-18 and J2-16 ");

//***************ON RELAY 10 and 1***************//
relayBoard.begin(LOW,HIGH, LOW, 4);
tcaselect(6, TCAADDR1);
relayBoard.relayOn(10);
relayBoard.begin(LOW,LOW,HIGH, 4);
tcaselect(6, TCAADDR1);
relayBoard.relayOn(1);
delay(5);
NoCon();
//***************OFF THE RELAYS*****************//
relayBoard.begin(LOW,HIGH, LOW, 4);
tcaselect(6, TCAADDR1);
relayBoard.relayOff(10);
relayBoard.begin(LOW,LOW, HIGH, 4);
tcaselect(6, TCAADDR1);
relayBoard.relayOff(1);
delay(5);
Serial.println("\n");
Serial.println("S3 ON test completed");
////////////;
}
//****************************************************//
//*****************END OF S3 ON TEST*****************//
//***************************************************//


//****************************************************//
//*****************START S3 OFF TEST*****************//
//****************************************************//

void s3Off()
{
Wire.begin();
Serial.println("\n");
Serial.println("S3 OFF TEST");
Serial.println("\n");
//***************J2-5(13) and J2-11(6)************//

//********************RELAY 13********************//
relayBoard.begin(LOW, LOW, LOW, 4);
tcaselect(6, TCAADDR1);
relayBoard.relayOn(13);

//*****************RELAY 6**********************//
relayBoard.begin(LOW, LOW, HIGH, 4);
tcaselect(6, TCAADDR1);
relayBoard.relayOn(6);
delay(5);
Serial.println("Testing J2-5 and J2-11 ");
NoCon();
delay(5);

//***************OFF THE RELAYS*****************//
relayBoard.begin(LOW, LOW, LOW, 4);
tcaselect(6, TCAADDR1);
relayBoard.relayOff(13);
relayBoard.begin(LOW, LOW, HIGH, 4);
tcaselect(6, TCAADDR1);
relayBoard.relayOff(6);
delay(5);
//**********************************************//


//*****************J2-18 to J2-17*****************//
Serial.println("\n");
Serial.println("Testing J2-18 and J2-17 ");

//*****************ON RELAY 10 and 8*****************//
relayBoard.begin(LOW,HIGH, LOW, 4);
tcaselect(6, TCAADDR1);
relayBoard.relayOn(10);
relayBoard.relayOn(8);
delay(5);
NoCon();
delay(5);

//*****************OFF the relays*****************//
relayBoard.begin(LOW,HIGH, LOW, 4);
tcaselect(6, TCAADDR1);
relayBoard.relayOff(10);
relayBoard.relayOff(8);
delay(5);
//**********************************************//


//*****************J2-18 to J2-16*****************//
Serial.println("\n");
Serial.println("Testing J2-18 and J2-16 ");

//////////ON RELAY 10 and 1/////////
relayBoard.begin(LOW,HIGH, LOW, 4);
tcaselect(6, TCAADDR1);
relayBoard.relayOn(10);
relayBoard.begin(LOW,LOW,HIGH, 4);
tcaselect(6, TCAADDR1);
relayBoard.relayOn(1);
delay(5);
Cont();

///OFF the relays//////
relayBoard.begin(LOW,HIGH, LOW, 4);
tcaselect(6, TCAADDR1);
relayBoard.relayOff(10);

relayBoard.begin(LOW,LOW, HIGH, 4);
tcaselect(6, TCAADDR1);
relayBoard.relayOff(1);
delay(5);
Serial.println("\n");
Serial.println("S3 OFF test completed");
////////////;
}
//******************************************************//
//*****************E N D  S3 OFF************************//
//******************************************************//


//******************************************************//
//*****************START S4 ON**************************//
//******************************************************//

void s4On()
{
Wire.begin();
Serial.println("\n");
Serial.println("S4 ON TEST");
Serial.println("\n");

//***************J3-5(13) and J3-12(14)***************//
//**********************RELAY 13**********************//
relayBoard.begin(LOW, LOW, LOW, 4);
tcaselect(7, TCAADDR1);
relayBoard.relayOn(13);
//********************RELAY 4***********************//
relayBoard.begin(LOW, LOW, HIGH, 4);
tcaselect(7, TCAADDR1);
relayBoard.relayOn(4);
delay(5);
Serial.println("Testing J3-5 and J3-12 ");
Cont();
delay(5);

//******************OFF THE RELAYS******************//
relayBoard.begin(LOW, LOW, LOW, 4);
tcaselect(7, TCAADDR1);
relayBoard.relayOff(13);
relayBoard.begin(LOW, LOW, HIGH, 4);
tcaselect(7, TCAADDR1);
relayBoard.relayOff(4);
delay(5);
//************************************************//


//*************J3-18(10) to J3-17(8)**********//
Serial.println("\n");
Serial.println("Testing J3-18 and J3-17 ");
//*************ON RELAY 10 and 8*************//
relayBoard.begin(LOW,HIGH, LOW, 4);
tcaselect(7, TCAADDR1);
relayBoard.relayOn(10);
relayBoard.relayOn(8);
delay(5);
Cont();
delay(5);

//***************OFF the relays***************//
relayBoard.begin(LOW,HIGH, LOW, 4);
tcaselect(7, TCAADDR1);
relayBoard.relayOff(10);
relayBoard.relayOff(8);
delay(5);

//********************************************//
//************J3-18(10) to J3-16(1)************//
Serial.println("\n");
Serial.println("Testing J3-18 and J3-16 ");

//***************ON RELAY 10 and 1***************//
relayBoard.begin(LOW,HIGH, LOW, 4);
tcaselect(7, TCAADDR1);
relayBoard.relayOn(10);
relayBoard.begin(LOW,LOW,HIGH, 4);
tcaselect(7, TCAADDR1);
relayBoard.relayOn(1);
delay(5);
NoCon();

//***************OFF THE RELAYS*****************//
relayBoard.begin(LOW,HIGH, LOW, 4);
tcaselect(7, TCAADDR1);
relayBoard.relayOff(10);
relayBoard.begin(LOW,LOW, HIGH, 4);
tcaselect(7, TCAADDR1);
relayBoard.relayOff(1);
delay(5);
Serial.println("\n");
Serial.println("S4 ON test completed");
////////////;

}
//////////////////////////////////////////////////////
//*********************END S4 ON********************//
//////////////////////////////////////////////////////


//////////////////////////////////////////////////////
//*****************START S4 OFF**********************//
//////////////////////////////////////////////////////

void s4Off()
{

Wire.begin();
Serial.println("\n");
Serial.println("S4 OFF TEST");
Serial.println("\n");

//***************J3-5(13) and J3-12(14)***************//
//**********************RELAY 13**********************//
relayBoard.begin(LOW, LOW, LOW, 4);
tcaselect(7, TCAADDR1);
relayBoard.relayOn(13);
//********************RELAY 4***********************//
relayBoard.begin(LOW, LOW, HIGH, 4);
tcaselect(7, TCAADDR1);
relayBoard.relayOn(4);
delay(5);
Serial.println("Testing J3-5 and J3-12 ");
NoCon();
delay(5);

//******************OFF THE RELAYS******************//
relayBoard.begin(LOW, LOW, LOW, 4);
tcaselect(7, TCAADDR1);
relayBoard.relayOff(13);
relayBoard.begin(LOW, LOW, HIGH, 4);
tcaselect(7, TCAADDR1);
relayBoard.relayOff(4);
delay(5);
//************************************************//


//*************J3-18(10) to J3-17(8)**********//
Serial.println("\n");
Serial.println("Testing J3-18 and J3-17 ");
//*************ON RELAY 10 and 8*************//
relayBoard.begin(LOW,HIGH, LOW, 4);
tcaselect(7, TCAADDR1);
relayBoard.relayOn(10);
relayBoard.relayOn(8);
delay(5);
NoCon();
delay(5);

//***************OFF the relays***************//
relayBoard.begin(LOW,HIGH, LOW, 4);
tcaselect(7, TCAADDR1);
relayBoard.relayOff(10);
relayBoard.relayOff(8);
delay(5);

//********************************************//
//************J3-18(10) to J3-16(1)************//
Serial.println("\n");
Serial.println("Testing J3-18 and J3-16 ");

//***************ON RELAY 10 and 1***************//
relayBoard.begin(LOW,HIGH, LOW, 4);
tcaselect(7, TCAADDR1);
relayBoard.relayOn(10);
relayBoard.begin(LOW,LOW,HIGH, 4);
tcaselect(7, TCAADDR1);
relayBoard.relayOn(1);
delay(5);
Cont();

//***************OFF THE RELAYS*****************//
relayBoard.begin(LOW,HIGH, LOW, 4);
tcaselect(7, TCAADDR1);
relayBoard.relayOff(10);
relayBoard.begin(LOW,LOW, HIGH, 4);
tcaselect(7, TCAADDR1);
relayBoard.relayOff(1);
delay(5);
Serial.println("\n");
Serial.println("S4 OFF test completed");
////////////;

}
////////////////////////////////////////////////////////
///*****************END S4 OFF************************//
////////////////////////////////////////////////////////

void Cont()

{

int Vin=5;        //voltage at 5V pin of arduino
float Vout=0;     //voltage at A0 pin of arduino
float R1=1020;    //value of known resistance
float R2=0;       //value of unknown resistance
int a2d_data=0;
float buffer=0;


  delay(100);
  a2d_data=analogRead(A0);
  delay(100);

  if(a2d_data)
  {
    buffer=a2d_data*Vin;
    Vout=(buffer)/1024.0;
    buffer=(Vin/Vout)-1;
    R2=R1*buffer;
  if ( R2<100)
  {
     Serial.print(R2);
     Serial.print("\t");
     Serial.print("ohms");
     Serial.print("\t");
     Serial.print(" CON  :  PASS");

  }
//
  else if

        ( R2> 100)
        {

       Serial.print(R2);
       Serial.print("\t");
       Serial.print(" NO CON  :  FAIL");
        }

    delay(1000);

    }

    }

////////no con check/////////////
void NoCon()

{

int Vin=5;        //voltage at 5V pin of arduino
float Vout=0;     //voltage at A0 pin of arduino
float R1=1020;    //value of known resistance
float R2=0;       //value of unknown resistance
int a2d_data=0;
float buffer=0;
int x;

    // con_ohm();

  delay(100);
  a2d_data=analogRead(A0);
  delay(100);

  if(a2d_data)
  {
    buffer=a2d_data*Vin;
    Vout=(buffer)/1024.0;
    buffer=(Vin/Vout)-1;
    R2=R1*buffer;
    if ( R2<= 100)
    {

      Serial.print(" CON  :    FAIL ");

    }

 else if (R2>=1000)
    {
      Serial.print(" NO CON :  PASS ");
    }

    delay(1000);
    }

    }


   void waitForSerial()
  {
  while (!Serial.available())
  {
  }
  }

 void getCommand()
   {
  if(inputString.length()>0)
    {
     commandString = inputString.substring(1,5);
   }
   }


void turnLedOn(int pin)
{
  digitalWrite(pin,HIGH);
}

void turnLedOff(int pin)
{
  digitalWrite(pin,LOW);
}

void serialEvent() {
  while (Serial.available()) {
    // get the new byte:
    char inChar = (char)Serial.read();
    // add it to the inputString:h
    inputString += inChar;
    // if the incoming character is a newline, set a flag
    // so the main loop can do something about it:
    if (inChar == '\n') {
      stringComplete = true;
    }
  }
}
