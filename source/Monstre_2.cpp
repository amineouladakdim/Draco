#include "Monstre_2.h"
#include "Hero.h"
#include "Fenetre.h"
#include "Niveau.h"

Monstre_2:: Monstre_2(int x, int y) : Entite (x, y)
{
    //On intialise la taille du sprite (hauteur et largeur) dans les variables m_cx et m_cy
  m_cx = MONSTRE2_MARCHE1_CX;
  m_cy = MONSTRE2_MARCHE1_CY;
  //On initalise l'image soit avec la frame 1 soit avec la frame 2 au hasard (pour plus de naturel)
  m_Image = IMG_MONSTRE2_MARCHE1 + (rand () % 2);
  //Le monstre 2 à deux vie donc il a un nouveau membre 'vie'
  m_Vie = 2;
   //On itinitalise la vitesse horizontal à -1 vue que le monstre_2 bouge toujours à gauche
  m_xVit = -1;
  m_yVit = 0;
}

void Monstre_2:: Blesser ()
{
    //Test sur le nombre du vie du monstre

    //Si il est blessé et qu'il avait 2 , on lui remet qu'une
  if (m_Vie == 2)
  {
    m_Vie = 1;

//L'animation du monstre change en MARCHE3 qui correspond à monstre 2 frappé
    m_Image = IMG_MONSTRE2_MARCHE3;
//Rénisialition de la taille de l'image au cas ou elle differe
    m_cx = MONSTRE2_MARCHE2_CX;
    m_cy = MONSTRE2_MARCHE2_CY;
  }
  else
  {
           Fenetre::jouer_son(4);
//Si il n'avait qu'une vie , on lui affecte l'état 'mort'
    m_Vie = 0;
    m_Etat = MORT_EN_COURS;
  //on lui affecte le sprite du monstre mort
    m_Image = IMG_MONSTRE2_MORT;
  //Rénisialition de la taille de l'image au cas ou elle differe
    m_cx = MONSTRE2_MORT_CX;
    m_cy = MONSTRE2_MORT_CY;
  //on intialise le timer de la mort à 0 , comme ça il disparait aprés un certain temps
    m_TimerMort.Init ();
  }

   //On effectue un bond sur le héros
  Hero :: Create () -> m_yVit = 10;
}

void Monstre_2:: Update ()
{
  Entite :: Update ();

  //Si le héros a déjà sauté sur le monstre
  if (m_Etat == MORT_EN_COURS)
  {
    //Le monstre2 (écrasé) doit rester une demi-seconde et après il doit disparaître
    if (m_TimerMort.Get () > 500)
    {
      m_Etat = MORT;
    }
  }
  else
  {
    //Si le monstre atteint le début du niveau, il repart depuis la fin du niveau
    if (m_x < 0)
      m_x = Niveau :: GetNbDecors () * FENETRE_LARGEUR;
    if (m_y < 0)
      m_y = 0;

    //Mise à jour de l'image
    //Les images changent tous les 350 millièmes de seconde
    if (m_ImageTimer.Get () > 350)
    {
      m_ImageTimer.Init ();

      //Si le monstre n'est pas blessé
      if (m_Vie == 2)
         //L'image prend le sprite MARCHE1 si elle est en MARCHE2 ou vice-versa
        m_Image = (m_Image == IMG_MONSTRE2_MARCHE1)? IMG_MONSTRE2_MARCHE2: IMG_MONSTRE2_MARCHE1;
      else //Sinon
       //L'image prend le sprite MARCHE1=3 si elle est en MARCHE4 ou vice-versa
        m_Image = (m_Image == IMG_MONSTRE2_MARCHE3)? IMG_MONSTRE2_MARCHE4: IMG_MONSTRE2_MARCHE3;
    }
  }
}
