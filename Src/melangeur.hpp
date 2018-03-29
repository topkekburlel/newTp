#ifndef MMAZE_MELANGEUR_HPP
#define MMAZE_MELANGEUR_HPP

namespace MMaze {

class Melangeur {
	
	private :
	
		const int CONSTANTE_TAILLE_DEPART = 50;
		char* tab; 								// pointeur vers le premier octet du tableau
		int tailleMax;							// taille maximale allouee
		int nbElements;							// nombre d elements
		int tailleDonnee;						// taille en octets des elements

	public :

		Melangeur(int octets) ;

		~Melangeur() ;

		void inserer(const void* elem);

		void retirer(void* elem);
		
		void vider();

		int taille();
		
		char* accesDernierElem(int indiceElem);

		/* vos membres ici */

} ;

} //end of namespace MMaze

#endif
