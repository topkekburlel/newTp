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
}

bool Tuile::mur(Mur m) const {
	return tabMurs[m.index()];
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
		mel.inserer(i);
	}
	int* tabPortes = {2,4,11,13};
	int* tabDepart = {5,6,9,10};
	int index;
	int intCouleurHasard;
	enum Couleur cc;
	
	//PORTES
	for(int k = 0; k<4 ; k++) {
		index = tabPortes[k];
		mel.retirer(intCouleurHasard);
		
		tabCases[index]. //  ici faut tirer au sort une couleur
	}
	tabCases[2].setColor(JAUNE);
	tabCases[4].setColor(VERT);
	tabCases[11].setColor(ORANGE);
	tabCases[13].setColor(VIOLET);
	
	// DEPART
	tabCases[5].setColor(JAUNE);
	tabCases[6].setColor(VERT);
	tabCases[9].setColor(ORANGE);
	tabCases[10].setColor(VIOLET);
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
