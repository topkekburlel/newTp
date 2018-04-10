#include "joueur.hpp"


namespace MMaze {
joueur::joueur()
{
    tuile_act = nullptr;
	position = -1;
	c = AUCUNE;
}

joueur::joueur(int i, Tuile* depart, Plateau* plateau){
    plat_jeu = plateau;
	tuile_act = depart;
	position = 1 + 4*(i/2) + (i%2);
	c = tuile_act->tabCases[position]->color;
}

joueur::~joueur()
{
    tuile_act = nullptr;
}

void joueur::mouvement(int tuile, int pos)
{
    tuile_act = plat_jeu->tab_tuile[tuile];
    position = pos;
}
}
