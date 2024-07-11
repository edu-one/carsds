/* Copyright (C) Denys Valchuk - All Rights Reserved
 * ZHZhbGNodWtAZ21haWwuY29tCg==
 */

#include "CountResult.h"
#include "CSVUtils.h"

#include <csv.hpp>

namespace {
    using dv::Transport;
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