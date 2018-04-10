#ifndef ARRETE_HPP
#define ARRETE_HPP


#include "case.hpp"
#include <vector>


namespace MMaze {


class Arrete
{
    public:
        
        int taille;
		std::vector<Case*> vectorArrete;
		enum Direction dir;
		

		Arrete();
		Arrete(Case * ca, enum Direction d);
        //Arrete(enum Direction direction1_, Case * caseBout1_, enum Direction direction2_, Case * caseBout2_); // une arrete est un couple de Cases avec une direction
        virtual ~Arrete();
		void ajouterCases(Case * ca);
		void constructArrete(Case * ca, enum Direction d);
		
		void maxGauche(Case * ca);
		void maxHaut(Case * ca);
		void maxBas(Case * ca);
		void maxDroite(Case * ca);
};

}

#endif // ARRETE_HPP

