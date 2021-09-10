#include "Json/JsonObject.h"

#include <type_traits>

namespace Json {

std::ostream& operator<<(std::ostream& os, JsonType type) {
    os << static_cast<std::underlying_type<JsonType>::type>(type);
    return os;
}
}