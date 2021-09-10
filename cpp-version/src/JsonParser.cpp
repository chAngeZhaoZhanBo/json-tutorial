#include "Json/JsonParser.h"

#include <algorithm>
#include <cctype>

using namespace std::literals;

namespace Json {

static constexpr std::string_view null_sv = "null"sv;
static constexpr std::string_view true_sv = "true"sv;
static constexpr std::string_view false_sv = "false"sv;

bool isspace(char c) {
    return static_cast<bool>(std::isspace(c));
}

static void ParseWhiteSpace(std::string_view& json) {
    auto iter = std::find_if_not(json.begin(), json.end(), isspace);
    json.remove_prefix(std::distance(json.begin(), iter));
}

static ParseResult ParseToken(std::string_view& json, std::string_view token) {
    if(json.substr(0, token.size()) != token) {
        return PARSE_INVALID_VALUE;
    }
    json.remove_prefix(token.size());
    return PARSE_OK;
}

static ParseResult ParseNull(std::string_view& json, JsonObject& obj) {
    ParseResult ret = ParseToken(json, null_sv);
    if(ret == PARSE_OK) {
        obj.SetType(JsonType::Null);
    }
    return ret;
}

static ParseResult ParseTrue(std::string_view& json, JsonObject& obj) {
    ParseResult ret = ParseToken(json, true_sv);
    if(ret == PARSE_OK) {
        obj.SetType(JsonType::True);
    }
    return ret;
}

static ParseResult ParseFalse(std::string_view& json, JsonObject& obj) {
    ParseResult ret = ParseToken(json, false_sv);
    if(ret == PARSE_OK) {
        obj.SetType(JsonType::False);
    }
    return ret;
}

static ParseResult ParseValue(std::string_view& json, JsonObject& obj) {
    switch (json[0]) {
        case 'n':
            return ParseNull(json, obj);
        case 't':
            return ParseTrue(json, obj);
        case 'f':
            return ParseFalse(json, obj);
        case '\0':
            return PARSE_EXPECT_VALUE;
        default:
            return PARSE_INVALID_VALUE;
    }
}

ParseResult JsonParser::Parse(std::string_view json, JsonObject& obj) {
    obj.SetType(JsonType::Null);
    ParseWhiteSpace(json);
    ParseResult ret = ParseValue(json, obj);
    if(ret != PARSE_OK) {
        return ret;
    }
    ParseWhiteSpace(json);
    if(!json.empty()) {
        ret = PARSE_ROOT_NOT_SINGULAR;
    }
    return ret;
}

}  // namespace Json