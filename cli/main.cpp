/* Copyright (C) Denys Valchuk - All Rights Reserved
 * ZHZhbGNodWtAZ21haWwuY29tCg==
 */

#include <carsprocessor.h>

#include <iostream>
#include <filesystem>
#include <cstdlib>
#include <chrono>

namespace {
    void printUsage(const std::string_view appName) {
        std::cerr << "Usage: " << appName << " <seq|par> <input file>" << std::endl;
    }
}

int main(int argc, char* argv[]) {
    if (argc < 3) {
        printUsage(argv[0]);
        return EXIT_FAILURE;
    }

    const std::string_view mode = argv[1];
    if (mode != "seq" && mode != "par") {
        std::cerr << "Unknown mode: " << mode << std::endl;
        printUsage(argv[0]);
        return EXIT_FAILURE;
    }

    const std::filesystem::path in = argv[2];

    const auto t1 = std::chrono::high_resolution_clock::now();
    nlohmann::json result;
    if (mode == "seq") {
        result = dv::carsds::processSeq(in);
    } else {
        result = dv::carsds::processPar(in);
    }
    const auto t2 = std::chrono::high_resolution_clock::now();
    const std::chrono::duration<double, std::milli> ms = t2 - t1;
    std::cout << "Time: " << ms.count() << " ms" << std::endl;

    return EXIT_SUCCESS;
}