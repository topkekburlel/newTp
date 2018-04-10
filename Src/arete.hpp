#ifndef ARETE_HPP
#define ARETE_HPP


class arete
{
    public:
        int direction;
        /*
        1 : haut
        2 : gauche
        3 : bas
        4 : droite
        */

        int taille;
        noeud* dest;
        // bool chang_tuile         pas forcément utile


        arete();
        arete(int direction_, int taille_, noeud* dest_);
        virtual ~arete();

    protected:

    private:
};

#endif // ARETE_HPP
