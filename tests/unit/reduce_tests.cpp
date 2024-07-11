/* Copyright (C) Denys Valchuk - All Rights Reserved
 * ZHZhbGNodWtAZ21haWwuY29tCg==
 */

#include "Transport.h"
#include "CountResult.h"

#include <gtest/gtest.h>

#include <vector>
#include <numeric>
#include <unordered_map>
#include <execution>
#include <chrono>


using namespace dv;


namespace {
    struct GenResult {
        Transports transports;
        CategoriesCount categoriesCount;
        FuelsCount fuelsCount;
    };

    GenResult generateRandomTransports(size_t num) {
        GenResult result;
        result.transports.reserve(num);
        for(size_t i = 0; i < num; ++i) {
            Transport transport = {
                static_cast<Transport::Category>(i % 7),
                static_cast<Transport::Fuel>(i % 5),
                "Company" + std::to_string(i)
            };
            result.transports.push_back(transport);
            result.categoriesCount[transport.category]++;
            result.fuelsCount[transport.fuel]++;
        }
        return result;
    }
}


template <typename ExecutionType> class TransportTest : public ::testing::Test {};

using ExecutionTypes = ::testing::Types<std::execution::sequenced_policy, std::execution::parallel_policy, std::execution::parallel_unsequenced_policy>;

TYPED_TEST_SUITE(TransportTest, ExecutionTypes);

//TYPED_TEST(TransportTest, DISABLED_CountBig) {
TYPED_TEST(TransportTest, CountBig) {
    const size_t num = 10000;
    GenResult result = generateRandomTransports(num);
    constexpr TypeParam executionPolicy;
    CountResult count = std::reduce(executionPolicy, result.transports.begin(), result.transports.end(),
                                    CountResult{}, [](CountResult lhs, CountResult rhs) {
        return lhs + rhs;
    });

    EXPECT_EQ(count.categories, result.categoriesCount);
    EXPECT_EQ(count.fuels, result.fuelsCount);
    EXPECT_EQ(count.companies.size(), num);
}
