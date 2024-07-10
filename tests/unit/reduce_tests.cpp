/* Copyright (C) Denys Valchuk - All Rights Reserved
 * ZHZhbGNodWtAZ21haWwuY29tCg==
 */

#include "Transport.h"

#include <gtest/gtest.h>

#include <vector>
#include <numeric>
#include <unordered_map>
#include <execution>
#include <chrono>


using namespace dv;


namespace {
    using Transports = std::vector<Transport>;
    using TypesCount = std::unordered_map<Transport::Type, size_t>;
    using FuelsCount = std::unordered_map<Transport::Fuel, size_t>;
    using CompaniesCount = std::unordered_map<std::string, size_t>;


    struct CountResult {
        TypesCount types;
        FuelsCount fuels;
        CompaniesCount companies;

        CountResult(const Transport& transport) {
            types[transport.type]++;
            fuels[transport.fuel]++;
            companies[transport.company]++;
        }

        CountResult() = default;
        CountResult(const CountResult&) = default;
        CountResult(CountResult&&) = default;
        CountResult& operator=(const CountResult&) = default;
        CountResult& operator=(CountResult&&) = default;

        CountResult& operator+=(const CountResult& other) {
            for(const auto& [type, count] : other.types) {
                types[type] += count;
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

    struct GenResult {
        Transports transports;
        TypesCount typesCount;
        FuelsCount fuelsCount;
    };

    GenResult generateRandomTransports(size_t num) {
        GenResult result;
        result.transports.reserve(num);
        for(size_t i = 0; i < num; ++i) {
            Transport transport = {
                static_cast<Transport::Type>(i % 7),
                static_cast<Transport::Fuel>(i % 5),
                "Company" + std::to_string(i)
            };
            result.transports.push_back(transport);
            result.typesCount[transport.type]++;
            result.fuelsCount[transport.fuel]++;
        }
        return result;
    }
}

template <typename ExecutionType> class TransportTest : public ::testing::Test {};

using ExecutionTypes = ::testing::Types<std::execution::sequenced_policy, std::execution::parallel_policy, std::execution::parallel_unsequenced_policy>;

TYPED_TEST_SUITE(TransportTest, ExecutionTypes);

TYPED_TEST(TransportTest, CountBig) {
    const size_t num = 10000;
    GenResult result = generateRandomTransports(num);
    CountResult count = std::reduce(TypeParam{}, result.transports.begin(), result.transports.end(),
                                    CountResult{}, [](CountResult lhs, CountResult rhs) {
        return lhs + rhs;
    });

    EXPECT_EQ(count.types, result.typesCount);
    EXPECT_EQ(count.fuels, result.fuelsCount);
    EXPECT_EQ(count.companies.size(), num);
}