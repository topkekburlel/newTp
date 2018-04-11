#include "Plateau.hpp"
#include "tuile.hpp"

namespace MMaze {

Plateau::Plateau()
{
    nbTuile = 0;
}

void Plateau::incNbTuile() {
	nbTuile += 1;
}


Plateau::~Plateau()
{
    //dtor
}

}
