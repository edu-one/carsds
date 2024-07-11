/* Copyright (C) Denys Valchuk - All Rights Reserved
 * ZHZhbGNodWtAZ21haWwuY29tCg==
 */

#include "CountResult.h"

#include <csv.hpp>

namespace {
    using dv::Transport;

    constexpr auto kCategoryHeader = "category";
    constexpr auto kFuelHeader = "fuel";
    constexpr auto kCompanyHeader = "makerName";

    Transport::Category toCategory(const csv::CSVRow& row) {
        const auto category = row[kCategoryHeader].get<std::string_view>();
        // TODO:denysv: do we have more categories in csv?
        if (category == "Transport") {
            return Transport::Category::Transport;
        } else if (category == "Non Transport") {
            return Transport::Category::NonTransport;
        }
        return Transport::Category::Unknown;
    }

    Transport::Fuel toFuel(const csv::CSVRow& row) {
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

    std::string toCompany(const csv::CSVRow& row) {
        return row[kCompanyHeader].get<std::string>();
    }

} // unnamed namespace

namespace dv {

    CountResult::CountResult(const csv::CSVRow& row) {
        categories[toCategory(row)]++;
        fuels[toFuel(row)]++;
        companies[toCompany(row)]++;
    }

    CountResult::CountResult(const Transport& transport) {
        categories[transport.category]++;
        fuels[transport.fuel]++;
        companies[transport.company]++;
    }

    CountResult &CountResult::operator+=(const CountResult &other) {
        for (const auto &[type, count] : other.categories) {
            categories[type] += count;
        }
        for (const auto &[fuel, count] : other.fuels) {
            fuels[fuel] += count;
        }
        for (const auto &[company, count] : other.companies) {
            companies[company] += count;
        }
        return *this;
    }

    CountResult CountResult::operator+(const CountResult& other) const {
        CountResult result = *this;
        result += other;
        return result;
    }

} // namespace dv