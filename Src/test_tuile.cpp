#include "tuile.hpp"
#include "melangeur.hpp"
#include "couleurs.hpp"
#include "joueur.hpp"
#include "Plateau.hpp"

#include <iostream>
#include <cstdlib>


using namespace MMaze ;

int main() {
	joueur * tabJoueur[4];
	Plateau * p = new Plateau();
	Tuile * tempTuile;
	bool enJeu = true;
	int currIndexTuile = 0;
	int tempCouleur;
	Melangeur melTuiles = Melangeur(sizeof(Tuile));
	Melangeur couleurObjectifs = Melangeur(sizeof(int));
	Melangeur couleurSorties = Melangeur(sizeof(int));
	for(int i = 0; i<4; i++) {
		couleurObjectifs.inserer(&i);		// on insere 4 int dans les melangeurs qui representeront nos couleurs
		couleurSorties.inserer(&i);			// dans l'enum COULEUR
	}
	
	p->tab_tuile[currIndexTuile] = new Tuile(currIndexTuile);  	// setup de la tuile de depart
	p->tab_tuile[currIndexTuile]->setTuileDepart();
	p->incNbTuile();
	currIndexTuile += 1;
	
	for (int i = 1; i < 5; i++){ 					// 4 tuiles avec un objectif
		couleurObjectifs.retirer(&tempCouleur);
		tempTuile = new Tuile(currIndexTuile);
		tempTuile->setTuileObjectif(tempCouleur);
		melTuiles.inserer(tempTuile);
		currIndexTuile += 1;
	}
	for (int i = 5; i < 9; i++){ 					// 4 tuiles avec une sortie
		couleurSorties.retirer(&tempCouleur);
		tempTuile = new Tuile(currIndexTuile);
		tempTuile->setTuileSortie(tempCouleur);
		melTuiles.inserer(tempTuile);
		currIndexTuile += 1;
	}
	for (int i = 9; i < 40; i++){			// le reste en tuiles normale
		tempTuile = new Tuile(currIndexTuile);
		tempTuile->setTuileNormale();
		melTuiles.inserer(tempTuile);
		currIndexTuile += 1;
	}
	
	//on set les joueurs !
	
	tabJoueur[0] = new joueur(0, p->tab_tuile[0],p);
	tabJoueur[1] = new joueur(1, p->tab_tuile[0],p);
	tabJoueur[2] = new joueur(2, p->tab_tuile[0],p);
	tabJoueur[3] = new joueur(3, p->tab_tuile[0],p);
	
	joueur * j;
	Case* c;
	Tuile* t;
	int obj_trouv;
	int iter = 0;
	while(enJeu) {
		iter++;
        for(int i = 0; i < 4; i++) {
			j = tabJoueur[i];
            if(!((j->status == j->tuile_act->tabCases[j->position]->type) || j->status != ACCES)) {
                c = j->trouve_site();
                tabJoueur[i]->mouvement(c->app_tuile, c->index_);
                c = j->tuile_act->tabCases[j->position];
                if((j->status == ACCES) && (c->type == ACCES) && (j->co == c->color) && c->nouv){
                    melTuiles.retirer(&t);
                    if(c->index_ == 2){
                        t->rotationTuile(3);
                        j->tuile_act->left = t;
                        j->plat_jeu->tab_tuile[j->tuile_act->left->id] = j->tuile_act->left;
						
                    }
                    if(c->index_ == 4){
                        j->tuile_act->up = t;
                        j->plat_jeu->tab_tuile[j->tuile_act->up->id] = j->tuile_act->up;
						
                    }
                    if(c->index_ == 11){
                        t->rotationTuile(1);
                        j->tuile_act->right = t;
                        j->plat_jeu->tab_tuile[j->tuile_act->right->id] = j->tuile_act->right;
                    }
                    if(c->index_ == 13){
                        t->rotationTuile(2);
                        j->tuile_act->down = t;
                        j->plat_jeu->tab_tuile[j->tuile_act->down->id] = j->tuile_act->down;
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
                if((j->status == OBJECTIF) && (c->type == OBJECTIF) && (j->co == c->color) && c->nouv){
                    c->nouv = false;
                    obj_trouv = obj_trouv + 1;
                    if(obj_trouv == 4){
                        for(i = 0; i < 4; i++){
                            tabJoueur[i]->status = SORTIE;
                        }
                        obj_trouv = 0;
                    }
                }
                if((j->status == SORTIE) && (c->type == SORTIE) && (j->co == c->color) && c->nouv){
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
int main() {

  Tuile t(0) ;
  
  std::cout << t << std::endl ;

  //utilisation des couleurs
  std::cout
    << TXT_JAUNE << "&"
    << TXT_ORANGE << "&"
    << TXT_VERT << "&"
    << TXT_VIOLET << "&"
    << TXT_CLEAR
    << BG_JAUNE << "&"
    << BG_ORANGE << "&"
    << BG_VERT << "&"
    << BG_VIOLET << "&"
    << TXT_CLEAR
    << std::endl ;

  return 0 ;
}
*/