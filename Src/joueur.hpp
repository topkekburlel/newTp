#ifndef JOUEUR_HPP
#define JOUEUR_HPP
#include "Plateau.hpp"
#include "tuile.hpp"


namespace MMaze {

class joueur
{
    public:
        Couleur c;
        Tuile* tuile_act;
        int position;
        Plateau* plat_jeu;

        joueur();
        joueur(int i, Tuile* depart, Plateau* plateau);
        virtual ~joueur();

        // gère le déplacement d'un joueur
        void mouvement(int tuile, int pos);

    protected:

    private:
};
}
#endif // JOUEUR_HPP
