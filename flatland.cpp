#ifndef FLAT_CPP
#define FLAT_CPP

#include <algorithm>
#include <functional>
#include <fstream>
#include <iterator>
#include <vector>

enum Direction {
    LEFT, RIGHT
};

auto fromChar(char c) -> Direction {
    switch (c) {
        case 's':
            return LEFT;
        case 'd':
            return RIGHT;
        default:
            throw std::invalid_argument("Value accepted : s | d");
    }
}

auto toChar(Direction d) -> char {
    switch (d) {
        case LEFT:
            return '<';
        case RIGHT:
            return '>';
        default:
            throw std::invalid_argument("Value accepted : L | R");
    }
}

class Triangle {
    unsigned int index;
    Direction direction;

public:
    Triangle(unsigned int index, Direction direction) : index(index), direction(direction) {}

    unsigned int getIndex() const {
        return index;
    }

    Direction getDirection() const {
        return direction;
    }

    bool operator==(const Triangle &rhs) const {
        return index == rhs.index &&
               direction == rhs.direction;
    }

    bool operator!=(const Triangle &rhs) const {
        return !(rhs == *this);
    }

    bool operator<(const Triangle &rhs) const {
        return index < rhs.index;
    }

    bool operator>(const Triangle &rhs) const {
        return rhs < *this;
    }

    bool operator<=(const Triangle &rhs) const {
        return !(rhs < *this);
    }

    bool operator>=(const Triangle &rhs) const {
        return !(*this < rhs);
    }

    friend std::ostream &operator<<(std::ostream &os, const Triangle &triangle) {
        os << "[" << triangle.index << " : " << toChar(triangle.direction) << "]";
        return os;
    }
};

auto removeLeftFromLeft(const std::vector<Triangle> &v) -> std::vector<Triangle> {
    if (v.size() <= 2) return v;

    std::vector<Triangle> r;

    r.push_back(v[0]);

    for (auto i = 1; i < v.size() - 1; ++i) {
        if (v[i].getDirection() == LEFT && !r.empty())
            r.pop_back();
        else
            r.push_back(v[i]);
    }

    r.push_back(v[v.size() - 1]);

    return r;
}

auto removeLeftFromRight(const std::vector<Triangle> &v) -> std::vector<Triangle> {
    if (v.size() <= 2) return v;

    std::vector<Triangle> r;

    r.push_back(v[v.size() - 1]);

    for (auto i = 1; i < v.size(); ++i) {
        auto j = v.size() - 1 - i;

        if (v[j].getDirection() == LEFT && i != (v.size() - 1))
            ++i;
        else
            r.push_back(v[j]);
    }

    std::reverse(r.begin(), r.end());

    return r;
}

auto removeLeftFrom(const Direction from) -> std::function<std::vector<Triangle>(const std::vector<Triangle> &v)> {
    switch (from) {
        case RIGHT:
            return removeLeftFromRight;
        case LEFT:
            return removeLeftFromLeft;
        default :
            throw std::invalid_argument("Value accepted : L | R");
    }
}

auto removeRightFromLeft(const std::vector<Triangle> &v) -> std::vector<Triangle> {
    if (v.size() <= 2) return v;

    std::vector<Triangle> r;

    r.push_back(v[0]);

    for (auto i = 1; i < v.size(); ++i) {
        if (v[i].getDirection() == RIGHT && i != (v.size() - 1))
            ++i;
        else
            r.push_back(v[i]);
    }

    return r;
}

auto removeRightFromRight(const std::vector<Triangle> &v) -> std::vector<Triangle> {
    if (v.size() <= 2) return v;

    std::vector<Triangle> r;

    r.push_back(v[v.size() - 1]);

    for (auto i = 1; i < v.size(); ++i) {
        auto j = v.size() - 1 - i;

        if (v[j].getDirection() == RIGHT && !r.empty())
            r.pop_back();
        else
            r.push_back(v[j]);
    }

    std::reverse(r.begin(), r.end());

    return r;
}

auto removeRightFrom(const Direction from) -> std::function<std::vector<Triangle>(const std::vector<Triangle> &v)> {
    switch (from) {
        case RIGHT:
            return removeRightFromRight;
        case LEFT:
            return removeRightFromLeft;
        default :
            throw std::invalid_argument("Value accepted : L | R");
    }
}

auto remove(const Direction what) -> std::function<std::function<std::vector<Triangle>(const std::vector<Triangle> &v)>(
        Direction)> {
    switch (what) {
        case RIGHT:
            return removeRightFrom;
        case LEFT:
            return removeLeftFrom;
        default :
            throw std::invalid_argument("Value accepted : L | R");
    }
}

auto removeBoth(const std::vector<Triangle> &t, const Direction direction) -> std::vector<Triangle> {

    auto r = remove(direction)(RIGHT)(t);
    auto l = remove(direction)(LEFT)(t);

    std::vector<Triangle> result;

    std::set_union(r.begin(), r.end(),
                   l.begin(), l.end(),
                   std::back_inserter(result));


    for (auto i : t) {
        std::cout << i << " ";
    }
    std::cout << " => ";

    for (auto i : result) {
        std::cout << i << " ";
    }
    std::cout << std::endl;

    return result;
}

auto outcast(const std::vector<Triangle> &triangles) -> std::vector<Triangle> {
    std::cout << "RR : " << std::endl;
    auto rrf = removeBoth(remove(RIGHT)(RIGHT)(triangles), LEFT);
    std::cout << "RL : " << std::endl;
    auto rlf = removeBoth(remove(RIGHT)(LEFT)(triangles), LEFT);
    std::vector<Triangle> r;

    std::set_union(rrf.begin(), rrf.end(),
                   rlf.begin(), rlf.end(),
                   std::back_inserter(r));

    std::cout << "LR : " << std::endl;
    auto lrf = removeBoth(remove(LEFT)(RIGHT)(triangles), RIGHT);
    std::cout << "LL : " << std::endl;
    auto llf = removeBoth(remove(LEFT)(LEFT)(triangles), RIGHT);
    std::vector<Triangle> l;

    std::set_union(lrf.begin(), lrf.end(),
                   llf.begin(), llf.end(),
                   std::back_inserter(l));


    std::vector<Triangle> f;
    std::set_union(r.begin(), r.end(),
                   l.begin(), l.end(),
                   std::back_inserter(f));

    std::cout << std::endl;
    for (auto i : f) {
        std::cout << i << " ";
    }
    std::cout << std::endl;

    return f;
}

auto outcast(std::istream &input) -> std::vector<Triangle> {
    unsigned long n = 0;
    std::vector<Triangle> triangles;

    input >> n;

    for (unsigned int i = 0; i < n; ++i) {
        char c;
        input >> c;
        triangles.emplace_back(i, fromChar(c));
    }

    return outcast(triangles);
}

auto convert(const std::vector<Direction> &directions) -> std::vector<Triangle> {
    std::vector<Triangle> triangles;
    for (unsigned int i = 0; i < directions.size(); ++i) {
        triangles.push_back(Triangle(i, directions[i]));
    }
    return triangles;
}

#endif //FLAT_CPP