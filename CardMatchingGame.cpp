#include <QApplication>
#include <QVBoxLayout>
#include <QSpacerItem>
#include <QWidget>
#include <QtWidgets>
#include <cardbutton.h>
#include <gamegrid.h>




int main(int argc, char* argv[]) {
    QApplication app(argc, argv);

    QMainWindow mainWindow;
    QWidget *centralWidget = new QWidget(&mainWindow);
    mainWindow.setCentralWidget(centralWidget);
    QVBoxLayout *vb = new QVBoxLayout(centralWidget);
    GameGrid *gameGrid = new GameGrid();


    QPushButton* newGameButton = new QPushButton("New Game");
    newGameButton->setFixedWidth(100);
    newGameButton->setFixedHeight(200);
    QObject::connect(newGameButton, &QPushButton::clicked, gameGrid, &GameGrid::startNewGame);



    QHBoxLayout *topLayout = new QHBoxLayout(); // Create a horizontal layout for the top section
    topLayout->addWidget(gameGrid->m_scoreLabel); // Add the score label to the top layout
    topLayout->addWidget(gameGrid->m_attemptLabel); // Add the remaining attempt label to the top layout
    topLayout->addWidget(newGameButton); //New button to start game again
    vb->addLayout(topLayout);
    vb->addLayout(gameGrid->m_gridLayout);
    mainWindow.resize(640,480);


    mainWindow.show();
    return app.exec();
}



