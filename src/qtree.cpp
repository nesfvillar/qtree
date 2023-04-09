#include "qtree.hpp"

#include <memory>
#include <stdexcept>

using namespace qtree;

QTree::QTree(std::size_t node_capacity, Square boundary):
    _node_capacity(node_capacity),
    _boundary(boundary)
{
}

bool QTree::insert(const Point<2>& p)
{
    if (!_boundary.contains_point(p)) return false;

    if (_points.size() < _node_capacity && !_subtrees.has_value())
    {
        _points.push_back(p);
        return true;
    }

    if (!_subtrees.has_value()) subdivide();

    for (auto& subtree : _subtrees.value())
    {
        if (subtree->insert(p)) return true;
    }

    throw std::logic_error("Could not insert a point");
}

std::vector<Point<2>> QTree::query_range(const Square& sq) const
{
    std::vector<Point<2>> result;

    if (!_boundary.intersects(sq)) return result;

    for (const auto& p : _points) {
        if (_boundary.contains_point(p)) result.push_back(p);
    }

    if (_subtrees.has_value())
    {
        for (const auto& subtree : _subtrees.value())
        {
            auto subtree_result = subtree->query_range(sq);
            result.insert(result.end(), subtree_result.begin(), subtree_result.end());
        }
    }

    return result;
}

void QTree::subdivide()
{
    auto center = _boundary.get_center();
    auto new_radius = _boundary.get_radius() / 2;

    _subtrees =
    { {
        {std::make_unique<QTree>(_node_capacity, Square(center + Point<2>{new_radius, new_radius }, new_radius))},
        {std::make_unique<QTree>(_node_capacity, Square(center + Point<2>{new_radius, -new_radius }, new_radius))},
        {std::make_unique<QTree>(_node_capacity, Square(center + Point<2>{-new_radius, -new_radius }, new_radius))},
        {std::make_unique<QTree>(_node_capacity, Square(center + Point<2>{-new_radius, new_radius }, new_radius))}
    } };
}
