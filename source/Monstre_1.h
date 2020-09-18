#ifndef Monstre_1_H_
#define Monstre_1_H_

#include "Entite.h"

class Monstre_1 : public Entite
{
  friend Monstre_1* EntiteManager :: Creer_Monstre_1 (int, int);

  Monstre_1 (int, int);
  ~Monstre_1 ();
  public:

    //Mise à jour du canard
    void Update ();

    //Lorsque le héros saute sur le canard
    void Blesser ();
};

#endif
