#include "Fenetre.h"
#include "Niveau.h"
#include "Entite.h"
#include "Hero.h"

//En créant une fenetre on instancie le héros , le niveau et l'entité manager ainsi que les entrées du clavier
Fenetre :: Fenetre ()
{
    EntiteManager :: Create ();
	Hero :: Create ();
	Niveau :: Create ();

  m_Entree = Entree_Clavier :: Create ();
  m_Ecran = NULL;
  //La page qu'on affiche est celle de l'intro
  m_Page = PAGE_INTRO;

  m_TimerFinLance = false;

  //Création de le fenêtre (SDL , initalisation de la taille , des couleurs )
  CreerFenetre ();
}

Fenetre :: ~Fenetre ()
{
	EntiteManager :: Kill ();
  Niveau :: Kill ();
  Entree_Clavier:: Kill ();
}
Mix_Music* msc;

void Fenetre :: CreerFenetre ()
{
    TTF_Init();
  if (SDL_Init (SDL_INIT_VIDEO) < 0)
  {
    fprintf (stderr, "Impossible d'initialiser SDL : %s", SDL_GetError ());
    return;
  }

    if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024) == -1) //Initialisation de l'API Mixer
   {
      printf("%s", Mix_GetError());
   }
 Mix_AllocateChannels(6); //Allouer 6 canaux

   msc=jouer_musique();

  m_Ecran = SDL_SetVideoMode (FENETRE_LARGEUR, FENETRE_HAUTEUR, 24, SDL_HWSURFACE | SDL_DOUBLEBUF);
  if (m_Ecran == NULL)
  {
    fprintf (stderr, "Impossible de passer en %dx%d 24bits : %s",
          FENETRE_LARGEUR, FENETRE_HAUTEUR, SDL_GetError ());
    return;
  }

   //Pas de curseur
	SDL_ShowCursor (0);
	//Titre de la fenêtre
	SDL_WM_SetCaption ("The tales of Draco", 0);

	GestionEvenements ();
 //Libération de la surface
  SDL_FreeSurface (m_Ecran);
  //Mix_HaltMusic(); //Arrête la musique
   Mix_CloseAudio(); //Fermeture de l'API
   Mix_FreeMusic(msc); //Libération de la musique
  TTF_Quit();
  SDL_Quit ();
}
Mix_Music* Fenetre::jouer_musique()
{
     Mix_Music *musique; //Création du pointeur de type Mix_Music
   musique = Mix_LoadMUS("Musique/musique.mid"); //Chargement de la musique
      Mix_VolumeMusic(MIX_MAX_VOLUME / 4); //Mettre le volume à la moitié
   Mix_PlayMusic(musique, -1); //Jouer infiniment la musique

return musique;
}

void Fenetre::jouer_son(int s)
{
     Mix_Chunk *son; //Création du pointeur de type Mix_Music
     if(s==1)
     {
   son = Mix_LoadWAV("Musique/star.wav"); //Chargement de la musique
   Mix_PlayChannel(2, son,0);
     }
     else if (s==2)
     {
       son = Mix_LoadWAV("Musique/jump.wav"); //Chargement de la musique
   Mix_PlayChannel(3, son,0);
     }
     else if (s==3)
     {
       son = Mix_LoadWAV("Musique/destroy.wav"); //Chargement de la musique
   Mix_PlayChannel(4, son,0);
     }
     else if (s==4)
     {
       son = Mix_LoadWAV("Musique/bumper.wav"); //Chargement de la musique
   Mix_PlayChannel(5, son,0);
     }


}
void Fenetre :: GestionEvenements ()
{
  Affichage* Affichage = Affichage :: Create (m_Ecran);
  SDL_Event event;
  while (1)
  {
    switch (m_Page)
    {
      case PAGE_INTRO:
        m_Page = PageIntro ();
        Affichage -> DessinerIntro ();
        break;
      case PAGE_JEU:
        if (Hero :: Create () -> GetEtat () == MORT || Niveau :: Create () -> GetNiveauFini ())
        {
          //il faut lancer le chronomètre
          if (!m_TimerFinLance)
          {
            m_TimerFin.Init ();
            m_TimerFinLance = true;
          }
          else
          {
            m_TimerFinLance = false;
            m_Page = PAGE_INTRO;
          }
        }
        m_Page = PageJeu ();
        Affichage -> DessinerJeu ();
        break;
      case PAGE_NULL: //On quitte
        return;
    }
  }
  Affichage :: Kill ();
}

EPage Fenetre :: PageIntro ()
{
  SDL_Event event;
  while (SDL_PollEvent (&event))
  {
    switch (event.type)
    {
      case SDL_QUIT:
        return PAGE_NULL;
      case SDL_KEYDOWN:
        if (((SDL_KeyboardEvent*) &event) -> keysym.sym == SDLK_ESCAPE)
          return PAGE_NULL;
        if (((SDL_KeyboardEvent*) &event) -> keysym.sym == SDLK_SPACE)
          return PAGE_JEU;
    }
  }
  return PAGE_INTRO;
}

EPage Fenetre :: PageJeu ()
{
  SDL_Event event;
  while (SDL_PollEvent (&event))
  {
    switch (event.type)
    {
      case SDL_QUIT:
        return PAGE_NULL;
      case SDL_KEYDOWN:
      case SDL_KEYUP:
        //Si on appuie Echap
        if (m_Entree -> Event ((SDL_KeyboardEvent*) &event) == true)
        {
          //Si le héros n'est plus vivant, on retourne à l'écran principal
          if (Hero :: Create () -> GetEtat () != VIVANT || Niveau :: Create () -> GetNiveauFini ())
          {
            //On détruit toutes les classes
            EntiteManager :: Kill ();
            Niveau :: Kill ();

            //Et on les recrée
            EntiteManager :: Create ();
            Niveau :: Create ();

            return PAGE_INTRO;
          }
        //Sinon, on quitte le jeu
        return PAGE_NULL;
        }
    }
  }
  return PAGE_JEU;
}
