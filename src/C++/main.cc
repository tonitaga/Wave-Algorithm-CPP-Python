#include "wave_algorithm.h"

int main() {
    Matrix<int> matrix {
            {0, 2, 0, 0, 0, 0, 2, 0, 0, 0, 0, 2, 0, 0, 0, 0, 2, 0, 0, 0, 0, 2, 0, 0, 0, 0, 2, 0, 0, 0},
            {0, 2, 0, 1, 0, 0, 2, 0, 1, 0, 0, 2, 0, 1, 0, 0, 2, 0, 1, 0, 0, 2, 0, 1, 0, 0, 2, 0, 1, 0},
            {0, 2, 0, 5, 0, 0, 2, 0, 5, 0, 0, 2, 0, 5, 0, 0, 2, 0, 5, 0, 0, 2, 0, 5, 0, 0, 2, 0, 5, 0},
            {0, 2, 2, 1, 0, 0, 2, 2, 1, 0, 0, 2, 2, 1, 0, 0, 2, 2, 1, 0, 0, 2, 2, 1, 0, 0, 2, 2, 1, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
    };

    WaveAlgorithm wave(matrix, {0, 0}, {2, 27}, 0);
    auto path = wave.getPath();

    for (auto point : path)
        printf("[%d, %d] -> ", point.row, point.col);

    return EXIT_SUCCESS;
}