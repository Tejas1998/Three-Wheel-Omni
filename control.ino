void omni()
{
  //  fRX=fRX*a+RX*(1-a);
  //  fRY=fRY*a+RY*(1-a);


  fLX = fLX * a + LX * (1 - a);
  fLY = fLY * a + LY * (1 - a);

  theta = atan2(fLX, fLY) * 180 / 3.141592;
  if (theta < 0) theta = map(theta, -180, 0, 180, 360);

  magnitude = abs(fLX) > abs(fLY)  ? abs(fLX) : abs(fLY);
  magnitude = map(magnitude, 0, 128, 0, 100);

  if (magnitude < 80 && !r1 && !r2)
  {
    if (fheading > 185.7)
      pw = (pw - (0.50 * (185 - fheading) * (185 - fheading)));
    else if (fheading < 184)
      pw = (pw + (0.50 * (185 - fheading) * (185 - fheading)));
  }
  fpw = fpw * ra + pw * (1 - ra); // to control turn CW CCW swooth
}
void control(int ang)
{
  pwmA = magnitude * cos(0.0176 * (60.00 - ang));
  pwmB = magnitude * cos(0.0176 * (180.00 - ang));
  pwmC = magnitude * cos(0.0176 * (300.00 - ang));
  motorA(pwmA + fpw);
  motorB(pwmB + fpw);
  motorC(pwmC + fpw);
}
