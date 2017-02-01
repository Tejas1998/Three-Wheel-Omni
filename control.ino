void omni()
{
  fLX = fLX * a + LX * (1 - a);
  fLY = fLY * a + LY * (1 - a);

  theta = atan2(fLX, fLY) * 180 / 3.141592;
  if (theta < 0) theta = map(theta, -180, 0, 180, 360);

  magnitude = abs(fLX) > abs(fLY)  ? abs(fLX) : abs(fLY);
  magnitude = map(magnitude, 0, 128, 0, 100);
  if (mag_flg == 0)
  {
    update_mag();
    if (magnitude <= 100 && !r1 && !r2)
    {
      if (fheading > (fx_ang + delta))
        pw = (pw + (0.1 * (fx_ang - fheading) * (fx_ang - fheading)));
      else if (fheading < (fx_ang - delta))
        pw = (pw - (0.1 * (fx_ang - fheading) * (fx_ang - fheading)));
    }
  }
  fpw = fpw * ra + pw * (1 - ra); // to control turn CW CCW swooth
  Serial.print(theta);
  Serial.print(" ");
  Serial.println(magnitude);
}

void control(int angle)
{
  pwmA = magnitude * cos(0.0176 * (270.00 - angle));
  pwmB = magnitude * cos(0.0176 * (390.00 - angle));
  pwmC = magnitude * cos(0.0176 * (510.00 - angle));
  motorA(pwmA - fpw);
  motorB(pwmB - fpw);
  motorC(pwmC - fpw);
}

void off()
{
  motorA(0);
  motorB(0);
  motorC(0);
  frpwm = 0;
  reset_value();
}

void reset_value()
{
  up = 0; down = 0; left = 0; right = 0; triangle = 0; sqr = 0; cross = 0; circle = 0; r1 = 0; r2 = 0; p_r2 = 0; l1 = 0; l2 = 0; p_l2 = 0; r3 = 0; l3 = 0; start = 0; select = 0;
  RY = 0; RX = 0; LY = 0; LX = 0; magnitude = 0; pwmA = 0; pwmB = 0; pwmC = 0; //omni();
}


