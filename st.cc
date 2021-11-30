#include <iostream>
#include <string>
#include <fstream>
#include <cmath>

int Usage(const std::string& program) {
    std::cerr << "Calculates min, max, min, stddev, and count\n";
    std::cerr << "Usage: " << program << " [file]" << "\n";
    return EXIT_FAILURE;
}

int main(int argc, const char** argv) {
    std::ios::sync_with_stdio(false);
    if (argc != 1 && argc != 2) return Usage(argv[0]);
    std::string filename{argc == 1 || std::strcmp(argv[1], "-") == 0 ? "/dev/stdin" : argv[1]};
    if (filename == "--help" || filename == "-h") {
        Usage(argv[1]);
        return 0;
    }

    std::ifstream ifs{filename};
    if (!ifs) {
        std::cerr << "Error reading in file " + filename << "\n";
        return EXIT_FAILURE;
    }

    // sum and sum of squares
    double s = 0, ss = 0;
    uint64_t count = 0;
    double min = std::numeric_limits<double>::max();
    double max = std::numeric_limits<double>::min();


    std::string line;
    while(std::getline(ifs, line)) {
        double x = std::stod(line);
        s += x; ss += x*x;
        min = std::min(min, x);
        max = std::max(max, x);
        ++count;
    }

    std::cout << "count\t" << count << "\n";
    if (count != 0) {
        auto count_double = static_cast<double>(count);
        std::cout << "min\t" << min << "\n";
        const auto mean = s / count_double;
        std::cout << "mean\t" << mean << "\n";
        std::cout << "stddev\t" << sqrt((ss / count_double - mean*mean) * count_double / (count_double - 1)) << "\n";
        std::cout << "max\t" << max << "\n";
    }

    return 0;
}
