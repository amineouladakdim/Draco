#ifndef Monstre_3_H_
#define Monstre_3_H_

#include "Entite.h"

typedef enum
{
  CHUTE_EN_COURS,
  MARCHE
} EParachuteEtat;

class Monstre_3: public Entite
{
  friend Monstre_3* EntiteManager :: Creer_Monstre_3 (int, int);

  //Chronomètre pour ralentir la chute de l'entité
  Timer m_TimerParachute;
  //Si on a déjà pris en compte que le canard n'a plus son parachute
  bool m_MarcheInitialisee;

  //Etat
  EParachuteEtat m_ParachuteEtat;

  Monstre_3(int, int);
  ~Monstre_3();
  public:
    //Mise à jour
    void Update ();

    void Blesser ();
};

#endif
