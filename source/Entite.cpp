#include "Entite.h"

Entite :: Entite ()
{
  //Initialisation des chronomètres
  m_Timer.Init ();
  m_ImageTimer.Init ();

  //Initialisation des coordonnées
  m_x = 0;
  m_y = 0;
  m_xVit = 0;
  m_yVit = 0;

  m_Etat = VIVANT;

  m_Heros = true;
}

Entite :: Entite (int X, int Y)
{
  //Initialisation des chronomètres
  m_Timer.Init ();
  m_ImageTimer.Init ();

  //Initialisation des coordonnées
  m_x = X;
  m_y = Y;
  m_xVit = 0;
  m_yVit = 0;

  m_Etat = VIVANT;

  m_Heros = false;
}

Entite :: ~Entite ()
{
}

//Si l'entité doit être affichée à l'écran
bool Entite :: EstDansEcran (Entite* Heros)
{
  return (m_x + m_cx > Heros -> m_x - Heros -> m_cx - FENETRE_LARGEUR / 2 && m_x < Heros -> m_x + Heros -> m_cx + FENETRE_LARGEUR / 2);

}

void Entite :: GetRect (SDL_Rect* Rect)
{
  Rect -> x = m_x;
  Rect -> y = m_y;
  Rect -> w = m_cx;
  Rect -> h = m_cy;
}

void Entite :: Update ()
{
  //Les entités meurent différemment selon ce qu'elles sont
  if (m_Etat == MORT_EN_COURS)
    return;
  //L'entité est mise à jour toutes les 30 millisecondes (équivaut à 25 images par seconde)
  if (m_Timer.Get () > 30)
  {
    m_Timer.Init ();

    //Mise à jour de la position de l'entité
    m_x += m_xVit;
    m_y += m_yVit;

    //Mise à jour de la vitesse de l'entité
    m_xVit += gravX;
    m_yVit += gravY;

    //Afin que l'entité ne dépasse pas les limites
    if (m_x <= 0)
    {
      if (!m_Heros)
        m_x = Niveau :: GetNbDecors () * FENETRE_LARGEUR;
      else
        m_x = 0;
    }
    if (m_y < 0)
      m_y = 0;

    //Afin qu'il n'y ait plus de gravité si l'entité est sur le sol
    if (m_y <= 0 && m_yVit < 0)
      m_yVit = 0;
  }
}
