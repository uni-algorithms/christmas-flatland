#include <cassert>
#include "flatland.h"

flatland solver;

auto main() -> int {
    std::ifstream input("input.txt");
    std::ofstream output("output.txt");
    assert(input);
    assert(output);

    auto result = solver.outcast(input);
    output << result.size() << std::endl;
    for (auto t : result) {
        output << t << " ";
    }

    input.close();
    output.close();
    return 0;
}