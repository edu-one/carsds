/* Copyright (C) Denys Valchuk - All Rights Reserved
 * ZHZhbGNodWtAZ21haWwuY29tCg==
 */

#include "carsprocessor.h"
#include "Transport.h"
#include "CountResult.h"

#include <csv.hpp>

#include <execution>
#include <numeric>
#include <stdexcept>
#include <string_view>

using dv::CountResult;

namespace dv::carsds {

nlohmann::json processSeq(const std::filesystem::path& in) {
    if (!std::filesystem::exists(in)) {
        throw std::runtime_error("File does not exist");
    }
    
    auto format = csv::CSVFormat().delimiter({','}).header_row(0);
    const auto pathStr = in.string();
    // memory mapped by default...
    csv::CSVReader reader(pathStr, format);

    // to specify execution policy we should use forward iterator instead of input iterator...
    CountResult count = std::reduce(reader.begin(), reader.end(),
                                    CountResult{}, [](CountResult lhs, CountResult rhs) {
        return lhs + rhs;
    });

    return count;
}

nlohmann::json processPar(const std::filesystem::path& in) {
    if (!std::filesystem::exists(in)) {
        throw std::runtime_error("File does not exist");
    }

    Transports transports;
    {
        auto format = csv::CSVFormat().delimiter({','}).header_row(0);
        const auto pathStr = in.string();
        // memory mapped by default...
        csv::CSVReader reader(pathStr, format);

        for (auto &row : reader) {
            transports.emplace_back(Transport::fromCSVRow(row));
        }
        // scope to release memory, which is not needed anymore...
        // if we have lot of memory - we can avoid this scope, to save time on memory deallocation...
    }

    // to specify execution policy we should use forward iterator instead of input iterator...
    CountResult count = std::reduce(std::execution::par, transports.begin(), transports.end(),
                                    CountResult{}, [](CountResult lhs, CountResult rhs) {
        return lhs + rhs;
    });

    return count;
}

} // namespace dv::carsds
