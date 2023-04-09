#pragma once

#include "point.hpp"
#include "square.hpp"

#include <array>
#include <vector>
#include <optional>

namespace qtree
{
    class QTree
    {
    public:

        QTree(
            std::size_t node_capacity,
            Square _boundary
        );

        bool insert(Point<2> p);

        std::vector<Point<2>> query_range(const Square& sq) const;

    private:
        void subdivide();

        std::size_t _node_capacity;
        Square _boundary;
        std::optional<std::array<std::unique_ptr<QTree>, 4>> _subtrees;
        std::vector<Point<2>> _points;

    };
}
