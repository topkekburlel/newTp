#include "tuile.hpp"
#include "joueur.hpp"
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
                //t = m�langeur pour tirer une tuile
                j->tuile_act->up = t;
            }
            if(j->position = 4 && j->tuile_act->left == nullptr){
                //t = m�langeur pour tirer une tuile
                //t.rotation(1)
                j->tuile_act->left = t;
            }
            if(j->position = 13 && j->tuile_act->down == nullptr){
                //t = m�langeur pour tirer une tuile
                //t.rotation(2)
                j->tuile_act->down = t;
            }
            if(j->position = 11 && j->tuile_act->right == nullptr){
                //t = m�langeur pour tirer une tuile
                //t.rotation(3)
                j->tuile_act->right = t;
            }
    }
}
*/

int main() {
	joueur * tabJoueur[4];
	Tuile * tabTuile[NB_TUILE_MAX];
	Tuile * tempTuile;
	int currIndexTuile = 0;
	int tempCouleur;
	Melangeur melTuiles = Melangeur(sizeof(Tuile));
	Melangeur couleurObjectifs = Melangeur(sizeof(int));
	Melangeur couleurSorties = Melangeur(sizeof(int));
	for(int i = 0; i<4; i++) {
		couleurObjectifs.inserer(&i);		// on insere 4 int dans les melangeurs qui representeront nos couleurs
		couleurSorties.inserer(&i);			// dans l'enum COULEUR
	}
	//bool enJeu = true;
	tabTuile[currIndexTuile] = new Tuile(currIndexTuile);  			// setup de la tuile de depart
	tabTuile[currIndexTuile]->setTuileDepart();
	currIndexTuile += 1;

	for (int i = 1; i < 5; i++){ 					// 4 tuiles avec un objectif
		couleurObjectifs.retirer(&tempCouleur);
		tabTuile[currIndexTuile] = new Tuile(currIndexTuile);
		tabTuile[currIndexTuile]->setTuileObjectif(tempCouleur);
		melTuiles.inserer(tabTuile[currIndexTuile]);
		currIndexTuile += 1;
	}
	for (int i = 5; i < 9; i++){ 					// 4 tuiles avec une sortie
		couleurSorties.retirer(&tempCouleur);
		tabTuile[currIndexTuile] = new Tuile(currIndexTuile);
		tabTuile[currIndexTuile]->setTuileSortie(tempCouleur);
		melTuiles.inserer(tabTuile[currIndexTuile]);
		currIndexTuile += 1;
	}
	for (int i = 9; i < NB_TUILE_MAX; i++){			// le reste en tuiles normale
		tabTuile[currIndexTuile] = new Tuile(currIndexTuile);
		tabTuile[currIndexTuile]->setTuileNormale();
		melTuiles.inserer(tabTuile[currIndexTuile]);
		currIndexTuile += 1;
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
