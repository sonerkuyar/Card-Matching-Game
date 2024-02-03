#include "cardbutton.h"

CardButton::CardButton(const QString& key,QWidget *parent) : QPushButton(parent), m_faceUp(false), m_matched(false)
{
    connect(this, &QPushButton::clicked, this, [this]() {
        emit cardClicked(this);
    });
    this-> key = key;
    setFixedHeight(50);
    setText(cardface);

}

void CardButton::setId(int id)
{
    m_id = id;
}

int CardButton::getId() const
{
    return m_id;
}

void CardButton::flip()
{
    m_faceUp = !m_faceUp;
    setText(m_faceUp ? key : cardface);
}

void CardButton::setFaceUp(bool faceUp)
{
    m_faceUp = faceUp;
    setText(m_faceUp ? key : cardface);
}

bool CardButton::isFaceUp() const
{
    return m_faceUp;
}

bool CardButton::isMatched() const
{
    return m_matched;
}
void CardButton:: setMatched(){
    m_matched = true;

}

