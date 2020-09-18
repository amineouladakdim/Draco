#ifndef Timer_H_
#define Timer_H_

#include <time.h>

class Timer
{
  long int m_Timer;
  public:
    //Initialiser le timer � z�ro
    void Init ();
    //Obtenir le temps �coul� (en milli-secondes) depuis le dernier appel � la fonction Init ()
    long int Get ();
};

#endif
