#ifndef MMAZE_TUILE_HPP
#define MMAZE_TUILE_HPP

#include "case.hpp"
#include "mur.hpp"

#include <vector>
#include <iostream>

#define TAILLE_MAX 8

namespace MMaze {

class Tuile {
  //const int TAILLE_MAX = 8;


  public :
    Case *tabCases[16];
    Mur *tabMurs[24];
    int currNbSites;
    Case *tabSites[TAILLE_MAX];

    Tuile();

    //indique si deux cases voisines sont separees par un mur
    bool mur(Mur m) const ;

    //indique si une case est accessible depuis les portes ou non
    bool accessible(Case c) const ;

    //affichage
    friend std::ostream& operator<<(std::ostream& out, const Tuile& t) ;

  private :

    //affichage
    void afficher_horizontal(std::ostream& out, unsigned int i) const ;
    void afficher_vertical(std::ostream& out, unsigned int i) const ;
} ;

} //end of namespace MMaze

#endif
