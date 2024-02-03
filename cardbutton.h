#ifndef CARDBUTTON_H
#define CARDBUTTON_H
#include <QPushButton>


class CardButton: public QPushButton
{
    Q_OBJECT
public:
    CardButton(const QString& key, QWidget* parent = 0);
    QString key;
    QString cardface = "?";
    void setId(int id);
    int getId() const;
    void flip();
    void setFaceUp(bool faceUp);
    bool isFaceUp() const;
    bool isMatched() const;
    void setMatched();
signals:
    void cardClicked(CardButton* button);

private:

    int m_id;
    bool m_faceUp;
    bool m_matched;
};

#endif // CARDBUTTON_H
