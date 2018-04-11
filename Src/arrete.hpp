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

