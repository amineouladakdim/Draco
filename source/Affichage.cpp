#include "Affichage.h"
#include "Niveau.h"
#include "Hero.h"
#include "sstream"
using namespace std;

char * NomsImages[] =
{
  "Images\\Heros\\Marche1.png",
  "Images\\Heros\\Marche2.png",
  "Images\\Heros\\Saut1.png",
  "Images\\Heros\\Saut2.png",
  "Images\\MONSTRE1\\Marche1.png",
  "Images\\MONSTRE1\\Marche2.png",
  "Images\\MONSTRE1\\Mort.png",
  "Images\\MONSTRE2\\Marche1.png",
  "Images\\MONSTRE2\\Marche2.png",
  "Images\\MONSTRE2\\Marche3.png",
  "Images\\MONSTRE2\\Marche4.png",
  "Images\\MONSTRE2\\Mort.png",
  "Images\\MONSTRE3\\Chute.png",
  "Images\\MONSTRE3\\Marche1.png",
  "Images\\MONSTRE3\\Marche2.png",
  "Images\\MONSTRE3\\Mort.png",
  "IMAGES\\Bonus\\gemme.png"
};

Affichage* Affichage :: m_pAffichage = NULL;

//void Affichage::incr_nbrgemme()
//{
//}


void Affichage::Afficher_Nbr_Gemmes()
{
    SDL_Surface* gem=NULL;

std::string result;
std::stringstream sstm;
sstm << "x" << Affichage::Get_nbrgemme() ;
result = sstm.str();

 gem = IMG_Load (NomsImages[16]);

TTF_Font *police = NULL;
SDL_Surface* texte =NULL;
SDL_Rect posi;
posi.x=50;
posi.y=50;

SDL_Rect posig;
posig.x=15;
posig.y=50;
SDL_Color couleurNoire = {255, 255, 255};
/* Chargement de la police */
police = TTF_OpenFont("arial.ttf", 20);

/* �criture du texte dans la SDL_Surface texte en mode Blended (optimal) */
texte= TTF_RenderText_Solid(police, result.c_str() , couleurNoire);

SDL_BlitSurface (texte, NULL, m_Surface, &posi);
SDL_BlitSurface (gem, NULL, m_Surface, &posig);

SDL_FreeSurface(texte);
SDL_FreeSurface(gem);
TTF_CloseFont(police);


}
 //void Affichage::Set_nbrgemme(int x)
//{
    //nbr_gemmes=x;
//}

int Affichage::nbr_gemmes=0;

 int Affichage::Get_nbrgemme()
{
   return nbr_gemmes;
//return 1;
}
Affichage :: Affichage (int x)
{
//nbr_gemmes=x;
}



Affichage :: Affichage ()
{
  m_TimerNiveauEnclenche = false;
// nbr_gemmes=0;
  //Chargement des images

  //Images des entit�s
  m_Pictures = new SDL_Surface* [NB_IMAGES];
  for (int i = 0; i < NB_IMAGES; i++)
  {
    m_Pictures[i] = IMG_Load (NomsImages[i]);
  }


  //Chargement de l'�cran d'accueil
  m_Intro = IMG_Load(IMG_INTRO);
  //Chargement du paysage
  m_Decor = IMG_Load (IMG_PAYSAGE);
  //Chargement de l'�cran "Gagn�"
  m_Gagne = IMG_Load (IMG_GAGNE);
  //Chargement du drapeau "fin"
  m_Fin = IMG_Load (IMG_FIN);
}

Affichage :: ~Affichage ()
{
  //D�chargement des images
  for (int i = 0; i < NB_IMAGES; i++)
    SDL_FreeSurface (m_Pictures[i]);
  delete m_Pictures;
  SDL_FreeSurface (m_Intro);
  SDL_FreeSurface (m_Decor);
  SDL_FreeSurface (m_Gagne);
  SDL_FreeSurface (m_Fin);
}

Affichage* Affichage :: Create (SDL_Surface* Surface)
{
  if (m_pAffichage == NULL)
  {
    m_pAffichage = new Affichage;
    m_pAffichage -> m_Surface= Surface;
  }
  return m_pAffichage;
}

void Affichage :: Kill ()
{
  if (m_pAffichage != NULL)
  {
    delete m_pAffichage;
    m_pAffichage = NULL;
  }
}

void Affichage :: DessinerPaysage ()
{
  Hero* Heros = Hero :: Create ();
  if (Heros == NULL)
    return;
  //La position du h�ros
  int x = Heros -> x (), y = Heros -> y (), cx = Heros -> cx ();
  //Le nombre de fois que le paysage doit �tre dessin�
  int nb = (x % FENETRE_LARGEUR == 0) ? 1: 2;

  //Rectangle dans lequel doit �tre dessin�e l'image
  SDL_Rect RectImage = { 0, 0, FENETRE_LARGEUR, FENETRE_HAUTEUR };

  for (int i = 0; i < nb; i++)
  {
    if (i == 0) //Dessin de la premi�re partie du paysage
      RectImage.x = -(x % FENETRE_LARGEUR);
    else //Dessin de la deuxi�me partie du paysage
      RectImage.x = -(x % FENETRE_LARGEUR - FENETRE_LARGEUR);

    SDL_BlitSurface (m_Decor, NULL, m_Surface, &RectImage);
  }

  int Fin = Niveau :: Create () -> GetNbDecors () * FENETRE_LARGEUR;

  //Dessin du drapeau s'il doit �tre affich�
  if (Fin > x - cx - FENETRE_LARGEUR / 2 && Fin < x + cx + FENETRE_LARGEUR / 2)
  {
    RectImage.x = Fin - (x - FENETRE_LARGEUR / 2);
    RectImage.y = 345 - FIN_CY;
    RectImage.w = FIN_CX;
    RectImage.h = FIN_CY;
    SDL_BlitSurface (m_Fin, NULL, m_Surface, &RectImage);
  }
}

void Affichage :: DessinerJeu ()
{
  //Si le joueur a termin� le niveau
  if (Niveau :: GetNiveauFini ())
  {
    //Si le chronom�tre a d�j� �t� enclench�
    if (m_TimerNiveauEnclenche)
    {
      //On attend 2 secondes avant d'afficher l'�cran
      if (m_TimerNiveauFini.Get () > 1000)
      {
        //On affiche l'�cran "Gagn�"
        SDL_BlitSurface (m_Gagne, NULL, m_Surface, NULL);
        SDL_Flip (m_Surface);
        return;
      }
    }
    else
    {
      m_TimerNiveauEnclenche = true;
      m_TimerNiveauFini.Init ();
    }
    return;
  }

  //On dessine d'abord le fond
  DessinerPaysage ();

  //Le gestionnaire d'entit�s
  EntiteManager* EntiteManager = EntiteManager :: Create ();
  //Mise � jour des entit�s
  EntiteManager -> Update ();

  Entite* Entite;
  int cx, cy, x, y;
  SDL_Rect Image;

  //Position du h�ros
  int xHeros = Hero :: Create () -> x ();
  int yHeros = Hero :: Create () -> y ();

//Affichage des monstres
  for (int i = 0; i < MAX_ENTITES; i++)
  {
    Entite = EntiteManager -> GetEntiteParIndex_Monstres (i);

    //Si l'entit� n'existe pas ou elle ne peut pas �tre affich�e � l'�cran
    if (Entite == NULL || !Entite -> EstDansEcran (Hero :: Create ()))
      continue;

    //Position de l'entit�
    x = Entite -> x ();
    y = Entite -> y ();

    //Dimensions de l'entit�
    Image.w = Entite -> cx ();
    Image.h = Entite -> cy ();

    //Si l'entit� est le h�ros on dessine l'image de fa�on sp�ciale (pour le centrer)
    if (i == INDEX_ENTITE_HEROS)
    {
      Image.x = FENETRE_HAUTEUR / 2 + Image.w;
     // Image.y = FENETRE_HAUTEUR - yHeros - Image.h;
     Image.y = 345 - yHeros - Image.h;
    }
    else
    {
      Image.x = x - (xHeros - FENETRE_LARGEUR / 2);
      Image.y = 345 - y - Image.h;
    //  Image.y = FENETRE_HAUTEUR - y - Image.h;
    }

    SDL_BlitSurface (m_Pictures[Entite -> GetImage ()], NULL, m_Surface, &Image);
  }

  //Affichage des gemmes

   for (int i = 0; i < MAX_ENTITES; i++)
  {
    Entite = EntiteManager -> GetEntiteParIndex_Gemmes(i);

    //Si l'entit� n'existe pas ou elle ne peut pas �tre affich�e � l'�cran
    if (Entite == NULL || !Entite -> EstDansEcran (Hero :: Create ()))
      continue;

    //Position de l'entit�
    x = Entite -> x ();
    y = Entite -> y ();

    //Dimensions de l'entit�
    Image.w = Entite -> cx ();
    Image.h = Entite -> cy ();


      Image.x = x - (xHeros - FENETRE_LARGEUR / 2);
      Image.y = 345 - y - Image.h;


    SDL_BlitSurface (m_Pictures[Entite -> GetImage ()], NULL, m_Surface, &Image);
  }

Afficher_Nbr_Gemmes();

  SDL_Flip (m_Surface);
}

void Affichage :: DessinerIntro ()
{
  SDL_BlitSurface (m_Intro, NULL, m_Surface, NULL);
  SDL_Flip (m_Surface);
}
