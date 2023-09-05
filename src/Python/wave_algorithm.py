"""

File: wave_algorithm.py
Author: [Gubaydullin Nurislam / School 21]

Description:
This file contains the implementation of the WaveAlgorithm class,
which implements the Wave Algorithm for finding the shortest path in a matrix.
It also includes the Pair class, which represents a pair of values (row, column).

School21 Algorithms Club Quote:
    "Building innovative solutions for efficient algorithms."

"""


class Pair:
    """
    This class represents a pair of values (row, column).

    Args:
        row (int): The row value.
        col (int): The column value.

    Attributes:
        row (int): The row value.
        col (int): The column value.

    Methods:
        __iter__(): Returns an iterator over the pair values.

    """

    def __init__(self, row: int, col: int):
        self.row = row
        self.col = col

    def __iter__(self):
        return iter((self.row, self.col))


class WaveAlgorithm:
    """
    This class implements the Wave Algorithm for finding the shortest path in a matrix.
    The algorithm starts from a given start point and searches for the shortest path to a given finish point,
    considering a specified empty value in the matrix.

    Args:
        matrix (list): The matrix representing the environment.
        start (Pair): The starting point (row, column) in the matrix.
        finish (Pair): The finishing point (row, column) in the matrix.
        empty (int): The value representing empty cells in the matrix.

    Attributes:
        __matrix (list): The matrix representing the environment.
        __start (Pair): The starting point (row, column) in the matrix.
        __finish (Pair): The finishing point (row, column) in the matrix.
        __empty (int): The value representing empty cells in the matrix.
        __wave (list): List of points in the current wavefront.
        __wave_step (int): The current step of the wavefront.
        __old_wave (list): List of points in the previous wavefront.
        __length_map (list): 2D list representing the lengths of the paths from the start point to each cell.

    Methods:
        get_path(): Finds the shortest path from the start point to the finish point in the matrix.
        __step_wave(): Performs one step of the wavefront propagation.
        __initialize_start_state(): Initializes the start state of the algorithm.
        __get_neighbors(position): Returns a list of valid neighboring positions for a given position.
        __make_path(): Constructs the shortest path from the finish point to the start point.

    """

    def __init__(self, matrix: list, start: Pair, finish: Pair, empty: int):
        """
        Initializes a new instance of the WaveAlgorithm class.

        Args:
            matrix (list): The matrix representing the environment.
            start (Pair): The starting point (row, column) in the matrix.
            finish (Pair): The finishing point (row, column) in the matrix.
            empty (int): The value representing empty cells in the matrix.
        """

        self.__matrix = matrix
        self.__start = start
        self.__finish = finish
        self.__empty = empty

        self.__initialize_start_state()

    def get_path(self) -> list:
        """
        Finds the shortest path from the start point to the finish point in the matrix.

        Returns:
            list: The list of points representing the shortest path from the start to the finish point.
        """

        self.__initialize_start_state()

        while len(self.__old_wave) != 0:
            if self.__step_wave():
                break

        return self.__make_path()

    def __step_wave(self) -> bool:
        """
        Performs one step of the wavefront propagation.

        Returns:
            bool: True if the finish point is reached, False otherwise.
        """

        self.__wave_step += 1

        for row, col in self.__old_wave:
            neighbors = self.__get_neighbors(Pair(row, col))

            for x, y in neighbors:
                if self.__matrix[x][y] == self.__empty:
                    if self.__length_map[x][y] == -1:
                        self.__wave.append(Pair(x, y))
                        self.__length_map[x][y] = self.__wave_step

                    finish_row, finish_col = self.__finish
                    if x == finish_row and y == finish_col:
                        return True

        self.__old_wave = list(self.__wave)
        self.__wave.clear()

        return False

    def __initialize_start_state(self) -> None:
        """
        Initializes the start state of the algorithm.
        """

        self.__wave = list()
        self.__wave_step = 0
        self.__old_wave = [self.__start]
        self.__length_map = []

        for _ in range(len(self.__matrix)):
            self.__length_map.append([-1] * len(self.__matrix[0]))

        row, col = self.__start
        self.__length_map[row][col] = 0

    def __get_neighbors(self, position: Pair) -> list:
        """
        Returns a list of valid neighboring positions for a given position.

        Args:
            position (Pair): The current position (row, column) in the matrix.

        Returns:
            list: The list of valid neighboring positions.
        """

        neighbors = []

        row, col = position

        if row - 1 >= 0:
            neighbors.append(Pair(row - 1, col))
        if row + 1 < len(self.__matrix):
            neighbors.append(Pair(row + 1, col))
        if col - 1 >= 0:
            neighbors.append(Pair(row, col - 1))
        if col + 1 < len(self.__matrix[0]):
            neighbors.append(Pair(row, col + 1))

        return neighbors

    def __make_path(self) -> list:
        """
        Constructs the shortest path from the finish point to the start point.

        Returns:
            list: The list of points representing the shortest path from the finish to the start point.
        """

        row, col = self.__finish
        if self.__length_map[row][col] == -1:
            return list()

        enter_order_path = []

        while self.__length_map[row][col] != 0:
            compare = self.__length_map[row][col]
            neighbors = self.__get_neighbors(Pair(row, col))

            for x, y in neighbors:
                if self.__length_map[x][y] + 1 == compare and self.__matrix[x][y] == self.__empty:
                    row, col = x, y
                    enter_order_path.append(Pair(row, col))
                    break

        return enter_order_path
