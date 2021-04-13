#ifndef WINDOW_H
#define WINDOW_H

#include <vector>
#include <QWidget>
#include <QTimer>
#include <QGridLayout>
#include <QLabel>
#include <QApplication>
#include <QPushButton>
#include "Grid.h"
#include "Blinker.h"
#include "Pond.h"
#include "Glider.h"
#include <Qt>

/*
class Window:
    Klasa reprezentująca okno aplikacji graficznej. Klasa ta zawiera planszę oraz przyciski
    potrzebne do obsługi programu.
*/
class Window : public QWidget
{
    Q_OBJECT                            // Macro dzięki któremu obiekt może mieć sygnały i sloty.

    private:
        Grid *grid;            // Siatka komórek.
        int row, col;           // Liczba wierszy i kolumn.
        QLabel *title;          // Tytuł aplikacji.
        std::vector<std::vector<QPushButton*> > buttons;    // Tablica przycisk.
        QTimer *timer;          // Obiekt timera.

    public slots:
        void handleClear();     // Czyści siatkę.
        void handleStart();     // Obsługuje start obliczeń.
        void handlePause();     // Zatrzymanie programu.
        void handleClick();     // Zmienia stan konkretnej komórki po kliknięciu.
        void handleSave();      // Zapisuje stan siatki do pliku output.txt.
        void handleRead();      // Wczytuje z pliku output.txt.
        void handleGenerateGlider();      // Generuje Glidera na siatce.
        void handleGenerateBlinker();     // Generuje Blinkera na siatce.
        void handleGeneratePond();        // Generuje Pond na siatce.
        void handleGenerateRandomGrid();  // Generuje losową siatkę.
        void calculateStep();   // Oblicza kolejny krok.

    public:
        Window(QWidget *parent = NULL, int rows = 10, int cols = 10);   // Konstruktor.
        virtual ~Window();              // Destruktor.

    private:
        QHBoxLayout* setupHeader();                     // Pomocnicza funkcja do budowy nagłówka aplikacji.
        QGridLayout* setupGrid();                       // Pomocnicza funkcja do budowy siatki.
        QHBoxLayout* setupButtonRow();                  // Pomocnicza funkcja do budowy przycisków menu.
        Qt::GlobalColor getColor(int x, int y);    // Zwraca kolor przycisku.
        void draw();            // Rysuje siatkę.

};

#endif // WINDOW_H
