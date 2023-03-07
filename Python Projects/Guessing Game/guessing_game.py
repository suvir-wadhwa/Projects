# Author: <Suvir Wadhwa>
# Assignment #4 - Guessing Game
# Date due: 2021-04-08
# I pledge that I have completed this assignment without
# collaborating with anyone else, in conformance with the
# NYU School of Engineering Policies and Procedures on
# Academic Misconduct.

####### DO NOT EDIT CODE BELOW (changing MAX_MISSES is ok) ########
import random
import sys

MAX_MISSES = 5
BORDER_LENGTH = 30
SINGLE_CHAR_LENGTH = 1


def blank_chars(word):
    """Returns a list of underscore characters with the same length as word.

    :param word: target word as a string
    :return: a list of underscore characters ('_')

    >>> blank_chars("happiness")
    ['_', '_', '_', '_', '_', '_', '_', '_', '_']
    """
    underscore_list = []
    for i in range(len(word)):
        underscore_list.append('_')

    return underscore_list


def space_chars(chars):
    """Returns a string with the characters in chars list separated by spaces.

    :param chars: a list of characters
    :return: a string containing characters in chars with intervening spaces

    >>> space_chars(['h', '_', 'p', 'p', '_', 'n', '_', '_', '_'])
    'h _ p p _ n _ _ _'
    """
    joined_string = " ".join(chars)

    # print(joined_string)

    return joined_string


def get_guess():
    """Prompts the user for a guess to check for the game's current word. When the user
    enters input other than a single character, the function prompts the user again
    for a guess. Only when the user enters a single character will the prompt for
    a guess stop being displayed. The function returns the single-character guess
    entered by the user.

    :return guess: a single character guessed by user
    """
    guess = input("Guess:\t")
    while True:
        if len(guess) != SINGLE_CHAR_LENGTH or not guess.isalpha():
            guess = input("Guess:\t")
        else:
            break

    guess_output = guess.lower()

    return guess_output


def check_guess(word, guess):
    """Returns a list of positions where guess is present in word.
    An empty list should be returned when guess is not a single
    character or when guess is not present in word.


    :param word: target word as a string
    :param guess: a single character guessed by user
    :return positions: list of integer positions
    """
    position_list = []
    for i in range(len(word)):
        if word[i] == guess:
            position_list.append(i)

    return position_list


def update_chars(chars, guess, positions):
    """Updates the list of characters, chars, so that the characters
    at the index values in the positions list are updated to the
    character guess.


    :param chars: a list of characters
    :param guess: a single character guessed by user
    :param positions: list of integer positions
    :return: None
    """
    for i in positions:
        chars[i] = guess


def add_to_misses(misses, guess):
    """Adds the character guess to the misses list.

    :param misses: list of guesses not present in target word
    :param guess: a single character guessed by user
    :return: None
    """
    misses.append(guess)


def is_round_complete(chars, misses):
    """Indicates whether or not a round has ended. This function returns True
    when the user has successfully guessed the target word or exceeds the
    number of allowed misses. Otherwise, the function returns False,
    indicating that the round is not complete. A message revealing the
    user's success or failure guessing the target word is output by this
    function when the round is complete.


    :param chars: a list of characters
    :param misses: list of guesses not present in target word
    :return status: True when round is finished, False otherwise
    """
    if len(misses) > MAX_MISSES:
        print("")
        print("SORRY! NO GUESSES LEFT.")
        return True
    elif '_' not in chars:
        print("")
        print("YOU GOT IT!")
        return True
    else:
        return False


def update_state(chars, misses, guess, positions):
    """Updates the state of the game based on user's guess. Calls the function update_chars() when
    the positions list is not empty to reveal the indices where the character guess is present. Calls the
    function add_to_misses() when the positions list is empty to add guess to the misses list.

    :param chars: a list of characters
    :param misses: list of guesses not present in target word
    :param guess: a single character guessed by user
    :param positions: list of integer positions
    :return: None
    """
    if positions == []:
        add_to_misses(misses, guess)
    else:
        update_chars(chars, guess, positions)


def read_words(filepath):
    """Opens a file of word located at filepath, reads the file of words line by line,
    and adds each word from the file to a list. The list is returned by the
    function

    :param filepath: path to input file of words (one per line)
    :return word_list: list of strings contained in input file
    """
    word_file = open(filepath, 'r')
    word_list = word_file.readlines()
    for i in word_list:
        updated_word = i.strip()
        word_list[word_list.index(i)] = updated_word

    word_file.close()

    return word_list


def get_word(words):
    """Selects a single word randomly from words list and returns it.

    :param words: list of strings
    :return word: string from words list
    """
    random_int = random.randrange(len(words))
    random_word = words[random_int]

    return random_word


def is_game_complete():
    """Prompts the user with "Play again (Y/N)?". The question is repeated
    until the user enters a valid response (one of Y/y/N/n). The function
    returns False if the user enters 'Y' or 'y' and returns True if the user
    enters 'N' or 'n'.

    :return response: boolean representing game completion status
    """
    play_again = input("Play again (Y/N)? ")
    valid_options = 'YyNn'
    while True:
        if play_again not in valid_options:
            play_again = input("Play again (Y/N)? ")
        else:
            break
    if play_again.lower() == 'y':
        return False
    else:
        return True


def run_guessing_game(words_filepath):
    """Controls running The Guessing Game. This includes parsing
    the words file and executing multiple rounds of the game.

    :param words_filepath: the location of the file of words for the game
    :return: None
    """
    try:
        read_words(words_filepath)
    except FileNotFoundError:
        print("The provided file location is not valid. Please enter a valid path to a file.")
        return

    print("Welcome to The Guessing Game!")
    while True:

        word_list = read_words(words_filepath)
        random_word = get_word(word_list)
        character_list = blank_chars(random_word)  # initialized as an underscore list
        misses = []
        done = False
        while not done:
            # while loop for game repeated lines
            while not is_round_complete(character_list, misses):
                display_game_state(character_list, misses)
                # Prompt for Guess
                guess = get_guess()
                position_list = check_guess(random_word, guess)
                update_state(character_list, misses, guess, position_list)

            else:
                done = True
        display_game_state(random_word, misses)  # Displays original word for the round

        play_again = is_game_complete()
        if play_again is True:
            print("")
            print('Goodbye.')
            break
        else:
            continue


def display_game_state(chars, misses):
    """
    Displays the current state of the game: the list of characters to display
    and the list of misses.
    """

    print()
    print('=' * BORDER_LENGTH)
    print()

    print("Word:\t{}\n".format(space_chars(chars)))
    print("Misses:\t{}\n".format("".join(misses)))

####### DO NOT EDIT CODE ABOVE (changing MAX_MISSES is ok) ########


def main():

    ########## DO NOT EDIT ASSIGNMENT STATEMENT BELOW #########

    #filepath = sys.argv[-1]
    ########## DO NOT EDIT ASSIGNMENT STATEMENT ABOVE #########

    # call run_guessing_game() with filepath as argument and remove pass below
    run_guessing_game("word_file.txt")




if __name__ == '__main__':
    main()
