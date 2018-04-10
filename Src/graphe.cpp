#include "graphe.hpp"


namespace MMaze {
	
Graphe::Graphe(Case * depart)
{
	for(int i = 0; i<4;i++) {
		tabArretes[i] = new Arrete(depart,tabDir[i]);
	}
}

Graphe::~Graphe()
{
    free(*tabArretes);
}

void Graphe::addArretes(Arrete * a) {
	for(int i = 0;i<a->taille;i++) {
		addArretesFromCase(a->vectorArrete[i]);
	}
}

void Graphe::addArretesFromCase(Case * c) {
	for(int j = 0;j<4;j++) {
		tabArretes[j] = new Arrete(c,tabDir[j]);
	}
}

}