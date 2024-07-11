/* Copyright (C) Denys Valchuk - All Rights Reserved
 * ZHZhbGNodWtAZ21haWwuY29tCg==
 */

#include "Transport.h"
#include "CSVUtils.h"

#include <csv.hpp>

namespace dv {

Transport Transport::fromCSVRow(const csv::CSVRow& row) {
    Transport result;
    result.category = toCategory(row);
    result.fuel = toFuel(row);
    result.company = toCompany(row);
    return result;
}

} // namespace dv
