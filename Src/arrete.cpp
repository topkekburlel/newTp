#include "arrete.hpp"
#include "direction.hpp"
#include <iostream>

namespace MMaze {


Arrete::Arrete(Case * ca, enum Direction d) {
	taille = 0;
	constructArrete(ca, d);
}

Arrete::Arrete() {
	taille = 0;
}

Arrete::~Arrete()
{
    //dtor
}

void Arrete::constructArrete(Case * ca, enum Direction d) {
	if(d == HAUT) {
		maxHaut(ca);
	} else if (d == BAS) {
		maxBas(ca);
	} else if (d == GAUCHE) {
		maxGauche(ca);
	} else if (d == DROITE) {
		maxDroite(ca);
	} else {
		std::cerr<<"ERREUR : direction non definie"<<std::endl;
	}
}

void Arrete::maxGauche(Case * ca) {
	vectorArrete.push_back(ca);
	taille += 1;
	while(ca->getGauche() != NULL) {
		ca = ca->getGauche();
		vectorArrete.push_back(ca);
		taille += 1;
	}
}

void Arrete::maxHaut(Case * ca) {
	vectorArrete.push_back(ca);
	taille += 1;
	while(ca->getHaut() != NULL) {
		ca = ca->getHaut();
		vectorArrete.push_back(ca);
		taille += 1;
	}
}

void Arrete::maxBas(Case * ca) {
	vectorArrete.push_back(ca);
	taille += 1;
	while(ca->getBas() != NULL) {
		ca = ca->getBas();
		vectorArrete.push_back(ca);
		taille += 1;
	}
}

void Arrete::maxDroite(Case * ca) {
	vectorArrete.push_back(ca);
	taille += 1;
	while(ca->getDroite() != NULL) {
		ca = ca->getDroite();
		vectorArrete.push_back(ca);
		taille += 1;
	}
}

}