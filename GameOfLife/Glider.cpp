#include <iostream>
#include "Glider.h"

using namespace std;

// Konstruktor.
Glider::Glider(int rows,int cols)
{
    if(rows < 10) rows = 10;
    if(cols < 10) cols = 10;
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
Glider::~Glider(){}

// Inicjuje siatkę.
void Glider::initGrid(){
    cells[0][1]->changeType();
    cells[1][2]->changeType();
    cells[2][0]->changeType();
    cells[2][1]->changeType();
    cells[2][2]->changeType();
}
