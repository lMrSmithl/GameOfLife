#include <iostream>
#include "Blinker.h"

using namespace std;

// Konstruktor.
Blinker::Blinker(int rows,int cols)
{
    if(rows < 5) rows = 5;
    if(cols < 5) cols = 5;
    this->row = rows;
    this->col = cols;
    for(int i=0; i < rows; i++)
    {
        std::vector<Cell*> row;                 // Tworzony jest nowy wektor kolumn dla każdego wiersza.
        cells.push_back(row);
        for(int j=0; j < cols; j++)
        {
            Cell *cell = new Cell();        // Tworzone są komórki oraz dodawane do siatki.
            cells.at(i).push_back(cell);
        }
    }

    this->initGrid();
}

// Destructor.
Blinker::~Blinker(){}

// Inicjuje siatkę.
void Blinker::initGrid(){
    int centerx = row / 2;
    int centery = col / 2;

    cells[centerx-1][centery]->changeType();
    cells[centerx][centery]->changeType();
    cells[centerx+1][centery]->changeType();
}
