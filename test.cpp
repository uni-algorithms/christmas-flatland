#define CATCH_CONFIG_MAIN

#include <catch.hpp>
#include "flatland.h"

SCENARIO("flatland check if an even sequence is solvable from left to right and then store results") {
    GIVEN("a flatland solver") {
        flatland solver;
        std::unordered_map<std::string, bool> tests = {
                {"ssss",   false},
                {"dddd",   true},
                {"sssd",   false},
                {"ssds",   true},
                {"dsdd",   true},
                {"ssdd",   true},
                {"ddss",   true},
                {"sdss",   false},
                {"ddsd",   true},
                {"sdsd",   false},
                {"sdds",   false},
                {"dssd",   true},
                {"dsss",   true},
                {"ddds",   true},
                {"dsds",   true},

                {"ssddss", true},
                {"ddssdd", true},
                {"sssssd", false},
                {"sddddd", false},
                {"sssdsd", false},
                {"sdsddd", false},
        };

        for (auto test : tests) {
            WHEN("solve : " + test.first) {
                REQUIRE(test.second == solver.isRightSolvable(test.first));

                THEN("store : " + test.first) {
                    REQUIRE(test == *solver.mapRightSolvable.find(test.first));
                }
            }
        }
    }
}

SCENARIO("flatland finds the possible unreachable triangles of an odd sequence ") {
    GIVEN("a flatland solver") {
        flatland solver;
        std::unordered_map<std::string, std::vector<int> > tests = {
                {"sssddss",   {0, 2, 6}},
                {"ssddssdsd", {2, 8}},
        };

        for (auto test : tests) {
            WHEN("outcast : " + test.first) {
                REQUIRE(test.second == solver.outcast(test.first));
            }
        }
    }
}