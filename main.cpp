#include <cassert>
#include "flatland.cpp"

auto main() -> int {
    std::ifstream input("input.txt");
    std::ofstream output("output.txt");
    assert(input);
    assert(output);

    auto result = outcast(input);
    output << result.size() << std::endl;
    for(Triangle t : result) {
        output << t.getIndex() << " ";
    }

    input.close();
    output.close();
    return 0;
}