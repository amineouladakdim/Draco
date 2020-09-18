#include "Entite.h"

Entite :: Entite ()
{
  //Initialisation des chronom�tres
  m_Timer.Init ();
  m_ImageTimer.Init ();

  //Initialisation des coordonn�es
  m_x = 0;
  m_y = 0;
  m_xVit = 0;
  m_yVit = 0;

  m_Etat = VIVANT;

  m_Heros = true;
}

Entite :: Entite (int X, int Y)
{
  //Initialisation des chronom�tres
  m_Timer.Init ();
  m_ImageTimer.Init ();

  //Initialisation des coordonn�es
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

//Si l'entit� doit �tre affich�e � l'�cran
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
  //Les entit�s meurent diff�remment selon ce qu'elles sont
  if (m_Etat == MORT_EN_COURS)
    return;
  //L'entit� est mise � jour toutes les 30 millisecondes (�quivaut � 25 images par seconde)
  if (m_Timer.Get () > 30)
  {
    m_Timer.Init ();

    //Mise � jour de la position de l'entit�
    m_x += m_xVit;
    m_y += m_yVit;

    //Mise � jour de la vitesse de l'entit�
    m_xVit += gravX;
    m_yVit += gravY;

    //Afin que l'entit� ne d�passe pas les limites
    if (m_x <= 0)
    {
      if (!m_Heros)
        m_x = Niveau :: GetNbDecors () * FENETRE_LARGEUR;
      else
        m_x = 0;
    }
    if (m_y < 0)
      m_y = 0;

    //Afin qu'il n'y ait plus de gravit� si l'entit� est sur le sol
    if (m_y <= 0 && m_yVit < 0)
      m_yVit = 0;
  }
}
