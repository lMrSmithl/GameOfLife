// Główny plik do uruchomienia aplikacji.
#include <stdexcept>
#include "Window.h"
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

using namespace std;

// Główna metoda odpowiedzialna za utworzenie klas oraz uruchomienie aplikacji.
int main(int argc, char *argv[])
{
    QApplication app(argc, argv);                   // Tworzy aplikację okienkową.
    int rows = 30, cols = 40;                       // Liczba kolumn i wierszy w siatce.
    Window widget(NULL,rows,cols);              // Tworzy okno klasy Window.
    widget.show();                                  // Wyświetla aplikację na ekranie.
    return app.exec();                          // Uruchamia GUI.
}
