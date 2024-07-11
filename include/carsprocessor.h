/* Copyright (C) Denys Valchuk - All Rights Reserved
 * ZHZhbGNodWtAZ21haWwuY29tCg== 
 */

#ifndef __DV_INCLUDE_CARSDS_H__
#define __DV_INCLUDE_CARSDS_H__

#include <nlohmann/json.hpp>

#include <filesystem>

namespace dv::carsds {
    nlohmann::json processSeq(const std::filesystem::path& in);
    nlohmann::json processPar(const std::filesystem::path& in);
} // namespace dv::carsds

#endif // __DV_INCLUDE_CARSDS_H__
