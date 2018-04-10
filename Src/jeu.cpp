#include "tuile.hpp"
//#include "joueur.hpp"
#include "melangeur.hpp"

#include <iostream>
#include <cstdlib>

#define NB_TUILE_MAX 40

namespace MMaze {
/*
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
*/

int main() {
	//Joueur* tabJoueur[4];
	//Tuile* tabTuile[NB_TUILE_MAX];
	Tuile * tempTuile;
	int tempCouleur;
	Melangeur melTuiles = Melangeur(sizeof(Tuile));
	Melangeur couleurObjectifs = Melangeur(sizeof(int));
	Melangeur couleurSorties = Melangeur(sizeof(int));
	for(int i = 0; i<4; i++) {
			couleurObjectifs.inserer(&i);		// on insere 4 int dans les melangeurs qui representeront nos couleurs
			couleurSorties.inserer(&i);			// dans l'enum COULEUR
	}
	//bool enJeu = true;
	Tuile * tuileDeDepart = new Tuile();  			// setup de la tuile de depart
	tuileDeDepart->setTuileDepart();
	
	for (int i = 1; i < 5; i++){ 					// 4 tuiles avec un objectif
		couleurObjectifs.retirer(&tempCouleur);
		tempTuile = new Tuile();
		tempTuile->setTuileObjectif(tempCouleur);
		melTuiles.inserer(tempTuile);
	}
	for (int i = 5; i < 9; i++){ 					// 4 tuiles avec une sortie
		couleurSorties.retirer(&tempCouleur);
		tempTuile = new Tuile();
		tempTuile->setTuileSortie(tempCouleur);
		melTuiles.inserer(tempTuile);
	}
	for (int i = 9; i < NB_TUILE_MAX; i++){			// le reste en tuiles normale
		tempTuile = new Tuile();
		tempTuile->setTuileNormale();
		melTuiles.inserer(tempTuile);
	}
	
	/*
	tabJoueur[0] = new Joueur(JAUNE);
	tabJoueur[1] = new Joueur(VERT);
	tabJoueur[2] = new Joueur(ORANGE);
	tabJoueur[3] = new Joueur(VIOLET);
	
	
	
	while(enJeu){
		for(i = 0; i > 4; i++){
			tabJoueur[i].mouvement();
			verif_tuile(tabJoueur[i]);
		}
	}*/
	/* avec un tableau de tuiles
	tabTuile[0] = new Tuile;
	tabTuile[0].setTuileDepart();
	for (i = 1; i < 5; i++){ 					// 4 tuiles avec un objectif
		couleurObjectifs.retirer(&tempCouleur);
		tabTuile[i] = new Tuile();
		tabTuile[i].setTuileObjectif(tempCouleur);
	}
	for (i = 5; i < 9; i++){ 					// 4 tuiles avec une sortie
		couleurSorties.retirer(&tempCouleur);
		tabTuile[i] = new Tuile();
		tabTuile[i].setTuileSortie(tempCouleur);
	}
	for (i = 9; i < NB_TUILE_MAX; i++){			// le reste en tuiles normale
		tabTuile[i] = new Tuile();
		tabTuile[i].setTuileNotmale();
	}
	*/
	return 0;
}

}