//
// Created by wakym on 10/5/2025.
//

/*
#include "Card.h"

#include "Deck.h"
#include "Hand.h"
#include <iostream>
using namespace std;

bool test_Card();
bool test_Deck();
bool test_Hand();

int main() {
    if (test_Card()) {
        cout << "Passed all Card test cases" << endl;
    }
    if (test_Deck()) {
        cout << "Passed all Deck test cases" << endl;
    }
    if (test_Hand()) {
        cout << "Passed all Hand test cases" << endl;
    }
    return 0;
}

bool test_Card() {
    bool passed = true;

    // Test Card constructor and getValue()
    Card aceHearts(Card::HEARTS, Card::ACE);
    if (aceHearts.getValue() != 1) {
        passed = false;
        cout << "FAILED ace getValue test case" << endl;
    }

    Card kingSpades(Card::SPADES, Card::KING);
    if (kingSpades.getValue() != 10) {
        passed = false;
        cout << "FAILED king getValue test case" << endl;
    }

    Card fiveClubs(Card::CLUBS, Card::FIVE);
    if (fiveClubs.getValue() != 5) {
        passed = false;
        cout << "FAILED five getValue test case" << endl;
    }

    Card jackDiamonds(Card::DIAMONDS, Card::JACK);
    if (jackDiamonds.getValue() != 10) {
        passed = false;
        cout << "FAILED jack getValue test case" << endl;
    }

    Card queenHearts(Card::HEARTS, Card::QUEEN);
    if (queenHearts.getValue() != 10) {
        passed = false;
        cout << "FAILED queen getValue test case" << endl;
    }

    // Test isAce()
    if (!aceHearts.isAce()) {
        passed = false;
        cout << "FAILED ace isAce test case" << endl;
    }

    if (kingSpades.isAce()) {
        passed = false;
        cout << "FAILED king isAce test case" << endl;
    }

    // Test getSuitString()
    if (aceHearts.getSuitString() != "Hearts") {
        passed = false;
        cout << "FAILED hearts getSuitString test case" << endl;
    }

    if (kingSpades.getSuitString() != "Spades") {
        passed = false;
        cout << "FAILED spades getSuitString test case" << endl;
    }

    if (fiveClubs.getSuitString() != "Clubs") {
        passed = false;
        cout << "FAILED clubs getSuitString test case" << endl;
    }

    if (jackDiamonds.getSuitString() != "Diamonds") {
        passed = false;
        cout << "FAILED diamonds getSuitString test case" << endl;
    }

    // Test getRankString()
    if (aceHearts.getRankString() != "Ace") {
        passed = false;
        cout << "FAILED ace getRankString test case" << endl;
    }

    if (kingSpades.getRankString() != "King") {
        passed = false;
        cout << "FAILED king getRankString test case" << endl;
    }

    if (fiveClubs.getRankString() != "5") {
        passed = false;
        cout << "FAILED five getRankString test case" << endl;
    }

    if (jackDiamonds.getRankString() != "Jack") {
        passed = false;
        cout << "FAILED jack getRankString test case" << endl;
    }

    // Test toString()
    if (aceHearts.toString() != "Ace of Hearts") {
        passed = false;
        cout << "FAILED ace toString test case" << endl;
    }

    if (kingSpades.toString() != "King of Spades") {
        passed = false;
        cout << "FAILED king toString test case" << endl;
    }

    // Test getSuit() and getRank()
    if (aceHearts.getSuit() != Card::HEARTS) {
        passed = false;
        cout << "FAILED getSuit test case" << endl;
    }

    if (aceHearts.getRank() != Card::ACE) {
        passed = false;
        cout << "FAILED getRank test case" << endl;
    }

    return passed;
}

bool test_Deck() {
    bool passed = true;

    // Test deck initialization
    Deck deck;
    if (deck.remainingCards() != 52) {
        passed = false;
        cout << "FAILED deck initialization test case" << endl;
    }

    // Test dealCard()
    Card firstCard = deck.dealCard();
    if (deck.remainingCards() != 51) {
        passed = false;
        cout << "FAILED dealCard remaining cards test case" << endl;
    }

    // Deal multiple cards
    for (int i = 0; i < 10; i++) {
        deck.dealCard();
    }
    if (deck.remainingCards() != 41) {
        passed = false;
        cout << "FAILED multiple dealCard test case" << endl;
    }

    // Test needsReshuffle()
    Deck deck2;
    for (int i = 0; i < 43; i++) {
        deck2.dealCard();
    }
    if (!deck2.needsReshuffle()) {
        passed = false;
        cout << "FAILED needsReshuffle test case" << endl;
    }

    if (deck.needsReshuffle()) {
        passed = false;
        cout << "FAILED doesn't need reshuffle test case" << endl;
    }

    // Test that dealing all cards and more causes reshuffle
    Deck deck3;
    for (int i = 0; i < 55; i++) {
        deck3.dealCard();
    }
    if (deck3.remainingCards() >= 52) {
        passed = false;
        cout << "FAILED auto-reshuffle test case" << endl;
    }

    return passed;
}

bool test_Hand() {
    bool passed = true;

    // Test empty hand
    Hand hand;
    if (hand.getValue() != 0) {
        passed = false;
        cout << "FAILED empty hand getValue test case" << endl;
    }

    if (hand.size() != 0) {
        passed = false;
        cout << "FAILED empty hand size test case" << endl;
    }

    // Test adding cards
    Card aceHearts(Card::HEARTS, Card::ACE);
    hand.addCard(aceHearts);
    if (hand.size() != 1) {
        passed = false;
        cout << "FAILED addCard size test case" << endl;
    }

    if (hand.getValue() != 11) {
        passed = false;
        cout << "FAILED single ace value test case (should be 11)" << endl;
    }

    // Test ace value adjustment (ace + 10 = 21)
    Card tenSpades(Card::SPADES, Card::TEN);
    hand.addCard(tenSpades);
    if (hand.getValue() != 21) {
        passed = false;
        cout << "FAILED ace + 10 test case" << endl;
    }

    // Test blackjack detection
    if (!hand.isBlackjack()) {
        passed = false;
        cout << "FAILED isBlackjack test case" << endl;
    }

    // Test non-blackjack 21
    Hand hand2;
    hand2.addCard(Card(Card::HEARTS, Card::SEVEN));
    hand2.addCard(Card(Card::CLUBS, Card::SEVEN));
    hand2.addCard(Card(Card::DIAMONDS, Card::SEVEN));
    if (hand2.getValue() != 21) {
        passed = false;
        cout << "FAILED three sevens value test case" << endl;
    }
    if (hand2.isBlackjack()) {
        passed = false;
        cout << "FAILED three sevens not blackjack test case" << endl;
    }

    // Test bust detection
    Hand hand3;
    hand3.addCard(Card(Card::HEARTS, Card::KING));
    hand3.addCard(Card(Card::CLUBS, Card::KING));
    hand3.addCard(Card(Card::DIAMONDS, Card::FIVE));
    if (!hand3.isBusted()) {
        passed = false;
        cout << "FAILED isBusted test case" << endl;
    }
    if (hand3.getValue() != 25) {
        passed = false;
        cout << "FAILED busted hand value test case" << endl;
    }

    // Test multiple aces
    Hand hand4;
    hand4.addCard(Card(Card::HEARTS, Card::ACE));
    hand4.addCard(Card(Card::CLUBS, Card::ACE));
    if (hand4.getValue() != 12) {
        passed = false;
        cout << "FAILED two aces test case (should be 12)" << endl;
    }

    hand4.addCard(Card(Card::DIAMONDS, Card::NINE));
    if (hand4.getValue() != 21) {
        passed = false;
        cout << "FAILED two aces + 9 test case" << endl;
    }

    // Test three aces
    Hand hand5;
    hand5.addCard(Card(Card::HEARTS, Card::ACE));
    hand5.addCard(Card(Card::CLUBS, Card::ACE));
    hand5.addCard(Card(Card::DIAMONDS, Card::ACE));
    if (hand5.getValue() != 13) {
        passed = false;
        cout << "FAILED three aces test case (should be 13)" << endl;
    }

    // Test clear()
    hand.clear();
    if (hand.size() != 0) {
        passed = false;
        cout << "FAILED clear size test case" << endl;
    }
    if (hand.getValue() != 0) {
        passed = false;
        cout << "FAILED clear value test case" << endl;
    }

    // Test getCard()
    Hand hand6;
    Card sevenHearts(Card::HEARTS, Card::SEVEN);
    hand6.addCard(sevenHearts);
    if (hand6.getCard(0).getRank() != Card::SEVEN) {
        passed = false;
        cout << "FAILED getCard test case" << endl;
    }

    return passed;
}
*/
