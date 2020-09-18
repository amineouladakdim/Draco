#include "Monstre_3.h"
#include "Hero.h"
#include "Fenetre.h"
#include "Niveau.h"

Monstre_3:: Monstre_3(int x, int y) : Entite (x, y)
{
  //Initalisation de l'image en chute car le monstre 3 est un monstre volant
  m_Image = IMG_MONSTRE3_CHUTE;
  //On initialise la taille du sprite (hauteur et largeur) dans les variables m_cx et m_cy
  m_cx = MONSTRE3_CHUTE_CX;
  m_cy = MONSTRE3_CHUTE_CY;
  //On initialise la vitesse
  m_xVit = 0;
  m_yVit = 0;
//On initialise le compteur du parachute
  m_TimerParachute.Init ();
  //et on le met en état de chute
  m_ParachuteEtat = CHUTE_EN_COURS;
  //quand il est en chute il marche pas
  m_MarcheInitialisee = false;
}

void Monstre_3:: Blesser ()
{
    //si le monstre etait en état de chute le moment quand il est blessé , on le met en état de marche
  if (m_ParachuteEtat == CHUTE_EN_COURS)
  {
      //affectation de l'état de marche
    m_ParachuteEtat = MARCHE;
     //changement de l'image en marche
    m_Image = IMG_MONSTRE3_MARCHE1;
    //et recalcul de la taille de l'image
    m_cx = MONSTRE3_MARCHE_CX;
    m_cy = MONSTRE3_MARCHE_CY;
   //On initialise le timer à 0 pour changer l'animation après un certain temps
    m_ImageTimer.Init ();
    //il est en marche ( non pas en chute )
    m_MarcheInitialisee = true;
  }
  else
  {
           Fenetre::jouer_son(4);
    //si il n'etait pas en chute le moment quand il est blessé il meurt , changement d'état en "mort"
    m_Etat = MORT_EN_COURS;
    //changement du sprite
    m_Image = IMG_MONSTRE3_MORT;
    //calcul de la taille du nouveau sprite
    m_cx = MONSTRE3_MORT_CX;
    m_cy = MONSTRE3_MORT_CY;
      //on intialise le timer de la mort à 0 , comme ça il disparait aprés un certain temps
    m_TimerMort.Init ();
  }

  Hero :: Create () -> m_yVit = 10;
}

void Monstre_3:: Update ()
{
    //Le monstre3 (écrasé) doit rester une demi-seconde et après il doit disparaître
  if (m_Etat == MORT_EN_COURS)
  {
    if (m_TimerMort.Get () > 500)
      m_Etat = MORT;
    return;
  }

  if (m_y == 0 && !m_MarcheInitialisee)
  {
    m_ParachuteEtat = MARCHE;
    m_Image = IMG_MONSTRE3_MARCHE1;

    m_cx = MONSTRE3_MARCHE_CX;
    m_cy = MONSTRE3_MARCHE_CY;

    m_ImageTimer.Init ();
    m_MarcheInitialisee = true;
  }

  if (m_ParachuteEtat == CHUTE_EN_COURS)
  {
    //Simulation du parachute
    if (m_TimerParachute.Get () > 50 && m_y > 0)
    {
      m_y--;

      m_x -= 2;

      m_TimerParachute.Init ();
    }
  }

  if (m_ParachuteEtat == MARCHE)
  {
    m_xVit = -1;
    Entite :: Update();

    if (m_ImageTimer.Get () > 350)
    {
      m_ImageTimer.Init ();

      m_Image = (m_Image == IMG_MONSTRE3_MARCHE1)? IMG_MONSTRE3_MARCHE2: IMG_MONSTRE3_MARCHE1;
    }
  }

  if (m_x < 0)
    m_x = Niveau :: GetNbDecors () * FENETRE_LARGEUR;
}
