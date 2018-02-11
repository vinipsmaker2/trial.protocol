///////////////////////////////////////////////////////////////////////////////
//
// Copyright (C) 2018 Bjorn Reese <breese@users.sourceforge.net>
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
///////////////////////////////////////////////////////////////////////////////

#include <limits>
#include <sstream>
#include <iomanip>
#include <trial/protocol/buffer/string.hpp>
#include <trial/protocol/json/parse.hpp>
#include <trial/protocol/core/detail/lightweight_test.hpp>

using namespace trial::dynamic;
using namespace trial::protocol;

//-----------------------------------------------------------------------------

namespace parser_suite
{

void parse_empty()
{
    std::string input = "";
    auto result = json::parse(input);
    TRIAL_PROTOCOL_TEST(result.empty());
}

void parse_null()
{
    std::string input = "null";
    auto result = json::parse(input);
    TRIAL_PROTOCOL_TEST(result.same<nullable>());
}

void parse_boolean()
{
    std::string input = "true";
    auto result = json::parse(input);
    TRIAL_PROTOCOL_TEST(result.same<bool>());
    TRIAL_PROTOCOL_TEST_EQUAL(result.value<bool>(), true);
}

void parse_integer()
{
    // signed char
    {
        using integer_type = signed char;
        auto value = std::numeric_limits<integer_type>::lowest();
        std::ostringstream input;
        input.precision(std::numeric_limits<integer_type>::max_digits10);
        input << signed(value);
        auto result = json::parse(input.str());
        TRIAL_PROTOCOL_TEST(result.same<integer_type>());
        TRIAL_PROTOCOL_TEST_EQUAL(result.value<integer_type>(), value);
    }
    // unsigned char
    {
        using integer_type = unsigned char;
        auto value = std::numeric_limits<integer_type>::max();
        std::ostringstream input;
        input.precision(std::numeric_limits<integer_type>::max_digits10);
        input << unsigned(value);
        auto result = json::parse(input.str());
        TRIAL_PROTOCOL_TEST(result.same<integer_type>());
        TRIAL_PROTOCOL_TEST_EQUAL(result.value<integer_type>(), value);
    }
    // signed short int
    {
        using integer_type = signed short int;
        auto value = std::numeric_limits<integer_type>::lowest();
        std::ostringstream input;
        input.precision(std::numeric_limits<integer_type>::max_digits10);
        input << value;
        auto result = json::parse(input.str());
        TRIAL_PROTOCOL_TEST(result.same<integer_type>());
        TRIAL_PROTOCOL_TEST_EQUAL(result.value<integer_type>(), value);
    }
    // unsigned short int
    {
        using integer_type = unsigned short int;
        auto value = std::numeric_limits<integer_type>::max();
        std::ostringstream input;
        input.precision(std::numeric_limits<integer_type>::max_digits10);
        input << value;
        auto result = json::parse(input.str());
        TRIAL_PROTOCOL_TEST(result.same<integer_type>());
        TRIAL_PROTOCOL_TEST_EQUAL(result.value<integer_type>(), value);
    }
    // signed int
    {
        using integer_type = signed int;
        auto value = std::numeric_limits<integer_type>::lowest();
        std::ostringstream input;
        input.precision(std::numeric_limits<integer_type>::max_digits10);
        input << value;
        auto result = json::parse(input.str());
        TRIAL_PROTOCOL_TEST(result.same<integer_type>());
        TRIAL_PROTOCOL_TEST_EQUAL(result.value<integer_type>(), value);
    }
    // unsigned int
    {
        using integer_type = unsigned int;
        auto value = std::numeric_limits<integer_type>::max();
        std::ostringstream input;
        input.precision(std::numeric_limits<integer_type>::max_digits10);
        input << value;
        auto result = json::parse(input.str());
        TRIAL_PROTOCOL_TEST(result.same<integer_type>());
        TRIAL_PROTOCOL_TEST_EQUAL(result.value<integer_type>(), value);
    }
    // signed long int
    {
        using integer_type = signed long int;
        auto value = std::numeric_limits<integer_type>::lowest();
        std::ostringstream input;
        input.precision(std::numeric_limits<integer_type>::max_digits10);
        input << value;
        auto result = json::parse(input.str());
        TRIAL_PROTOCOL_TEST(result.same<integer_type>());
        TRIAL_PROTOCOL_TEST_EQUAL(result.value<integer_type>(), value);
    }
    // unsigned long int
    {
        using integer_type = unsigned long int;
        auto value = std::numeric_limits<integer_type>::max();
        std::ostringstream input;
        input.precision(std::numeric_limits<integer_type>::max_digits10);
        input << value;
        auto result = json::parse(input.str());
        TRIAL_PROTOCOL_TEST(result.same<integer_type>());
        TRIAL_PROTOCOL_TEST_EQUAL(result.value<integer_type>(), value);
    }
    // signed long long int
    {
        using integer_type = signed long long int;
        auto value = std::numeric_limits<integer_type>::lowest();
        std::ostringstream input;
        input.precision(std::numeric_limits<integer_type>::max_digits10);
        input << value;
        auto result = json::parse(input.str());
        TRIAL_PROTOCOL_TEST(result.same<integer_type>() || result.same<signed long int>());
        TRIAL_PROTOCOL_TEST_EQUAL(result.value<integer_type>(), value);
    }
    // unsigned long long int
    {
        using integer_type = unsigned long long int;
        auto value = std::numeric_limits<integer_type>::max();
        std::ostringstream input;
        input.precision(std::numeric_limits<integer_type>::max_digits10);
        input << value;
        auto result = json::parse(input.str());
        TRIAL_PROTOCOL_TEST(result.same<integer_type>() || result.same<unsigned long int>());
        TRIAL_PROTOCOL_TEST_EQUAL(result.value<integer_type>(), value);
    }
}

void parse_real()
{
    const float tolerance = 1e-5f;
    {
        auto value = std::numeric_limits<float>::min();
        std::ostringstream input;
        input.precision(std::numeric_limits<float>::max_digits10);
        input << value;
        auto result = json::parse(input.str());
        TRIAL_PROTOCOL_TEST(result.same<float>());
        TRIAL_PROTOCOL_TEST_CLOSE(result.value<float>(),
                                  value,
                                  tolerance);
    }
    {
        auto value = std::numeric_limits<float>::lowest();
        std::ostringstream input;
        input.precision(std::numeric_limits<float>::max_digits10);
        input << value;
        auto result = json::parse(input.str());
        TRIAL_PROTOCOL_TEST(result.same<float>());
        TRIAL_PROTOCOL_TEST_CLOSE(result.value<float>(),
                                  value,
                                  std::abs(value * tolerance));
    }
    {
        auto value = std::numeric_limits<float>::max();
        std::ostringstream input;
        input.precision(std::numeric_limits<float>::max_digits10);
        input << value;
        auto result = json::parse(input.str());
        TRIAL_PROTOCOL_TEST(result.same<float>());
        TRIAL_PROTOCOL_TEST_CLOSE(result.value<float>(),
                                  value,
                                  std::abs(value * tolerance));
    }
}

void parse_long_real()
{
    const double tolerance = 1e-5;
    {
        auto value = std::numeric_limits<double>::min();
        std::ostringstream input;
        input.precision(std::numeric_limits<double>::max_digits10);
        input << value;
        auto result = json::parse(input.str());
        TRIAL_PROTOCOL_TEST(result.same<double>());
        TRIAL_PROTOCOL_TEST_CLOSE(result.value<double>(),
                                  value,
                                  tolerance);
    }
    {
        auto value = std::numeric_limits<double>::lowest();
        std::ostringstream input;
        input.precision(std::numeric_limits<double>::max_digits10);
        input << value;
        auto result = json::parse(input.str());
        TRIAL_PROTOCOL_TEST(result.same<double>());
        TRIAL_PROTOCOL_TEST_CLOSE(result.value<double>(),
                                  value,
                                  std::abs(value * tolerance));
    }
    {
        auto value = std::numeric_limits<double>::max();
        std::ostringstream input;
        input.precision(std::numeric_limits<double>::max_digits10);
        input << value;
        auto result = json::parse(input.str());
        TRIAL_PROTOCOL_TEST(result.same<double>());
        TRIAL_PROTOCOL_TEST_CLOSE(result.value<double>(),
                                  value,
                                  std::abs(value * tolerance));
    }
}

void parse_long_long_real()
{
    const long double tolerance = 1e-5L;
    {
        auto value = std::numeric_limits<long double>::min();
        std::ostringstream input;
        input.precision(std::numeric_limits<long double>::max_digits10);
        input << value;
        auto result = json::parse(input.str());
        TRIAL_PROTOCOL_TEST(result.same<long double>());
        TRIAL_PROTOCOL_TEST_CLOSE(result.value<long double>(),
                                  value,
                                  tolerance);
    }
    {
        auto value = std::numeric_limits<long double>::lowest();
        std::ostringstream input;
        input.precision(std::numeric_limits<long double>::max_digits10);
        input << value;
        auto result = json::parse(input.str());
        TRIAL_PROTOCOL_TEST(result.same<long double>());
        TRIAL_PROTOCOL_TEST_CLOSE(result.value<long double>(),
                                  value,
                                  std::abs(value * tolerance));
    }
    {
        auto value = std::numeric_limits<long double>::max();
        std::ostringstream input;
        input.precision(std::numeric_limits<long double>::max_digits10);
        input << value;
        auto result = json::parse(input.str());
        TRIAL_PROTOCOL_TEST(result.same<long double>());
        TRIAL_PROTOCOL_TEST_CLOSE(result.value<long double>(),
                                  value,
                                  std::abs(value * tolerance));
    }
}

void parse_string()
{
    std::string input = "\"alpha\"";
    auto result = json::parse(input);
    TRIAL_PROTOCOL_TEST(result.is<std::string>());
    TRIAL_PROTOCOL_TEST_EQUAL(result.value<std::string>(), "alpha");
}

void parse_array()
{
    std::string input = "[null,true,2,3.0,\"alpha\"]";
    auto result = json::parse(input);
    TRIAL_PROTOCOL_TEST(result.is<array>());

    variable expect = { null, true, 2, 3.0, "alpha" };
    TRIAL_PROTOCOL_TEST_ALL_WITH(result.begin(), result.end(),
                                 expect.begin(), expect.end(),
                                 std::equal_to<variable>());
}

void parse_map()
{
    std::string input = "{\"alpha\":null,\"bravo\":true,\"charlie\":2,\"delta\":3.0,\"echo\":\"hydrogen\"}";
    auto result = json::parse(input);
    TRIAL_PROTOCOL_TEST(result.is<map>());

    variable expect =
        {
            { "alpha", null },
            { "bravo", true },
            { "charlie", 2 },
            { "delta", 3.0 },
            { "echo", "hydrogen" }
        };
    TRIAL_PROTOCOL_TEST_ALL_WITH(result.begin(), result.end(),
                                 expect.begin(), expect.end(),
                                 std::equal_to<variable>());
}

void run()
{
    parse_empty();
    parse_null();
    parse_boolean();
    parse_integer();
    parse_real();
    parse_long_real();
    parse_long_long_real();
    parse_string();
    parse_array();
    parse_map();
}

} // namespace parser_suite

//-----------------------------------------------------------------------------

namespace failure_suite
{

void fail_garbage()
{
    std::string input = "x";
    TRIAL_PROTOCOL_TEST_THROW_EQUAL(json::parse(input),
                                    json::error,
                                    "unexpected token");
}

void fail_minus()
{
    std::string input = "-";
    TRIAL_PROTOCOL_TEST_THROW_EQUAL(json::parse(input),
                                    json::error,
                                    "unexpected token");
}

void fail_array_begin()
{
    std::string input = "[";
    TRIAL_PROTOCOL_TEST_THROW_EQUAL(json::parse(input),
                                    json::error,
                                    "expected end array bracket");
}

void fail_array_end()
{
    std::string input = "]";
    TRIAL_PROTOCOL_TEST_THROW_EQUAL(json::parse(input),
                                    json::error,
                                    "unbalanced end array bracket");
}

void fail_object_begin()
{
    std::string input = "{";
    TRIAL_PROTOCOL_TEST_THROW_EQUAL(json::parse(input),
                                    json::error,
                                    "expected end object bracket");
}

void fail_object_end()
{
    std::string input = "}";
    TRIAL_PROTOCOL_TEST_THROW_EQUAL(json::parse(input),
                                    json::error,
                                    "unbalanced end object bracket");
}

void fail_array_begin_object_end()
{
    std::string input = "[}";
    TRIAL_PROTOCOL_TEST_THROW_EQUAL(json::parse(input),
                                    json::error,
                                    "expected end array bracket");
}

void fail_object_begin_array_end()
{
    std::string input = "{]";
    TRIAL_PROTOCOL_TEST_THROW_EQUAL(json::parse(input),
                                    json::error,
                                    "expected end object bracket");
}

void run()
{
    fail_garbage();
    fail_minus();
    fail_array_begin();
    fail_array_end();
    fail_object_begin();
    fail_object_end();
    fail_array_begin_object_end();
    fail_object_begin_array_end();
}

} // namespace failure_suite

//-----------------------------------------------------------------------------
// main
//-----------------------------------------------------------------------------

int main()
{
    parser_suite::run();
    failure_suite::run();

    return boost::report_errors();
}