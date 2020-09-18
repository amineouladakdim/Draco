#include "Hero.h"
#include "Niveau.h"

Hero :: Hero ()
{
//Initialisation de la taille du h�ros
  m_cx = 47;
  m_cy = 77;
//Affectation du sprite 1 correspondant � la marche ( le premier pas )
  m_Image = IMG_HEROS_MARCHE1;
}

Hero :: ~Hero ()
{
}

//fonction de malade :o

Hero* Hero :: Create ()
{
  EntiteManager* EntiteManager = EntiteManager :: Create ();
  if (EntiteManager == NULL)
    return NULL;
  if (EntiteManager -> GetEntiteParIndex_Monstres (INDEX_ENTITE_HEROS) == NULL)
    EntiteManager :: Create () -> CreateHeros ();
  return dynamic_cast <Hero*> (EntiteManager -> GetEntiteParIndex_Monstres (INDEX_ENTITE_HEROS));
}


//Si le h�ros est dans la direction droite,  la vitesse est � 6 (x=+6) si � gauche (x=-4)
void Hero :: Deplacer (EDirection Direction)
{
  m_xVit = (Direction == DIRECTION_DROITE)? 6: -4;
}

void Hero :: Sauter ()
{
  //Si le h�ros se trouve sur le sol on saut d'une hauteur de 23 (y=y-23)
  if (m_y == 0)
    m_yVit = 23;
}

//Si le h�ros est bl�ss�
void Hero :: Blesser ()
{
    //Changement de sprite
  m_Image = IMG_HEROS_MARCHE1;
  //Changement d'�tat
  m_Etat = MORT_EN_COURS;

  //Intialisation des chronom�tres pour changer de sprite apr�s un certain temps ou apres des evenemments comme la mort
  m_ImageTimer.Init ();
  m_TimerMort.Init ();

  //Afin qu'on voit le h�ros "mourir"
  m_xVit = 0;
  //le h�ros descend ( � la supermario vers le bas en fonction de la taille de son sprite )
  m_yVit = m_cx / 2;
}

//MAJ des tailles du h�ros en fonction du sprite
void Hero :: UpdateDimensions ()
{
  switch (m_Image)
  {
    case IMG_HEROS_MARCHE1:
      m_cx = HEROS_MARCHE1_CX;
      m_cy = HEROS_MARCHE1_CY;
      break;
    case IMG_HEROS_MARCHE2:
      m_cx = HEROS_MARCHE2_CX;
      m_cy = HEROS_MARCHE2_CY;
      break;
    case IMG_HEROS_SAUT1:
      m_cx = HEROS_SAUT1_CX;
      m_cy = HEROS_SAUT1_CY;
      break;
    case IMG_HEROS_SAUT2:
      m_cx = HEROS_SAUT2_CX;
      m_cy = HEROS_SAUT2_CY;
      break;
  }
}

//La mise � jour du h�ros se fait en plusieurs �tapes:
//  Si le h�ros est mort:
//    * On met � jour la position
//  S'il est toujours en vie
//   * Mise � jour de la position et de la vitesse du h�ros
//   * Mise � jour de son image
void Hero :: Update ()
{
  Entite :: Update ();
  if (m_Etat == MORT_EN_COURS)
  {
    //On voit le h�ros "mourir" jusqu'� ce qu'il soit "en-dessous" du sol
    if (m_y + m_cy < 0)
    {
      m_Etat == MORT;
    }
    else
    {
      if (m_ImageTimer.Get () > 50)
      {
        m_ImageTimer.Init ();

        //Mise � jour de la position du h�ros
        m_x += m_xVit;
        m_y += m_yVit;

        //Mise � jour de la vitesse du h�ros
        m_xVit += gravX;
        m_yVit += gravY;
      }
    }
  }
  else
  {
    //Si le h�ros a atteint la limite du niveau (le joueur a donc termin� le niveau)
    if (m_x >= Niveau :: GetNbDecors () * FENETRE_LARGEUR)
    //Affectation Niveau fini
      Niveau :: SetNiveauFini ();

    //Gestion des animations
    //Les images changent tous les 150�mes de secondes
    if (m_ImageTimer.Get () > 150)
    {
      m_ImageTimer.Init ();
      if (m_y == 0) //Si le h�ros se trouve sur le sol
      {
        if (m_xVit == 0) //Le h�ros ne marche pas
          m_Image = IMG_HEROS_MARCHE1;
        else
        {
          if (m_Image != IMG_HEROS_MARCHE1)
            m_Image = IMG_HEROS_MARCHE1;
          else
            m_Image = IMG_HEROS_MARCHE2;
        }
      }
      else //Le h�ros est en train de sauter
      {
        if (m_yVit > 0) //Le h�ros monte
          m_Image = IMG_HEROS_SAUT1;
        else //Le h�ros descend
          m_Image = IMG_HEROS_SAUT2;
      }
      //Mise � jour des dimensions
      UpdateDimensions ();
    }
  }
}
