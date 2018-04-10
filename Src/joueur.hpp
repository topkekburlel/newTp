#ifndef JOUEUR_HPP
#define JOUEUR_HPP
#include "Plateau.hpp"
#include "tuile.hpp"


namespace MMaze {
class joueur
{
    public:
        couleur c;
        tuile* tuile_act;
        int position;
        Plateau* plat_jeu;

        joueur();
        joueur(int i, tuile* depart, Plateau* plateau);
        virtual ~joueur();

        // g�re le d�placement d'un joueur
        mouvement(int tuile, int pos);

    protected:

    private:
};
}
#endif // JOUEUR_HPP
