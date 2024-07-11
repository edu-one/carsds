/* Copyright (C) Denys Valchuk - All Rights Reserved
 * ZHZhbGNodWtAZ21haWwuY29tCg==
 */

#ifndef __DV_INCLUDE_COUNTRESULT_H__
#define __DV_INCLUDE_COUNTRESULT_H__

#include "Transport.h"

#include <nlohmann/json.hpp>

#include <unordered_map>

namespace csv {
    class CSVRow;
}

namespace dv {

    using CategoriesCount = std::unordered_map<Transport::Category, size_t>;
    using FuelsCount = std::unordered_map<Transport::Fuel, size_t>;
    using CompaniesCount = std::unordered_map<std::string, size_t>;

    struct CountResult {
        CategoriesCount categories;
        FuelsCount fuels;
        CompaniesCount companies;

        /*
         * @brief required to work with std::reduce over csv::CSVReader
         */
        CountResult(const csv::CSVRow& row);

        /*
         * @brief required to work with std::reduce over Transports
         */
        CountResult(const Transport& transport);

        CountResult() = default;
        CountResult(const CountResult&) = default;
        CountResult(CountResult&&) = default;
        CountResult& operator=(const CountResult&) = default;
        CountResult& operator=(CountResult&&) = default;

        CountResult& operator+=(const CountResult& other);

        CountResult operator+(const CountResult& other) const;
    };

} // namespace dv

NLOHMANN_JSON_NAMESPACE_BEGIN

template<> struct adl_serializer<dv::CountResult> {
    static void to_json(json &result, const dv::CountResult &cr) {
        result["categories"] = cr.categories;
        result["fuels"] = cr.fuels;
        result["companies"] = cr.companies;
    }
};

NLOHMANN_JSON_NAMESPACE_END


#endif // __DV_INCLUDE_COUNTRESULT_H__
