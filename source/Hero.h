#ifndef Hero_H_
#define Hero_H_

#include "Entite.h"
#include "Monstre_1.h"
#include "Monstre_2.h"
#include "Monstre_3.h"

class Hero : public Entite
{
  friend Hero* EntiteManager :: CreateHeros ();
  friend void Monstre_1 :: Blesser ();
  friend void Monstre_2 :: Blesser ();
 friend void Monstre_3 :: Blesser ();

  //Mise à jour des dimensions de l'entité
  void UpdateDimensions ();

  Hero ();
  ~Hero ();
  public:
    static Hero* Create ();

    //Lors de l'appui d'un flèche (droite / gauche)
    void Deplacer (EDirection);
    //Lorsqu'on relâche une flèche
    void Stopper () { m_xVit = 0; }
    void Sauter ();
    //Blessure infligée au héros; renvoie true s'il meurt, false dans le cas contraire
    void Blesser ();

    void Update ();
};

#endif
