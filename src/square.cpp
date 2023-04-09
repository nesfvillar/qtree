#include "square.hpp"

#include <math.h>

using namespace qtree;

Square::Square(Point<2> center, double radius):
    _center(center),
    _radius(radius)
{
}

bool Square::contains_point(Point<2> point) const
{
    auto distance = _center - point;
    for (std::size_t i = 0; i < 2; i++)
    {
        if (std::fabs(distance[i]) > _radius)
        {
            return false;
        }
    }
    return true;
}

bool Square::intersects_square(const Square& square) const
{
    auto distance_centers = square._center - _center;
    double radius_sum = square._radius + _radius;
    for (std::size_t i = 0; i < 2; i++)
    {
        if (distance_centers[i] - radius_sum < 0)
        {
            return true;
        }
    }
    return false;
}

const Point<2>& qtree::Square::get_center() const
{
    return _center;
}

const double& qtree::Square::get_radius() const
{
    return _radius;
}
