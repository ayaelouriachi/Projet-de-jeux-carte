// gameengine.h
#ifndef GAMEENGINE_H
#define GAMEENGINE_H

#include <QObject>
#include <QList>
#include "cartes.h"

class GameEngine : public QObject
{
    Q_OBJECT
public:
    explicit GameEngine(QObject *parent = nullptr);

    void startGame();

signals:
    void playerScored(int score);
    void computerScored(int score);
    void gameEnded();

public slots:
    void playerMove(Cartes *card);

private:
    int playerScore;
    int computerScore;
    QList<Cartes*> playerCards;
    QList<Cartes*> computerCards;
    QList<Cartes*> cartesList;
    void computerMove();
    void calculateScores();
    void endGame();
};

#endif // GAMEENGINE_H
