#ifndef Timer_H_
#define Timer_H_

#include <time.h>

class Timer
{
  long int m_Timer;
  public:
    //Initialiser le timer à zéro
    void Init ();
    //Obtenir le temps écoulé (en milli-secondes) depuis le dernier appel à la fonction Init ()
    long int Get ();
};

#endif
