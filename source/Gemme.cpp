
#include "Gemme.h"
#include "Hero.h"
#include "Fenetre.h"
#include "Niveau.h"

Gemme :: Gemme (int x, int y) : Entite (x, y)
{
  //On intialise la taille du sprite (hauteur et largeur) dans les variables m_cx et m_cy
  m_cx = GEMME_CX;
  m_cy = GEMME_CY;

  //On initalise l'image soit avec la frame 1 soit avec la frame 2 au hasard (pour plus de naturel)
  m_Image = IMG_GEMME;
  //On initialise le timer � 0 pour changer l'animation apr�s un certain temps
  m_ImageTimer.Init();

  //On itinitalise la vitesse horizontal � -2 vue que le monstre_1 bouge toujours � gauche
  m_xVit = 0;
  m_yVit = 0;
}

void Gemme :: Blesser ()
{
  //On gere les �tat si le monstre est touch�
  m_Etat = MORT_EN_COURS;
  //on lui affecte le sprite du monstre mort
  m_Image = IMG_GEMME;
  //pareil pour la taille car un monstre mort est plus petit qu'un monstre vivant (�cras�)
  m_cx = GEMME_CX;
  m_cy = GEMME_CY;

  //on intialise le timer de la mort � 0 , comme �a il disparait apr�s un certain temps
  m_TimerMort.Init ();
}

void Gemme :: Update ()
{
  Entite :: Update ();

  //Si le h�ros a d�j� saut� sur le monstre
  if (m_Etat == MORT_EN_COURS)
  {
    //Le monstre (�cras�) doit rester une demi-seconde et apr�s il doit dispara�tre
    if (m_TimerMort.Get () > 100)
    {
    //Attribution de l'�tat : mort
      m_Etat = MORT;
    }
  }

}
