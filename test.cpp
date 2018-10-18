#define CATCH_CONFIG_MAIN

#include <catch.hpp>
#include "flatland.cpp"

SCENARIO("flatlandia") {
    GIVEN("ssrrrss") {
        std::vector<Triangle> triangles = convert({
                                                          LEFT,
                                                          LEFT,
                                                          RIGHT,
                                                          RIGHT,
                                                          RIGHT,
                                                          LEFT,
                                                          LEFT,
                                                  });

        WHEN("remove LEFT from LEFT") {
            std::vector<Triangle> expected = {Triangle(2, RIGHT), Triangle(3, RIGHT), Triangle(6, LEFT)};
            REQUIRE(remove(LEFT)(LEFT)(triangles) == expected);
        }

        WHEN("remove LEFT from RIGHT") {
            std::vector<Triangle> expected = {Triangle(2, RIGHT), Triangle(3, RIGHT), Triangle(6, LEFT)};
            REQUIRE(remove(LEFT)(RIGHT)(triangles) == expected);
        }

        WHEN("remove RIGHT from LEFT") {
            std::vector<Triangle> expected = {Triangle(0, LEFT), Triangle(1, LEFT), Triangle(6, LEFT)};
            REQUIRE(remove(RIGHT)(LEFT)(triangles) == expected);
        }

        WHEN("remove RIGHT from RIGHT") {
            std::vector<Triangle> expected = {Triangle(0, LEFT), Triangle(1, LEFT), Triangle(2, RIGHT)};
            REQUIRE(remove(RIGHT)(RIGHT)(triangles) == expected);
        }
    }

    GIVEN("srs") {
        std::vector<Triangle> triangles = convert({
                                                          LEFT,
                                                          RIGHT,
                                                          LEFT,
                                                  });

        WHEN("remove LEFT from LEFT") {
            REQUIRE(remove(LEFT)(LEFT)(triangles) == triangles);
        }

        WHEN("remove LEFT from RIGHT") {
            REQUIRE(remove(LEFT)(RIGHT)(triangles) == triangles);
        }

        WHEN("remove RIGHT from LEFT") {
            std::vector<Triangle> expected = {Triangle(0, LEFT)};
            REQUIRE(remove(RIGHT)(LEFT)(triangles) == expected);
        }

        WHEN("remove RIGHT from RIGHT") {
            std::vector<Triangle> expected = {Triangle(0, LEFT)};
            REQUIRE(remove(RIGHT)(RIGHT)(triangles) == expected);
        }
    }

    GIVEN("sssddss") {
        std::vector<Triangle> triangles = convert({
                                                          LEFT,
                                                          LEFT,
                                                          LEFT,
                                                          RIGHT,
                                                          RIGHT,
                                                          LEFT,
                                                          LEFT,
                                                  });

        WHEN("remove LEFT from LEFT") {
            std::vector<Triangle> expected = {Triangle(2, LEFT), Triangle(3, RIGHT), Triangle(6, LEFT)};
            REQUIRE(remove(LEFT)(LEFT)(triangles) == expected);
        }

        WHEN("remove LEFT from RIGHT") {
            std::vector<Triangle> expected = {Triangle(0, LEFT), Triangle(3, RIGHT), Triangle(6, LEFT)};
            REQUIRE(remove(LEFT)(RIGHT)(triangles) == expected);
        }

        WHEN("remove RIGHT from LEFT") {
            std::vector<Triangle> expected = {Triangle(0, LEFT), Triangle(1, LEFT), Triangle(2, LEFT),
                                              Triangle(5, LEFT), Triangle(6, LEFT)};
            REQUIRE(remove(RIGHT)(LEFT)(triangles) == expected);
        }

        WHEN("remove RIGHT from RIGHT") {
            std::vector<Triangle> expected = {Triangle(0, LEFT), Triangle(1, LEFT), Triangle(2, LEFT)};
            REQUIRE(remove(RIGHT)(RIGHT)(triangles) == expected);
        }
    }

    GIVEN("ssddssdsd") {
        std::vector<Triangle> triangles = convert({
                                                          LEFT,
                                                          LEFT,
                                                          RIGHT,
                                                          RIGHT,
                                                          LEFT,
                                                          LEFT,
                                                          RIGHT,
                                                          LEFT,
                                                          RIGHT,
                                                  });

        WHEN("remove LEFT from LEFT") {
            std::vector<Triangle> expected = {Triangle(8, RIGHT)};
            REQUIRE(remove(LEFT)(LEFT)(triangles) == expected);
        }

        WHEN("remove LEFT from RIGHT") {
            std::vector<Triangle> expected = {Triangle(2, RIGHT), Triangle(3, RIGHT), Triangle(8, RIGHT)};
            REQUIRE(remove(LEFT)(RIGHT)(triangles) == expected);
        }

        WHEN("remove RIGHT from LEFT") {
            std::vector<Triangle> expected = {Triangle(0, LEFT), Triangle(1, LEFT), Triangle(4, LEFT),
                                              Triangle(5, LEFT), Triangle(8, RIGHT)};
            REQUIRE(remove(RIGHT)(LEFT)(triangles) == expected);
        }

        WHEN("remove RIGHT from RIGHT") {
            std::vector<Triangle> expected = {Triangle(0, LEFT), Triangle(1, LEFT), Triangle(8, RIGHT)};
            REQUIRE(remove(RIGHT)(RIGHT)(triangles) == expected);
        }
    }
}

SCENARIO("test provided : 3 triangles") {
    GIVEN("sss") {
        std::vector<Triangle> triangles = convert({
                                                          LEFT,
                                                          LEFT,
                                                          LEFT,
                                                  });
        std::vector<Triangle> expected = {Triangle(2, LEFT)};
        REQUIRE(outcast(triangles) == expected);
    }

    GIVEN("dss") {
        std::vector<Triangle> triangles = convert({
                                                          RIGHT,
                                                          LEFT,
                                                          LEFT,
                                                  });
        std::vector<Triangle> expected = {Triangle(2, LEFT)};
        REQUIRE(outcast(triangles) == expected);
    }

    GIVEN("ssd") {
        std::vector<Triangle> triangles = convert({
                                                          LEFT,
                                                          LEFT,
                                                          RIGHT,
                                                  });
        std::vector<Triangle> expected = {Triangle(2, RIGHT)};
        REQUIRE(outcast(triangles) == expected);
    }

    GIVEN("dsd") {
        std::vector<Triangle> triangles = convert({
                                                          RIGHT,
                                                          LEFT,
                                                          RIGHT,
                                                  });
        std::vector<Triangle> expected = {Triangle(2, RIGHT)};
        REQUIRE(outcast(triangles) == expected);
    }

    GIVEN("sds") {
        std::vector<Triangle> triangles = convert({
                                                          LEFT,
                                                          RIGHT,
                                                          LEFT,
                                                  });
        std::vector<Triangle> expected = {Triangle(0, LEFT)};
        REQUIRE(outcast(triangles) == expected);
    }

    GIVEN("dds") {
        std::vector<Triangle> triangles = convert({
                                                          RIGHT,
                                                          RIGHT,
                                                          LEFT,
                                                  });
        std::vector<Triangle> expected = {Triangle(0, RIGHT)};
        REQUIRE(outcast(triangles) == expected);
    }

    GIVEN("sdd") {
        std::vector<Triangle> triangles = convert({
                                                          LEFT,
                                                          RIGHT,
                                                          RIGHT,
                                                  });
        std::vector<Triangle> expected = {Triangle(0, LEFT)};
        REQUIRE(outcast(triangles) == expected);
    }

    GIVEN("ddd") {
        std::vector<Triangle> triangles = convert({
                                                          RIGHT,
                                                          RIGHT,
                                                          RIGHT,
                                                  });
        std::vector<Triangle> expected = {Triangle(0, RIGHT)};
        REQUIRE(outcast(triangles) == expected);
    }
}

TEST_CASE("test provided : sssddss") {
    std::vector<Triangle> triangles = convert({
                                                      LEFT,
                                                      LEFT,
                                                      LEFT,
                                                      RIGHT,
                                                      RIGHT,
                                                      LEFT,
                                                      LEFT,
                                              });
    std::vector<Triangle> expected = {Triangle(0, LEFT), Triangle(2, LEFT), Triangle(6, LEFT)};
    REQUIRE(outcast(triangles) == expected);
}

TEST_CASE("test provided : ssddssdsd") {
    std::vector<Triangle> triangles = convert({
                                                      LEFT,
                                                      LEFT,
                                                      RIGHT,
                                                      RIGHT,
                                                      LEFT,
                                                      LEFT,
                                                      RIGHT,
                                                      LEFT,
                                                      RIGHT,
                                              });

    std::vector<Triangle> expected = {Triangle(2, RIGHT), Triangle(8, RIGHT)};
    REQUIRE(outcast(triangles) == expected);
}

TEST_CASE("test provided : ssddssdsddsddsdsd") {
    std::vector<Triangle> triangles = convert({
                                                      LEFT,
                                                      LEFT,
                                                      RIGHT,
                                                      RIGHT,
                                                      LEFT,
                                                      LEFT,
                                                      RIGHT,
                                                      LEFT,
                                                      RIGHT,
                                                      RIGHT,
                                                      LEFT,
                                                      RIGHT,
                                                      RIGHT,
                                                      LEFT,
                                                      RIGHT,
                                                      LEFT,
                                                      RIGHT,
                                              });

    std::vector<Triangle> expected = {Triangle(2, RIGHT), Triangle(8, RIGHT), Triangle(16, RIGHT)};
    REQUIRE(outcast(triangles) == expected);
}