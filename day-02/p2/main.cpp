#include <iostream>
#include <vector>
#include <fstream>

template <typename  T>
void printContainer(const T& container) {
    std::cout << '[';
    for (const auto& c : container) {
        std::cout << c << ',';
    }
    std::cout << ']';
}

bool isReportSafeHelper(std::vector<int> levels, const int direction, const bool isSafe) {
    for (size_t i = 1; i < levels.size(); i++) {
        const int difference = std::abs(levels[i - 1] - levels[i]);
        if (difference > 3 || direction * (levels[i - 1] - levels[i]) <= 0 ) {
            if (isSafe)
                return false;
            const std::vector<int>::iterator nextElem = levels.erase(levels.begin() + i);
            const std::vector<int>::iterator prevElem = nextElem - 1;
            return isReportSafeHelper(std::vector<int>(prevElem, levels.end()), direction, true);
        }
    }
    return true;
}

bool isReportSafe(std::vector<int>& levels) {
    if (isReportSafeHelper(levels, levels[0] - levels[1], false)) {
        return true;
    }

    // try removing the first and second elements
    for (size_t i = 0; i < 2 && i < levels.size(); i++) {
        std::vector<int> copy = levels;
        copy.erase(copy.begin() + i);
        if (isReportSafeHelper(copy, copy[0] - copy[1], true))
            return true;
    }
    return false;
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
        // printContainer(levels);
        // std::cout << '\t';
        std::cout << std::boolalpha;
        std::cout << isReportSafe(levels) << std::endl;
        safeLevelNb += isReportSafe(levels);
    }
    // printf("%d\n", safeLevelNb);
}