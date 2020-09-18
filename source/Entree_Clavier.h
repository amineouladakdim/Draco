#ifndef Entree_Clavier_H_
#define Entree_Clavier_H_

#include <SDL\SDL.h>

class Entree_Clavier
{
  bool m_Espace, m_Droite, m_Gauche;
  static Entree_Clavier* m_pEntreeClavier;

  Entree_Clavier ();
  ~Entree_Clavier ();
  public:
    static Entree_Clavier* Create ();
    static void Kill ();

    bool Espace () { return m_Espace; }
    bool Droite () { return m_Droite; }
    bool Gauche () { return m_Gauche; }

    bool Event (SDL_KeyboardEvent*); //Appelée quand une touche est appuyée
};

#endif
