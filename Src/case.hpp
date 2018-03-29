#ifndef MMAZE_CASE_HPP
#define MMAZE_CASE_HPP

#include "direction.hpp"

namespace MMaze {

/* +---+---+---+---+
 * | 0 | 1 | 2 | 3 |
 * +---+---+---+---+
 * | 4 | 5 | 6 | 7 |
 * +---+---+---+---+
 * | 8 | 9 | 10| 11|
 * +---+---+---+---+
 * | 12| 13| 14| 15|
 * +---+---+---+---+
 */

class Case {

  public :

    //construction depuis ligne et colonne
    Case(unsigned int l, unsigned int c) ;

    //construction implicite depuis un entier dans [0,15], voir ci-dessus
    explicit Case(unsigned int index) ;

    //conversion vers un entier dans [0,15], voir ci-dessus
    unsigned int index() const ;

    //egalite entre les cases
    bool operator==(Case rhs) const ;

    //cases voisines par direction
    //exception si non existante
    Case bas() const ;
    Case droite() const ;
    Case haut() const ;
    Case gauche() const ;

    //cases voisines selon la direction
    Case voisine(Direction d) const ;

    //ligne et colonne de la case
    unsigned int operator[](unsigned int i) const ;

    //rotation de la case
    Case tourne(int rotation) const ;

  private :

    //stockage sous forme d'un entier comme ci-dessus
    unsigned int index_ ;

} ;

} //end of namespace MMaze

#endif
