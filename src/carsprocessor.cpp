/* Copyright (C) Denys Valchuk - All Rights Reserved
 * ZHZhbGNodWtAZ21haWwuY29tCg==
 */

#include "carsprocessor.h"
#include "Transport.h"

#include <csv.hpp>

#include <execution>
#include <numeric>
#include <stdexcept>
#include <unordered_map>
#include <string_view>

using namespace csv;
using namespace dv;

namespace {
    constexpr auto kCategoryHeader = "category";
    constexpr auto kFuelHeader = "fuel";
    constexpr auto kCompanyHeader = "makerName";

    using CategoriesCount = std::unordered_map<Transport::Category, size_t>;
    using FuelsCount = std::unordered_map<Transport::Fuel, size_t>;
    using CompaniesCount = std::unordered_map<std::string, size_t>;

    Transport::Category toCategory(const CSVRow& row) {
        const auto category = row[kCategoryHeader].get<std::string_view>();
        // TODO:denysv: do we have more categories in csv?
        if (category == "Transport") {
            return Transport::Category::Transport;
        } else if (category == "Non Transport") {
            return Transport::Category::NonTransport;
        }
        return Transport::Category::Unknown;
    }

    Transport::Fuel toFuel(const CSVRow& row) {
        const auto fuel = row[kFuelHeader].get<std::string_view>();
        if (fuel == "PETROL") {
            return Transport::Fuel::Petrol;
        } else if (fuel == "DIESEL") {
            return Transport::Fuel::Diesel;
        } else if (fuel == "BATTERY") {
            return Transport::Fuel::Battery;
        } else if (fuel == "CNG PETROL") {
            return Transport::Fuel::CNGPetrol;
        } else if (fuel == "PETROL LPG") {
            return Transport::Fuel::PetrolLPG;
        }
        return Transport::Fuel::Unknown;
    }

    std::string toCompany(const CSVRow& row) {
        return row[kCompanyHeader].get<std::string>();
    }

    struct CountResult {
        CategoriesCount categories;
        FuelsCount fuels;
        CompaniesCount companies;

        CountResult(const CSVRow& row) {
            categories[toCategory(row)]++;
            fuels[toFuel(row)]++;
            companies[toCompany(row)]++;
        }

        CountResult() = default;
        CountResult(const CountResult&) = default;
        CountResult(CountResult&&) = default;
        CountResult& operator=(const CountResult&) = default;
        CountResult& operator=(CountResult&&) = default;

        CountResult& operator+=(const CountResult& other) {
            for(const auto& [type, count] : other.categories) {
                categories[type] += count;
            }
            for(const auto& [fuel, count] : other.fuels) {
                fuels[fuel] += count;
            }
            for(const auto& [company, count] : other.companies) {
                companies[company] += count;
            }
            return *this;
        }

        CountResult operator+(const CountResult& other) const {
            CountResult result = *this;
            result += other;
            return result;
        }

    };

    void to_json(nlohmann::json &j, const CountResult &info) {
        j = nlohmann::json::object();
        j["categories"] = info.categories;
        j["fuels"] = info.fuels;
        j["companies"] = info.companies;
    }
}

namespace dv::carsds {

nlohmann::json processSeq(const std::filesystem::path& in) {
    if (!std::filesystem::exists(in)) {
        throw std::runtime_error("File does not exist");
    }
    
    auto format = csv::CSVFormat().delimiter({','}).header_row(0);
    const auto inStr = in.string();
    // memory mapped by default...
    csv::CSVReader reader(inStr, format);

    // to specify execution policy we should use forward iterator instead of input iterator...
    CountResult count = std::reduce(reader.begin(), reader.end(),
                                    CountResult{}, [](CountResult lhs, CountResult rhs) {
        return lhs + rhs;
    });

    return count;
}

} // namespace dv::carsds
