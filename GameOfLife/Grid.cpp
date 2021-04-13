#include <iostream>
#include <fstream>
#include "Grid.h"

using namespace std;

// Konstruktor.
Grid::Grid(int rows,int cols)
{
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
}

// Destructor.
Grid::~Grid(){}

void Grid::initGrid(){
    for(int i=0; i < row; i++)
    {
        for(int j=0; j < col; j++)
        {
            cells[i][j]->setType(DEAD);
        }
    }
}

// Accessor dla tablicy komórek.
std::vector<std::vector<Cell*> >& Grid::getCells()
{
    return this->cells;
}

// Zmienia stan komórki w odpowienim punkcie.
void Grid::changeCell(int x, int y)
{
    if(x > 0 && y > 0 && y <= col && x <= row)
        this->cells[x-1][y-1]->changeType();
}

// Getter wierszy.
int Grid::getRow(){
    return this->row;
}

// Getter kolumn.
int Grid::getCol(){
    return this->col;
}

// Oblicza następny stan wszystkich komórek.
void Grid::calculateStep(){
    vector< vector<bool> > is_live(row);
    for(int m=0; m<row; m++)
    {
        is_live.at(m).resize(col);

        for(int n=0; n<col; n++)
        {
            //oblicza żywe sąsiedztwo
            int neighbors = 0;
            for(int i=-1; i<=1; i++)
            {
                for(int j=-1; j<=1; j++)
                {
                    if(0 <= m+i && m+i < row && 0 <= n+j && n+j < col){
                        if(cells[m+i][n+j]->getType() == LIVE){
                            neighbors++;
                        }
                    }
                }
            }

            // Jeżeli dana komórka jest żywa, należy odjąć tą komórkę z sąsiedztwa.
            neighbors -= static_cast<int>(cells[m][n]->getType() == LIVE);

            // Inicjujemy wartość pomocniczej tablicy.
            is_live[m][n] = cells[m][n]->getType() == LIVE;

            // Zapisujemy w tablicy następny krok iteracji
            is_live[m][n] = (is_live[m][n] && (neighbors == 3 || neighbors == 2)) ||
                            (!is_live[m][n] && neighbors == 3);
        }
    }

    // Zmieniamy typy komórek we właściwej tablicy.
    for(int m=0; m<row; m++)
    {
        int col = cells.at(m).size();
        for(int n=0; n<col; n++)
            cells[m][n]->setType(is_live[m][n] ? LIVE : DEAD);
    }
}

// Pokazuje siatkę.
void Grid::draw(){
    cout<<"Grid:"<<endl;
    for(int i = 0; i < this->row; i++){
        cout<<"| ";
        for(int j = 0; j < this->col; j++){
            cout<<static_cast<int>(this->cells[i][j]->getType() == LIVE)<<" |";
        }
        cout<<endl;
    }
}

// Wczytuje dane z pliku.
void Grid::readFromFile()
{
    ifstream file;
    file.open("output.txt");
    vector<vector<int>> tmp(row, vector<int>(col));

    if(file.is_open()){
        for (int i = 0; i < row; i++)
        {
            for (int j = 0; j < col; j++)
                {
                    file >> tmp[i][j];
                }
            }
    }
    else {
        cout<<"Cannot open file"<<endl;
    }

    file.close();

    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++){
            if(tmp[i][j] == 1){
                this->cells[i][j]->setType(LIVE);
            }
            else {
                this->cells[i][j]->setType(DEAD);
            }
        }
    }
}
