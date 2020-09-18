
#include "Fenetre.h"

int main ()
{
  Fenetre fenetre;

  return 0;
}

//Pour qu'on puisse compiler sous Windows
#ifdef WIN32

#include <windows.h>

int WINAPI WinMain (HINSTANCE, HINSTANCE, LPSTR, int)
{
  main ();
}

#endif


