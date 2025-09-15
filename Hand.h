//
// Created by wakym on 9/13/2025.
//

#ifndef HAND_H
#define HAND_H
#include <iostream>
#include <vector>

#include "Card.h"


class Hand {
private:
    std::vector<Card> cards;

public:
    // Add a card to the hand
    void addCard(const Card& card) {
        cards.push_back(card);
    }

    const Card& getCard(size_t index) const {
        return cards[index];
    }

    // Calculate the total value of the hand
    int getValue() const {
        int total = 0;
        int aces = 0;

        // First, add up all non-ace cards
        for (const Card& card : cards) {
            if (card.isAce()) {
                aces++;
                total += 1;  // Count ace as 1 initially
            } else {
                total += card.getValue();
            }
        }

        // Convert aces from 1 to 11 if beneficial
        while (aces > 0 && total + 10 <= 21) {
            total += 10;
            aces--;
        }

        return total;
    }
    bool isBlackjack() const {
        return cards.size() == 2 && getValue() == 21;
    }
    // Check if hand is busted (over 21)
    bool isBusted() const {
        return getValue() > 21;
    }
    void clear() {
        cards.clear();
    }
    void display(bool hideFirstCard = false) const {
        for (size_t i = 0; i < cards.size(); i++) {
            if (i == 0 && hideFirstCard) {
                std::cout << "[Hidden Card]";
            } else {
                std::cout << cards[i].toString();
            }
            if (i < cards.size() - 1) {
                std::cout << ", ";
            }
        }
        if (!hideFirstCard) {
            std::cout << " (Total: " << getValue() << ")";
        }
    }

    // Get number of cards in hand
    size_t size() const {
        return cards.size();
    }


};



#endif //HAND_H
