#ifndef Gemme_H_
#define Gemme_H_

#include "Entite.h"

class Gemme : public Entite
{
  friend Gemme* EntiteManager :: Creer_Gemme (int, int);

  Gemme (int, int);
  ~Gemme ();
  public:

    //Mise à jour du canard
    void Update ();

    //Lorsque le héros saute sur le canard
    void Blesser ();
};

#endif
