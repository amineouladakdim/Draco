#ifndef Affichage_H_
#define Affichage_H_
#include <SDL\SDL.h>
#include <SDL\SDL_image.h>
#include<SDL/SDL_ttf.h>
#include "Fenetre.h"
#include "EntiteManager.h"
#include "Entite.h"
#include "Timer.h"
#include <string>

#define NB_IMAGES 17
#define IMG_INTRO "Images\\Divers\\Intro.png"
#define IMG_PAYSAGE "Images\\Divers\\Decor2.png"
#define IMG_GAGNE "Images\\Divers\\Gagne.png"
#define IMG_FIN "Images\\Divers\\Fin.png"

#define IMG_GEMME 16
#define GEMME_CX 32
#define GEMME_CY 24

#define FIN_CX 84
#define FIN_CY 135

#define IMG_MONSTRE1_MARCHE1 4
#define IMG_MONSTRE1_MARCHE2 5
#define IMG_MONSTRE1_MORT 6

#define MONSTRE1_MARCHE_CX 56
#define MONSTRE1_MARCHE_CY 50
#define MONSTRE1_MORT_CX 54
#define MONSTRE1_MORT_CY 23

#define IMG_MONSTRE2_MARCHE1 7
#define IMG_MONSTRE2_MARCHE2 8
#define IMG_MONSTRE2_MARCHE3 9
#define IMG_MONSTRE2_MARCHE4 10
#define IMG_MONSTRE2_MORT 11

#define MONSTRE2_MARCHE1_CX 78
#define MONSTRE2_MARCHE1_CY 134
#define MONSTRE2_MARCHE2_CX 78
#define MONSTRE2_MARCHE2_CY 100
#define MONSTRE2_MORT_CX 78
#define MONSTRE2_MORT_CY 46

//Index des images correspondantes
#define IMG_HEROS_MARCHE1 0
#define IMG_HEROS_MARCHE2 1
#define IMG_HEROS_SAUT1 2
#define IMG_HEROS_SAUT2 3

//Dimensions des images correspondantes
#define HEROS_MARCHE1_CX 47
#define HEROS_MARCHE1_CY 77
#define HEROS_MARCHE2_CX 44
#define HEROS_MARCHE2_CY 76
#define HEROS_SAUT1_CX 50
#define HEROS_SAUT1_CY 78
#define HEROS_SAUT2_CX 47
#define HEROS_SAUT2_CY 75

#define IMG_MONSTRE3_CHUTE 12
#define IMG_MONSTRE3_MARCHE1 13
#define IMG_MONSTRE3_MARCHE2 14
#define IMG_MONSTRE3_MORT 15

#define MONSTRE3_CHUTE_CX 50
#define MONSTRE3_CHUTE_CY 92
#define MONSTRE3_MARCHE_CX 60
#define MONSTRE3_MARCHE_CY 63
#define MONSTRE3_MORT_CX 60
#define MONSTRE3_MORT_CY 33

using namespace std;



class Affichage
{
  //Chronomètre quand le joueur aura fini le niveau
  Timer m_TimerNiveauFini;
  //Pour savoir si le chronomètre a été enclenché
  bool m_TimerNiveauEnclenche;


  //Surface sur laquelle l'affichage va s'effectuer
  SDL_Surface* m_Surface;
  //Images des entités
  SDL_Surface** m_Pictures;
  //Fonds (écran d'accueil, décor, etc.)
  SDL_Surface* m_Intro, *m_Decor, *m_Gagne, *m_Fin;

  static Affichage* m_pAffichage;


  //Dessiner le paysage
  void DessinerPaysage ();



   void Afficher_Nbr_Gemmes();


  public:
Affichage(int x);
Affichage();
~Affichage();

  static int nbr_gemmes;

 static int Get_nbrgemme();

// void Set_nbrgemme(int x);
 //void incr_nbrgemme();

    //Affichage de l'écran d'accueil
    void DessinerIntro ();
    //Affichage du décor et des entités
    void DessinerJeu ();
    //Affichage de l'image de fin (le texte "Vous avez gagné" ou "Vous avez perdu")
    void DessinerFin (bool);

    static Affichage* Create (SDL_Surface*);
    static void Kill ();
};

#endif
