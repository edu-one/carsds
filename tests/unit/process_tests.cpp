/* Copyright (C) Denys Valchuk - All Rights Reserved
 * ZHZhbGNodWtAZ21haWwuY29tCg==
 */

#include <carsprocessor.h>

#include <gtest/gtest.h>

#include <filesystem>

namespace fs = std::filesystem;


namespace {
    const fs::path kResourcesDir = fs::path{DV_RESOURCES_DIR};
    const fs::path kJuneDSPath = kResourcesDir / "telangana_vehicle_sales_June.csv";
    const fs::path kJulyDSPath = kResourcesDir / "telangana_vehicle_sales_July.csv";
    const fs::path kBigDSPath = kResourcesDir / "telangana_vehicle_sales.csv";
    const fs::path kSmallDSPath = kResourcesDir / "telangana_vehicle_sales_small.csv";
}


TEST(Process, smallDS_SEQ) {
    const auto result = dv::carsds::processSeq(kSmallDSPath);

    const auto& categories = result["categories"];
    const auto& fuels = result["fuels"];
    const auto& companies = result["companies"];

    ASSERT_EQ(categories["Transport"], 6);
    ASSERT_EQ(categories["NonTransport"], 52);

    const nlohmann::json expectedFuels = R"({
        "Petrol": 47,
        "Diesel": 6,
        "Battery": 2,
        "CNGPetrol": 1,
        "Unknown": 2
    })"_json;
    ASSERT_EQ(fuels, expectedFuels);

    const auto expectedCompanies = R"({
        "BAJAJ AUTO LTD": 9,
        "EICHER TRACTORS": 1,
        "HERO MOTOCORP LTD": 6,
        "HONDA MOTORCYCLE&SCOOTER(I)P L": 10,
        "JOHN DEERE INDIA PVT LIMITED": 1,
        "M/S SRI RAMA ENG.CO": 1,
        "M/S SRI SHIVA AGRO INDUSTRIES": 1,
        "M/S. KIA INDIA PVT LTD.,": 1,
        "M/S. OLA ELECTRIC TECHNOLOGIES PVT.LTD.,": 2,
        "MAHINDRA & MAHINDRA LTD": 1,
        "MARUTI SUZUKI INDIA LTD.,": 6,
        "ROYAL ENFIELD": 3,
        "SUZUKI MOTORCYCLE (I) PVT LTD": 6,
        "TATA MOTORS LTD": 2,
        "TATA MOTORS PASSENGER VEHICLES LTD": 1,
        "TVS MOTOR COMPANY LTD": 7
    })"_json;
    ASSERT_EQ(companies, expectedCompanies);
}