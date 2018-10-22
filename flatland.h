#ifndef FLATLAND_H
#define FLATLAND_H
#define LEFT 's'
#define RIGHT 'd'

#include <algorithm>
#include <fstream>
#include <iterator>
#include <string>
#include <unordered_map>
#include <vector>

constexpr auto pair(const char a, const char f) -> const unsigned int {
    return (a << 16) + f;
}

auto swapLR(char c) -> char {
    switch (c) {
        case LEFT :
            return RIGHT;
        case RIGHT :
            return LEFT;
        default:
            return c;
    }
}

class flatland {

public:
    std::unordered_map<std::string, bool> mapRightSolvable = {
            {"ss", false},
            {"sd", false},
            {"ds", true},
            {"dd", true},
    };

    auto isRightSolvable(const std::string &sequence) -> bool {
        auto it = mapRightSolvable.find(sequence);

        if (it != mapRightSolvable.end()) {
            return it->second;
        }

        std::vector<std::string> reduced;

        for (unsigned long i = 0; i < sequence.size() - 1; i++) {
            switch (pair(sequence[i], sequence[i + 1])) {
                case pair(LEFT, LEFT) :
                case pair(RIGHT, RIGHT) :
                case pair(RIGHT, LEFT) :
                    std::string tmp(sequence);
                    reduced.push_back(tmp.erase(i, 2));
                    break;
            }
        }

        auto isSolvable = std::any_of(reduced.begin(), reduced.end(),
                                      [this](const std::string &s) -> bool { return this->isRightSolvable(s); });

        mapRightSolvable.emplace(sequence, isSolvable);
        return isSolvable;
    }

    auto isLeftResolvable(const std::string &sequence) -> bool {
        std::string reverse(sequence.size(), 'X');
        std::transform(sequence.rbegin(), sequence.rend(), reverse.begin(), swapLR);
        return isRightSolvable(reverse);
    }

    auto outcast(const std::string &directions) -> std::vector<int> {
        std::vector<int> outcast;

        for (auto i = directions.begin(); i < directions.end(); i += 2) {
            bool l = true;
            if (i > directions.begin() + 1) {
                std::string left;
                std::copy(directions.begin(), i, std::back_inserter(left));
                l = isLeftResolvable(left);
            }

            bool r = true;
            if (i < directions.end() - 1) {
                std::string right;
                std::copy(i + 1, directions.end(), std::back_inserter(right));
                r = isRightSolvable(right);
            }

            if (l && r)
                outcast.push_back(i - directions.begin());
        }

        return outcast;
    }

    auto outcast(std::istream &input) -> std::vector<int> {
        unsigned long n = 0;
        std::string triangles;

        input >> n;

        for (unsigned int i = 0; i < n; ++i) {
            char c;
            input >> c;
            triangles.push_back(c);
        }

        return outcast(triangles);
    }
};

#endif //FLATLAND_H
