# Author: <Suvir Wadhwa>
# Assignment #6 - Battleship
# Date due: 2021-05-06
# I pledge that I have completed this assignment without
# collaborating with anyone else, in conformance with the
# NYU School of Engineering Policies and Procedures on
# Academic Misconduct.

import random

### DO NOT EDIT BELOW (with the exception of MAX_MISSES) ###

HIT_CHAR = 'x'
MISS_CHAR = 'o'
BLANK_CHAR = '.'
HORIZONTAL = 'h'
VERTICAL = 'v'
MAX_MISSES = 20
SHIP_SIZES = {
    "carrier": 5,
    "battleship": 4,
    "cruiser": 3,
    "submarine": 3,
    "destroyer": 2
}
NUM_ROWS = 10
NUM_COLS = 10
ROW_IDX = 0
COL_IDX = 1
MIN_ROW_LABEL = 'A'
MAX_ROW_LABEL = 'J'


def get_random_position():
    """Generates a random location on a board of NUM_ROWS x NUM_COLS."""

    row_choice = chr(
                    random.choice(
                        range(
                            ord(MIN_ROW_LABEL),
                            ord(MIN_ROW_LABEL) + NUM_ROWS
                        )
                    )
    )

    col_choice = random.randint(0, NUM_COLS - 1)

    return (row_choice, col_choice)


def play_battleship():
    """Controls flow of Battleship games including display of
    welcome and goodbye messages.

    :return: None
    """

    print("Let's Play Battleship!\n")

    game_over = False

    while not game_over:

        game = Game()
        game.display_board()

        while not game.is_complete():
            pos = game.get_guess()
            result = game.check_guess(pos)
            game.update_game(result, pos)
            game.display_board()

        game_over = end_program()

    print("Goodbye.")

### DO NOT EDIT ABOVE (with the exception of MAX_MISSES) ###


class Ship:

    def __init__(self, name, start_position, orientation):
        """Creates a new ship with the given name, placed at start_position in the
        provided orientation. The number of positions occupied by the ship is determined
        by looking up the name in the SHIP_SIZE dictionary.

        :param name: the name of the ship
        :param start_position: tuple representing the starting position of ship on the board
        :param orientation: the orientation of the ship ('v' - vertical, 'h' - horizontal)
        :return: None
        """
        self.name = name
        self.positions = {}
        self.sunk = False
        length_of_ship = SHIP_SIZES[name]
        if orientation == VERTICAL:
            start_row = ord(start_position[ROW_IDX])
            start_column = start_position[COL_IDX]
            counter = 0
            while counter < length_of_ship:
                partial_position = (chr(start_row), start_column)
                self.positions[partial_position] = False
                counter += 1
                start_row += 1
        else:
            start_row = (start_position[ROW_IDX])
            start_column = start_position[COL_IDX]
            counter = 0
            while counter < length_of_ship:
                partial_position = (start_row, start_column)
                self.positions[partial_position] = False
                counter += 1
                start_column += 1


class Game:
    def __init__(self, max_misses=MAX_MISSES):
        """ Creates a new game with max_misses possible missed guesses.
        The board is initialized in this function and ships are randomly
        placed on the board.

        :param max_misses: maximum number of misses allowed before game ends
        """
        self.max_misses = max_misses
        self.guesses = []
        self.ships = []
        self.board = {}
        Game.initialize_board(self)
        self.create_and_place_ships()

    def initialize_board(self):
        """Sets the board to it's initial state with each position occupied by
        a period ('.') string.

        :return: None
        """
        self.board = {}
        starting_letter_val = ord(MIN_ROW_LABEL)
        end_letter_val = ord(MAX_ROW_LABEL)
        while starting_letter_val <= end_letter_val:
            self.board[chr(starting_letter_val)] = [BLANK_CHAR] * NUM_COLS
            starting_letter_val += 1

    def in_bounds(self, start_position, ship_size, orientation):
        """Checks that a ship requiring ship_size positions can be placed at start position.

        :param start_position: tuple representing the starting position of ship on the board
        :param ship_size: number of positions needed to place ship
        :param orientation: the orientation of the ship ('v' - vertical, 'h' - horizontal)
        :return status: True if ship placement inside board boundary, False otherwise
        """
        if orientation == VERTICAL:
            start_row_index = start_position[ROW_IDX]
            lowest_position = ord(MIN_ROW_LABEL)
            highest_position = ord(MAX_ROW_LABEL)
            if (ord(start_row_index) + ship_size) in range(lowest_position, highest_position+1):
                return True
            else:
                return False
        else:
            start_column_index = start_position[COL_IDX]
            lowest_position = 0
            highest_position = 9
            if (start_column_index + ship_size) in range(lowest_position, highest_position+1):
                return True
            else:
                return False

    def overlaps_ship(self, start_position, ship_size, orientation):
        """Checks for overlap between previously placed ships and a potential new ship
        placement requiring ship_size positions beginning at start_position in the
        given orientation.

        :param start_position: tuple representing the starting position of ship on the board
        :param ship_size: number of positions needed to place ship
        :param orientation: the orientation of the ship ('v' - vertical, 'h' - horizontal)
        :return status: True if ship placement overlaps previously placed ship, False otherwise
        """
        if orientation == VERTICAL:
            start_row = ord(start_position[ROW_IDX])
            start_column = start_position[COL_IDX]
            counter = 0
            while counter < ship_size:
                partial_position = (chr(start_row), start_column)
                for ship in self.ships:
                    if partial_position in ship.positions.keys():
                        return True
                counter += 1
                start_row += 1
        else:
            start_row = (start_position[ROW_IDX])
            start_column = start_position[COL_IDX]
            counter = 0
            while counter < ship_size:
                partial_position = (start_row, start_column)
                for ship in self.ships:
                    if partial_position in ship.positions.keys():
                        return True
                counter += 1
                start_column += 1
        return False

    def place_ship(self, start_position, ship_size):
        """Determines if placement is possible for ship requiring ship_size positions placed at
        start_position. Returns the orientation where placement is possible or None if no placement
        in either orientation is possible.

        :param start_position: tuple representing the starting position of ship on the board
        :param ship_size: number of positions needed to place ship
        :return orientation: 'h' if horizontal placement possible, 'v' if vertical placement possible,
            None if no placement possible
        """
        if Game.overlaps_ship(self, start_position, ship_size, HORIZONTAL) is not True and Game.in_bounds(self, start_position, ship_size, HORIZONTAL) is True:
            return HORIZONTAL
        elif Game.overlaps_ship(self, start_position, ship_size, VERTICAL) is not True and Game.in_bounds(self, start_position, ship_size, VERTICAL) is True:
            return VERTICAL
        else:
            return None

    def create_and_place_ships(self):
        """Instantiates ship objects with valid board placements.

        :return: None
        """
        for i in self._ship_types:
            is_true = True
            while is_true:
                start_position = get_random_position()
                ship_size = SHIP_SIZES[i]
                orientation = self.place_ship(start_position, ship_size)
                if orientation is None:
                    continue
                else:
                    is_true = False
                    ship = Ship(i, start_position, orientation)
                    self.ships.append(ship)

    def get_guess(self):
        """Prompts the user for a row and column to attack. The
        return value is a board position in (row, column) format

        :return position: a board position as a (row, column) tuple
        """
        row = input("Enter a row: ")
        is_true_1 = True
        while is_true_1:
            if ord(row) not in range(ord(MIN_ROW_LABEL), ord(MAX_ROW_LABEL) + 1):
                row = input("Enter a row: ")
            else:
                is_true_1 = False

        column = int(input("Enter a column:"))
        is_true_2 = True
        while is_true_2:
            if column not in range(0, 10):
                column = int(input("Enter a column:"))
            else:
                is_true_2 = False

        return row, column

    def check_guess(self, position):
        """Checks whether or not position is occupied by a ship. A hit is
        registered when position occupied by a ship and position not hit
        previously. A miss occurs otherwise.

        :param position: a (row,column) tuple guessed by user
        :return: guess_status: True when guess results in hit, False when guess results in miss
        """
        output = False
        for ship in self.ships:
            counter = 0
            for pos in ship.positions:
                if (pos == position) and (ship.positions[pos] == False):
                    ship.positions[pos] = True
                    output = True
                if ship.positions[pos] == True:
                    counter += 1
            if counter == SHIP_SIZES[ship.name]:
                ship.sunk = True
                print("You sunk the {}!".format(ship.name))
        return output

    def update_game(self, guess_status, position):
        """Updates the game by modifying the board with a hit or miss
        symbol based on guess_status of position.

        :param guess_status: True when position is a hit, False otherwise
        :param position:  a (row,column) tuple guessed by user
        :return: None
        """
        row = position[ROW_IDX]
        column = position[COL_IDX]

        if guess_status == True:
            self.board[row][column] = HIT_CHAR
        else:
            self.guesses.append(position)
            if self.board[row][column] == BLANK_CHAR:
                self.board[row][column] = MISS_CHAR

    def is_complete(self):
        """Checks to see if a Battleship game has ended. Returns True when the game is complete
        with a message indicating whether the game ended due to successfully sinking all ships
        or reaching the maximum number of guesses. Returns False when the game is not
        complete.

        :return: True on game completion, False otherwise
        """
        sunk_counter = 0
        for ship in self.ships:
            if ship.sunk:
                sunk_counter += 1

        if len(self.guesses) >= MAX_MISSES:
            print("SORRY! NO GUESSES LEFT.")
            return True
        elif sunk_counter == len(self.ships):
            print("YOU WIN!")
            return True
        else:
            return False




    ########## DO NOT EDIT #########
    
    _ship_types = ["carrier", "battleship", "cruiser", "submarine", "destroyer"]
    
    
    def display_board(self):
        """ Displays the current state of the board."""

        print()
        print("  " + ' '.join('{}'.format(i) for i in range(len(self.board))))
        for row_label in self.board.keys():
            print('{} '.format(row_label) + ' '.join(self.board[row_label]))
        print()

    ########## DO NOT EDIT #########


def end_program():
    """Prompts the user with "Play again (Y/N)?" The question is repeated
    until the user enters a valid response (Y/y/N/n). The function returns
    False if the user enters 'Y' or 'y' and returns True if the user enters
    'N' or 'n'.

    :return response: boolean indicating whether to end the program
    """
    play_again = input("Play again (Y/N)?")
    valid_inputs = ['y', 'Y', 'n', 'N']
    is_true = True
    while is_true:
        if play_again not in valid_inputs:
            play_again = input("Play again (Y/N)?")
        else:
            is_true = False

    if play_again == 'y' or play_again == 'Y':
        return False
    else:
        return True


def main():
    """Executes one or more games of Battleship."""

    play_battleship()


if __name__ == "__main__":
    main()
