#include "Wire.h"
#include "I2Cdev.h"
#include "HMC5883L.h"s
//=============================================================================
#include<PS2X_lib.h>
//=============================================================================
//PS2 SETUP
#define CLOCK     25  //blue
#define ATTENTION 31  //yellow
#define DATA      27  //brown
#define COMMAND   29  //orange
#define BAUD_RATE 115200
//=============================================================================
PS2X ps2x;

#define lim 100
#define lim1 120

char ch;
boolean up = 0, down = 0, left, right, triangle = 0, sqr = 0, cross = 0, circle = 0, r1 = 0, r2 = 0, p_r2 = 0, l1 = 0, l2 = 0, p_l2 = 0, r3 = 0, l3 = 0, start = 0, select = 0;
int RY = 0, RX, LY = 0, LX = 0;
float pw, fpw;
float ra = 0.47; //weight for turn X,Y
float fRY, fRX, fLY, fLX;
float a = 0.946; //weight for X,Y
float magnitude, theta;
float delta = 1;
void readButtons();// to check the value of PS2 buttons
void printState(); // to print/read the value of PS2 buttons

int pwmA = 0, pwmB = 0, pwmC = 0;
int TRN_PWM = 65;
float fx_ang = 185;
static int dir = 1;
int mag_flg = 0;
float rpwm = 0, rpma = 0.35, frpwm = 0;
HMC5883L mag;
int mp_flg = 0;

boolean flag_move = 0;
static int flag = 0, rflag = 0;
static int p = 50;

int16_t mx, my, mz;
float fheading, ma = 0.82;
int type = 1;
void setup()
{
  Wire.begin();
  type = ps2x.config_gamepad(CLOCK, COMMAND, ATTENTION, DATA); // (clock(blue),command(orange), attention(yellow), data(brown))
  Serial.begin(BAUD_RATE);
  Serial1.begin(9600);
  Serial2.begin(9600);
  mag.initialize();
  Serial.println(mag.testConnection() ? "HMC5883L connection successful" : "HMC5883L connection failed");
  if (mag.testConnection())
  {
    mag.getHeading(&mx, &my, &mz);
    float heading = atan2(my, mx);
    heading = heading * 180 / M_PI;
    fheading = heading;
    mag_flg = 0;
    delay(1000);
    update_mag();
    fx_ang = fheading;
    if (fx_ang < -90 || fx_ang > 90)
    {
      mp_flg = 0;
      if (fx_ang < 0)
        fx_ang += 2 * M_PI;
    }
    Serial.println(fx_ang);
  }
  else
  {
    mag_flg = 1;
  }
  type = ps2x.readType();
  delay(1000);
}

void loop()
{
  type = ps2x.readType();
  if (mag.testConnection())
  {
    mag_flg = 0;
  }
  else
  {
    mag_flg = 1;
  }
  if (type != 1)
  {
    off();
    while (type == 0)
    {
      Serial.println(type);
      type = ps2x.config_gamepad(CLOCK, COMMAND, ATTENTION, DATA);
      delay(1);
    }
  }
  else
  {
    readButtons();
    //    printState();
    if (r1 || r2)
      pw = r1 > r2 ? TRN_PWM : -TRN_PWM;
    else
      pw = 0;
    omni();
    control(theta);
    if (flag == 1)
    {
      r1 = l1;
      r2 = l2;
      LX = RX;
      LY = RY;
    }
  }
}
