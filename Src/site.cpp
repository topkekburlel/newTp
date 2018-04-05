#include "site.hpp"

namespace MMaze {

	Site::Site(Case * c, enum Couleur co, enum Types t) {
		ca = c;
		color = co;
		type = t;
		representante = this;
	}
		
	void Site::setColor(enum Couleur c) {
		color = c;
	}
	
	void Site::setType(enum Types t) {
		type = t;
	}
  
	void Site::setRepresentante(Site * rpz) {
		representante = rpz;
	}
	
	Site * Site::rec_representante(Site * cr) {
		if(cr->representante != cr)
		{
			cr->representante = rec_representante(cr->representante);
		}
		return cr->representante;
	}

} //end of namespace MMaze
