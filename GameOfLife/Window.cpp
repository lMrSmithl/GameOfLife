#include <iostream>
#include <fstream>
#include "Window.h"
#include "RandomGrid.h"
#include "Blinker.h"
#include "Glider.h"
#include "Pond.h"

using namespace std;

template<typename T>
void writeToFile(T grid, int x, int y)
{
    ofstream file;
    file.open("output.txt");

    for (int i = 0; i < x; i++)
    {
        for (int j = 0; j < y; j++)
        {
            int tmp = 0;
            if (grid->getCells()[i][j]->getType() == LIVE) {
                tmp = 1;
            }
            file<<tmp<<" ";
        }
        file<<"\n";
    }

    file.close();
}

// Konstruktor.
Window::Window(QWidget *parent,int rows,int cols)
: QWidget(parent)
{
    this->timer = new QTimer(this);
    this->row = rows;
    this->col = cols;
    QHBoxLayout *header = setupHeader();
    QGridLayout *gridLeyaut = setupGrid();
    QHBoxLayout *buttonRow = setupButtonRow();
    QVBoxLayout *layout = new QVBoxLayout();
    layout->addLayout(header);
    layout->addLayout(gridLeyaut);
    layout->addLayout(buttonRow);
    setLayout(layout);
}

// Destructor.
Window::~Window()
{
    delete this->title;
    delete this->grid;
    delete this->timer;
}

// Tworzy sekcję nagłówka w GUI.
QHBoxLayout* Window::setupHeader()
{
    QHBoxLayout *header = new QHBoxLayout();
    header->setAlignment(Qt::AlignHCenter);

    this->title = new QLabel("Game of life",this);             // Tworzy napis z tytułem aplikacji.
    this->title->setAlignment(Qt::AlignHCenter);
    this->title->setFont(QFont("Arial", 32, QFont::Bold));

    header->addWidget(this->title);     // Dodaje widget do layoutu.

    return header;                      // Zwraca nagłówek.
}

// Tworzy planszę oraz siatkę.
QGridLayout* Window::setupGrid()
{
    QGridLayout *gridLayout = new QGridLayout();    // Tworzy planszę.

    gridLayout->setHorizontalSpacing(0);
    gridLayout->setVerticalSpacing(0);
    gridLayout->setSpacing(0);
    gridLayout->setAlignment(Qt::AlignHCenter);

    for(int i=0; i < row; i++)
    {
        this->grid = new Grid(this->row, this->col);    // Tworzymy siatkę.
        std::vector<QPushButton*> row;                  // Tworzymy wektor 2D przycisków.
        buttons.push_back(row);
        for(int j=0; j < col; j++)
        {
            QPushButton *button = new QPushButton();
            button->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
            button->setMinimumSize(19,19);

            QString str;
            QTextStream(&str) << i << "." << j;
            button->setObjectName(str);

            connect(button,SIGNAL(clicked()),this,SLOT(handleClick()));

            buttons.at(i).push_back(button);

            gridLayout->addWidget(button,i,j);          // Dodajemy widget z przyciskiem.
            gridLayout->setColumnStretch(j,1);
        }
        gridLayout->setRowStretch(i,1);
    }
    draw();
    return gridLayout;
}

// Buduje sekcję przycisków aplikacji.
QHBoxLayout* Window::setupButtonRow()
{
    QHBoxLayout *buttonRow = new QHBoxLayout();
    buttonRow->setAlignment(Qt::AlignHCenter);

    // Tworzy przycisk do czyszczenia planszy
    QPushButton *clearButton = new QPushButton("CLEAR");
    clearButton->setFixedSize(100,25);
    connect(clearButton, SIGNAL(clicked()), this, SLOT(handleClear()));
    buttonRow->addWidget(clearButton);

    // Przycisk do wznawiania/uruchamiania symulacji.
    QPushButton *startButton = new QPushButton("START/RESUME");
    startButton->setFixedSize(100,25);
    connect(startButton, SIGNAL(clicked()), this, SLOT(handleStart()));
    buttonRow->addWidget(startButton);

    // Przycisk zatrzymania symulacji.
    QPushButton *pauseButton = new QPushButton("PAUSE");
    pauseButton->setFixedSize(100,25);
    connect(pauseButton, SIGNAL(clicked()), this, SLOT(handlePause()));
    buttonRow->addWidget(pauseButton);

    // Przycisk kończący program.
    QPushButton *quitButton = new QPushButton("EXIT");
    quitButton->setFixedSize(100,25);
    connect(quitButton, SIGNAL(clicked()), qApp, SLOT(quit()));
    buttonRow->addWidget(quitButton);

    // Przycisk zapisujący do pliku.
    QPushButton *toFileButton = new QPushButton("SAVE TO FILE");
    toFileButton->setFixedSize(100,25);
    connect(toFileButton, SIGNAL(clicked()), this, SLOT(handleSave()));
    buttonRow->addWidget(toFileButton);

    // Przycisk wczytujący z pliku.
    QPushButton *fromFileButton = new QPushButton("READ FROM FILE");
    fromFileButton->setFixedSize(100,25);
    connect(fromFileButton, SIGNAL(clicked()), this, SLOT(handleRead()));
    buttonRow->addWidget(fromFileButton);

    // Przycisk generujący Glidera.
    QPushButton *gliderButton = new QPushButton("GLIDER");
    gliderButton->setFixedSize(100,25);
    connect(gliderButton, SIGNAL(clicked()), this, SLOT(handleGenerateGlider()));
    buttonRow->addWidget(gliderButton);

    // Przycisk generujący Blinkera.
    QPushButton *blinkerButton = new QPushButton("BLINKER");
    blinkerButton->setFixedSize(100,25);
    connect(blinkerButton, SIGNAL(clicked()), this, SLOT(handleGenerateBlinker()));
    buttonRow->addWidget(blinkerButton);

    // Przycisk generujący Pond.
    QPushButton *pondButton = new QPushButton("POND");
    pondButton->setFixedSize(100,25);
    connect(pondButton, SIGNAL(clicked()), this, SLOT(handleGeneratePond()));
    buttonRow->addWidget(pondButton);

    // Przycisk generujący RandomGrid.
    QPushButton *randomButton = new QPushButton("RANDOM");
    randomButton->setFixedSize(100,25);
    connect(randomButton, SIGNAL(clicked()), this, SLOT(handleGenerateRandomGrid()));
    buttonRow->addWidget(randomButton);

    return buttonRow;               // Zwraca sekcję przycisków.
}

// Zwraca kolor przycisku.
Qt::GlobalColor Window::getColor(int x, int y)
{
    switch(this->grid->getCells()[x][y]->getType())
        {
            default:
            case DEAD:
                return Qt::darkRed;
            case LIVE:
                return Qt::darkGreen;
        }
}

// Rysuje siatkę.
void Window::draw()
{
    for(int i = 0; i < row; i++){
        for(int j = 0; j < col; j++){
            Qt::GlobalColor gc = getColor(i, j);
            this->buttons[i][j]->setPalette(QPalette(gc,gc));
            this->buttons[i][j]->setAutoFillBackground(true);
            this->buttons[i][j]->setFlat(true);
        }
    }
}

// Oblicza kolejny krok.
void Window::calculateStep()
{
    this->grid->calculateStep();
    draw();
}

// Obsługuje start obliczeń.
void Window::handleStart()
{
    connect(this->timer, SIGNAL(timeout()), this, SLOT(calculateStep()));    // Uruchamia obliczenia następnego kroku.
    this->timer->start(500);    // Następny krok obliczeń co 500 milisekund.
}

// Czyści siatkę.
void Window::handleClear()
{
    for(int i = 0; i < row; i++){
        for(int j = 0; j < col; j++){
            this->grid->getCells()[i][j]->setType(DEAD);
        }
    }
    draw();
}

// Zatrzymanie programu.
void Window::handlePause()
{
    if(this->timer->isActive()){
        this->timer->stop();        // Zatrzymuje timer.
    }
}

// Zmienia stan konkretnej komórki po kliknięciu.
void Window::handleClick()
{
    QPushButton *button = qobject_cast<QPushButton *>(QObject::sender());

    int i = button->objectName().split(".")[0].toInt();
    int j = button->objectName().split(".")[1].toInt();
    this->grid->getCells()[i][j]->changeType();
    draw();
}

// Zapisuje stan siatki do pliku output.txt.
void Window::handleSave()
{
    writeToFile(this->grid, this->row, this->col);
}

// Wczytuje z pliku output.txt.
void Window::handleRead()
{
    this->grid->readFromFile();
    draw();
}

// Generuje losową siatkę.
void Window::handleGenerateRandomGrid()
{
    this->grid = new RandomGrid(row, col);
    draw();
}

// Generuje Pond na siatce.
void Window::handleGeneratePond()
{
    this->grid = new Pond(row, col);
    draw();
}

// Generuje Blinkera na siatce.
void Window::handleGenerateBlinker()
{
    this->grid = new Blinker(row, col);
    draw();
}

// Generuje Glidera na siatce.
void Window::handleGenerateGlider()
{
    this->grid = new Glider(row, col);
    draw();
}
