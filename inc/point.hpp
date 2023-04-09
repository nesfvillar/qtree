#pragma once

#include <array>

namespace qtree
{
    template <std::size_t N, class T = double>
    class Point
    {
    public:
        Point(std::initializer_list<T> values):
            _values(values)
        {
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
            return Point(result);
        }

        Point<N, T> operator+(const Point& rhs) const
        {
            std::array<T, N> result;
            for (std::size_t i = 0; i < N; i++)
            {
                result[i] = _values[i] + _rhs[i];
            }
            return Point(result);
        }

        Point<N, T> operator-(const Point& rhs) const
        {
            std::array<T, N> result;
            for (std::size_t i = 0; i < N; i++)
            {
                result[i] = _values[i] - rhs[i];
            }
            return Point(result);
        }

    private:
        std::array <T, N> _values;
    };
}
