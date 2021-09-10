#ifndef JSON_PARSER_H__
#define JSON_PARSER_H__


#include "Json/JsonObject.h"

#include <string_view>

namespace Json {

enum ParseResult {
    PARSE_OK = 0,
    PARSE_EXPECT_VALUE,
    PARSE_INVALID_VALUE,
    PARSE_ROOT_NOT_SINGULAR
};

class JsonParser {
   public:
    static ParseResult Parse(std::string_view s, JsonObject& obj);
};

}  // namespace Json

#endif