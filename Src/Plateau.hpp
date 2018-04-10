#ifndef PLATEAU_HPP
#define PLATEAU_HPP
#include "tuile.hpp"


class Plateau
{
    public:
        tuile* tab_tuile[40];
        int nbTuile;
        Plateau();
        virtual ~Plateau();

    protected:

    private:
};

#endif // PLATEAU_HPP
