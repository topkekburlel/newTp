#include "tuile.hpp"
#include "couleurs.hpp"

#include <cassert>
#include <iostream>
#include <cstdlib>

namespace MMaze {

Tuile::Tuile() {
    int i,j;
	nbMurs = 0;
    indexSites = 0;
	tuile_depart = false;
	for(i = 0; i<16; i++)
    {
        tabCases[i] = new Case(i);
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

Case * Tuile::rec_representante(Case * cr) {
	if(cr->getRepresentante() != cr)
	{
		cr->setRepresentante(rec_representante(cr->getRepresentante()));
	}
	return cr->getRepresentante();
}

	// int distanceXCases(Case * c);
	// int distanceYCases(Case * c);

void Tuile::union_site(Case * site1, Case * site2) {
	Case * s1 = rec_representante(site1);
	Case * s2 = rec_representante(site2);
	Case * tmpRepresentante;
	int currDistanceX;
	int currDistanceY;
	if(site1 == site2) { return; }
	while(true) {
		currDistanceX = s1->distanceXCases(s2);
		currDistanceY = s1->distanceYCases(s2);
		if(currDistanceX < 0) { // s1 est sur la gauche(x) de s2
			// un pas a droite
			tmpRepresentante = s1;
			s1 = tabCases[s1->index()+1];
			s1->setRepresentante(tmpRepresentante);
			// et on casse le mur de gauche
			casse_murGauche(s1);
		} else if(currDistanceX > 0) { // s1 est sur la droite(x) de s2
			// un pas a gauche
			tmpRepresentante = s1;
			s1 = tabCases[s1->index()-1];
			s1->setRepresentante(tmpRepresentante);
			// et on casse le mur de droite
			casse_murDroite(s1);
		} else if(currDistanceY > 0) { // s1 est en bas(y) de s2
			// un pas en haut
			tmpRepresentante = s1;
			s1 = tabCases[s1->index()-4];
			s1->setRepresentante(tmpRepresentante);
			// et on casse le mur d'en bas
			casse_murBas(s1);
		} else if(currDistanceY < 0) { // s1 est en haut(y) de s2
			// un pas en bas
			tmpRepresentante = s1;
			s1 = tabCases[s1->index()+4];
			s1->setRepresentante(tmpRepresentante);
			// et on casse le mur d'en haut
			casse_murHaut(s1);
		} else {
			break;
		}
	}
}

void Tuile::casse_murDroite(Case * c) {
	int colonneCase = c->index()%4;
	int ligneCase = c->index()/4;
	switch(colonneCase) {
		case 0:
			tabMurs[ligneCase+12] = nullptr;
			break;
		case 1:
			tabMurs[ligneCase+16] = nullptr;
			break;
		case 2:
			tabMurs[ligneCase+20] = nullptr;
			break;
		default:
			std::cerr<<"Erreur : casse_murDroite == ECHEC"<<std::endl;
			break;
	}
}

void Tuile::casse_murGauche(Case * c) {
	int colonneCase = c->index()%4;
	int ligneCase = c->index()/4;
	switch(colonneCase) {
		case 1:
			tabMurs[ligneCase+12] = nullptr;
			break;
		case 2:
			tabMurs[ligneCase+16] = nullptr;
			break;
		case 3:
			tabMurs[ligneCase+20] = nullptr;
			break;
		default:
			std::cerr<<"Erreur : casse_murGauche == ECHEC"<<std::endl;
			break;
	}
}

void Tuile::casse_murBas(Case * c) {
	if(c->index()<12) {
		tabMurs[c->index()] = nullptr;
		return;
	}
	std::cerr<<"Erreur : casse_murBas == ECHEC"<<std::endl;
}

void Tuile::casse_murHaut(Case * c) {
	if(c->index()>3) {
		tabMurs[c->index()-4] = nullptr;
		return;
	}
	std::cerr<<"Erreur : casse_murHaut == ECHEC"<<std::endl;
}

/*

bool Tuile::verification(){
	Case * r = rec_representante(tabVraiSites[0])
	for(i=1; i<currNbSites; i++){
		if(rec_representante(tabVraiSites[i]) != r)
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
*/

bool Tuile::accessible(Case c) const {
	/* remplacez ce code */
	return false;
}


void Tuile::setTuileDepart() {
	tuile_depart = true;
	
	//PORTES
	setPortes(tuile_depart);
	
	// DEPART
	setDepart();
	// UNION FIND
	for(int j = 0;j<indexSites;j++) {
		union_site(tabSites[j],tabSites[0]);
	}
	/* look up for representante
	for(int j = 0;j<indexSites;j++) {
		std::cout<<"tabSites["<<j<<"]->getRepresentante() == "<<tabSites[j]->getRepresentante()<<std::endl;
	}
	*/
}

void Tuile::setTuileNormale() {
	tuile_depart = false;	
	
	//PORTES A MODIFIER
	setPortes(tuile_depart);
}

void Tuile::setPortes(bool depart) {
	int index;
	int intCouleurHasard;
	enum Couleur cc;
	int tabPortes[4] = {2,4,11,13};		// tableau des index des sites de type ACCES
	if(depart) {
		Melangeur mel = Melangeur(sizeof(int));
		for(int i = 0; i<4; i++) {
			mel.inserer(&i);				// on insere 4 int dans le melangeur qui representera nos couleurs
		}
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
			/*
			Case(index).setColor(cc);
			std::cout<<Case(index).index()<<" Set color a la valeur : "<<Case(index).getCouleur()<<" grace a cc = "<<cc<<std::endl;
			Case(index).setType(ACCES);
			*/
			tabCases[index]->setColor(cc);
			tabCases[index]->setType(ACCES);
			tabSites[indexSites] = tabCases[index];
			indexSites += 1;
		}
	}
}

void Tuile::setDepart() {
	int index;
	int intCouleurHasard;
	enum Couleur cc;
	int tabDepart[4] = {5,6,9,10};	// tableau des index des sites de type POINT_DE_DEPART
	Melangeur mel = Melangeur(sizeof(int));

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
		tabCases[index]->setColor(cc);
		tabCases[index]->setType(POINT_DE_DEPART);
		tabSites[indexSites] = tabCases[index];
		indexSites += 1;
	}
}

const char* Tuile::returnCouleurBG(Case * c) const {
	enum Couleur co = c->getCouleur();
	switch(co) {
			case JAUNE:
				return BG_JAUNE;
				break;
			case VERT:
				return BG_VERT;
				break;
			case ORANGE:
				return BG_ORANGE;
				break;
			case VIOLET:
				return BG_VIOLET;
				break;
			default:
				return BG_DEFAULT;
				break;
		}
}

void Tuile::afficher_horizontal(std::ostream& out, unsigned int i) const {
	assert(i < 5);
	if(i == 0) {
		out << "+";
		for(unsigned int m = 0; m < 4; ++m) {
			Case * down = tabCases[i+m];
			if(down->getType()==ACCES) {
				out <<returnCouleurBG(down)<<" ^ "<<BG_DEFAULT<<"+";
			} else {
				out << "---+";
			}
		}
	} else if(i == 4) {
		out << "+";
		for(unsigned int m = 0; m < 4; ++m) {
			Case * up = tabCases[3*i+m];
			if(up->getType()==ACCES) {
				out <<returnCouleurBG(up)<<" v "<<BG_DEFAULT<<"+";
			} else {
				out << "---+";
			}
		}
	} else {
		out << "+";
		for(unsigned int m = 0; m < 4; ++m) {
			Case up = Case(i-1, m);
			Case down = Case(i, m);
			if(mur(Mur(up, down))) {
				out << "---+";
			} else {
				out << "   +";
			}
		}
	}
}

void Tuile::afficher_vertical(std::ostream& out, unsigned int i) const {
	assert(i < 4);
	if(tabCases[4*i]->getType()==ACCES) { out<<returnCouleurBG(tabCases[4*i])<<"<"<<BG_DEFAULT; }
	else { out << "|"; }
	for(unsigned int m = 0; m < 4; ++m) {
		out << "   ";
		if(m < 3) {
			Case left = Case(i, m);
			Case right = Case(i, m+1);
			if(m < 3 && mur(Mur(left, right))) {
				out << "|";
			} else {
				out << " ";
			}
		}
	}
	if(tabCases[4*i+3]->getType()==ACCES) { out<<returnCouleurBG(tabCases[4*i+3])<<">"<<BG_DEFAULT; }
	else { out << "|"; }
}

std::ostream& operator<< (std::ostream& out, const Tuile& t) {
  for(unsigned int i = 0; i < 4; ++i) {
    t.afficher_horizontal(out, i);
    out << std::endl ;
    t.afficher_vertical(out, i);
    out << std::endl ;
  }
  t.afficher_horizontal(out, 4);
  return out ;
}

} //end of namespace MMaze
