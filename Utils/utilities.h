#include <plugin.h>

MYFLT clamp_value(MYFLT min, MYFLT max, MYFLT value)
{
  MYFLT res = value;
  if (value < min) 
  res = min;
  else if (value > max)
  res = max;
  return res;  
}