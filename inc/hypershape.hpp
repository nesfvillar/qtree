#pragma once

#include "point.hpp"
#include <concepts>

namespace qtree
{
    template <std::size_t D, class Shape, class IntersectShape = Shape, class T = double>
    concept CompatibleShapes = requires(Point<D, T> p, Shape s, IntersectShape other)
    {
        {s.contains_point(p)};

        {other.contains_point(p)};

        {intersects(s, other)};

        {intersects(other, s)};
    };

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

    template <std::size_t D, class T = double>
    class HyperSphere
    {
    public:
        HyperSphere(Point<D, T> center, T radius):
            _center(center), _radius(radius)
        {
        }

        bool contains_point(const Point<D, T>& point) const
        {
            return _center.euclidean_distance(point) <= _radius;
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

    template<std::size_t D, class T>
    bool intersects(const HyperCube<D, T>& left, const HyperCube<D, T>& right)
    {
        auto center_difference = left.get_center() - right.get_center();
        T sum_radius = left.get_radius() + right.get_radius();

        for (std::size_t i = 0; i < D; i++)
        {
            if (center_difference[i] <= sum_radius) return true;
        }
        return false;
    }

    template<std::size_t D, class T>
    bool intersects(const HyperCube<D, T>& cube, const HyperSphere<D, T>& sphere)
    {
        const auto& cube_center = cube.get_center();
        const auto& sphere_center = sphere.get_center();

        T sum_radius = sqrt(2) * cube.get_radius() + sphere.get_radius();
        return cube_center.euclidean_distance(sphere_center) <= sum_radius;
    }

    template<std::size_t D, class T>
    bool intersects(const HyperSphere<D, T>& sphere, const HyperCube<D, T>& cube)
    {
        return intersects(cube, sphere);
    }


    template<std::size_t D, class T>
    bool intersects(const HyperSphere<D, T>& left, const HyperSphere<D, T>& right)
    {
        const auto& left_center = left.get_center();
        const auto& right_center = right.get_center();

        T sum_radius = left.get_radius() + right.get_radius();
        return left_center.euclidean_distance(right_center) <= sum_radius;
    }
}
