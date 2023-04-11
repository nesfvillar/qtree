#pragma once

#include <array>
#include <math.h>
#include <ostream>

namespace qtree
{
    template <std::size_t N, class T = double>
    class Point
    {
    public:
        Point(const std::array<T, N>& values):
            _values(values)
        {
        }

        Point(std::array<T, N>&& values):
            _values(values)
        {
        }

        T euclidean_distance(const Point<N, T>& other) const
        {
            auto difference = other - *this;
            T distance;
            for (std::size_t i = 0; i < N; i++)
            {
                distance += pow(difference[i], 2);
            }
            return sqrt(distance);
        }

        T chebyshev_distance(const Point<N, T>& other) const
        {
            auto difference = other - *this;
            T distance = -INFINITY;
            for (std::size_t i = 0; i < N; i++)
            {
                T abs_d = fabs(difference[i]);
                distance = abs_d > distance ? abs_d : distance;
            }
            return distance;
        }

        const T& operator[](std::size_t i) const
        {
            return _values[i];
        }

        Point<N, T> operator-() const
        {
            std::array<T, N> result;
            for (std::size_t i = 0; i < N; i++)
            {
                result[i] = -_values[i];
            }
            return Point(std::move(result));
        }

        Point<N, T> operator+(const Point& rhs) const
        {
            std::array<T, N> result;
            for (std::size_t i = 0; i < N; i++)
            {
                result[i] = _values[i] + rhs[i];
            }
            return Point(std::move(result));
        }

        Point<N, T> operator-(const Point& rhs) const
        {
            std::array<T, N> result;
            for (std::size_t i = 0; i < N; i++)
            {
                result[i] = _values[i] - rhs[i];
            }
            return Point(std::move(result));
        }

        friend std::ostream& operator<<(std::ostream& ostream, const Point<N, T>& point)
        {
            ostream << "Point: (";
            for (std::size_t i = 0; i < N; i++)
            {
                ostream << point[i];
                if (i < (N - 1)) ostream << ", ";
            }
            ostream << ")";
            return ostream;
        }

    private:
        std::array <T, N> _values;
    };
}
