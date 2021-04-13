#ifndef BLINKER_H
#define BLINKER_H

#include <vector>
#include "Grid.h"

/*
class Blinker:
    Jest to klasa dziedzicząca po Grid. Inicjuje tablicę tak, aby w środku był Blinkier
    - figura, która oscylacyjnie wraca do swojej pierwotnej formy.
*/
class Blinker :public Grid {
    public:
        Blinker(int rows=5,int cols=5);       // Konstructor.
        virtual ~Blinker();                   // Destruktor.

    protected:
        void initGrid();        // Inicjuje siatkę.

};

#endif // BLINKER_H
