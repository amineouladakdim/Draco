#ifndef EntiteManager_H_
#define EntiteManager_H_

#include <stdlib.h>
#include <time.h>

//Nombre maximal d'entités possible
#define MAX_ENTITES 50
//Index du pointeur sur l'entité héros dans la table des entités
#define INDEX_ENTITE_HEROS 0

class Entite;
class Hero;
class Monstre_1;
class Monstre_2;
class Monstre_3;
class Gemme;


class EntiteManager
{
  //Table des pointeurs sur les entités
  class Entite *m_Monstres[MAX_ENTITES];
  class Entite *m_Gemmes[MAX_ENTITES];
  //La seule instance est pointée par m_pEntiteManager
  static EntiteManager *m_pEntiteManager;

  //Obtenir un index libre dans le tableau d'entités
  int GetIndexLibre_Monstres ();
  int GetIndexLibre_Gemmes ();
  //Tester les chocs entre le héros et les autres entités
  void GererCollisions ();

//  friend void Affichage :: incr_nbrgemme();
  //On ne peut pas créer une instance avec new ni en détruire une avec delete
  EntiteManager ();
  ~EntiteManager ();

  public:
    static EntiteManager* Create (); //Crée la seule instance et la renvoie
    static void Kill ();

    Entite* GetEntiteParIndex_Monstres (unsigned int);
    Entite* GetEntiteParIndex_Gemmes (unsigned int);
    //Crée le héros
    Hero* CreateHeros ();
    //Crée  monstre1
    Monstre_1* Creer_Monstre_1 (int, int);
    //Crée monstre2
    Monstre_2* Creer_Monstre_2 (int, int);
    //Crée montre3
    Monstre_3* Creer_Monstre_3 (int, int);
    //Crée gemme
    Gemme* Creer_Gemme(int,int);

    //Mise à jour de toutes les entités
    void Update ();

    //Détruit une entité
    void KillEntite_Monstres (unsigned int);
      void KillEntite_Gemmes (unsigned int);
};

#endif
