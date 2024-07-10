#ifndef __DV_INCLUDE_TRANSPORT_H__
#define __DV_INCLUDE_TRANSPORT_H__

#include <string>

namespace dv {
    struct Transport {
        enum class Type { Car, Bus, Truck };
        enum class Fuel { Gasoline, Diesel, Electric };

        Type type;
        Fuel fuel;
        std::string company;
    };
}



#endif // __DV_INCLUDE_TRANSPORT_H__
