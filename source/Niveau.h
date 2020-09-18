#ifndef Niveau_H_
#define Niveau_H_

#include "EntiteManager.h"

//#define FICHIER_NIVEAU "IGLU.niv"

class Niveau
{
  //Est-ce que le niveau est fini ?
  bool m_NiveauFini;

  //Nombre de décors constituant le niveau
  int m_nbDecors;

  //Seule instance possible
  static Niveau* m_pNiveau;

  Niveau ();
  ~Niveau ();

  public:
    static Niveau* Create ();
    static void Kill ();

    static void SetNiveauFini ();
    static bool GetNiveauFini ();

    static int GetNbDecors ();
};

#endif
