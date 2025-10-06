//
// Created by wakym on 9/8/2025.
//

#ifndef M1OEP_RACONWAY_CARD_H
#define M1OEP_RACONWAY_CARD_H


#include <string>

class Card {
public:
    enum Suit { HEARTS,
            DIAMONDS,
            CLUBS,
            SPADES };
    enum Rank { ACE = 1,
            TWO,
            THREE,
            FOUR,
            FIVE,
            SIX,
            SEVEN,
            EIGHT,
            NINE,
            TEN,
            JACK,
            QUEEN,
            KING };


private:
    Suit suit;
    Rank rank;

public:

    Card() = default;
    Card(Suit suit, Rank rank);
    // Get the value
    int getValue() const {
        if (rank >= JACK) {
            return 10;
        }
        return rank;
    }

    // Check if Ace
    bool isAce() const {
        return rank == ACE;
    }

   
    std::string getSuitString() const {
        switch (suit) {
            case HEARTS: return "Hearts";
            case DIAMONDS: return "Diamonds";
            case CLUBS: return "Clubs";
            case SPADES: return "Spades";
        }
        return "";
    }

    // Get rank as string
    std::string getRankString() const {
        switch (rank) {
            case ACE: return "Ace";
            case TWO: return "2";
            case THREE: return "3";
            case FOUR: return "4";
            case FIVE: return "5";
            case SIX: return "6";
            case SEVEN: return "7";
            case EIGHT: return "8";
            case NINE: return "9";
            case TEN: return "10";
            case JACK: return "Jack";
            case QUEEN: return "Queen";
            case KING: return "King";

        }
        return nullptr;
    }
    // Convert to string
    std::string toString() const {
        return getRankString() + " of " + getSuitString();
    }


    Suit getSuit() const {
        return suit; }
    Rank getRank() const {
        return rank; }


};


#endif //M1OEP_RACONWAY_CARD_H
