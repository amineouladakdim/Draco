#ifndef Entite_H_
#define Entite_H_

#include <stdlib.h>
#include "Timer.h"
#include "Fenetre.h"
#include "EntiteManager.h"
#include "Niveau.h"
#include "Affichage.h"

#define gravX 0
#define gravY -2

typedef enum
{
  DIRECTION_DROITE = 0,
  DIRECTION_GAUCHE,
} EDirection;

typedef enum
{
  VIVANT,
  MORT_EN_COURS,
  MORT
} EVie;

class Entite
{
  friend void EntiteManager :: KillEntite_Monstres (unsigned int);
 friend void EntiteManager :: KillEntite_Gemmes (unsigned int);
  protected:

  //Direction dans laquelle l'entit� se d�place
  EDirection m_Direction;

  //Chronom�tre pour l'entit�
  Timer m_Timer;
  //Chronom�trepour les images
  Timer m_ImageTimer;
  //Chronom�tre lorsque l'entit� est morte
  Timer m_TimerMort;

  //Image de l'entit�
  int m_Image;
  //Nombre d'images
  int m_nbImages;
  //Index des images
  int m_IndexImages[6];

  //Dimensions de l'entit�
  int m_cx, m_cy;
  //Position de l'entit�
  int m_x, m_y;
  //Vitesse de l'entit�
  int m_xVit, m_yVit;

  //Si l'entit� est le h�ros
  bool m_Heros;

  //Etat de l'entit�
  EVie m_Etat;

  Entite ();
  Entite (int, int);
  ~Entite ();
  public:

    //Si l'entit� peut �tre affich�e dans l'�cran
    bool EstDansEcran (Entite*);

    //Obtenir l'index de l'image correspondant � l'entit�
    int GetImage () { return m_Image; }

    //Retourne les dimensions de l'entit�
    int cx () { return m_cx; }
    int cy () { return m_cy; }

    //Retourne la position de l'entit�
    int x () { return m_x; }
    int y () { return m_y; }

    //Retourne la position et les dimensions de l'entit� dans une structure
    void GetRect (SDL_Rect*);

    //Retourne l'�tat de l'entit� (mort, "mort en cours" ou vivant)
    int GetEtat () { return m_Etat; }

    virtual void Update ();

    virtual void Blesser () { }
};

#endif
