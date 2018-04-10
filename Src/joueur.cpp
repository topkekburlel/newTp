#include "joueur.hpp"

joueur::joueur()
{
    tuile_act = nullptr;
	position = -1;
	c = AUCUNE;
}

joueur::joueur(int i, tuile* depart){
    plat_jeu = plateau;
	tuile_act = depart;
	position = 1 + 4*(i/2) + (i%2);
	c = tabCases[position]->color;
}

joueur::~joueur()
{
    tuile_act = nullptr;
}

joueur::mouvement(int tuile, int pos)
{
    tuile_act = plat_jeu[tuile];
    position = pos;
}
