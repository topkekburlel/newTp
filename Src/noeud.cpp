#include "noeud.hpp"

noeud::noeud()
{
    localisation = nullptr;
    id = -1;
    nbArete = 0
}

noeud::noeud(tuile* tuile, int case_id){
    localisation = tuile;
    id = case_id;
}

noeud::~noeud()
{
    //dtor
}
