#include "EntiteManager.h"
#include "Entree_Clavier.h"
#include "Entite.h"
#include "Hero.h"
#include "Monstre_1.h"
#include "Monstre_2.h"
#include "Monstre_3.h"
#include "Gemme.h"
#include "Affichage.h"

//Si un point se trouve dans un rectangle
bool PointDansRect (int xPoint, int yPoint, SDL_Rect* Rect)
{
  if (xPoint >= Rect -> x && xPoint <= Rect -> x + Rect -> w && yPoint >= Rect -> y && yPoint <= Rect -> y + Rect -> h)
  return true;


  return false;
}



//Vérification que deux rectangles se touchent
bool RectSeTouchent (SDL_Rect* Rect1, SDL_Rect* Rect2)
{
  if (PointDansRect (Rect1 -> x, Rect1 -> y, Rect2))
    return true;
  if (PointDansRect (Rect1 -> x, Rect1 -> y + Rect1 -> h, Rect2))
    return true;
  if (PointDansRect (Rect1 -> x + (Rect1 -> w)/4, Rect1 -> y, Rect2))
    return true;
  if (PointDansRect (Rect1 -> x + Rect1 -> w, Rect1 -> y + Rect1 -> h, Rect2))
    return true;
  return false;
}

EntiteManager* EntiteManager :: m_pEntiteManager = NULL;

EntiteManager :: EntiteManager ()
{
     //Initialisation de tous les cases du tableau des entités ( monstre ) à NULL
  for (int i = 0; i < MAX_ENTITES; i++)
   {
        m_Monstres[i] = NULL;
   }
    //Initialisation de tous les cases du tableau des entités ( gemme ) à NULL
  for (int i = 0; i < MAX_ENTITES; i++)
  {
    m_Gemmes[i] = NULL;
  }
  //Initialisation du générateur de nombres aléatoires
  srand (time (NULL));
}

EntiteManager :: ~EntiteManager ()
{
}

int EntiteManager :: GetIndexLibre_Monstres ()
{
  for (int i = INDEX_ENTITE_HEROS + 1; i < MAX_ENTITES; i ++)
    if (m_Monstres[i] == NULL)
      return i;
  //Plus de place dans le tableau
  return -1;
}

int EntiteManager :: GetIndexLibre_Gemmes ()
{
  for (int i = INDEX_ENTITE_HEROS + 1; i < MAX_ENTITES; i ++)
    if (m_Gemmes[i] == NULL)
      return i;
  //Plus de place dans le tableau
  return -1;
}

EntiteManager* EntiteManager :: Create ()
{
  if (m_pEntiteManager == NULL) //L'instance n'a pas encore été créee
    m_pEntiteManager = new EntiteManager;
  return m_pEntiteManager;
}

void EntiteManager :: Kill ()
{
  if (m_pEntiteManager != NULL)
  {
    for (int i = 0; i < MAX_ENTITES; i++)
    {
      m_pEntiteManager -> KillEntite_Gemmes (i);
      m_pEntiteManager -> KillEntite_Monstres (i);
    }
    delete m_pEntiteManager;
    m_pEntiteManager = NULL;
  }
}

Entite* EntiteManager :: GetEntiteParIndex_Monstres (unsigned int i)
{
  return m_Monstres[i];
}

Entite* EntiteManager :: GetEntiteParIndex_Gemmes (unsigned int i)
{
  return m_Gemmes[i];
}

Hero* EntiteManager :: CreateHeros ()
{
  if (m_Monstres[INDEX_ENTITE_HEROS] == NULL)
    m_Monstres[INDEX_ENTITE_HEROS] = new Hero;
  return dynamic_cast <Hero*> (m_Monstres[INDEX_ENTITE_HEROS]);
}

Monstre_1* EntiteManager :: Creer_Monstre_1 (int x, int y)
{
  int Index = GetIndexLibre_Monstres ();
  if (Index == -1)
    return NULL;
  m_Monstres[Index] = new Monstre_1 (x, y);
  return dynamic_cast <Monstre_1*> (m_Monstres[Index]);
}

Monstre_2* EntiteManager :: Creer_Monstre_2 (int x, int y)
{
  int Index = GetIndexLibre_Monstres ();
  if (Index == -1)
    return NULL;
  m_Monstres[Index] = new Monstre_2 (x, y);
  return dynamic_cast <Monstre_2*> (m_Monstres[Index]);
}

Monstre_3* EntiteManager :: Creer_Monstre_3 (int x, int y)
{
  int Index = GetIndexLibre_Monstres ();
  if (Index == -1)
    return NULL;
  m_Monstres[Index] = new Monstre_3 (x, y);
  return dynamic_cast <Monstre_3*> (m_Monstres[Index]);
}

Gemme* EntiteManager :: Creer_Gemme (int x, int y)
{
  int Index = GetIndexLibre_Gemmes ();
  if (Index == -1)
    return NULL;
  m_Gemmes[Index] = new Gemme (x, y);
  return dynamic_cast <Gemme*> (m_Gemmes[Index]);
}

void EntiteManager :: KillEntite_Monstres (unsigned int i)
{
  if (m_Monstres[i] != NULL)
  {
    delete m_Monstres[i];
    m_Monstres[i] = NULL;
  }

}

void EntiteManager :: KillEntite_Gemmes (unsigned int i)
{
   if (m_Gemmes[i] != NULL)
  {
    delete m_Gemmes[i];
    m_Gemmes[i] = NULL;
  }
}

//La mise à jour se fait en deux étapes:
// * Les mouvements du héros à appliquer s'il n'est pas mort
// * La gestion des collisions entre le héros et les autres entités
void EntiteManager :: Update ()
{

  //Si le héros est mort, on ne met à jour que le héros
  if (Hero :: Create () -> GetEtat () != VIVANT)
  {
    Hero :: Create () -> Update ();
  }
  else //Sinon on met à jour toutes les entités
  {
    //Mouvements du héros
    if (Entree_Clavier :: Create () -> Droite ())
      Hero :: Create()  -> Deplacer (DIRECTION_DROITE);
    else if (Entree_Clavier :: Create () -> Gauche ())
      Hero :: Create()  -> Deplacer (DIRECTION_GAUCHE);
    else
      Hero :: Create()  -> Stopper ();
    if (Entree_Clavier :: Create () -> Espace ())
      Hero :: Create () -> Sauter ();

    //Gestion des collisions
    GererCollisions ();
  }
}

void EntiteManager :: GererCollisions ()
{

  Hero* Heros = dynamic_cast <Hero*> (m_Monstres[INDEX_ENTITE_HEROS]);

  //Hauteur du héros avant sa mise à jour
  int yOld = Heros -> y ();

  //Si pas de héros, pas de collisions à gérer
  if (Heros == NULL)
    return;

  Heros -> Update ();

  //Position et dimensions du héros
  SDL_Rect RectHeros;
  Heros -> GetRect (&RectHeros);

  //Position et dimensions de l'entité
  SDL_Rect RectMonstre;
  SDL_Rect RectGemme;


  for (int i = INDEX_ENTITE_HEROS + 1; i < MAX_ENTITES; i++)
  {
    //Gestion des collisions avec les gemmes
    if (m_Gemmes[i] == NULL)
     continue;
    m_Gemmes[i] -> Update();
    //Si l'entité n'est plus vivante on l'a détruit
     if (m_Gemmes[i] -> GetEtat () != VIVANT)
    {
      if (m_Gemmes[i] -> GetEtat () == MORT)
        KillEntite_Gemmes (i);
      continue;
    }


 if (m_Gemmes[i] -> EstDansEcran (Heros))
    {
      //Position et dimensions de l'entité
      m_Gemmes[i] -> GetRect (&RectGemme);

      //S'il y a une collision entre le héros et l'entité
      if (RectSeTouchent (&RectHeros, &RectGemme))
      {

          m_Gemmes[i] -> Blesser ();
Affichage::nbr_gemmes=Affichage::nbr_gemmes+1;
Fenetre::jouer_son(1);
      }
    }


  }

  for (int i = INDEX_ENTITE_HEROS + 1; i < MAX_ENTITES; i++)
  {

    //Gestion des collisions

    if (m_Monstres[i] == NULL)
      continue;

   // if (m_Gemmes[i] == NULL)
     // continue;

    m_Monstres[i] -> Update ();

    //Si l'entité n'est plus vivante on l'a détruit
    if (m_Monstres[i] -> GetEtat () != VIVANT)
    {
      if (m_Monstres[i] -> GetEtat () == MORT)
        KillEntite_Monstres (i);
      continue;
    }


if (m_Monstres[i] -> EstDansEcran (Heros))
    {
      //Position et dimensions de l'entité
      m_Monstres[i] -> GetRect (&RectMonstre);

      //S'il y a une collision entre le héros et l'entité
      if (RectSeTouchent (&RectHeros, &RectMonstre))
      {

        //Pour que le héros tue l'ennemi, il faut qu'il saute sur au moins le tiers de l'entité
        if (RectHeros.y > RectMonstre.y + (RectMonstre.h / 2 * 1))
        {
            Fenetre::jouer_son(4);
          m_Monstres[i] -> Blesser ();
        }
        else
          Heros -> Blesser ();
      }
    }


  }
}
