from wave_algorithm import WaveAlgorithm
from wave_algorithm import Point

if __name__ == '__main__':
    matrix = [
        [0, 2, 0, 0, 0, 0, 2, 0, 0, 0, 0, 2, 0, 0, 0, 0, 2, 0, 0, 0, 0, 2, 0, 0, 0, 0, 2, 0, 0, 0],
        [0, 2, 0, 1, 0, 0, 2, 0, 1, 0, 0, 2, 0, 1, 0, 0, 2, 0, 1, 0, 0, 2, 0, 1, 0, 0, 2, 0, 1, 0],
        [0, 2, 0, 5, 0, 0, 2, 0, 5, 0, 0, 2, 0, 5, 0, 0, 2, 0, 5, 0, 0, 2, 0, 5, 0, 0, 2, 0, 5, 0],
        [0, 2, 2, 1, 0, 0, 2, 2, 1, 0, 0, 2, 2, 1, 0, 0, 2, 2, 1, 0, 0, 2, 2, 1, 0, 0, 2, 2, 1, 0],
        [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0]
    ]

    wave_algorithm = WaveAlgorithm()
    path = wave_algorithm.get_path(matrix, Point(0, 0), Point(2, 27), 0)

    for point in path:
        print(f'[{point.row}, {point.col}]')
