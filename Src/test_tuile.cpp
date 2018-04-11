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
	Plateau * p;
	Tuile * tempTuile;
	bool enJeu = true;
	// int currIndexTuile = 0;
	int currIndexTuile = 1;
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

	int indexCaseAcces = 0; // contiendra l'index de la case ACCES de la tuile piochee
	while(enJeu) {
        for(int i = 0; i > 4; i++) {
			Case * c = tabJoueur[i]->trouve_site();
			tabJoueur[i]->mouvement(c->app_tuile, c->index_);
			// si un joueur se trouve sur un case de type ACCES .. ET que sa couleur correspond à la couleur de la case ALORS on tire une tuile
			if(tabJoueur[i]->tuile_act->tabCases[tabJoueur[i]->position]->getType() == ACCES && tabJoueur[i]->tuile_act->tabCases[tabJoueur[i]->position]->getCouleur() == tabJoueur[i]->co) {
				melTuiles.retirer(&tempTuile);
				p->tab_tuile[tempTuile->id] = tempTuile;
				/*
				*** ON CONNECTE la case : tabJoueur[i]->tuile_act->tabCases[position] AVEC la case : tempTuile->tabCases[indexCaseAcces] ***
				* 	connecte_tuile_arete(tabJoueur[i]->tuile_act->tabCases[position]) ?
				*/
				// et la vie continue =D (en vré .. mon domaine de compétences s'arrête là ...)
			}
        }
		//faudra pas oublier de set :  enJeu = false
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