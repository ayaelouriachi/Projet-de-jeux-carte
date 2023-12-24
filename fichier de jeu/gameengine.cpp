// gameengine.cpp

#include <algorithm> // For std::max

GameEngine::GameEngine(QObject *parent) : QObject(parent), playerScore(0), computerScore(0)
{
    // Initialiser game engine
}

void GameEngine::startGame()
{
    // Distri
    playerCards = cartesList.mid(0, 20);
    computerCards = cartesList.mid(20, 20);

    // Start the first turn
    emit playerScored(playerScore);
    emit computerScored(computerScore);
}

void GameEngine::playerMove(Cartes *card)
{
    // Handle the player's move
    // You can add more logic here based on the specific rules of your game
    // For now, we'll assume the player always wins to demonstrate the signals

    // Increase the player's score based on the card value
    playerScore += card->getNumero();

    // Emit the player's new score
    emit playerScored(playerScore);

    // Proceed with the computer's move
    computerMove();
}

void GameEngine::computerMove()
{
    // Handle the computer's move
    // You can add more logic here based on the specific rules of your game
    // For now, we'll assume the computer always wins to demonstrate the signals

    // Increase the computer's score based on a random card value
    computerScore += computerCards[qrand() % computerCards.size()]->getNumero();

    // Emit the computer's new score
    emit computerScored(computerScore);

    // Check if the game should end
    calculateScores();
}

void GameEngine::calculateScores()
{
    // Check if the game should end based on the scores
    if (playerScore >= 100 || computerScore >= 100)
    {
        // Emit a signal indicating the end of the game
        endGame();
    }
}

void GameEngine::endGame()
{
    // Emit a signal indicating the end of the game
    emit gameEnded();
}
