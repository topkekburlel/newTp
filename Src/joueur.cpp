#include "joueur.hpp"

joueur::joueur()
{
    tuile_act = nullptr;
	position = 0;
	c = AUCUNE;
}

Joueur::joueur(int i, tuile* depart){
	tuile_act = depart;
	position = 1 + 4*(i/2) + (i%2);
	c = tabCases[position]->color;
}

joueur::~joueur()
{
    //dtor
}
