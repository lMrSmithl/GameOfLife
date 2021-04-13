#ifndef CELL_H
#define CELL_H

#include <iostream>

// Enum reprezentujący stany komórki.
enum CellType
{
    DEAD,                   // DEAD = Martwa komórka.
    LIVE                    // LIVE = Żywa komórka
};

/*
Class: Cell.
    Klasa reprezentująca komórkę w siatce. Typ komórki jest wyliczany
    i przechowywany w postaci wartości Enum. Komórka przechowuje również liczbę
    aktualnie żywych sąsiadów z otoczenia.
*/
class Cell {
    private:
        CellType type;                  // Typ komórki (DEAD lub LIVE.)
        int neighbors;                  // Liczba żywych sąsiadów komórki.

    public:
        Cell(CellType type = DEAD);                  // Konstruktor do tworzenia komórki.
        virtual ~Cell();                    // Destruktor.
        void setType(CellType type);    // Setter pozwalający zmienić typ komórki.
        CellType getType() const;               // Getter dla typu komórki.
        void changeType();                  // Zmienia typ komórki na przeciwny.

};

#endif // CELL_H
