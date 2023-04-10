#include "qtree.hpp"

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

void QTree::subdivide()
{
    auto center = _boundary.get_center();
    auto new_radius = _boundary.get_radius() / 2;

    _subtrees =
    { {
        {std::make_unique<QTree>(_node_capacity, Square(center + Point<2>({new_radius, new_radius}), new_radius))},
        {std::make_unique<QTree>(_node_capacity, Square(center + Point<2>({new_radius, -new_radius }), new_radius))},
        {std::make_unique<QTree>(_node_capacity, Square(center + Point<2>({-new_radius, -new_radius }), new_radius))},
        {std::make_unique<QTree>(_node_capacity, Square(center + Point<2>({-new_radius, new_radius }), new_radius))}
    } };
}
