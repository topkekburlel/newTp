#include "tuile.hpp"
#include "couleurs.hpp"
#include "melangeur.hpp"

#include <cassert>
#include <iostream>
#include <cstdlib>

namespace MMaze {

Tuile::Tuile() {
    int i,j;
	nbMurs = 0;
    currNbSites = 0;
	tuile_depart = false;
	for(i = 0; i<16; i++)
    {
        tabCases[i] = new Case(i);
		tabSites[i] = new Site(tabCases[i],AUCUNE,RIEN);
    }
    for(j = 0; j<24; j++)
    {
        tabMurs[j] = new Mur(j);
		nbMurs += 1;
    }
	setTuileDepart();
}

bool Tuile::mur(Mur m) const {
	return tabMurs[m.index()];
}


void Tuile::union_site(Site* site1, Site* site2){
	site1 = rec_representante(site1);
	site2 = rec_representante(site2);
	if(site1 != site2){
		if(site1->hauteur < site2->hauteur){
			site1->representante = site2;
		}
		else{
			if(site1->hauteur == site2->hauteur){
				site1->hauteur = site1->hauteur + 1;
			}
			site2->representante = site1;
		}
	}
}

bool Tuile::verification(){
	Site* r = rec_representant(tabVraiSites[0])
	for(i=1; i<currNbSites; i++){
		if(rec_representant(tabVraiSites[i]) != r)
			return false;
	}
	return true;
}

bool Tuile::union_mur(Mur mur){
	site0 = rec_representante(tabSites[operator[](1).index_]);
	site1 = rec_representante(tabSites[operator[](0).index_]);
	if(site0 != site1){
		if(site0->hauteur < site1->hauteur){
			site0->representante = site1;
		}
		else{
			if(site0->hauteur == site1->hauteur){
				site0->hauteur = site0->hauteur + 1;
			}
			site1->representante = site0;
		}
		tabMurs[mur->index_] = NULL;
		return verification();
	}
	return false;
}


bool Tuile::accessible(Case c) const {
  /* remplacez ce code */
  return false;
}

void Tuile::afficher_horizontal(std::ostream& out, unsigned int i) const {
  assert(i < 5) ;
  if(i == 0 || i == 4) {
    out << "+---+---+---+---+" ;
  } else {
    out << "+" ;
    for(unsigned int m = 0; m < 4; ++m) {
      Case up = Case(i-1, m) ;
      Case down = Case(i, m) ;
      if(mur(Mur(up, down))) {
        out << "---+" ;
      } else {
        out << "   +" ;
      }
    }
  }
}

void Tuile::afficher_vertical(std::ostream& out, unsigned int i) const {
  assert(i < 4) ;
  out << "|" ;
  for(unsigned int m = 0; m < 4; ++m) {
    out << "   " ;
    if(m < 3) {
      Case left = Case(i, m) ;
      Case right = Case(i, m+1) ;
      if(m < 3 && mur(Mur(left, right))) {
        out << "|" ;
      } else {
        out << " " ;
      }
    }
  }
  out << "|" ;
}

void Tuile::setTuileDepart() {
	tuile_depart = true;
	Melangeur mel = Melangeur(sizeof(int));
	for(int i = 0; i<4; i++) {
		mel.inserer(&i);			// on insere 4 int dans le melangeur qui representera nos couleurs
	}
	int tabPortes[4] = {2,4,11,13};	// tableau des index des sites de type ACCES
	int tabDepart[4] = {5,6,9,10};	// tableau des index des sites de type POINT_DE_DEPART
	int index;
	int intCouleurHasard;
	enum Couleur cc;

	//PORTES
	for(int k = 0; k<4 ; k++) {
		index = tabPortes[k];
		mel.retirer(&intCouleurHasard);
		switch(intCouleurHasard) {
			case 1:
				cc = JAUNE;
				break;
			case 2:
				cc = ORANGE;
				break;
			case 3:
				cc = VERT;
				break;
			case 0:
				cc = VIOLET;
				break;
			default:
				std::cerr<<"Erreur : mauvaise couleur tiree pour une porte, iteration k = "<<k<<" et intCouleurHasard = "<<intCouleurHasard<<std::endl;
				break;
		}
		tabSites[index]->setColor(cc);
		tabSites[index]->setType(ACCES);
	}

	// DEPART
	for(int i = 0; i<4; i++) {
		mel.inserer(&i);
	}
	for(int k = 0; k<4 ; k++) {
		index = tabDepart[k];
		mel.retirer(&intCouleurHasard);
		switch(intCouleurHasard) {
			case 1:
				cc = JAUNE;
				break;
			case 2:
				cc = ORANGE;
				break;
			case 3:
				cc = VERT;
				break;
			case 0:
				cc = VIOLET;
				break;
			default:
				std::cerr<<"Erreur : mauvaise couleur tiree pour un depart, iteration k = "<<k<<" et intCouleurHasard = "<<intCouleurHasard<<std::endl;
				break;
		}
		tabSites[index]->setColor(cc);
		tabSites[index]->setType(POINT_DE_DEPART);
	}
}

void Tuile::setPortes() {

}

std::ostream& operator<< (std::ostream& out, const Tuile& t) {
  for(unsigned int i = 0; i < 4; ++i) {
    t.afficher_horizontal(out, i) ;
    out << std::endl ;
    t.afficher_vertical(out, i) ;
    out << std::endl ;
  }
  t.afficher_horizontal(out, 4) ;
  return out ;
}

} //end of namespace MMaze
