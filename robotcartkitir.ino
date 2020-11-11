//www.elegoo.com

#include <IRremote.h>

#define RECV_PIN  12        //Infrared signal receiving pin
#define LED       13        //define LED pin
#define F 16736925  // FORWARD
#define B 16754775  // BACK
#define L 16720605  // LEFT
#define R 16761405  // RIGHT
#define S 16712445  // STOP
#define UNKNOWN_F 5316027     // FORWARD
#define UNKNOWN_B 2747854299  // BACK
#define UNKNOWN_L 1386468383  // LEFT
#define UNKNOWN_R 553536955   // RIGHT
#define UNKNOWN_S 3622325019  // STOP
#define REPEAT 0xFFFFFFFF
#define KEY1 16738455
#define KEY2 16750695
#define KEY3 16756815
#define KEY4 16724175
#define KEY5 16718055
#define KEY6 16743045
#define OK 0xFF02FD
// car control 
// define IO pin
#define ENA 5
#define ENB 6
#define IN1 7
#define IN2 8
#define IN3 9
#define IN4 11
typedef unsigned char u8;  //Change the name of unsigned char to u8


//bool state = LOW;           //define default input mode
unsigned long val; 
unsigned long state;
unsigned long speed = 1;

bool b_move = false;

IRrecv irrecv(RECV_PIN);   //initialization
decode_results results;   //Define structure type


void display_speed()
{
  Serial.println(speed);
}


void execute_state()
{
 u8 motor_speed = map(speed, 0, 6, 0, 255);
    switch(state)
    {
      case L:
      case UNKNOWN_L:
        left(motor_speed);
        break;
      case R:
      case UNKNOWN_R:
        right(motor_speed);
        break;
      case F:
      case UNKNOWN_F:
        forward(motor_speed);
        break;
     case B:
     case UNKNOWN_B:
        back(motor_speed);
        break;
     case S:
        stop();
    }
}

void forward(u8 car_speed)
{
  Serial.print("Forward, speed "); Serial.println(car_speed);
  if (b_move)
  {
  analogWrite(ENA, car_speed);
  analogWrite(ENB, car_speed);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  }
}


void back(u8 car_speed)
{
Serial.print("Backward, speed "); Serial.println(car_speed);
  if (b_move)
  {
  analogWrite(ENA, car_speed);
  analogWrite(ENB, car_speed);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  }
}


void left(u8 car_speed)
{
Serial.print("Left, speed "); Serial.println(car_speed);
  if (b_move)
  {
  analogWrite(ENA, car_speed);
  analogWrite(ENB, car_speed);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);

  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  }
}

void right(u8 car_speed)
{
  Serial.print("Right, speed "); Serial.println(car_speed);
  if (b_move)
  {
  analogWrite(ENA, car_speed);
  analogWrite(ENB, car_speed);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  }
}

void stop()
{
  digitalWrite(ENA, LOW);
  digitalWrite(ENB, LOW);
}

void togle_move()
{
  b_move = !b_move;
  if (b_move)
  {
    Serial.println("Move enabled.");
  }
  else
  {
    Serial.println("Move disabled.");
  }
}


void setup() {
  pinMode(IN1,OUTPUT);//before useing io pin, pin mode must be set first 
  pinMode(IN2,OUTPUT);
  pinMode(IN3,OUTPUT);
  pinMode(IN4,OUTPUT);
  pinMode(ENA,OUTPUT);
  pinMode(ENB,OUTPUT);
  
  pinMode(LED, OUTPUT); //initialize LED as an output
  Serial.begin(9600);  // debug output at 9600 baud
  irrecv.enableIRIn();  // Start receiving
}

void loop() {
  if (irrecv.decode(&results)) { 
    val = results.value;
    Serial.println(val, HEX);
    irrecv.resume();      // Receive the next value
    delay(150);
    switch(val)
    {
      case L:
      case R:
      case F:
      case B:
        state = val;
        break;
      case REPEAT:
        break;
      // Deal with the speed
      case KEY1:
        speed = 1;
        break;
      case KEY2:
        speed = 2;
        break;
      case KEY3:
        speed = 3;
        break;
      case KEY4:
        speed = 4;
        break;
      case KEY5:
        speed = 5;
        break;
      case KEY6:
        speed = 6;
        break;
      case OK:
        togle_move();
        break;
      
        
    }
    
  }
  else
  {
    state = S;
  } 
  execute_state();
}
