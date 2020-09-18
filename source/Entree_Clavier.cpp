#include "Entree_Clavier.h"
#include "Hero.h"
#include "Affichage.h"

Entree_Clavier* Entree_Clavier :: m_pEntreeClavier = NULL;

Entree_Clavier :: Entree_Clavier ()
{
//Initialisation des touches à false ( non touché )
  m_Espace = false;
  m_Droite = false;
  m_Gauche = false;
}

Entree_Clavier :: ~Entree_Clavier ()
{
}

Entree_Clavier* Entree_Clavier :: Create ()
{
  if (m_pEntreeClavier == NULL)
    m_pEntreeClavier = new Entree_Clavier;
  return m_pEntreeClavier;
}

void Entree_Clavier :: Kill ()
{
  if (m_pEntreeClavier != NULL)
  {
    delete m_pEntreeClavier;
    m_pEntreeClavier = NULL;
  }
}

//Fonction appelée lors de l'appui d'une touche; retourne true si la touche est Escape, false en cas contraire
bool Entree_Clavier :: Event (SDL_KeyboardEvent * event)
{
  switch (event -> type)
  {
    case SDL_KEYUP: //Touche relâchée
      switch (event -> keysym.sym)
      {
        case SDLK_RIGHT:
          m_Droite = false;
          break;
        case SDLK_LEFT:
          m_Gauche = false;
          break;
        case SDLK_SPACE:
          m_Espace = false;
          break;
      }
      return false;
    case SDL_KEYDOWN:
      switch (event -> keysym.sym)
      {
        case SDLK_RIGHT:
          m_Droite = true;
          break;
        case SDLK_LEFT:
          m_Gauche = true;
          break;
        case SDLK_SPACE:
        Fenetre::jouer_son(2);
          m_Espace = true;
          break;
        case SDLK_ESCAPE:
          return true;
      }
      break;
  }
  return false;
}
