#include "gamegrid.h"
#include "QtWidgets/qlabel.h"
#include <QThread>
#include <QCoreApplication>
#include <random>


GameGrid::GameGrid() : QWidget(),lastSelectedCard(nullptr)
{
    m_gridLayout = new QGridLayout();
    m_attemptLabel = new QLabel("No. of Tries Remaining: 50");
    m_scoreLabel = new QLabel("Score: 0");

    shuffleStrings();
    initializeCards();

}

void GameGrid::clickHandler(CardButton* button){

    if(button ->isFaceUp() || wait)
        return;

    button->flip();

    if(!lastSelectedCard)
        lastSelectedCard = button;
    else{

        ++attempt_count;
        m_attemptLabel->setText("No. of Tries Remaining: " + QString::number(50 - attempt_count));
        m_scoreLabel->setText("Score: " + QString::number(matched_counter));
        checkMatch(button);
        allMatched();
        if (attempt_count == 50) {
            lostGame();
        }

    }
}

void GameGrid::shuffleStrings(){
    // duplicate object because each should appear twice
    strings = {
        "Elephant",
        "Rainbow",
        "Bicycle",
        "Sunflower",
        "Chocolate",
        "Telescope",
        "Penguin",
        "Watermelon",
        "Butterfly",
        "Balloon",
        "Jellyfish",
        "Guitar",
        "Fireworks",
        "Pineapple",
        "Moonlight"
    };
    std::vector<QString> duplicatedStrings;
    duplicatedStrings.reserve(strings.size() * 2);
    for (const auto& str : strings) {
        duplicatedStrings.push_back(str);
        duplicatedStrings.push_back(str);
    }

    // shuffle the order of object
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::shuffle(duplicatedStrings.begin(), duplicatedStrings.end(), std::default_random_engine(seed));

    // assign the shuffled vector to original one
    strings = duplicatedStrings;
}

void GameGrid::initializeCards(){
    for (int row = 0; row < 5; row++) {
        for (int col = 0; col < 6; col++) {

            CardButton *cardButton = new CardButton(strings[row*6+col]);
            connect(cardButton, &CardButton::cardClicked, this, &GameGrid::clickHandler);
            m_gridLayout->addWidget(cardButton, row, col);
        }
    }

}

void GameGrid::checkMatch(CardButton* button){

    if(button->key == lastSelectedCard->key){
        button->setMatched();
        lastSelectedCard->setMatched();
        matched_counter++;
        m_scoreLabel->setText("Score: " + QString::number(matched_counter));
     }
    else{
        QElapsedTimer timer;
        timer.start();
        wait = true;
        while (timer.elapsed() < 1000) {
            // Wait for 1 seconds
            QCoreApplication::processEvents();
        }

        button->flip();
        lastSelectedCard->flip();
        wait = false;
    }


    lastSelectedCard = nullptr;

}
void GameGrid:: allMatched(){
    // check the all matches
    if(matched_counter == 15){
        winGame();

    }
}
void GameGrid::startNewGame() {
    // Clear the existing cards from the layout
    if (wait)
        return;
    QLayoutItem* child;
    while ((child = m_gridLayout->takeAt(0)) != nullptr)
    {
        delete child->widget();
        delete child;
    }

    m_attemptLabel->setText("No. of Tries Remaining: 50");
    m_scoreLabel->setText("Score: 0");

    // Reset game variables
    attempt_count = 0;
    matched_counter = 0;
    lastSelectedCard = nullptr;

    // Shuffle the strings and initialize new cards
    shuffleStrings();
    initializeCards();

    // Update the layout
    m_gridLayout->update();
    m_attemptLabel->update();
    m_scoreLabel->update();
}

void GameGrid::lostGame() {
    //lost game function to use when the attempts are finished


    QMessageBox msgBox;
    msgBox.setText("YOU LOST!");
    msgBox.setInformativeText("Do you want to start a new game?");
    msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
    int ret = msgBox.exec();

    if (ret == QMessageBox::Yes) {
        startNewGame();

    }
    if (ret == QMessageBox::No)
    {
        qApp->exit();
    }

}

void GameGrid::winGame() {
    // check function when the all pairs are matched

    QMessageBox msgBox;
    msgBox.setText("YOU WIN!");
    msgBox.setInformativeText("Do you want to start a new game?");
    msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
    int ret = msgBox.exec();

    if (ret == QMessageBox::Yes) {
        startNewGame();

    }
    if (ret == QMessageBox::No)
    {
        qApp->exit();
    }

}






