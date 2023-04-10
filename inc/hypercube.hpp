#pragma once

#include "point.hpp"

namespace qtree
{
    template <std::size_t D, class T = double>
    class HyperCube
    {
    public:
        HyperCube(Point<D, T> center, T radius):
            _center(center), _radius(radius)
        {
        }

        bool contains_point(const Point<D, T>& point) const
        {
            return _center.chebyshev_distance(point) <= _radius;
        }

        bool intersects(const HyperCube<D, T>& other) const
        {
            auto center_distance = other._center - _center;
            T radius_sum = other._radius + _radius;
            for (std::size_t i = 0; i < D; i++)
            {
                if (center_distance[i] <= radius_sum) return true;
            }
            return false;
        }

        const Point<D, T>& get_center() const
        {
            return _center;
        }

        const T& get_radius() const
        {
            return _radius;
        }

    private:
        Point<D, T> _center;
        T _radius;
    };
}
