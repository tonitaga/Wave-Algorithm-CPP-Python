#ifndef WAVE_ALGORITHM_WAVE_ALGORITHM_H_
#define WAVE_ALGORITHM_WAVE_ALGORITHM_H_

#include <vector>
#include <type_traits>

template <typename T>
using Matrix = std::vector<std::vector<T>>;

struct Point {
    int row = -1, col = -1;

    Point() = default;
    Point(int r, int c) : row(r), col(c) {};
    Point(std::size_t r, std::size_t c) : row(r), col(c) {};
};

class WaveAlgorithm {
public:
    template <typename T>
    std::vector<Point> getPath(const Matrix<T> &matrix, Point from, Point to, T empty);

private:
    Matrix<int> length_map_;
    std::vector<Point> old_wave_, wave_;
    int wave_step_ {};

private:
    template <typename T>
    void InitializeStartState(const Matrix<T> &matrix, Point from);

    template <typename T>
    bool StepWave(const Matrix<T> &matrix, Point to, T empty);

    template <typename T>
    std::vector<Point> getNeighbors(const Matrix<T> &matrix, Point current);

    template<typename T>
    std::vector<Point> MakePath(const Matrix<T> &matrix, Point to, T empty);

    template<typename T>
    bool PointsIsValid(const Matrix<T> &matrix, Point from, Point to);

    void DebugLengthMap(int width);
};

#include "wave_algorithm.tpp"

#endif // WAVE_ALGORITHM_WAVE_ALGORITHM_H_
