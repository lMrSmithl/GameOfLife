#ifndef GRID_H
#define GRID_H

#include <vector>
#include "Cell.h"

/*
class Grid:
    Jest to klasa zawierająca siatkę komórek oraz podstawowe metody potrzebne do obliczania
    stanu komórek w konkretnym kroku symulacji.
*/
class Grid {
    protected:
        int row;               // Liczba wierszy.
        int col;                // Liczba kolumn.
        std::vector<std::vector<Cell*> > cells;     // 2D vector zawierający komórki.
        virtual void initGrid();        // Inicjuje siatkę.

    public:
        Grid(int rows=3,int cols=3);       // Konstructor.
        virtual ~Grid();                   // Destruktor.
        std::vector<std::vector<Cell*> >& getCells();       // Accessor dla tablicy komórek.
        void calculateStep();           // Oblicza następny stan wszystkich komórek.
        void changeCell(int x, int y);  // Zmienia stan komórki w odpowienim punkcie.
        int getRow();       // Getter wierszy.
        int getCol();       // Getter kolumn.
        void draw();        // Pokazuje siatkę.
        void readFromFile();        // Wczytuje dane z pliku.

};

#endif // GRID_H
