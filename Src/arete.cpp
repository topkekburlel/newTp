#include "arete.hpp"


namespace MMaze {
Arete::Arete()
{
}

Arete::Arete(int direction_, int taille_, int tuile_, int pos_){
    direction = direction_;
    taille = taille_;
    tuile = tuile_;
    position = pos_;
}
}
