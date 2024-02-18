int counter = 0;
//count the numbers of turn  //Remember to change back counter to 0, uncomment initialise, soft=false
int i =0;

void left90(){     //turn 90degrees to left
  Serial.println("LEFT90");
  forward();
  delay(500);
  RightMotor->setSpeed(150);
  LeftMotor->setSpeed(150);
  LeftMotor->run(BACKWARD);
  RightMotor->run(FORWARD);
  delay(1000);
  while(svr==LOW){
    Serial.println("INSIDEWHILELOOP");
    LeftMotor->run(BACKWARD);
    RightMotor->run(FORWARD);
    svr=digitalRead(sr);
  }
}

void right90(){  //turn right 90
  Serial.println("RIGHT90"); 
  forward();
  delay(500);
  RightMotor->setSpeed(150);
  LeftMotor->setSpeed(150);
  LeftMotor->run(FORWARD);
  RightMotor->run(BACKWARD);
  delay(1500);
  while(svl==LOW){
    Serial.println("INSIDEWHILELOOP");
    LeftMotor->run(FORWARD);
    RightMotor->run(BACKWARD);
    svl=digitalRead(sl);
 }
}

void hardleft90(){      //turn left faster
  Serial.println("LEFT90");    
        RightMotor->setSpeed(200);
        LeftMotor->setSpeed(0);
        LeftMotor->run(FORWARD);
        RightMotor->run(FORWARD);
        delay(2000);
        while(svr==LOW){
            Serial.println("INSIDEWHILELOOP");
            LeftMotor->run(BACKWARD);
            RightMotor->run(FORWARD);
            svr=digitalRead(sr);
        }
}

void hardright90(){    //turn right faster
   Serial.println("RIGHT90"); 
    RightMotor->setSpeed(0);
    LeftMotor->setSpeed(200);
    LeftMotor->run(FORWARD);
    RightMotor->run(FORWARD);
    delay(2000);
    while(svl==LOW){
        Serial.println("INSIDEWHILELOOP");
        LeftMotor->run(FORWARD);
        RightMotor->run(BACKWARD);
        svl=digitalRead(sl);
     }
}

void counterfunction(){
Serial.println(counter);
if (counter == 0)
{
 left90();
  }
  counter++; 
  }
  
else if (counter == 1)   //Moving into the junction
{
  right90();
    LeftMotor->run(FORWARD);  //turn a bit move to face forward
    RightMotor->run(BACKWARD);
    delay(100);
    release();
  counter++;
  }


else if (counter == 2) //Sensing and detecting the block
{ 
    stop();
    ultrasensor(ultrasensor_reading()); 
    grab();
    delay(700);
    lift();
    backward();
    delay(400);
    svvl = LOW;
    svvr = LOW;
    while(svvl == LOW && svvr == LOW){
      Serial.println("BACKWARD");
      backward();    
      svvr=digitalRead(ssr);
      svvl=digitalRead(ssl);
    }
    backward();
    delay(500);
    if (SOFT == true) {    //TURN LEFT to the way back to the zone if SOFT
        hardleft90();
      }
    else {                        //Turn RIGHT to the way back to the zone if HARD
   hardright90();
    }
    counter++;
    }


else if (counter == 3) //moving into junction of the putting zone
{
if (SOFT == true) 
{
left90();
}

else 
{                    //TURN RIGHT to the way back to the zone if HARD
right90();
}
counter++;
}

else if (counter==4)    //Putting the block and linetracking until the second line
  {
    LeftMotor->run(RELEASE);
    RightMotor->run(RELEASE);
    puttingdown();
    release();
    svvl = LOW;
    svvr = LOW;
    backward();
    delay(1000);

    if (SOFT==true){
    RightMotor->setSpeed(150);
    LeftMotor->setSpeed(150);
    LeftMotor->run(BACKWARD);
    RightMotor->run(FORWARD);
    delay(1500);
    svr=digitalRead(sr);
    while(svr==LOW){
    Serial.println("TURN180");
    LeftMotor->run(BACKWARD);
    RightMotor->run(FORWARD);
    svr=digitalRead(sr);
    }
    }
    else{
    RightMotor->setSpeed(150);
    LeftMotor->setSpeed(150);
    LeftMotor->run(FORWARD);
    RightMotor->run(BACKWARD);
    delay(1500);
    svl=digitalRead(sl);
    while(svl==LOW){
    Serial.println("TURN180");
    LeftMotor->run(FORWARD);
    RightMotor->run(BACKWARD);
    svl=digitalRead(sl);
    }
    }
    i=0;
    while(i<2){
      linetracking();
      Serial.println("LINETRACKING");
      svvr=digitalRead(ssr);
      svvl=digitalRead(ssl);
      if (svvl == HIGH || svvr == HIGH){
        Serial.println("DETECTWHITELINE");
        i+=1;
        delay(800);
      }
    }
if (SOFT == false) {
        hardleft90();      //turn left
      }
else {                        //Turn RIGHT to the way back to the zone if SOFT
   hardright90();
    }
  counter++;
  }


  else if (counter == 5)
  {
  if (SOFT == true) {       //Turn Right into the second block junction if SOFT
 right90();
    LeftMotor->run(FORWARD);
    RightMotor->run(BACKWARD);
    delay(100);
  
    }
    else {                //Turn Left into the second block junction if HARD
  left90();
    LeftMotor->run(BACKWARD);
    RightMotor->run(FORWARD);
    delay(100);
    }
    counter++;
  }


  else if (counter == 6)   //Sensing the second block and backwardlinetracking and turn
  {
    stop();
    ultrasensor(ultrasensor_reading()); 
    grab();
    delay(700);
    lift();
    backward();
    delay(400);
    svvl = LOW;
    svvr = LOW;
    while(svvl == LOW && svvr == LOW){
      Serial.println("BACKWARD");
      backward();     //Backward linetracking
      svvr=digitalRead(ssr);
      svvl=digitalRead(ssl);
    }
    backward();
    delay(300);
 
    if (SOFT == false) {
        hardleft90();
      }
    else {                        //Turn RIGHT to the way back to the zone if HARD
  hardright90();
    }
  counter++;
  }


  else if (counter == 7)   //Turning to the way back to the putting zone for the second block
  {
  if (SOFT == true) {
  left90();
    }

  else {                        
  right90();
    }
  counter++;
  }


 else if (counter == 8){   //Putting the second block and backwardlinetracking till second line
  LeftMotor->run(RELEASE);
  RightMotor->run(RELEASE);
  puttingdown();
  release();
  svvl = LOW;
  svvr = LOW;
  backward();
  delay(1000);
  if (SOFT==true){
   left90();
    }
    else{
right90();
    }
    i=0;
  while(i<1){
    linetracking();
    Serial.println("LINETRACKING");
    svvr=digitalRead(ssr);
    svvl=digitalRead(ssl);
    if (svvl == HIGH || svvr == HIGH){
      Serial.println("DETECTWHITELINE");
      i+=1;
      delay(800);
    }
  }
  
  if (SOFT == false) {   //TURN LEFT to the way back to the zone if HARD
 hardleft90();
      }
  
  else {                        //Turn RIGHT to the way back to the zone if SOFT
      hardright90();
      }
    counter++;
  }


else if (counter == 9){   //Turning back to the end zone
 if (SOFT == true) {
 right90();
    LeftMotor->run(FORWARD);
    RightMotor->run(BACKWARD);
    delay(100);
    }
else {                        
  left90();
    LeftMotor->run(BACKWARD);
    RightMotor->run(FORWARD);
    delay(100);
    }
counter++;
}


else if(counter == 10){        //Go back to the starting point
  forward();
  delay(1900);
  stop();
  delay(1000000000);                 
}
}
