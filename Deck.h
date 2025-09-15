//
// Created by wakym on 9/7/2025.
//

#ifndef M1OEP_RACONWAY_DECK_H
#define M1OEP_RACONWAY_DECK_H


#include <algorithm>
#include <random>
#include <stack>
#include <vector>

#include "Card.h"

class Deck {

private:
    std::vector<Card> cards;
    size_t currentCard;

public:
    // Constructor - creates a full deck of 52 cards
    Deck() {
        initializeDeck();
        shuffle();
    }

    // Initialize the deck with all 52 cards
    void initializeDeck() {
        cards.clear();
        for (int suit = Card::HEARTS; suit <= Card::SPADES; suit++) {
            for (int rank = Card::ACE; rank <= Card::KING; rank++) {
                cards.push_back(Card(static_cast<Card::Suit>(suit),
                                   static_cast<Card::Rank>(rank)));
            }
        }
        currentCard = 0;
    }

    void shuffle() {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::shuffle(cards.begin(), cards.end(), gen);
        currentCard = 0;
    }

    Card dealCard() {
        if (currentCard >= cards.size()) {
            shuffle();
        }
        return cards[currentCard++];
    }

    // Check if deck needs reshuffling
    bool needsReshuffle() const {
        return (cards.size() - currentCard) < 10;
    }

    // Get remaining cards count
    int remainingCards() const {
        return cards.size() - currentCard;
    }
};


#endif //M1OEP_RACONWAY_DECK_H
