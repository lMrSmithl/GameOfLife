#include <iostream>
#include "Pond.h"

using namespace std;

// Konstruktor.
Pond::Pond(int rows,int cols)
{
    if(rows < 6) rows = 6;
    if(cols < 6) cols = 6;
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
Pond::~Pond(){}

// Inicjuje siatkę.
void Pond::initGrid(){
    int centerx = row / 2 - 1;
    int centery = col / 2 - 1;

    cells[centerx-1][centery]->changeType();
    cells[centerx-1][centery+1]->changeType();
    cells[centerx][centery-1]->changeType();
    cells[centerx+1][centery-1]->changeType();
    cells[centerx][centery+2]->changeType();
    cells[centerx+1][centery+2]->changeType();
    cells[centerx+2][centery]->changeType();
    cells[centerx+2][centery+1]->changeType();
}
