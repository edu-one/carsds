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

using ProcessFunc = nlohmann::json (*)(const std::filesystem::path&);

struct ProcessTest : public ::testing::TestWithParam<ProcessFunc> {
    struct PrintToStringParamName {
        std::string operator()(const ::testing::TestParamInfo<ProcessFunc>& info) {
            // TODO:denysv: there could be a better way to do this...
            if (info.param == dv::carsds::processSeq) {
                return "Seq";
            } else {
                return "Par";
            }
        }
    };
};

TEST_P(ProcessTest, smallDS) {
    auto process = GetParam();
    const auto result = process(kSmallDSPath);

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

#ifdef NDEBUG
TEST_P(ProcessTest, juneDS) {
#else
TEST_P(ProcessTest, DISABLED_juneDS) {
#endif
    auto process = GetParam();
    const auto result = process(kJuneDSPath);

    const auto& categories = result["categories"];
    const auto& fuels = result["fuels"];
    const auto& companies = result["companies"];

    ASSERT_EQ(categories["Transport"], 18494);
    ASSERT_EQ(categories["NonTransport"], 136421);

    const nlohmann::json expectedFuels = R"({
        "Battery": 8018,
        "CNGPetrol": 4459,
        "Diesel": 21507,
        "Petrol": 116477,
        "PetrolLPG": 1360,
        "Unknown": 3094
    })"_json;
    ASSERT_EQ(fuels, expectedFuels);
    ASSERT_EQ(companies.size(), 399);
}

#ifdef NDEBUG
TEST_P(ProcessTest, bigDS) {
#else
TEST_P(ProcessTest, DISABLED_bigDS) {
#endif
    auto process = GetParam();
    const auto result = process(kBigDSPath);
    std::cout << result.dump(4) << std::endl;

    const auto& categories = result["categories"];
    const auto& fuels = result["fuels"];
    const auto& companies = result["companies"];

    ASSERT_EQ(categories["Transport"], 75454);
    ASSERT_EQ(categories["NonTransport"], 552412);

    const nlohmann::json expectedFuels = R"({
        "Battery": 36508,
        "CNGPetrol": 15571,
        "Diesel": 78600,
        "Petrol": 477920,
        "PetrolLPG": 3951,
        "Unknown": 15316
    })"_json;
    ASSERT_EQ(fuels, expectedFuels);
    ASSERT_EQ(companies.size(), 528);
}

INSTANTIATE_TEST_SUITE_P(ProcessType, ProcessTest, ::testing::Values(dv::carsds::processSeq, dv::carsds::processPar), ProcessTest::PrintToStringParamName());