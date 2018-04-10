#include "mur.hpp"

#include <cassert>
#include <iostream>

namespace MMaze {

Mur::Mur(Case c0, Case c1) {
  assert(c0[0] == c1[0] || c0[1] == c1[1]) ;
  const int diff = c0[0] - c1[0] + c0[1] - c1[1] ;
  assert(diff == 1 || diff == -1) ;

  Case cref = (c0[0] > c1[0]) || (c0[1] > c1[1]) ? c1 : c0 ;
  if(c0[0] == c1[0]) {
    index_ = 12 + cref[0] + 4*cref[1] ;
  } else {
    index_ = cref.index() ;
  }
  app_tuile = c0.app_tuile;
}

Mur::Mur(unsigned int index, int t) : index_(index) {
  assert(index < 24) ;
  app_tuile = t;
}

unsigned int Mur::index() const {
  return index_ ;
}

bool Mur::operator==(Mur rhs) const {
  return index_ == rhs.index_ ;
}

Case Mur::operator[](unsigned int i) const {
  assert(i < 2) ;
  if(index_ < 12) { //mur horizontal
    if(i == 0) {
      return Case(index_, app_tuile) ;
    } else {
      return Case(index_ + 4, app_tuile) ;
    }
  } else { //mur vertical
    unsigned int base = index_ - 12 ;
    if(i == 0) {
      return Case((base >> 2) + ((base & 3) << 2), app_tuile) ;
    } else {
      return Case((base >> 2) + ((base & 3) << 2) + 1, app_tuile) ;
    }
  }
}

Mur Mur::tourne(int rotation) const {
  Case c0 = (*this)[0] ;
  Case c1 = (*this)[1] ;
  return Mur(c0.tourne(rotation), c1.tourne(rotation));
}

} //end of namespace MMaze
