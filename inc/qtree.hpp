#pragma once

#include "point.hpp"
#include "hypercube.hpp"

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

        QTree(
            std::size_t node_capacity,
            Square _boundary
        );

        bool insert(const Point<2>& p);

        std::vector<Point<2>> query_range(const Square& sq) const;

    private:
        void subdivide();

        std::size_t _node_capacity;
        Square _boundary;
        std::optional<std::array<std::unique_ptr<QTree>, 4>> _subtrees;
        std::vector<Point<2>> _points;

    };
}
