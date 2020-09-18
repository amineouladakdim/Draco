#include "Timer.h"

void Timer :: Init ()
{
  m_Timer = clock ();
}

long int Timer :: Get ()
{
  return clock () - m_Timer;
}
