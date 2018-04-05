#ifndef MMAZE_TUILE_HPP
#define MMAZE_TUILE_HPP

#include "case.hpp"
#include "mur.hpp"
#include "melangeur.hpp"
#include "site.hpp"

#include <vector>
#include <iostream>

#define TAILLE_MAX 8

namespace MMaze {

class Tuile {

  public :
    Case *tabCases[16];
    Site *tabSites[16];
    Mur *tabMurs[24];
	int nbMurs;
    int currNbSites;
    Site *tabVraiSites[TAILLE_MAX];
	bool tuile_depart;
	Melangeur *mel;

    Tuile();

    //indique si deux cases voisines sont separees par un mur
    bool mur(Mur m) const ;

    void Tuile::union_site(Site* site1, Site* site2);

    bool Tuile::verification();

    bool Tuile::union_mur(Mur mur);

    //indique si une case est accessible depuis les portes ou non
    bool accessible(Case c) const ;

	//set la tuile a tuile_depart == true;
	void setTuileDepart();

	void setPortes();

    //affichage
    friend std::ostream& operator<<(std::ostream& out, const Tuile& t) ;

  private :

    //affichage
    void afficher_horizontal(std::ostream& out, unsigned int i) const ;
    void afficher_vertical(std::ostream& out, unsigned int i) const ;
} ;

} //end of namespace MMaze

#endif
