#pragma once

#include "point.hpp"

namespace qtree
{
    template <std::size_t D, class T = double>
    class HyperSphere
    {
    public:
        HyperSphere(Point<D, T> center, T radius):
            _center(center), _radius(radius)
        {
        }

        bool contains_point(const Point<D, T>& point)
        {
            return _center.euclidean_distance(point) <= _radius;
        }

        bool intersects(const HyperSphere<D, T>& other)
        {
            return _center.euclidean_distance(other._center) <= (other._radius + _radius);
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
