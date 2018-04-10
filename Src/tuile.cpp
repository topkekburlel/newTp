#include "tuile.hpp"
#include "couleurs.hpp"

#include <cassert>
#include <iostream>
#include <cstdlib>
#include <ctime>

namespace MMaze {

Tuile::Tuile() {
    int i,j;
	nbMurs = 0;
    indexSites = 0;
	tuile_depart = false;
	up = nullptr;
	down = nullptr;
	right = nullptr;
	left = nullptr;
	for(i = 0; i<16; i++)
    {
        tabCases[i] = new Case(i,0);
    }
    for(j = 0; j<24; j++)
    {
        tabMurs[j] = new Mur(j, 0);
		nbMurs += 1;
    }
	setTuileDepart();
}

Tuile::Tuile(int id_) {
    id = id_;
    int i,j;
	nbMurs = 0;
    indexSites = 0;
	tuile_depart = false;
	up = nullptr;
	down = nullptr;
	right = nullptr;
	left = nullptr;
	for(i = 0; i<16; i++)
    {
        tabCases[i] = new Case(i, id);
    }
    for(j = 0; j<24; j++)
    {
        tabMurs[j] = new Mur(j, id);
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


bool Tuile::verification(Case* c){
	Case * r = rec_representante(tabSites[0]);
	return(rec_representante(c) != r);
}

bool Tuile::accessible(Case c) const {
	/* remplacez ce code */
	return false;
}


void Tuile::setTuileDepart() {
	tuile_depart = true;

	//PORTES
	setPortes(tuile_depart);

	// DEPARTS
	setDepart();

	// UNION FIND
	for(int j = 0;j<indexSites;j++) {
		union_site(tabSites[j],tabSites[0]);
	}
	/* look up for representantes
	for(int j = 0;j<indexSites;j++) {
		std::cout<<"tabSites["<<j<<"]->getRepresentante() == "<<tabSites[j]->getRepresentante()<<std::endl;
	}
	*/
}

void Tuile::setTuileNormale() {
	tuile_depart = false;

	//PORTES
	setPortes(tuile_depart);

	// UNION FIND
	for(int j = 0;j<indexSites;j++) {
		union_site(tabSites[j],tabSites[0]);
	}
}

void Tuile::setTuileObjectif(int cc) {
	tuile_depart = false;

	//PORTES
	setPortes(tuile_depart);

	//OBJECTIFS
	setObjectifs(cc);

	// UNION FIND
	for(int j = 0;j<indexSites;j++) {
		union_site(tabSites[j],tabSites[0]);
	}
}

void Tuile::setTuileSortie(int cc) {
	tuile_depart = false;

	//PORTES
	setPortes(tuile_depart);

	//SORTIES
	setSorties(cc);

	// UNION FIND
	for(int j = 0;j<indexSites;j++) {
		union_site(tabSites[j],tabSites[0]);
	}
}

void Tuile::setPortes(bool depart) {
	int index;
	int intCouleurHasard;
	enum Couleur cc;
	int tabPortes[4] = {2,4,11,13};		// tableau des index des sites de type ACCES
	Melangeur mel = Melangeur(sizeof(int));
	if(depart) {
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
			tabCases[index]->setColor(cc);
			tabCases[index]->setType(ACCES);
			tabSites[indexSites] = tabCases[index];
			indexSites += 1;
		}
	} else {
		for(int i = 0; i<4; i++) {
			mel.inserer(&i);		// on insere 4 int dans le melangeur qui representera nos couleurs
		}
		srand((int)time(0)); 		// sinon la generation de "random" est nulle
		int uneOuDeuxSorties = (rand()%3)+1; // 1,2 ou 3 sortie de couleur

		/* on place l'entree de la tuile */
		mel.retirer(&intCouleurHasard); // on reutilise "intCouleurHasard" pour tirer au sort une case ACCES
		index = tabPortes[intCouleurHasard];
		tabCases[index]->setType(ACCES);
		tabSites[indexSites] = tabCases[index];
		indexSites += 1;

		for(int i = 1;i<=uneOuDeuxSorties;i++) {
			mel.retirer(&intCouleurHasard);
			index = tabPortes[intCouleurHasard];
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
					std::cerr<<"Erreur : mauvaise couleur tiree pour une porte, iteration i = "<<i<<" et intCouleurHasard = "<<intCouleurHasard<<std::endl;
					break;
			}
			tabCases[index]->setType(ACCES);
			tabCases[index]->setColor(cc);
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


void Tuile::setObjectifs(int cc) {
	srand((int)time(0)); 		// sinon la generation de "random" est nulle
	int index = (rand()%3)+1;					/*									*/
	while(tabCases[index]->getType() != RIEN) { 	/* generation d'un index au hasard	*/
		index = (index+1)%16;					/*									*/
	}											/* 									*/
	enum Couleur coul;
	switch(cc) {
		case 1:
			coul = JAUNE;
			break;
		case 2:
			coul = ORANGE;
			break;
		case 3:
			coul = VERT;
			break;
		case 0:
			coul = VIOLET;
			break;
		default:
			std::cerr<<"Erreur : mauvais site tiree"<<std::endl;
			break;
	}
	tabCases[index]->setColor(coul);
	tabCases[index]->setType(OBJECTIF);
	tabSites[indexSites] = tabCases[index];
	indexSites += 1;
}

void Tuile::setSorties(int cc) {
	srand((int)time(0)); 		// sinon la generation de "random" est nulle
	int index = (rand()%3)+1;					/*									*/
	while(tabCases[index]->getType() != RIEN) { 	/* generation d'un index au hasard	*/
		index = (index+1)%16;					/*									*/
	}											/* 									*/
	enum Couleur coul;
	switch(cc) {
		case 1:
			coul = JAUNE;
			break;
		case 2:
			coul = ORANGE;
			break;
		case 3:
			coul = VERT;
			break;
		case 0:
			coul = VIOLET;
			break;
		default:
			std::cerr<<"Erreur : mauvais site tiree"<<std::endl;
			break;
	}
	tabCases[index]->setColor(coul);
	tabCases[index]->setType(OBJECTIF);
	tabSites[indexSites] = tabCases[index];
	indexSites += 1;
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
			Case up = Case(i-1, m, id);
			Case down = Case(i, m, id);
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
			Case left = Case(i, m, id);
			Case right = Case(i, m+1, id);
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

void Tuile::arete_tuile() {
    bool b = false;
	Case * c;
	int j = 1;
	for (int i = 0; i < 16; i++){
		if(verification(tabCases[i])){
			b = true;
			c = tabCases[i];
			while(c->index_ > 3 && b) {
				if(verification(tabCases[c->index_ - 4]) && tabMurs[c->index_ - 4] == nullptr){
					c->tab_access[c->nbArete] = new Arete(HAUT, j, c->app_tuile, c->index_ - 4);
					c->nbArete = c->nbArete + 1;
					j = j+1;
					c = tabCases[c->index_ - 4];
				}
				else{
					b = false;
				}
			}
			b = true;
			c = tabCases[i];
			j = 1;
			while((c->index_ % 4) < 3 && b){
				if(verification(tabCases[c->index_ + 1]) && tabMurs[c->index_ + 1] == nullptr){
					c->tab_access[c->nbArete] = new Arete(DROITE, j,  c->app_tuile, c->index_ + 1);
					c->nbArete = c->nbArete + 1;
					j = j+1;
					c = tabCases[c->index_ + 1];
				}
				else{
					b = false;
				}
			}
			b = true;
			c = tabCases[i];
			j = 1;
			while(c->index_ < 12 && b){
				if(verification(tabCases[c->index_ + 4]) && tabMurs[c->index_ + 4] == nullptr){
					c->tab_access[c->nbArete] = new Arete(BAS, j,  c->app_tuile, c->index_ + 4);
					c->nbArete = c->nbArete + 1;
					j = j+1;
					c = tabCases[c->index_ + 4];
				}
				else{
					b = false;
				}
			}
			b = true;
			c = tabCases[i];
			j = 1;
			while((c->index_ % 4) > 0 && b){
				if(verification(tabCases[c->index_ - 1]) && tabMurs[c->index_ - 1] == nullptr){
					c->tab_access[c->nbArete] = new Arete(GAUCHE, j,  c->app_tuile, c->index_ - 1);
					c->nbArete = c->nbArete + 1;
					j = j+1;
					c = tabCases[c->index_ - 1];
				}
				else{
					b = false;
				}
			}
		}
	}
}

void Tuile::connecte_tuile_arete(Case* c){
	Case* d;
	Tuile* t;
	int tab1[4];
	int tab2[4];
	int t1 = 1;
	int t2 = 1;
	int i, j;
	if(c->index_ == 2){
		t = up;
		d = t->tabCases[13];
		tab1[0] = c->index_;
		tab2[0] = d->index_;
		for(i=0; i<c->nbArete; i++){
			if(c->tab_access[i]->direction == BAS){
				tab1[t1] = c->tab_access[i]->position;
				t1 = t1 + 1;
			}
		}
		for(i=0; i< d->nbArete; i++){
			if(c->tab_access[i]->direction == HAUT){
				tab2[t2] = d->tab_access[i]->position;
				t2 = t2 + 1;
			}
		}
		for(i = 0; i < t1; i++){
			for(j = 0; j < t2; j++){
				tabCases[tab1[i]]->tab_access[tabCases[tab1[i]]->nbArete] = new Arete(HAUT, (i+j+1), t->id, tab2[j]);
				tabCases[tab1[i]]->nbArete = tabCases[tab1[i]]->nbArete + 1;
				tabCases[tab2[j]]->tab_access[tabCases[tab2[j]]->nbArete] = new Arete(BAS, (i+j+1), id, tab1[i]);
				tabCases[tab2[j]]->nbArete = tabCases[tab2[j]]->nbArete + 1;
			}
		}
	}
	if(c->index_ == 4){
        t = left;
		d = left->tabCases[11];
		tab1[0] = c->index_;
		tab2[0] = d->index_;
		for(i=0; i<c->nbArete; i++){
			if(c->tab_access[i]->direction == DROITE){
				tab1[t1] = c->tab_access[i]->position;
				t1 = t1 + 1;
			}
		}
		for(i=0; i<d->nbArete; i++){
			if(c->tab_access[i]->direction == GAUCHE){
				tab2[t2] = d->tab_access[i]->position;
				t2 = t2 + 1;
			}
		}
		for(i = 0; i < t1; i++){
			for(j = 0; j < t2; j++){
				tabCases[tab1[i]]->tab_access[tabCases[tab1[i]]->nbArete] = new Arete(GAUCHE, (i+j+1), t->id, tab2[j]);
				tabCases[tab1[i]]->nbArete = tabCases[tab1[i]]->nbArete + 1;
				tabCases[tab2[j]]->tab_access[tabCases[tab2[j]]->nbArete] = new Arete(DROITE, (i+j+1), id, tab1[i]);
				tabCases[tab2[j]]->nbArete = tabCases[tab2[j]]->nbArete + 1;
			}
		}
	}
	if(c->index_ == 11){
	    t = right;
		d = right->tabCases[4];
		tab1[0] = c->index_;
		tab2[0] = d->index_;
		for(i=0; i<c->nbArete; i++){
			if(c->tab_access[i]->direction == GAUCHE){
				tab1[t1] = c->tab_access[i]->position;
				t1 = t1 + 1;
			}
		}
		for(i=0; i<d->nbArete; i++){
			if(c->tab_access[i]->direction == DROITE){
				tab2[t2] = d->tab_access[i]->position;
				t2 = t2 + 1;
			}
		}
		for(i = 0; i < t1; i++){
			for(j = 0; j < t2; j++){
				tabCases[tab1[i]]->tab_access[tabCases[tab1[i]]->nbArete] = new Arete(DROITE, (i+j+1), t->id, tab2[j]);
				tabCases[tab1[i]]->nbArete = tabCases[tab1[i]]->nbArete + 1;
				tabCases[tab2[j]]->tab_access[tabCases[tab2[j]]->nbArete] = new Arete(GAUCHE, (i+j+1), id, tab1[i]);
				tabCases[tab2[j]]->nbArete = tabCases[tab2[j]]->nbArete + 1;
			}
		}
	}
	if(c->index_ == 13){
	    t = down;
		d = down->tabCases[2];
		tab1[0] = c->index_;
		tab2[0] = d->index_;
		for(i=0; i<c->nbArete; i++){
			if(c->tab_access[i]->direction == HAUT){
				tab1[t1] = c->tab_access[i]->position;
				t1 = t1 + 1;
			}
		}
		for(i=0; i<d->nbArete; i++){
			if(c->tab_access[i]->direction == BAS){
				tab2[t2] = d->tab_access[i]->position;
				t2 = t2 + 1;
			}
		}
		for(i = 0; i < t1; i++){
			for(j = 0; j < t2; j++){
				tabCases[tab1[i]]->tab_access[tabCases[tab1[i]]->nbArete] = new Arete(BAS, (i+j+1), t->id, tab2[j]);
				tabCases[tab1[i]]->nbArete = tabCases[tab1[i]]->nbArete + 1;
				tabCases[tab2[j]]->tab_access[tabCases[tab2[j]]->nbArete] = new Arete(HAUT, (i+j+1), id, tab1[i]);
				tabCases[tab2[j]]->nbArete = tabCases[tab2[j]]->nbArete + 1;
			}
		}
	}
}


} //end of namespace MMaze
