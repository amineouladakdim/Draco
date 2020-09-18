#include "Monstre_1.h"
#include "Hero.h"
#include "Fenetre.h"
#include "Niveau.h"

Monstre_1 :: Monstre_1 (int x, int y) : Entite (x, y)
{
  //On intialise la taille du sprite (hauteur et largeur) dans les variables m_cx et m_cy
  m_cx = MONSTRE1_MARCHE_CX;
  m_cy = MONSTRE1_MARCHE_CY;

  //On initalise l'image soit avec la frame 1 soit avec la frame 2 au hasard (pour plus de naturel)
  m_Image = IMG_MONSTRE1_MARCHE1 + (rand () % 2);
  //On initialise le timer � 0 pour changer l'animation apr�s un certain temps
  m_ImageTimer.Init ();

  //On itinitalise la vitesse horizontal � -2 vue que le monstre_1 bouge toujours � gauche
  m_xVit = -2;
  m_yVit = 0;
}

void Monstre_1 :: Blesser ()
{
         Fenetre::jouer_son(4);
  //On gere les �tat si le monstre est touch�
  m_Etat = MORT_EN_COURS;
  //on lui affecte le sprite du monstre mort
  m_Image = IMG_MONSTRE1_MORT;
  //pareil pour la taille car un monstre mort est plus petit qu'un monstre vivant (�cras�)
  m_cx = MONSTRE1_MORT_CX;
  m_cy = MONSTRE1_MORT_CY;
 //On effectue un bond sur le h�ros
  Hero :: Create () -> m_yVit = 10;
  //on intialise le timer de la mort � 0 , comme �a il disparait apr�s un certain temps
  m_TimerMort.Init ();
}

void Monstre_1 :: Update ()
{
  Entite :: Update ();

  //Si le h�ros a d�j� saut� sur le monstre
  if (m_Etat == MORT_EN_COURS)
  {
    //Le monstre (�cras�) doit rester une demi-seconde et apr�s il doit dispara�tre
    if (m_TimerMort.Get () > 500)
    {
    //Attribution de l'�tat : mort
      m_Etat = MORT;
    }
  }
  else
  {
    //Mise � jour de l'image
    //Les images changent tous les 200 milli�mes de seconde
    if (m_ImageTimer.Get () > 200)
    {
     //Initalisation apres chaque 200 milli�mes de seconde pour un nouveau d�compte
      m_ImageTimer.Init ();
    //L'image prend le sprite MARCHE1 si elle est en MARCHE2 ou vice-versa
      m_Image = (m_Image == IMG_MONSTRE1_MARCHE1)? IMG_MONSTRE1_MARCHE2: IMG_MONSTRE1_MARCHE1;
    }
  }
}
