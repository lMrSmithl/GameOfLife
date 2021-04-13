#ifndef GLIDER_H
#define GLIDER_H

#include <vector>
#include "Grid.h"

/*
class Glider:
    Jest to klasa dziedzicząca po Grid. Inicjuje tablicę tak, aby w środku był Glider
    - figura, która przemieszcza się po planszy.
*/
class Glider :public Grid {
    public:
        Glider(int rows=10,int cols=10);       // Konstructor.
        virtual ~Glider();                   // Destruktor.

    protected:
        void initGrid();    // Inicjuje siatkę.

};

#endif // GLIDER_H
