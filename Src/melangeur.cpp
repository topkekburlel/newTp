#include "melangeur.hpp"

#include <iostream>
#include <cstdlib>
#include <cstring>
#include <cassert>
namespace MMaze {

Melangeur::Melangeur(int octets) {
	tailleDonnee = octets;
	tab = (char*) malloc(CONSTANTE_TAILLE_DEPART*tailleDonnee);  // CONSTANTE_TAILLE_DEPART == 50
	tailleMax = CONSTANTE_TAILLE_DEPART;
	nbElements = 0;
}

Melangeur::~Melangeur() {
	vider();
}

void Melangeur::inserer(const void* elem) {
	if(nbElements >= tailleMax)
	{
		if(tailleMax == 0) { tailleMax = CONSTANTE_TAILLE_DEPART; }
		else { tailleMax *= 2; }
		tab = (char*) realloc(tab, tailleMax*tailleDonnee);
	}
	memcpy(tab+nbElements*tailleDonnee, elem, tailleDonnee); // memcpy(destination, source (ce qui doit etre copie), nombre de bytes a copier)
	nbElements += 1;
}

void Melangeur::retirer(void* elem) {
	if(nbElements > 1)
	{
		char* tempRand = tab + (rand()%nbElements)*tailleDonnee ;
		memcpy(elem, tempRand, tailleDonnee); // memcpy(destination, source (ce qui doit etre copie), nombre de bytes a copier)
		memcpy(tempRand, accesDernierElem(nbElements-1), tailleDonnee);
		nbElements -= 1;
	}
	else if(nbElements == 1)
	{
		memcpy(elem, accesDernierElem(nbElements-1), tailleDonnee); // memcpy(destination, source (ce qui doit etre copie), nombre de bytes a copier)
		nbElements -= 1;
	}
}

void Melangeur::vider() {
	if(tab != NULL)
	{
		free(tab);
		//tab = NULL;
	}
	tailleMax = nbElements = 0;
}

int Melangeur::taille() {
	return nbElements;
}

char* Melangeur::accesDernierElem(int indiceElem) {
	//return (char*) ((* tab+(nbElements*tailleDonnee))/4); pour me souvenir de ma betise
	assert(indiceElem<nbElements && indiceElem >= 0);
	return tab + indiceElem*tailleDonnee;
}

} //end of namespace MMaze
