#pragma once

#include "point.hpp"
#include "hypershape.hpp"

#include <array>
#include <vector>
#include <optional>
#include <memory>

namespace qtree
{
    class QTree
    {
    public:
        using Square = HyperCube<2>;
        using Circle = HyperSphere<2>;

        QTree(
            std::size_t node_capacity,
            Square _boundary
        );

        bool insert(const Point<2>& p);

        template <class Shape>
            requires CompatibleShapes<2, Square, Shape>
        std::vector<Point<2>> query_range(const Shape& shape) const
        {
            std::vector<Point<2>> result;

            if (!intersects(_boundary, shape)) return result;

            for (const auto& p : _points) {
                if (shape.contains_point(p)) result.push_back(p);
            }

            if (_subtrees.has_value())
            {
                for (const auto& subtree : _subtrees.value())
                {
                    auto subtree_result = subtree->query_range(shape);
                    result.insert(result.end(), subtree_result.begin(), subtree_result.end());
                }
            }

            return result;
        }

    private:
        void subdivide();

        std::size_t _node_capacity;
        Square _boundary;
        std::optional<std::array<std::unique_ptr<QTree>, 4>> _subtrees;
        std::vector<Point<2>> _points;

    };
}
