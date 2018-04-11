#ifndef PLATEAU_HPP
#define PLATEAU_HPP

#include "tuile.hpp"

namespace MMaze {
class Plateau
{
    public:
        Tuile * tab_tuile[40];
        int nbTuile;

        Plateau();
        virtual ~Plateau();
		
		void incNbTuile();

    protected:

    private:

};
}

#endif // PLATEAU_HPP
