#include "Plateau.hpp"
#include "tuile.hpp"

namespace MMaze {

Plateau::Plateau()
{
    nbTuile = 0;
	tab_tuile[nbTuile] = new Tuile(nbTuile);
	tab_tuile[nbTuile]->setTuileDepart();
	incNbTuile();
}

void Plateau::incNbTuile() {
	nbTuile += 1;
}

Plateau::~Plateau()
{
    //dtor
}

}
