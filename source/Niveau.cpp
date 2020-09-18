#include "Niveau.h"
#include "Fenetre.h"

Niveau* Niveau :: m_pNiveau = NULL;

Niveau :: Niveau ()
{
  m_NiveauFini = false;


  //Taille du niveau ( 3 décor , le héros doit traverser 3 fois le décor pour arriver à la fin du niveau )
  m_nbDecors = 9;

  //Création des entités ( monstre dans des endroits different du niveau )
  int g;
  int gact=0;
  for(g=250;g<m_nbDecors*FENETRE_LARGEUR;g=g+100)
  {
         EntiteManager :: Create () -> Creer_Gemme ( g , 0);
  }
 // EntiteManager :: Create () -> Creer_Gemme ( 250 , 0);

  EntiteManager :: Create () -> Creer_Monstre_1 (200, 0);
  EntiteManager :: Create () -> Creer_Monstre_1 (275, 0);

 EntiteManager :: Create () -> Creer_Monstre_2 (450, 0);
  EntiteManager :: Create () -> Creer_Monstre_2 (600, 0);
  EntiteManager :: Create () -> Creer_Monstre_3 (750, FENETRE_HAUTEUR / 2);
  EntiteManager :: Create () -> Creer_Monstre_1 (750, 0);
  EntiteManager :: Create () -> Creer_Monstre_1 (950, 0);
  EntiteManager :: Create () -> Creer_Monstre_1 (1000, 0);
  EntiteManager :: Create () -> Creer_Monstre_2 (1200, 0);
  EntiteManager :: Create () -> Creer_Monstre_1 (1300, 0);
  EntiteManager :: Create () -> Creer_Monstre_1 (1400, 0);
  EntiteManager :: Create () -> Creer_Monstre_1 (1450, 0);
  EntiteManager :: Create () -> Creer_Monstre_1 (1550, 0);
  EntiteManager :: Create () -> Creer_Monstre_1 (1650, 0);
  EntiteManager :: Create () -> Creer_Monstre_2 (1800, 0);
  EntiteManager :: Create () -> Creer_Monstre_3 (1850, FENETRE_HAUTEUR);
  EntiteManager :: Create () -> Creer_Monstre_1 (1900, 0);
  EntiteManager :: Create () -> Creer_Monstre_1 (2000, 0);
  EntiteManager :: Create () -> Creer_Monstre_1 (2150, 0);
  EntiteManager :: Create () -> Creer_Monstre_1 (2200, 0);
  EntiteManager :: Create () -> Creer_Monstre_2 (2300, 0);
  EntiteManager :: Create () -> Creer_Monstre_3 (2550, FENETRE_HAUTEUR * 2);
  EntiteManager :: Create () -> Creer_Monstre_1 (2650, 0);
  EntiteManager :: Create () -> Creer_Monstre_1 (2800, 0);
  EntiteManager :: Create () -> Creer_Monstre_1 (2900, 0);
  EntiteManager :: Create () -> Creer_Monstre_2 (3050, 0);
  EntiteManager :: Create () -> Creer_Monstre_1 (3200, 0);
  EntiteManager :: Create () -> Creer_Monstre_3 (3250, FENETRE_HAUTEUR * 2);
  EntiteManager :: Create () -> Creer_Monstre_1 (3275, 0);
  EntiteManager :: Create () -> Creer_Monstre_1 (3400, 0);
  EntiteManager :: Create () -> Creer_Monstre_1 (3550, 0);
  EntiteManager :: Create () -> Creer_Monstre_1 (3700, 0);
  EntiteManager :: Create () -> Creer_Monstre_3 (3800, FENETRE_HAUTEUR * 3);
  EntiteManager :: Create () -> Creer_Monstre_3 (3900, FENETRE_HAUTEUR * 3);
  EntiteManager :: Create () -> Creer_Monstre_2 (3900, 0);
  EntiteManager :: Create () -> Creer_Monstre_1 (4050, 0);
  EntiteManager :: Create () -> Creer_Monstre_2 (4100, 0);
  EntiteManager :: Create () -> Creer_Monstre_1 (4250, 0);
  EntiteManager :: Create () -> Creer_Monstre_3 (4300, FENETRE_HAUTEUR * 4);
  EntiteManager :: Create () -> Creer_Monstre_2 (4450, 0);
  EntiteManager :: Create () -> Creer_Monstre_2 (4600, 0);
  EntiteManager :: Create () -> Creer_Monstre_1 (4700, 0);
  EntiteManager :: Create () -> Creer_Monstre_1 (4900, 0);
  EntiteManager :: Create () -> Creer_Monstre_2 (5050, 0);
  EntiteManager :: Create () -> Creer_Monstre_3 (5300, FENETRE_HAUTEUR * 4);
}

Niveau :: ~Niveau ()
{
}

//GETTERS & SETTERS

void Niveau :: SetNiveauFini ()
{
    //Si le niveau n'est pas null
  if (m_pNiveau != NULL)
    m_pNiveau -> m_NiveauFini = true;
}

bool Niveau :: GetNiveauFini ()
{
     //Si le niveau n'est pas null
  if (m_pNiveau != NULL)
  //on retourne que le niveau est fini
    return m_pNiveau -> m_NiveauFini;
  //sinon
  return false;
}

int Niveau :: GetNbDecors ()
{
  if (m_pNiveau != NULL)
    return m_pNiveau -> m_nbDecors;
  return -1;
}


//création de niveau
Niveau* Niveau :: Create ()
{
  if (m_pNiveau == NULL)
    m_pNiveau = new Niveau;
  return m_pNiveau;
}

//déstruction de niveau
void Niveau :: Kill ()
{
  delete m_pNiveau;
  m_pNiveau = NULL;
}
