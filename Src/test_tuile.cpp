#include "tuile.hpp"
#include "melangeur.hpp"
#include "couleurs.hpp"

#include <iostream>
#include <cstdlib>

using namespace MMaze ;

int main() {

  Tuile t ;
  std::cout << t << std::endl ;

  //utilisation des couleurs
  std::cout
    << TXT_JAUNE << "&"
    << TXT_ORANGE << "&"
    << TXT_VERT << "&"
    << TXT_VIOLET << "&"
    << TXT_CLEAR
    << BG_JAUNE << "&"
    << BG_ORANGE << "&"
    << BG_VERT << "&"
    << BG_VIOLET << "&"
    << TXT_CLEAR
    << std::endl ;

  return 0 ;
}
