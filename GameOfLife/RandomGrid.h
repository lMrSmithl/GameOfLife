#ifndef RANDOMGRID_H
#define RANDOMGRID_H

#include <vector>
#include "Grid.h"

/*
class RandomGrid:
    Jest to klasa dziedzicząca po Grid. Inicjuje tablicę w sposób losowy.
*/
class RandomGrid :public Grid {
    public:
        RandomGrid(int rows=5,int cols=5);       // Konstructor.
        virtual ~RandomGrid();                   // Destruktor.

    protected:
        void initGrid();    // Inicjuje siatkę.

};

#endif // RANDOMGRID_H
