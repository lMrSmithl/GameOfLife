#ifndef POND_H
#define POND_H

#include <vector>
#include "Grid.h"

/*
class Pond:
    Jest to klasa dziedzicząca po Grid. Inicjuje tablicę tak, aby w środku był Staw
    - figura, która niezmiennie pozostaje taka sama.
*/
class Pond :public Grid {
    public:
        Pond(int rows=6,int cols=6);       // Konstructor.
        virtual ~Pond();                   // Destruktor.

    protected:
        void initGrid();    // Inicjuje siatkę.

};

#endif // POND_H
