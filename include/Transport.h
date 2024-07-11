#ifndef __DV_INCLUDE_TRANSPORT_H__
#define __DV_INCLUDE_TRANSPORT_H__

#include <string>
#include <unordered_map>

#include <nlohmann/json.hpp>
#include <magic_enum/magic_enum.hpp>

#define DV_JSON_SERIALIZE_ENUM_ENTRY(e) \
    { e, magic_enum::enum_name(e) }

namespace dv {
    struct Transport {
        enum class Category { Transport, NonTransport, Unknown };

        enum class Fuel { Petrol, Diesel, Battery, CNGPetrol, PetrolLPG, Unknown };

        Category category;
        Fuel fuel;
        std::string company;
    };
}


NLOHMANN_JSON_NAMESPACE_BEGIN

template <typename T> struct adl_serializer<std::unordered_map<dv::Transport::Category, T>> {
        static void to_json(json &result, const std::unordered_map<dv::Transport::Category, T> &map) {
            for (const auto &[key, value] : map)
                result[magic_enum::enum_name(key)] = value;
        }
};

template <typename T> struct adl_serializer<std::unordered_map<dv::Transport::Fuel, T>> {
        static void to_json(json &result, const std::unordered_map<dv::Transport::Fuel, T> &map) {
            for (const auto &[key, value] : map)
                result[magic_enum::enum_name(key)] = value;
        }
};

NLOHMANN_JSON_NAMESPACE_END

#endif // __DV_INCLUDE_TRANSPORT_H__
