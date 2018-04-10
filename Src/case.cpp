#include "case.hpp"


#include <cassert>
#include <stdexcept>

namespace MMaze {

Case::Case(unsigned int l, unsigned int c, int t) {
	assert(l < 4 && c < 4);
	index_ = 4*l + c ;
	color = AUCUNE;
	type = RIEN;
	representante = this;
	app_tuile = t;
	nbArete = 0;
	visit = true;
}

Case::Case(unsigned int index, int t) : index_(index) {
	assert(index < 16);
	color = AUCUNE;
	type = RIEN;
	representante = this;
	app_tuile = t;
	nbArete = 0;
	visit = true;
}

unsigned int Case::index() const {
	return index_;
}

bool Case::operator==(Case rhs) const {
	return index_ == rhs.index_;
}

Case Case::haut() const {
	if(index_ < 4) {
		throw std::domain_error("la case n'a pas de voisine haute") ;
	}
	return Case(index_ - 4, app_tuile);
}

Case Case::bas() const {
	if(index_ > 11) {
		throw std::domain_error("la case n'a pas de voisine basse") ;
	}
	return Case(index_ + 4, app_tuile) ;
}

Case Case::gauche() const {
	if(index_%4 == 0) {
		throw std::domain_error("la case n'a pas de voisine gauche") ;
	}
	return Case(index_ - 1, app_tuile) ;
}

Case Case::droite() const {
	if(index_%4 == 3) {
		throw std::domain_error("la case n'a pas de voisine droite") ;
	}
	return Case(index_ + 1, app_tuile) ;
}

void Case::setColor(enum Couleur c) {
	color = c;
}

enum Couleur Case::getCouleur() {
	return color;
}

void Case::setType(enum Types t) {
	type = t;
}

enum Types Case::getType() {
	return type;
}

void Case::setRepresentante(Case * rpz) {
	representante = rpz;
}

Case * Case::getRepresentante() {
	return representante;
}

int Case::distanceXCases(Case * c) {
	return (this->index_%4)-(c->index_%4);
}

int Case::distanceYCases(Case * c) {
	return (this->index_/4)-(c->index_/4);
}

unsigned int Case::operator[](unsigned int i) const {
	assert(i < 2);
	if(i == 0) return index_ / 4;
	return index_ % 4;
}

Case Case::tourne(int rotation) const {
	unsigned int l = index_ / 4;
	unsigned int c = index_ % 4;
	if(rotation & 2) {
		l = 3 - l;
	}
	if((rotation + 1) & 2) {
		c = 3 - c;
	}
	if(rotation & 1) {
		return Case(4 * c + l, app_tuile);
	} else {
		return Case(4 * l + c, app_tuile);
	}
}

} //end of namespace MMaze
