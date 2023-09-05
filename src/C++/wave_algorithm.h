//
//   File:    wave_algorithm.h
//   Author: [Gubaydullin Nurislam / School 21]
//
//   Description:
//      This file contains the implementation of the WaveAlgorithm class,
//      which implements the Wave Algorithm for finding the shortest path in a matrix.
//      It also includes the Pair class, which represents a pair of values (row, column).
//
//   School21 Algorithms Club Quote:
//      "Building innovative solutions for efficient algorithms."
//

#ifndef WAVE_ALGORITHM_WAVE_ALGORITHM_H_
#define WAVE_ALGORITHM_WAVE_ALGORITHM_H_

#include <bits/stdc++.h>

template <typename T>
using Matrix = std::vector<std::vector<T>>;

struct Point {
    int row = -1, col = -1;

    Point() = default;
    Point(int r, int c) : row(r), col(c) {};
    Point(std::size_t r, std::size_t c) : row(r), col(c) {};
};


/**
* @brief Class implementing the Wave Algorithm for pathfinding in a matrix.
* @tparam T The type of elements in the matrix. Must be a fundamental type.
*/
template <typename T>
class WaveAlgorithm {
    static_assert(std::is_fundamental_v<T>, "template parameter T must be fundamental");
public:
    /**
    * @brief Constructor for the WaveAlgorithm class.
    * @param matrix The matrix representing the environment.
    * @param from The starting point for pathfinding.
    * @param to The target point for pathfinding.
    * @param empty The value representing empty cells in the matrix.
    */
    WaveAlgorithm(const Matrix<T> &matrix, Point from, Point to, T empty)
        : matrix_(matrix), start_(from), finish_(to), empty_(empty) {};

    /**
    * @brief Finds the path from the starting point to the target point using the Wave Algorithm.
    * @return A vector of points representing the path from start to finish.
     * If no path is found, an empty vector is returned.
    */
    std::vector<Point> getPath() {
        InitializeStartState();

        while (!old_wave_.empty())
            if (StepWave())
                break;

        return MakePath();
    }

private:
    /**
    * @brief Initializes the starting state for the algorithm.
    */
    void InitializeStartState() {
        wave_.clear();
        wave_step_ = 0;
        old_wave_  = std::vector<Point>{start_};

        const auto row_length = matrix_.empty() ? 0 : matrix_[0].size();

        length_map_ = Matrix<T>(matrix_.size(), std::vector<int>(row_length, -1));
        length_map_[start_.row][start_.col] = wave_step_;
    }

    /**
     * @brief Performs a single step of the wave expansion.
     * @return True if the target point is reached, false otherwise.
     */
    bool StepWave() {
        ++wave_step_;

        for (auto [row, col] : old_wave_) {
            auto neighbors = getNeighbors({row, col});
            for (auto [x, y] : neighbors) {
                if (matrix_[x][y] == empty_) {
                    if (length_map_[x][y] == -1) {
                        wave_.emplace_back(x, y);
                        length_map_[x][y] = wave_step_;
                    }

                    if (x == finish_.row and y == finish_.col)
                        return true;
                }
            }
        }

        old_wave_ = std::move(wave_);
        return false;
    }

    /**
     * @brief Retrieves the neighbors of a given position in the matrix.
     * @param position The position for which to find neighbors.
     * @return A vector of neighboring points.
     */
    std::vector<Point> getNeighbors(Point position) {
        std::vector<Point> neighbors;
        neighbors.reserve(4); // Von Neumann's neighborhood

        auto [row, col] = position;

        if (row - 1 >= 0)
            neighbors.emplace_back(row - 1, col);
        if (row + 1 < matrix_.size())
            neighbors.emplace_back(row + 1, col);
        if (col - 1 >= 0)
            neighbors.emplace_back(row, col - 1);
        if (col + 1 < matrix_[0].size())
            neighbors.emplace_back(row, col + 1);

        return neighbors;
    }

    /**
     * @brief Constructs the path from the length map.
     * @return A vector of points representing the path from start to finish.
     */
    std::vector<Point> MakePath() {
        if (length_map_[finish_.row][finish_.col] == -1)
            return {};

        auto [row, col] = finish_;

        std::vector<Point> path;
        path.reserve(length_map_[row][col] + 1);
        path.push_back(finish_);

        while (length_map_[row][col] != 0) {
            auto compare = length_map_[row][col];
            auto neighbors = getNeighbors({row, col});

            for (auto [x, y] : neighbors) {
                if (length_map_[x][y] + 1 == compare and matrix_[x][y] == empty_) {
                    row = x, col = y;
                    path.emplace_back(row, col);
                    break;
                }
            }
        }

        return path;
    }

private:
    Matrix<int> length_map_, matrix_;
    std::vector<Point> old_wave_, wave_;
    Point start_, finish_;
    int wave_step_ {};
    T empty_;
};

#endif // WAVE_ALGORITHM_WAVE_ALGORITHM_H_
