#include <iostream>

#include "Cell.h"

using namespace std;

// Konstructor: Tworzy komórkę.
Cell::Cell(CellType type) :type(type){
    this->type = type;              // Domuślnie typ to DEAD.
}

// Destruktor.
Cell::~Cell(){}

// Getter dla typu komórki.
CellType Cell::getType() const
{
    return(this->type);
}

// Setter dla typu komórki
void Cell::setType(CellType type)
{
    this->type = type;
}

// Zmienia typ komórki.
void Cell::changeType()
{
    if(this->type == DEAD)            // Jeżeli type jest DEAD, zmienia na LIVE.
      type = LIVE;
    else
      type = DEAD;                    // Jeżeli type jest LIVE, zmienia na DEAD.

    setType(type);
}

