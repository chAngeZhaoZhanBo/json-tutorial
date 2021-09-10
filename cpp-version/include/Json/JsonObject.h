#ifndef JSON_OBJECT_H__
#define JSON_OBJECT_H__

#include <ostream>

namespace Json {

enum class JsonType { Null, False, True, Number, String, Array, Object };

std::ostream& operator<<(std::ostream& os, JsonType type);

class JsonObject {
    JsonType type;
   public:
    JsonObject(JsonType t = JsonType::Null) : type(t) {}
    JsonType GetType() const noexcept { return type; }
    void SetType(JsonType t) { type = t; }
};

}  // namespace Json

#endif
