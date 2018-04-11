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

	Joueur * tabJoueur[4];
	Tuile * tabTuile[NB_TUILE_MAX];
	Tuile * tempTuile;
	int currIndexTuile = 0;
	int tempCouleur;
	int obj_trouv = 0;
	Melangeur melTuiles = Melangeur(sizeof(Tuile));
	Melangeur couleurObjectifs = Melangeur(sizeof(int));
	Melangeur couleurSorties = Melangeur(sizeof(int));
	Joueur* j;
	Case* c;
	bool enJeu = true;
	for(int i = 0; i<4; i++) {
		couleurObjectifs.inserer(&i);		// on insere 4 int dans les melangeurs qui representeront nos couleurs
		couleurSorties.inserer(&i);			// dans l'enum COULEUR
	}
	//bool enJeu = true;
	tabTuile[currIndexTuile] = new Tuile(currIndexTuile);  			// setup de la tuile de depart
	tabTuile[currIndexTuile]->setTuileDepart();
	tabTuile[currIndexTuile]->arete_tuile();
	currIndexTuile += 1;

	for (int i = 1; i < 5; i++){ 					// 4 tuiles avec un objectif
		couleurObjectifs.retirer(&tempCouleur);
		tabTuile[currIndexTuile] = new Tuile(currIndexTuile);
		tabTuile[currIndexTuile]->setTuileObjectif(tempCouleur);
		tabTuile[currIndexTuile]->arete_tuile();
		melTuiles.inserer(tabTuile[currIndexTuile]);
		currIndexTuile += 1;
	}
	for (int i = 5; i < 9; i++){ 					// 4 tuiles avec une sortie
		couleurSorties.retirer(&tempCouleur);
		tabTuile[currIndexTuile] = new Tuile(currIndexTuile);
		tabTuile[currIndexTuile]->setTuileSortie(tempCouleur);
		melTuiles.inserer(tabTuile[currIndexTuile]);
		tabTuile[currIndexTuile]->arete_tuile();
		currIndexTuile += 1;
	}
	for (int i = 9; i < NB_TUILE_MAX; i++){			// le reste en tuiles normale
		tabTuile[currIndexTuile] = new Tuile(currIndexTuile);
		tabTuile[currIndexTuile]->setTuileNormale();
		melTuiles.inserer(tabTuile[currIndexTuile]);
		tabTuile[currIndexTuile]->arete_tuile();
		currIndexTuile += 1;
	}

/*
	tabJoueur[0] = new Joueur(JAUNE);
	tabJoueur[1] = new Joueur(VERT);
	tabJoueur[2] = new Joueur(ORANGE);
	tabJoueur[3] = new Joueur(VIOLET);

*/

	while(enJeu) {
        for(int i = 0; i > 4; i++) {
            j = tabJoueur[i];
            if(j->status != j->tuile_act->tabCases[j->position]->type || j->status == ACCES){
                c = j->trouve_site();
                j->mouvement(c->app_tuile, c->index_);
                Case* c = j->tuile_act->tabCases[j->position];
                if(j->status == ACCES && c->type == ACCES && j->co == c->color && c->nouv){
                    melTuiles.retirer(&tempTuile);
                    if(c->index_ == 2){
                        tempTuile->rotationTuile(3);
                        j->tuile_act->left = tempTuile;
                        j->plat_jeu->tab_tuile[j->tuile_act->left->id] = j->tuile_act->left;
                    }
                    if(c->index_ == 4){
                        j->tuile_act->up = tempTuile;
                        j->plat_jeu->tab_tuile[j->tuile_act->up->id] = j->tuile_act->up;
                    }
                    if(c->index_ == 11){
                        tempTuile->rotationTuile(1);
                        j->tuile_act->right = tempTuile;
                        j->plat_jeu->tab_tuile[j->tuile_act->right->id] = j->tuile_act->right;
                    }
                    if(c->index_ == 13){
                        tempTuile->rotationTuile(2);
                        j->tuile_act->down = tempTuile;
                        j->plat_jeu->tab_tuile[j->tuile_act->down->id] = j->tuile_act->down;
                    }
                    j->tuile_act->connecte_tuile_arete(c);
                    c->nouv = false;
                    if(tempTuile->id < 9){
                        obj_trouv = obj_trouv + 1;
                        if(obj_trouv == 8){
                            for(i = 0; i < 4; i++){
                                tabJoueur[i]->status = OBJECTIF;
                            }
                            obj_trouv = 0;
                        }
                    }
                }
                if(j->status == OBJECTIF && c->type == OBJECTIF && j->co == c->color && c->nouv){
                    c->nouv = false;
                    obj_trouv = obj_trouv + 1;
                    if(obj_trouv == 4){
                        for(i = 0; i < 4; i++){
                            tabJoueur[i]->status = SORTIE;
                        }
                        obj_trouv = 0;
                    }
                }
                if(j->status == SORTIE && c->type == SORTIE && j->co == c->color && c->nouv){
                    c->nouv = false;
                    obj_trouv = obj_trouv + 1;
                    if(obj_trouv == 4){
                        enJeu = false;
                    }
                }
            }
        }
    }
	return 0;
}

/*
void verif_pos(Joueur*j){
    Case* c = j->tuile_act->tabCases[position];
    if(j->status == ACCES && c->type == ACCES && j->co == c->color && c->nouv){
        Tuile* t = melTuiles.retirer();
        if(c->index_ == 2){
            t->rotationTuile(3);
            j->tuile_act->left = t;
            j->plat_jeu->tab_tuiles[j->tuile_act->left->id] = j->tuile_act->left;
        }
        if(c->index_ == 4){
            j->tuile_act->up = t;
            j->plat_jeu->tab_tuiles[j->tuile_act->up->id] = j->tuile_act->up;
        }
        if(c->index_ == 11){
            t->rotationTuile(1)
            j->tuile_act->right = t;
            j->plat_jeu->tab_tuiles[j->tuile_act->right->id] = j->tuile_act->right;
        }
        if(c->index_ == 13){
            t->rotationTuile(2);
            j->tuile_act->down = t;
            j->plat_jeu->tab_tuiles[j->tuile_act->down->id] = j->tuile_act->down;
        }
        j->tuile_act->connecte_tuile_arete(c);
        c->nouv = false;
        if(t->id < 9){
            obj_trouv = obj_trouv + 1;
            if(obj_trouv == 8){
                for(i = 0; i < 4; i++){
                    tabJoueur[i]->status = OBJECTIF;
                }
                obj_trouv = 0;
            }
        }
    }
    if(j->status == OBJECTIF && c->type == OBJECTIF && j->co == c->color && c->nouv){
        c->nouv = false;
        obj_trouv = obj_trouv + 1;
        if(obj_trouv == 4){
            for(i = 0; i < 4; i++){
                    tabJoueur[i]->status = SORTIE;
                }
                obj_trouv = 0;
        }
    }
    if(j->status == SORTIE && c->type == SORTIE && j->co == c->color && c->nouv){
        c->nouv = false;
        obj_trouv = obj_trouv + 1;
        if(obj_trouv == 4){
            enJeu = false;
        }
    }
}*/

}
