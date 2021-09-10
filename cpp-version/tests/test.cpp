#include <iostream>
#include <string>
#include <string_view>

#include "Json/Json.h"

using namespace Json;
using namespace std::literals;

static int main_ret = 0;
static int test_count = 0;
static int test_pass = 0;

#define EXPECT_EQ_BASE(equality, expect, actual)                               \
    do {                                                                       \
        test_count++;                                                          \
        if (equality)                                                          \
            test_pass++;                                                       \
        else {                                                                 \
            std::cerr << __FILE__ << ":" << __LINE__ << ": expect: " << expect \
                      << " actual: " << actual << '\n';                        \
            main_ret = 1;                                                      \
        }                                                                      \
    } while (0)

#define EXPECT_EQ_INT(expect, actual) \
    EXPECT_EQ_BASE((expect) == (actual), expect, actual)

static void test_parse_c_string() {
    JsonObject v;
    EXPECT_EQ_INT(PARSE_OK, JsonParser::Parse("false", v));
    EXPECT_EQ_INT(JsonType::False, v.GetType());
}

static void test_parse_string() {
    JsonObject v;
    EXPECT_EQ_INT(PARSE_OK, JsonParser::Parse("false"s, v));
    EXPECT_EQ_INT(JsonType::False, v.GetType());
}

static void test_parse_null() {
    JsonObject v(JsonType::False);
    EXPECT_EQ_INT(PARSE_OK, JsonParser::Parse("null"sv, v));
    EXPECT_EQ_INT(JsonType::Null, v.GetType());
}

static void test_parse_true() {
    JsonObject v(JsonType::False);
    EXPECT_EQ_INT(PARSE_OK, JsonParser::Parse("true"sv, v));
    EXPECT_EQ_INT(JsonType::True, v.GetType());
}

static void test_parse_false() {
    JsonObject v(JsonType::True);
    EXPECT_EQ_INT(PARSE_OK, JsonParser::Parse("false"sv, v));
    EXPECT_EQ_INT(JsonType::False, v.GetType());
}

static void test_parse_expect_value() {
    JsonObject v(JsonType::False);

    EXPECT_EQ_INT(PARSE_EXPECT_VALUE, JsonParser::Parse(""sv, v));
    EXPECT_EQ_INT(JsonType::Null, v.GetType());

    v.SetType(JsonType::False);
    EXPECT_EQ_INT(PARSE_EXPECT_VALUE, JsonParser::Parse(""sv, v));
    EXPECT_EQ_INT(JsonType::Null, v.GetType());
}

static void test_parse_invalid_value() {
    JsonObject v(JsonType::False);

    EXPECT_EQ_INT(PARSE_INVALID_VALUE, JsonParser::Parse("nul"sv, v));
    EXPECT_EQ_INT(JsonType::Null, v.GetType());

    v.SetType(JsonType::False);
    EXPECT_EQ_INT(PARSE_INVALID_VALUE, JsonParser::Parse("?"sv, v));
    EXPECT_EQ_INT(JsonType::Null, v.GetType());
}

static void test_parse_root_not_singular() {
    JsonObject v(JsonType::False);

    EXPECT_EQ_INT(PARSE_ROOT_NOT_SINGULAR, JsonParser::Parse("null x"sv, v));
    EXPECT_EQ_INT(JsonType::Null, v.GetType());
}

static void test_parse() {
    test_parse_c_string();
    test_parse_string();
    test_parse_null();
    test_parse_true();
    test_parse_false();
    test_parse_expect_value();
    test_parse_invalid_value();
    test_parse_root_not_singular();
}

int main() {
    test_parse();
    std::cout << test_pass << "/" << test_count << " ("
              << test_pass * 100.0 / test_count << "%) passed\n";
    return main_ret;
}