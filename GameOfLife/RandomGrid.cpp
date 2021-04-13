#include <iostream>
#include "RandomGrid.h"
#include <ctime>

using namespace std;

// Konstruktor.
RandomGrid::RandomGrid(int rows,int cols)
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
RandomGrid::~RandomGrid(){}

// Inicjuje siatkę.
void RandomGrid::initGrid(){
    srand( time( NULL ) );
    int range = ( rand() % (row*col) ) + (row+col);
    for(int i=0; i < range; i++)
    {
        int x = ( rand() % (row - 1) ) + 0;
        int y = ( rand() % (col - 1) ) + 0;

        cells[x][y]->changeType();
    }
}
