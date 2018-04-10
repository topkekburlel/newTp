#ifndef MMAZE_CASE_HPP
#define MMAZE_CASE_HPP

#include "direction.hpp"
#include "couleurs.hpp"
#include "arete.hpp"

namespace MMaze {
	enum Types {
		RIEN,
		POINT_DE_DEPART,
		OBJECTIF,
		SORTIE,
		ACCES
	 };
/* +---+---+---+---+
 * | 0 | 1 | 2 | 3 |	colonne : i%4
 * +---+---+---+---+	ligne : i/4
 * | 4 | 5 | 6 | 7 |
 * +---+---+---+---+
 * | 8 | 9 | 10| 11|
 * +---+---+---+---+
 * | 12| 13| 14| 15|
 * +---+---+---+---+

 * +---+---+---+---+
 * |   12  16  20  |
 * + 0 + 1 + 2 + 3 +
 * |   13  17  21  |
 * + 4 + 5 + 6 + 7 +
 * |   14  18  22  |
 * + 8 + 9 + 10+ 11+
 * |   15  19  23  |
 * +---+---+---+---+
 */

class Case {

	public :
        unsigned int index_;
		enum Couleur color;
		enum Types type;
		Case * representante;
		Arete* tab_access[14];
		int nbArete;
        int app_tuile;

		//construction depuis ligne et colonne
		Case(unsigned int l, unsigned int c, int t);

		//construction implicite depuis un entier dans [0,15], voir ci-dessus
		explicit Case(unsigned int index, int t);

		//conversion vers un entier dans [0,15], voir ci-dessus
		unsigned int index() const ;


		//egalite entre les cases
		bool operator==(Case rhs) const;

		//cases voisines par direction
		//exception si non existante
		Case bas() const;
        Case droite() const;
		Case haut() const;
		Case gauche() const;

		//cases voisines selon la direction
		Case voisine(Direction d) const;

		//ligne et colonne de la case
		unsigned int operator[](unsigned int i) const;

		//rotation de la case
		Case tourne(int rotation) const;

		// Set la couleur de la case
		void setColor(enum Couleur c);
		// Get la couleur de la case
		enum Couleur getCouleur();

		// Set le type de la case
		void setType(enum Types t);
		// Get le type de la case
		enum Types getType();

		// Set la representante de la case courante
		void setRepresentante(Case * rpz);
		Case * getRepresentante();

		int distanceXCases(Case * c);
		int distanceYCases(Case * c);

/*		void setHaut(Case * c);
		void setBas(Case * c);
		void setGauche(Case * c);
		void setDroite(Case * c);

		Case * getHaut();
		Case * getBas();
		Case * getGauche();
		Case * getDroite();
*/

	private :

		//stockage sous forme d'un entier comme ci-dessus

/*<<<<<<< HEAD
		Case * ptrHaut;
		Case * ptrBas;
		Case * ptrGauche;
		Case * ptrDroite;
		//Case * tab_pointeurVersCases[14];
=======
>>>>>>> parent of 749385d... Modif Viteuf
*/
};

} //end of namespace MMaze

#endif
