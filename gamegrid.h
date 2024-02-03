#ifndef GAMEGRID_H
#define GAMEGRID_H
#include "QtWidgets/qlabel.h"
#include <QGridLayout>
#include <QWidget>
#include <QMessageBox>
#include <QTimer>
#include <cardbutton.h>


class GameGrid: public QWidget
{
    Q_OBJECT

public:
    GameGrid();
    QGridLayout *m_gridLayout;
    QLabel *m_attemptLabel;
    QLabel *m_scoreLabel;
    std::vector<QString> strings;
    int attempt_count = 0;
    int matched_counter = 0;
    CardButton *lastSelectedCard;
    void startNewGame();
    void lostGame();
    void winGame();
    bool wait = false;


public slots:
    void clickHandler(CardButton* button);
private:
    void checkMatch(CardButton *button);
    void allMatched();
    void shuffleStrings();
    void initializeCards();


};



#endif // GAMEGRID_H
