/* Copyright (C) Denys Valchuk - All Rights Reserved
 * ZHZhbGNodWtAZ21haWwuY29tCg==
 */

#include "CSVUtils.h"

#include <csv.hpp>

namespace {
    constexpr auto kCategoryHeader = "category";
    constexpr auto kFuelHeader = "fuel";
    constexpr auto kCompanyHeader = "makerName";
} // unnamed namespace

namespace dv {

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

} // namespace dv