/* Copyright (C) Denys Valchuk - All Rights Reserved
 * ZHZhbGNodWtAZ21haWwuY29tCg==
 */

#ifndef __DV_INCLUDE_CSVUTILS_H__
#define __DV_INCLUDE_CSVUTILS_H__

#include "Transport.h"

namespace csv {
    class CSVRow;
}

namespace dv {
    Transport::Category toCategory(const csv::CSVRow &row);
    Transport::Fuel toFuel(const csv::CSVRow &row);
    std::string toCompany(const csv::CSVRow &row);
} // namespace dv

#endif // __DV_INCLUDE_CSVUTILS_H__
