#ifndef MMAZE_DIRECTION_HPP
#define MMAZE_DIRECTION_HPP

using namespace std;
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

namespace MMaze {

enum Direction {
  BAS,
  DROITE,
  HAUT,
  GAUCHE
};

Direction tourne(Direction d, int r) ;

Direction opposee(Direction d) ;

const char* nom(Direction d) ;

} //end of namespace MMaze

#endif
