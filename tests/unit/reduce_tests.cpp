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


TEST(Transport, CountByType) {
    const Transports transports = {
        {Transport::Type::Car, Transport::Fuel::Gasoline, "Toyota"},
        {Transport::Type::Bus, Transport::Fuel::Diesel, "Mercedes"},
        {Transport::Type::Truck, Transport::Fuel::Diesel, "Volvo"},
        {Transport::Type::Car, Transport::Fuel::Electric, "Tesla"},
        {Transport::Type::Bus, Transport::Fuel::Gasoline, "Volkswagen"},
        {Transport::Type::Truck, Transport::Fuel::Gasoline, "Ford"},
        {Transport::Type::Car, Transport::Fuel::Diesel, "BMW"},
        {Transport::Type::Bus, Transport::Fuel::Electric, "BYD"},
        {Transport::Type::Bus, Transport::Fuel::Gasoline, "BYD"}
    };
    TypesCount count = std::reduce(transports.begin(), transports.end(), TypesCount{}, [](TypesCount acc, Transport transport) {
        acc[transport.type]++;
        return acc;
    });

    EXPECT_EQ(count[Transport::Type::Car], 3);
    EXPECT_EQ(count[Transport::Type::Bus], 4);
    EXPECT_EQ(count[Transport::Type::Truck], 2);
}

TEST(Transport, CountByAll) {
    const Transports transports = {
        {Transport::Type::Car, Transport::Fuel::Gasoline, "Toyota"},
        {Transport::Type::Bus, Transport::Fuel::Diesel, "Mercedes"},
        {Transport::Type::Truck, Transport::Fuel::Diesel, "Volvo"},
        {Transport::Type::Car, Transport::Fuel::Electric, "Tesla"},
        {Transport::Type::Bus, Transport::Fuel::Gasoline, "Mercedes"},
        {Transport::Type::Truck, Transport::Fuel::Gasoline, "Mercedes"},
        {Transport::Type::Car, Transport::Fuel::Diesel, "BMW"},
        {Transport::Type::Bus, Transport::Fuel::Electric, "BYD"},
        {Transport::Type::Bus, Transport::Fuel::Gasoline, "BYD"}
    };
    CountResult count = std::reduce(transports.begin(), transports.end(), CountResult{}, [](CountResult acc, Transport transport) {
        acc.types[transport.type]++;
        acc.fuels[transport.fuel]++;
        acc.companies[transport.company]++;
        return acc;
    });

    EXPECT_EQ(count.types[Transport::Type::Car], 3);
    EXPECT_EQ(count.types[Transport::Type::Bus], 4);
    EXPECT_EQ(count.types[Transport::Type::Truck], 2);

    EXPECT_EQ(count.fuels[Transport::Fuel::Gasoline], 4);
    EXPECT_EQ(count.fuels[Transport::Fuel::Diesel], 3);
    EXPECT_EQ(count.fuels[Transport::Fuel::Electric], 2);

    EXPECT_EQ(count.companies["Toyota"], 1);
    EXPECT_EQ(count.companies["Mercedes"], 3);
    EXPECT_EQ(count.companies["Volvo"], 1);
    EXPECT_EQ(count.companies["BYD"], 2);
    EXPECT_EQ(count.companies.size(), 6);
}

TEST(Transport, CountBigSeq) {
    const size_t num = 10000;
    GenResult result = generateRandomTransports(num);
    CountResult count = std::reduce(/*std::execution::seq, */result.transports.begin(), result.transports.end(), CountResult{}, [](CountResult acc, Transport transport) {
        acc.types[transport.type]++;
        acc.fuels[transport.fuel]++;
        acc.companies[transport.company]++;
        return acc;
    });

    EXPECT_EQ(count.types, result.typesCount);
    EXPECT_EQ(count.fuels, result.fuelsCount);
    EXPECT_EQ(count.companies.size(), num);
}
