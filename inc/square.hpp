#pragma once

#include "point.hpp"

namespace qtree
{
    class Square
    {
    public:
        Square(Point<2> center, double radius);

        bool contains_point(Point<2> point) const;

        bool intersects_square(const Square& square) const;

        const Point<2>& get_center() const;

        const double& get_radius() const;

    private:
        Point<2> _center;
        double _radius;
    };
}
