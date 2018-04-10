#ifndef GRAPHE_HPP
#define GRAPHE_HPP


#include "case.hpp"
#include "arrete.hpp"

#define MAX_ARRETES 200


namespace MMaze {
	
class Graphe
{
    public:
        Arrete * tabArretes[MAX_ARRETES];
		enum Direction tabDir[4] = {HAUT,BAS,GAUCHE,DROITE};
		
		Graphe(Case * depart);
		~Graphe();
		
		void addArretes(Arrete * a);
		void addArretesFromCase(Case * c);
};

}
#endif // GRAPHE_HPP

