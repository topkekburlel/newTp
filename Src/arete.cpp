#include "arete.hpp"

arete::arete()
{
    noeud* = nullptr;
}

arete::arete(int direction_, int taille_, noeud* dest_){
    direction = direction_;
    taille = taille_;
    dest = dest_;
}

arete::~arete()
{
    //dtor
}
