#ifndef Monstre_2_H_
#define Monstre_2_H_

#include "Entite.h"

class Monstre_2: public Entite
{
  friend Monstre_2* EntiteManager :: Creer_Monstre_2 (int, int);

  //Points de vie
  int m_Vie;

  Monstre_2(int, int);
  ~Monstre_2();
  public:

    //Mise à jour du canard
    void Update ();

    //Lorsque le héros saute sur le canard
    void Blesser ();
};

#endif
