//
// Created by wakym on 9/13/2025.
//

#ifndef GAME_H
#define GAME_H
#include <fstream>

#include "Deck.h"
#include "Hand.h"
#include <iostream>

class Game {
private:
    Deck deck;
    Hand playerHand;
    Hand dealerHand;
    int totalGames;
    int playerWins;
    int dealerWins;
    int ties;
public:
     int pWins; int dWins; int pushes;
    Game() : totalGames(0), playerWins(0), dealerWins(0), ties(0) {
        loadStats();  // Load on startup
    }

    ~Game() {
        saveStats();  // Save on exit
    }

    void saveStats() {
        std::ofstream outFile("game_stats.txt");
        if (outFile.is_open()) {
            outFile << totalGames << std::endl;
            outFile << playerWins << std::endl;
            outFile << dealerWins << std::endl;
            outFile << ties << std::endl;
            outFile.close();
        }
    }

    void loadStats() {
        std::ifstream inFile("game_stats.txt");
        if (inFile.is_open()) {
            inFile >> totalGames >> playerWins >> dealerWins >> ties;
            inFile.close();
        }
    }


    // Start a new game
    void playGame() {
        std::cout << "Welcome to Blackjack!" << std::endl;
        std::cout << "Aces count as 1 or 11. Face cards count as 10." << std::endl << std::endl;

        char playAgain = 'y';
        while (playAgain == 'y' || playAgain == 'Y') {
            playRound();
            std::cout << "\nPlay another round? (y/n): ";
            std::cin >> playAgain;
            std::cout << std::endl;
        }
        std::cout << "Thanks for playing!" << std::endl;
    }
    // Deal initial 2 cards to each player
    void dealInitialCards() {
        playerHand.addCard(deck.dealCard());
        dealerHand.addCard(deck.dealCard());
        playerHand.addCard(deck.dealCard());
        dealerHand.addCard(deck.dealCard());
    }
    // Display both hands
    void displayHands(bool hideDealerCard = false) const {
        std::cout << "Dealer's hand: ";
        dealerHand.display(hideDealerCard);
        std::cout << std::endl;

        std::cout << "Your hand: ";
        playerHand.display();
        std::cout << std::endl << std::endl;
    }


    // Handle player's turn
    void playerTurn() {
        char choice;
        while (!playerHand.isBusted() && playerHand.getValue() < 21) {
            std::cout << "Do you want to (h)it or (s)tand? ";
            std::cin >> choice;

            if (choice == 'h' || choice == 'H') {
                playerHand.addCard(deck.dealCard());
                std::cout << "You drew: " << playerHand.getCard(playerHand.size() - 1).toString() << std::endl;
                displayHands(true);

                if (playerHand.isBusted()) {
                    std::cout << "Bust! You went over 21!" << std::endl;
                }
            } else if (choice == 's' || choice == 'S') {
                break;
            } else {
                std::cout << "Invalid choice. Please enter 'h' for hit or 's' for stand." << std::endl;
            }
        }
    }

    void dealerTurn() {
        std::cout << "Dealer's Turn" << std::endl;
        displayHands(false);

        // Dealer must hit on 16 and below, stand on 17 and above
        while (dealerHand.getValue() < 17) {
            dealerHand.addCard(deck.dealCard());
            std::cout << "Dealer draws: " << dealerHand.getCard(dealerHand.size() - 1).toString() << std::endl;
            displayHands(false);
        }

        if (dealerHand.isBusted()) {
            std::cout << "Dealer busts!" << std::endl;
        } else {
            std::cout << "Dealer stands with " << dealerHand.getValue() << std::endl;
        }
    }

    // Determine the winner of the round
    void determineWinner() {
        std::cout << "\n=== Final Result ===" << std::endl;
        displayHands(false);

        int playerValue = playerHand.getValue();
        int dealerValue = dealerHand.getValue();

        if (playerHand.isBusted()) {
            std::cout << "You busted! Dealer wins!" << std::endl;
        } else if (dealerHand.isBusted()) {
            std::cout << "Dealer busted! You win!" << std::endl;
        } else if (playerValue > dealerValue) {
            std::cout << "You win with " << playerValue << "!" << std::endl;
        } else if (dealerValue > playerValue) {
            std::cout << "Dealer wins with " << dealerValue << "!" << std::endl;
        } else {
            std::cout << "It's a tie with " << playerValue << "!" << std::endl;
        }
    }

    // Play a single round
    void playRound() {
        // Clear hands and check if deck needs reshuffling
        playerHand.clear();
        dealerHand.clear();

        if (deck.needsReshuffle()) {
            std::cout << "Reshuffling deck..." << std::endl;
            deck.shuffle();
        }

        // Initial deal - 2 cards each
        dealInitialCards();

        // Show initial hands
        displayHands(true);  // Hide dealer's first card

        // Check for blackjacks
        if (playerHand.isBlackjack() || dealerHand.isBlackjack()) {
            handleBlackjacks();
            return;
        }

        // Player's turn
        playerTurn();

        // If player didn't bust, dealer's turn
        if (!playerHand.isBusted()) {
            dealerTurn();
        }

        // Determine winner
        determineWinner();
    }

    // Handle blackjack scenarios
    void handleBlackjacks() {
        displayHands(false);
        if (playerHand.isBlackjack() && dealerHand.isBlackjack()) {
            std::cout << "Both have blackjack! It's a tie!" << std::endl;
        } else if (playerHand.isBlackjack()) {
            std::cout << "Blackjack! You win!" << std::endl;
        } else {
            std::cout << "Dealer has blackjack! Dealer wins!" << std::endl;
        }
    }



};
#endif //GAME_H
