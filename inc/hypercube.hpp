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
            auto distance = _center - point;
            for (std::size_t i = 0; i < D; i++)
            {
                if (std::fabs(distance[i]) > _radius)
                {
                    return false;
                }
            }
            return true;
        }

        bool intersects(const HyperCube<D, T>& other) const
        {
            auto distance_centers = other._center - _center;
            T radius_sum = other._radius + _radius;

            for (std::size_t i = 0; i < D; i++)
            {
                if (distance_centers[i] - radius_sum < 0)
                {
                    return true;
                }
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
