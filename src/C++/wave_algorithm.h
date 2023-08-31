#ifndef WAVE_ALGORITHM_WAVE_ALGORITHM_H_
#define WAVE_ALGORITHM_WAVE_ALGORITHM_H_

#include <vector>
#include <iomanip>
#include <iostream>
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
    std::vector<Point> getPath(const Matrix<T> &matrix, Point from, Point to, T empty) {
        static_assert(std::is_fundamental_v<T>, "template parameter T must be fundamental");

        if (!PointsIsValid(matrix, from, to))
            return {};

        InitializeStartState(matrix, from);

        while (!old_wave_.empty())
            if (StepWave(matrix, to, empty))
                break;

        DebugLengthMap(3);

        return MakePath(matrix, to, empty);
    }

private:
    template <typename T>
    void InitializeStartState(const Matrix<T> &matrix, Point from) {
        wave_.clear();
        wave_step_ = 0;
        old_wave_  = std::vector<Point>{from};

        const auto row_length = matrix.empty() ? 0 : matrix[0].size();

        length_map_ = Matrix<T>(matrix.size(), std::vector<int>(row_length, -1));
        length_map_[from.row][from.col] = wave_step_;
    }

    template <typename T>
    bool StepWave(const Matrix<T> &matrix, Point to, T empty) {
        ++wave_step_;

        for (auto [row, col] : old_wave_) {
            auto neighbors = getNeighbors(matrix, {row, col});
            for (auto [x, y] : neighbors) {
                if (matrix[x][y] == empty) {
                    if (length_map_[x][y] == -1) {
                        wave_.emplace_back(x, y);
                        length_map_[x][y] = wave_step_;
                    }

                    if (x == to.row and y == to.col)
                        return true;
                }
            }
        }

        old_wave_ = std::move(wave_);
        return false;
    }

    template <typename T>
    std::vector<Point> getNeighbors(const Matrix<T> &matrix, Point current) {
        std::vector<Point> neighbors;
        neighbors.reserve(4); // Von Neumann's neighborhood

        auto [row, col] = current;

        if (col - 1 >= 0)
            neighbors.emplace_back(row, col - 1);
        if (col + 1 < matrix[0].size())
            neighbors.emplace_back(row, col + 1);
        if (row - 1 >= 0)
            neighbors.emplace_back(row - 1, col);
        if (row + 1 < matrix.size())
            neighbors.emplace_back(row + 1, col);

        neighbors.shrink_to_fit();
        return neighbors;
    }

    template<typename T>
    std::vector<Point> MakePath(const Matrix<T> &matrix, Point to, T empty) {
        if (length_map_[to.row][to.col] == -1)
            return {};

        std::vector<Point> path;
        path.reserve(length_map_[to.row][to.col] + 1);
        path.push_back(to);

        auto [row, col] = to;

        while (length_map_[row][col] != 0) {
            auto compare_var = length_map_[row][col];
            auto neighbors = getNeighbors(matrix, {row, col});

            for (auto [x, y] : neighbors) {
                if (length_map_[x][y] + 1 == compare_var and matrix[x][y] == empty) {
                    row = x;
                    col = y;
                    break;
                }
            }


            path.emplace_back(row, col);
        }

        return path;
    }

    template<typename T>
    bool PointsIsValid(const Matrix<T> &matrix, Point from, Point to) {
        auto [frow, fcol] = from;
        auto [trow, tcol] = to;

        const int rows = matrix.size();
        const int cols = matrix.empty() ? 0 : matrix[0].size();

        return frow >= 0 and frow < rows and
               fcol >= 0 and fcol < cols and
               trow >= 0 and trow < rows and
               tcol >= 0 and tcol < cols;
    }

    void DebugLengthMap(int width) {
        for (const auto &row : length_map_) {
            for (const auto &row_item : row) {
                if (row_item == -1)
                    std::cout << std::setw(width) << 'X';
                else
                    std::cout << std::setw(width) << row_item;
            }
            std::cout << std::endl;
        }
    }

private:
    Matrix<int> length_map_;
    std::vector<Point> old_wave_, wave_;
    int wave_step_ {};
};

#endif // WAVE_ALGORITHM_WAVE_ALGORITHM_H_
