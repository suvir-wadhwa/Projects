
# Author: <Suvir Wadhwa>
# Assignment #3 - Blackjack
# Date due: 2021-03-25
# I pledge that I have completed this assignment without
# collaborating with anyone else, in conformance with the
# NYU School of Engineering Policies and Procedures on
# Academic Misconduct.

import random

FACE_CARD_VALUE = 10
ACE_VALUE = 1
CARD_LABELS = ('A', '2', '3', '4', '5', '6', '7', '8', '9', '10', 'J', 'Q', 'K')
BLACKJACK = 21
DEALER_THRESHOLD = 16


def deal_card():
    """Evaluates to a character representing one of 13
    cards in the CARD_LABELS tuple

    :return: a single- or double-character string representing a playing card

    >>> random.seed(13)
    >>> deal_card()
    '5'
    >>> deal_card()
    '5'
    >>> deal_card()
    'J'
    """
    card_label = random.choice(CARD_LABELS)
    # print(card_label)
    return card_label


def get_card_value(card_label):
    """Evaluates to the integer value associated with
    the card label (a single- or double-character string)

    :param card_label: a single- or double-character string representing a card
    :return: an int representing the card's value

    >>> card_label = 'A'
    >>> get_card_value(card_label)
    1
    >>> card_label = 'K'
    >>> get_card_value(card_label)
    10
    >>> card_label = '5'
    >>> get_card_value(card_label)
    5
    """
    face_cards = "JQK"
    if card_label in face_cards:
        # print(FACE_CARD_VALUE)
        return FACE_CARD_VALUE
    elif card_label == 'A':
        # print(ACE_VALUE)
        return ACE_VALUE
    elif int(card_label) in range(2, 11):
        # print(int(card_label))
        return int(card_label)


def deal_cards_to_player():
    """Deals cards to the player and returns the card
    total

    :return: the total value of the cards dealt
    """
    card_1 = deal_card()
    card_2 = deal_card()
    card_1_val = get_card_value(card_1)
    card_2_val = get_card_value(card_2)
    player_total = card_1_val + card_2_val
    print("Player drew {} and {}.".format(card_1, card_2))
    print("Player's total is {}.".format(player_total))
    print("")

    while player_total < BLACKJACK:
        hit_stay = input("Hit (h) or Stay (s)? ")
        print("")
        if hit_stay == 'h':
            new_player_card = deal_card()
            new_player_card_val = get_card_value(new_player_card)
            player_total = player_total + new_player_card_val
            print("Player drew {}.".format(new_player_card))
            print("Player's total is {}.".format(player_total))
            print("")
        elif hit_stay == 's':
            break
        else:
            continue
    if player_total > 21:
        deal_only_one_set_to_dealer()
    else:
        deal_cards_to_dealer()

    return player_total


def deal_only_one_set_to_dealer():
    dealer_card_1 = deal_card()
    dealer_card_2 = deal_card()
    dealer_card_1_val = get_card_value(dealer_card_1)
    dealer_card_2_val = get_card_value(dealer_card_2)
    dealer_total = dealer_card_1_val + dealer_card_2_val
    print("The dealer has {} and {}.".format(dealer_card_1, dealer_card_2))
    print("Dealer's total is {}.".format(dealer_total))
    print("")
    return dealer_total


def deal_cards_to_dealer():
    """Deals cards to the dealer and returns the card
    total

    :return: the total value of the cards dealt
    """
    dealer_card_1 = deal_card()
    dealer_card_2 = deal_card()
    dealer_card_1_val = get_card_value(dealer_card_1)
    dealer_card_2_val = get_card_value(dealer_card_2)
    dealer_total = dealer_card_1_val + dealer_card_2_val
    print("The dealer has {} and {}.".format(dealer_card_1, dealer_card_2))
    print("Dealer's total is {}.".format(dealer_total))
    print("")

    while dealer_total < DEALER_THRESHOLD:
        new_dealer_card = deal_card()
        new_dealer_card_val = get_card_value(new_dealer_card)
        dealer_total = dealer_total + new_dealer_card_val
        print("Dealer drew {}.".format(new_dealer_card))
        print("Dealer's total is {}.".format(dealer_total))
        print("")
    return dealer_total


def determine_outcome(player_total, dealer_total):
    """Determines the outcome of the game based on the value of
    the cards received by the player and dealer. Outputs a
    message indicating whether the player wins or loses.

    :param player_total: total value of cards drawn by player
    :param dealer_total: total value of cards drawn by dealer
    :return: None
    """
    if player_total > 21:
        print("YOU LOSE!")
        print("")
    elif player_total > dealer_total:
        print("YOU WIN!")
        print("")
    elif dealer_total > 21:
        print("YOU WIN!")
        print("")
    else:
        print("YOU LOSE!")
        print("")


def play_blackjack():
    """Allows user to play Blackjack by making function calls for
    dealing cards to the player and the dealer as well as
    determining a game's outcome

    :return: None
    """
    print("Let's Play Blackjack!")
    print("")
    player_total = deal_cards_to_player()
    if player_total > 21:
        dealer_total = deal_only_one_set_to_dealer()
    else:
        dealer_total = deal_cards_to_dealer()
    determine_outcome(player_total, dealer_total)

    while True:
        play_again = input("Play again (Y/N)?")
        print("")
        if play_again == 'Y':
            print("Let's Play Blackjack!")
            print("")
            player_total = deal_cards_to_player()
            if player_total > 21:
                dealer_total = deal_only_one_set_to_dealer()
            else:
                dealer_total = deal_cards_to_dealer()
            determine_outcome(player_total, dealer_total)
        elif play_again == 'N':
            break
        else:
            continue
    print("Goodbye.")
    print("")




####### DO NOT EDIT ABOVE ########

def main():
    """Runs a program for playing Blackjack with one player
    and a dealer
    """

    # call play_blackjack() here and remove pass below
    play_blackjack()



####### DO NOT REMOVE IF STATEMENT BELOW ########

if __name__ == "__main__":
    #Remove comments for next 4 lines to run doctests
    #print("Running doctests...")
    #import doctest
    #doctest.testmod(verbose=True)

    #print("\nRunning program...\n")

    main()
