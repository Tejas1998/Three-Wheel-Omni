void motorA(int t)
{
  t = t > lim ? lim : t;
  t = t < -lim ? -lim : t;
  int var = map(t, -100, 100, 127, 1);
  Serial2.write(var);
}
void motorC(int t)
{
  t = t > lim ? lim : t;
  t = t < -lim ? -lim : t;
  int var = map(t, 100, -100, 255, 128);
  Serial1.write(var);
}
void motorB(int t)
{
  t = t > lim ? lim : t;
  t = t < -lim ? -lim : t;
  int var = map(t, 100, -100, 1, 127);
  Serial1.write(var);
}
