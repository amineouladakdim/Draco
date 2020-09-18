#ifndef EntiteManager_H_
#define EntiteManager_H_

#include <stdlib.h>
#include <time.h>

//Nombre maximal d'entit�s possible
#define MAX_ENTITES 50
//Index du pointeur sur l'entit� h�ros dans la table des entit�s
#define INDEX_ENTITE_HEROS 0

class Entite;
class Hero;
class Monstre_1;
class Monstre_2;
class Monstre_3;
class Gemme;


class EntiteManager
{
  //Table des pointeurs sur les entit�s
  class Entite *m_Monstres[MAX_ENTITES];
  class Entite *m_Gemmes[MAX_ENTITES];
  //La seule instance est point�e par m_pEntiteManager
  static EntiteManager *m_pEntiteManager;

  //Obtenir un index libre dans le tableau d'entit�s
  int GetIndexLibre_Monstres ();
  int GetIndexLibre_Gemmes ();
  //Tester les chocs entre le h�ros et les autres entit�s
  void GererCollisions ();

//  friend void Affichage :: incr_nbrgemme();
  //On ne peut pas cr�er une instance avec new ni en d�truire une avec delete
  EntiteManager ();
  ~EntiteManager ();

  public:
    static EntiteManager* Create (); //Cr�e la seule instance et la renvoie
    static void Kill ();

    Entite* GetEntiteParIndex_Monstres (unsigned int);
    Entite* GetEntiteParIndex_Gemmes (unsigned int);
    //Cr�e le h�ros
    Hero* CreateHeros ();
    //Cr�e  monstre1
    Monstre_1* Creer_Monstre_1 (int, int);
    //Cr�e monstre2
    Monstre_2* Creer_Monstre_2 (int, int);
    //Cr�e montre3
    Monstre_3* Creer_Monstre_3 (int, int);
    //Cr�e gemme
    Gemme* Creer_Gemme(int,int);

    //Mise � jour de toutes les entit�s
    void Update ();

    //D�truit une entit�
    void KillEntite_Monstres (unsigned int);
      void KillEntite_Gemmes (unsigned int);
};

#endif
