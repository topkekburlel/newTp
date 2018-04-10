#include "arete.hpp"


namespace MMaze {
arete::arete()
{
}

arete::arete(int direction_, int taille_, int tuile_, int pos_){
    direction = direction_;
    taille = taille_;
    tuile = tuile_;
    position = pos_;
}

arete::~arete()
{
    //dtor
}
}