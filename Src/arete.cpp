#include "arete.hpp"

#include "case.hpp"

arete::arete()
{
    case* = nullptr;
}

arete::arete(int direction_, int taille_, case* dest_){
    direction = direction_;
    taille = taille_;
    dest = dest_;
}

arete::~arete()
{
    //dtor
}
