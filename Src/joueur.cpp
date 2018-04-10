#include "joueur.hpp"
#include "tuile.hpp"

#include <queue>

namespace MMaze {
joueur::joueur()
{
    tuile_act = nullptr;
	position = -1;
	color_j = AUCUNE;
	status = 0;
}

joueur::joueur(int i, Tuile* depart, Plateau* plateau){
    plat_jeu = plateau;
	tuile_act = depart;
	position = 1 + 4*(i/2) + (i%2);
	color_j = tuile_act->tabCases[position]->color;
	status = 0;
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

Case* joueur::trouve_site(){
	Case* c = tuile_act->tabCases[position];
	Case* d;
	Arete* a;
	int niveau, iteration, taille_niveau, taille_niveau_suiv;
	std::queue<Arete*> f;
	std::queue<Arete*> g;
	if(status < 4) {
		c->visit = false;
		for(int i = 0; i < c->nbArete; i++){
			f.push(c->tab_access[i]);
		}
		niveau = 1;
		iteration = 1;
		taille_niveau = c->nbArete;
		taille_niveau_suiv = 0;
		while(!f.empty()){
			a = f.front();
			g.push(a);
			f.pop();
			c = plat_jeu->tab_tuile[a->tuile]->tabCases[a->position];
			for(int i = 0; i < c->nbArete; i++){
				a = c->tab_access[i];
				d = plat_jeu->tab_tuile[a->tuile]->tabCases[a->position];
				if(d->visit){
					if(d->type == status && d->color == color_j){
						while(!g.empty()){
							a = g.front();
							d = plat_jeu->tab_tuile[a->tuile]->tabCases[a->position];
							d->visit = true;
							g.pop();
						}
						return c;
					}
					f.push(a);
					taille_niveau_suiv = taille_niveau_suiv + 1;
					iteration = iteration + 1;
				}
			}
			if(iteration == taille_niveau){
				niveau = niveau + 1;
				taille_niveau = taille_niveau_suiv;
				iteration = 1;
				taille_niveau_suiv = 0;
			}
			c->visit = false;
		}
	}
	return tuile_act->tabCases[position];
}

}
