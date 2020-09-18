#ifndef Fenetre_H_
#define Fenetre_H_
#include <SDL\SDL.h>
#include <SDL\SDL_mixer.h>
#include <stdlib.h>
#include "Entree_Clavier.h"
#include "EntiteManager.h"
#include "Affichage.h"
#include "Timer.h"


#define FENETRE_LARGEUR 640
#define FENETRE_HAUTEUR 480

typedef enum
{
  PAGE_INTRO,
  PAGE_JEU,
  PAGE_NULL
} EPage;

class Fenetre
{
  Entree_Clavier* m_Entree;
  SDL_Surface * m_Ecran;
  //Page courante
  EPage m_Page;
  //Chronom�tre lorsque le jeu est fini (soit le h�ros est mort, soit le joueur a termin� le niveau)
  Timer m_TimerFin;
  //Est-ce que m_TimerFin est lanc� ?
  bool m_TimerFinLance;

   //Cr�ation de la fen�tre
  void CreerFenetre ();
  void GestionEvenements ();
  Mix_Music* jouer_musique();

  EPage PageIntro ();
  EPage PageJeu ();
  public:
       static void jouer_son(int);
    Fenetre ();
    ~Fenetre ();
};

#endif
