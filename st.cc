#include <iostream>
#include <string>
#include <fstream>
#include <cmath>

int Usage(const std::string& program) {
    std::cerr << "Calculates count, min, max, mean, and stddev of numbers separated by newline\n";
    std::cerr << "Usage: " << program << " [file]" << "\n";
    return EXIT_FAILURE;
}

int main(int argc, const char** argv) {
    std::ios::sync_with_stdio(false);
    if (argc != 1 && argc != 2) return Usage(argv[0]);
    std::string filename{argc == 1 || std::strcmp(argv[1], "-") == 0 ? "/dev/stdin" : argv[1]};
    if (filename == "--help" || filename == "-h") {
        Usage(argv[0]);
        return 0;
    }

    std::ifstream ifs{filename};
    if (!ifs) {
        std::cerr << "Error reading in file " + filename << "\n";
        return EXIT_FAILURE;
    }

    // this utility must have O(1) space complexity
    // so we are sacrificing accuracy for memory efficiency
    double s = 0, ss = 0; // sum and sum of squares
    uint64_t count = 0;
    double min = std::numeric_limits<double>::max();
    double max = std::numeric_limits<double>::min();

    std::string line;
    uint64_t line_idx = 0;
    while(std::getline(ifs, line)) {
        ++line_idx;
        line.erase(std::remove_if(line.begin(), line.end(),
                                  [](char x) { return std::isspace(x); }), line.end());
        if (line.empty()) {
            std::cerr << "warning: skipping empty line at " << line_idx << "\n";
            continue;
        }
        double x = std::stod(line);
        s += x; ss += x*x;
        min = std::min(min, x);
        max = std::max(max, x);
        ++count;
    }

    do {
        std::cout << "count\t" << count << "\n";
        if (count == 0) break;

        auto count_double = static_cast<double>(count);
        std::cout << "min\t" << min << "\n";
        std::cout << "max\t" << max << "\n";
        const auto mean = s / count_double;
        std::cout << "mean\t" << mean << "\n";
        if (count == 1) break;

        std::cout << "stddev\t" << sqrt((ss / count_double - mean * mean) * count_double / (count_double - 1)) << "\n";
    } while (false);

    return 0;
}
