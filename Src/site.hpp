#ifndef MMAZE_TERM_SITE_HPP
#define MMAZE_TERM_SITE_HPP

#include "case.hpp"


namespace MMaze {

  enum Types {
	RIEN,
    POINT_DE_DEPART,
    OBJECTIF,
    SORTIE,
    ACCES
  };
  
  class Site {
	
	private :
	
		Case * ca;
		enum Couleur color;
		enum Types type;
		Site * representante;
		
		
	public :

		Site(Case * c, enum Couleur co, enum Types t);
		
		void setColor(enum Couleur c);
		void setType(enum Types t);
		void setRepresentante(Site * rpz);
		Site * rec_representante(Site * cr);
};

} //end of namespace MMaze

#endif
