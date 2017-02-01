#include "Wire.h"
#include "I2Cdev.h"
#include "HMC5883L.h"

#include<PS2X_lib.h>
//=============================================================================
//PS2 SETUP
#define CLOCK 44
#define ATTENTION 48
#define DATA 43
#define COMMAND 49
#define BAUD_RATE 115200
//=============================================================================

#define lim 100
#define MainPiston A12
PS2X ps2x;
boolean up = 0, down = 0, left, right, triangle = 0, sqr = 0, cross = 0, circle = 0, r1 = 0, r2 = 0, p_r2 = 0, l1 = 0, l2 = 0, p_l2 = 0, r3 = 0, l3 = 0, start = 0, select = 0;

boolean start_flag = 0;
int RY = 0, RX, LY = 0, LX = 0;

float pw, fpw;
float ra = 0.98; //weight for turn X,Y
float fRY, fRX, fLY, fLX;
float a = 0.99; //weight for X,Y
float magnitude, theta;

void readButtons();// to check the value of PS2 buttons
void printState(); // to print/read the value of PS2 buttons

int pwmA = 0, pwmB = 0, pwmC = 0;
int TRN_PWM = 70;

static int flag = 0;
static int p = 50;
static int dir = 1;

float rpwm = 0, rpma = 0.5, frpwm = 0;
HMC5883L mag;

int16_t mx, my, mz;
float fheading, ma = 0.85;

void setup()
{
  Wire.begin();
  Serial.begin(BAUD_RATE);

  mag.initialize();
  Serial.println(mag.testConnection() ? "HMC5883L connection successful" : "HMC5883L connection failed");
  ps2x.config_gamepad(CLOCK, COMMAND, ATTENTION, DATA); // (clock(blue),command(orange), attention(yellow), data(brown))

  Serial1.begin(19200);
  Serial2.begin(19200);

  Serial.flush();
  Serial1.flush();
  Serial2.flush();
  delay(1000);
}

void loop()
{
  readButtons();

  frpwm = frpwm * rpma + rpwm * (1 - rpma);

  if (l1)
  {
    dir = 1;
  }
  if (l2)
  {
    dir = 2;
  }

  if (r1 || r2)
    pw = r1 > r2 ? TRN_PWM : -TRN_PWM;
  else
    pw = 0;
  mag.getHeading(&mx, &my, &mz);
  float heading = atan2(my, mx);
  if (heading < 0)
    heading += 2 * M_PI;
  heading = heading * 180 / M_PI;
  fheading = fheading * ma + heading * (1 - ma);

  omni();
  control(theta); //omni control


  //    Serial.println(fheading);
  //  printState();
}











