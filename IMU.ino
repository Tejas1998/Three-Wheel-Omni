void update_mag()
{
  if(mag_flg==0)
    {
      mag.getHeading(&mx, &my, &mz);
      float heading = atan2(my, mx);
      heading=heading * 180/M_PI;
      if(mp_flg==0)
      {
        if(heading < 0)
          heading += 2 * M_PI;
      }  
      fheading=fheading*ma+heading*(1-ma);
    }
}
