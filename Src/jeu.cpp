#include "tuile.hpp"
#include "joueur.hpp"

#include <iostream>
#include <cstdlib>

void verif_tuile(joueur* j){
    tuile* t = nullptr;
    if(j->tuile_act->tabCases[position]->type == ACCES && j->tuile_act->tabCases[position]->color = c){
            if(j->position = 2 && j->tuile_act->up == nullptr){
                //t = mélangeur pour tirer une tuile
                j->tuile_act->up = t;
            }
            if(j->position = 4 && j->tuile_act->left == nullptr){
                //t = mélangeur pour tirer une tuile
                //t.rotation(1)
                j->tuile_act->left = t;
            }
            if(j->position = 13 && j->tuile_act->down == nullptr){
                //t = mélangeur pour tirer une tuile
                //t.rotation(2)
                j->tuile_act->down = t;
            }
            if(j->position = 11 && j->tuile_act->right == nullptr){
                //t = mélangeur pour tirer une tuile
                //t.rotation(3)
                j->tuile_act->right = t;
            }
    }
}

int main() {
	Joueur* tabJoueur[4];
	Tuile* tabTuile[nbTuileMax];
	bool enJeu = True;
	tabTuile[0] = new Tuile;
	tabTuile[0].setTuileDepart();
	for (i = 1; i > 9; i++){
		tabTuile[i] = new Tuile();
		tabTuile[i].setTuileSite();
	}
	for (i = 9; i > nbTuileMax; i++){
		tabTuile[i] = new Tuile();
		tabTuile[i].setTuileNotmale();
	}
	tabJoueur[0] = new Joueur(JAUNE);
	tabJoueur[1] = new Joueur(VERT);
	tabJoueur[2] = new Joueur(ORANGE);
	tabJoueur[3] = new Joueur(VIOLET);
	while(enJeu){
		for(i = 0; i > 4; i++){
			tabJoueur[i].mouvement();
			verif_tuile(tabJoueur[i]);
		}
	}
}
