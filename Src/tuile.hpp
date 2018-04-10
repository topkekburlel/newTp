#ifndef MMAZE_TUILE_HPP
#define MMAZE_TUILE_HPP

#include "case.hpp"
#include "mur.hpp"
#include "melangeur.hpp"

#include <vector>
#include <iostream>

#define TAILLE_MAX 8

namespace MMaze {

class Tuile {

  public :
    int id;
    Case *tabCases[16];
    Mur *tabMurs[24];
	int nbMurs;
    int indexSites;
    Case *tabSites[TAILLE_MAX];
	bool tuile_depart;
	Melangeur *mel;
	Tuile* up;
	Tuile* down;
    Tuile* right;
    Tuile* left;

    Tuile();

    //indique si deux cases voisines sont separees par un mur
    bool mur(Mur m) const ;

    void union_site(Case * site1, Case * site2);

    bool verification();

    bool union_mur(Mur mur);

    //indique si une case est accessible depuis les portes ou non
    bool accessible(Case c) const ;

	//set la tuile a tuile_depart == true;
	void setTuileDepart();

	//set une tuile normale
	void setTuileNormale();

	//set une tuile avec UN objectif
	void setTuileObjectif(int cc);

	//set une tuile avec UNE sortie
	void setTuileSortie(int cc);

	// set des portes pour les tuiles
	void setPortes(bool depart);

	//set les cases de depart des joueurs pour la tuile de depart
	void setDepart();

	void setSorties(int cc);

	void setObjectifs(int cc);

	// Change la couleur du Background
	const char* returnCouleurBG(Case * c) const;

	// cherche la representante "globale" de la tuile
	Case * rec_representante(Case * cr);


	//on casse les murs comme ca
	void casse_murDroite(Case * c);
	void casse_murGauche(Case * c);
	void casse_murHaut(Case * c);
	void casse_murBas(Case * c);

    //affichage
    friend std::ostream& operator<<(std::ostream& out, const Tuile& t) ;

    void Tuile::arete_tuile();
    void Tuile::connecte_tuile_arete(case* c);

  private :

    //affichage
    void afficher_horizontal(std::ostream& out, unsigned int i) const ;
    void afficher_vertical(std::ostream& out, unsigned int i) const ;
} ;

} //end of namespace MMaze

#endif
