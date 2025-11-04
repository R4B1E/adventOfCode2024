#include <iostream>
#include <vector>
#include <fstream>

template <typename  T>
void printContainer(const T& container) {
    std::cout << '[';
    for (const auto& c : container) {
        std::cout << c << ',';
    }
    std::cout << ']' << std::endl;
}

bool isReportSafe(const std::vector<int> &levels) {
    const int direction = levels[0] - levels[1];
    // loop through the levels with sliding window
    for (size_t i = 1; i < levels.size(); i++) {
        // printContainer(levels_set);
        const int difference = std::abs(levels[i - 1] - levels[i]);
        if (difference > 3 || direction * (levels[i - 1] - levels[i]) <= 0)
                return false;
    }
    return true;
}

std::vector<int> stovec(const std::string& line) {
    std::vector<int> levels;
    std::string level;
    for (size_t i = 0; i <= line.length(); i++) {
        if (line[i] == ' ' || line[i] == '\0') {
            levels.push_back(std::stoi(level));
            level.clear();
        }
        else if (line[i] == '\n')
            break;
        else
            level.push_back(line[i]);
    }
    return levels;
}

int main(const int ac, const char **av) {
    (void)ac;
    std::ifstream input(av[1]);
    std::string line;
    int safeLevelNb = 0;
    while (std::getline(input, line)) {
        std::vector<int> levels = stovec(line);
        safeLevelNb += isReportSafe(levels);
    }
    printf("%d\n", safeLevelNb);
}