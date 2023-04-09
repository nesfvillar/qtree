#include "qtree.hpp"

#include <iostream>

using namespace qtree;

int main()
{
    QTree::Square boundary(Point<2>({ 0, 0 }), 1.0);
    QTree qt(1, boundary);

    std::initializer_list<Point<2>> list =
    {
        Point<2>({0.5, 0.5}),
        Point<2>({-0.5, 0.25}),
        Point<2>({0.7, -0.1}),
        Point<2>({0.9, 0.7}),
        Point<2>({-0.7, -0.9}),
        Point<2>({0.5, -0.2})
    };

    for (const auto& p : list)
    {
        qt.insert(p);
    }

    QTree::Square check_boundary(Point<2>({ 0.5, 0.5 }), 0.5);

    auto result = qt.query_range(check_boundary);
    for (const auto& r : result)
    {
        std::cout << r << '\n';
    }

    return 1;

}