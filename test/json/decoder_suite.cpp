///////////////////////////////////////////////////////////////////////////////
//
// Copyright (C) 2015 Bjorn Reese <breese@users.sourceforge.net>
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
///////////////////////////////////////////////////////////////////////////////

#include <boost/test/unit_test.hpp>

#include <trial/protocol/json/detail/decoder.hpp>
#include "is_system_error.hpp"

using namespace trial::protocol;

BOOST_AUTO_TEST_SUITE(json_decoder_suite)

//-----------------------------------------------------------------------------
// Whitespaces
//-----------------------------------------------------------------------------

BOOST_AUTO_TEST_CASE(test_empty)
{
    const char input[] = "";
    json::detail::decoder decoder(input);
    BOOST_REQUIRE_EQUAL(decoder.token(), json::token::end);
}

BOOST_AUTO_TEST_CASE(test_white_spaces)
{
    const char input[] = "  ";
    json::detail::decoder decoder(input);
    BOOST_REQUIRE_EQUAL(decoder.token(), json::token::end);
}

BOOST_AUTO_TEST_CASE(test_white_tabs)
{
    const char input[] = "\t\t";
    json::detail::decoder decoder(input);
    BOOST_REQUIRE_EQUAL(decoder.token(), json::token::end);
}

BOOST_AUTO_TEST_CASE(test_white_carriage_returns)
{
    const char input[] = "\r\r";
    json::detail::decoder decoder(input);
    BOOST_REQUIRE_EQUAL(decoder.token(), json::token::end);
}

BOOST_AUTO_TEST_CASE(test_white_newlines)
{
    const char input[] = "\n\n";
    json::detail::decoder decoder(input);
    BOOST_REQUIRE_EQUAL(decoder.token(), json::token::end);
}

BOOST_AUTO_TEST_CASE(test_junk)
{
    const char input[] = "n true";
    json::detail::decoder decoder(input);
    BOOST_REQUIRE_EQUAL(decoder.token(), json::token::error_unexpected_token);
    decoder.next();
    BOOST_REQUIRE_EQUAL(decoder.token(), json::token::error_unexpected_token);
}

//-----------------------------------------------------------------------------
// Basic types
//-----------------------------------------------------------------------------

BOOST_AUTO_TEST_CASE(test_null)
{
    const char input[] = "null";
    json::detail::decoder decoder(input);
    BOOST_REQUIRE_EQUAL(decoder.token(), json::token::null);
    decoder.next();
    BOOST_REQUIRE_EQUAL(decoder.token(), json::token::end);
}

BOOST_AUTO_TEST_CASE(test_white_null)
{
    const char input[] = "  null  ";
    json::detail::decoder decoder(input);
    BOOST_REQUIRE_EQUAL(decoder.token(), json::token::null);
    decoder.next();
    BOOST_REQUIRE_EQUAL(decoder.token(), json::token::end);
}

BOOST_AUTO_TEST_CASE(fail_nul)
{
    const char input[] = "nul";
    json::detail::decoder decoder(input);
    BOOST_REQUIRE_EQUAL(decoder.token(), json::token::end);
    BOOST_REQUIRE_EQUAL(decoder.literal(), "nul");
}

BOOST_AUTO_TEST_CASE(fail_nuller)
{
    const char input[] = "nuller";
    json::detail::decoder decoder(input);
    BOOST_REQUIRE_EQUAL(decoder.token(), json::token::error_unexpected_token);
    BOOST_REQUIRE_EQUAL(decoder.literal(), "nuller");
}

BOOST_AUTO_TEST_CASE(test_false)
{
    const char input[] = "false";
    json::detail::decoder decoder(input);
    BOOST_REQUIRE_EQUAL(decoder.token(), json::token::false_value);
    decoder.next();
    BOOST_REQUIRE_EQUAL(decoder.token(), json::token::end);
}

BOOST_AUTO_TEST_CASE(test_white_false)
{
    const char input[] = "  false  ";
    json::detail::decoder decoder(input);
    BOOST_REQUIRE_EQUAL(decoder.token(), json::token::false_value);
    decoder.next();
    BOOST_REQUIRE_EQUAL(decoder.token(), json::token::end);
}

BOOST_AUTO_TEST_CASE(fail_fals)
{
    const char input[] = "fals";
    json::detail::decoder decoder(input);
    BOOST_REQUIRE_EQUAL(decoder.token(), json::token::end);
    BOOST_REQUIRE_EQUAL(decoder.literal(), "fals");
}

BOOST_AUTO_TEST_CASE(fail_falser)
{
    const char input[] = "falser";
    json::detail::decoder decoder(input);
    BOOST_REQUIRE_EQUAL(decoder.token(), json::token::error_unexpected_token);
    BOOST_REQUIRE_EQUAL(decoder.literal(), "falser");
}

BOOST_AUTO_TEST_CASE(test_true)
{
    const char input[] = "true";
    json::detail::decoder decoder(input);
    BOOST_REQUIRE_EQUAL(decoder.token(), json::token::true_value);
    decoder.next();
    BOOST_REQUIRE_EQUAL(decoder.token(), json::token::end);
}

BOOST_AUTO_TEST_CASE(test_white_true)
{
    const char input[] = "  true  ";
    json::detail::decoder decoder(input);
    BOOST_REQUIRE_EQUAL(decoder.token(), json::token::true_value);
    decoder.next();
    BOOST_REQUIRE_EQUAL(decoder.token(), json::token::end);
}

BOOST_AUTO_TEST_CASE(fail_tru)
{
    const char input[] = "tru";
    json::detail::decoder decoder(input);
    BOOST_REQUIRE_EQUAL(decoder.token(), json::token::end);
    BOOST_REQUIRE_EQUAL(decoder.literal(), "tru");
}

BOOST_AUTO_TEST_CASE(fail_truer)
{
    const char input[] = "truer";
    json::detail::decoder decoder(input);
    BOOST_REQUIRE_EQUAL(decoder.token(), json::token::error_unexpected_token);
    BOOST_REQUIRE_EQUAL(decoder.literal(), "truer");
}

//-----------------------------------------------------------------------------
// Integer
//-----------------------------------------------------------------------------

BOOST_AUTO_TEST_CASE(test_integer_zero)
{
    const char input[] = "0";
    json::detail::decoder decoder(input);
    BOOST_REQUIRE_EQUAL(decoder.token(), json::token::integer);
    BOOST_REQUIRE_EQUAL(decoder.value<int>(), 0);
    decoder.next();
    BOOST_REQUIRE_EQUAL(decoder.token(), json::token::end);
}

BOOST_AUTO_TEST_CASE(test_white_integer_zero)
{
    const char input[] = "  0  ";
    json::detail::decoder decoder(input);
    BOOST_REQUIRE_EQUAL(decoder.token(), json::token::integer);
    BOOST_REQUIRE_EQUAL(decoder.value<boost::int64_t>(), 0);
    decoder.next();
    BOOST_REQUIRE_EQUAL(decoder.token(), json::token::end);
}

BOOST_AUTO_TEST_CASE(test_integer_hundred)
{
    const char input[] = "100";
    json::detail::decoder decoder(input);
    BOOST_REQUIRE_EQUAL(decoder.token(), json::token::integer);
    BOOST_REQUIRE_EQUAL(decoder.value<boost::int64_t>(), 100);
    decoder.next();
    BOOST_REQUIRE_EQUAL(decoder.token(), json::token::end);
}

BOOST_AUTO_TEST_CASE(test_integer_minus_hundred)
{
    const char input[] = "-100";
    json::detail::decoder decoder(input);
    BOOST_REQUIRE_EQUAL(decoder.token(), json::token::integer);
    BOOST_REQUIRE_EQUAL(decoder.value<boost::int64_t>(), -100);
    decoder.next();
    BOOST_REQUIRE_EQUAL(decoder.token(), json::token::end);
}

BOOST_AUTO_TEST_CASE(test_integer_large)
{
    const char input[] = "100000000000000000";
    json::detail::decoder decoder(input);
    BOOST_REQUIRE_EQUAL(decoder.token(), json::token::integer);
    BOOST_REQUIRE_EQUAL(decoder.value<boost::int64_t>(), INT64_C(100000000000000000));
    decoder.next();
    BOOST_REQUIRE_EQUAL(decoder.token(), json::token::end);
}

BOOST_AUTO_TEST_CASE(test_integer_max)
{
    const char input[] = "9223372036854775807";
    json::detail::decoder decoder(input);
    BOOST_REQUIRE_EQUAL(decoder.token(), json::token::integer);
    BOOST_REQUIRE_EQUAL(decoder.value<boost::int64_t>(), INT64_C(9223372036854775807));
    decoder.next();
    BOOST_REQUIRE_EQUAL(decoder.token(), json::token::end);
}

BOOST_AUTO_TEST_CASE(fail_integer_minus)
{
    const char input[] = "-";
    json::detail::decoder decoder(input);
    BOOST_REQUIRE_EQUAL(decoder.token(), json::token::end);
    BOOST_REQUIRE_EQUAL(decoder.literal(), "-");
}

BOOST_AUTO_TEST_CASE(fail_integer_minus_white)
{
    const char input[] = "- 0";
    json::detail::decoder decoder(input);
    BOOST_REQUIRE_EQUAL(decoder.token(), json::token::error_unexpected_token);
    BOOST_REQUIRE_EQUAL(decoder.literal(), "-");
}

BOOST_AUTO_TEST_CASE(fail_integer_minus_a)
{
    const char input[] = "-a";
    json::detail::decoder decoder(input);
    BOOST_REQUIRE_EQUAL(decoder.token(), json::token::error_unexpected_token);
    BOOST_REQUIRE_EQUAL(decoder.literal(), "-");
}

BOOST_AUTO_TEST_CASE(fail_integer_too_large)
{
    const char input[] = "10000000000000000000";
    json::detail::decoder decoder(input);
    BOOST_REQUIRE_EQUAL(decoder.token(), json::token::integer);
    BOOST_REQUIRE_EQUAL(decoder.literal(), "10000000000000000000");
    BOOST_REQUIRE_EXCEPTION(decoder.value<boost::int64_t>(),
                            json::error,
                            test::is_system_error(json::invalid_value));
}

BOOST_AUTO_TEST_CASE(fail_integer_as_float)
{
    const char input[] = "1";
    json::detail::decoder decoder(input);
    BOOST_REQUIRE_EQUAL(decoder.token(), json::token::integer);
    BOOST_REQUIRE_EQUAL(decoder.value<int>(), 1);
    BOOST_REQUIRE_EXCEPTION(decoder.value<float>(),
                            json::error,
                            test::is_system_error(json::incompatible_type));
}

BOOST_AUTO_TEST_CASE(fail_integer_as_string)
{
    const char input[] = "1";
    json::detail::decoder decoder(input);
    BOOST_REQUIRE_EQUAL(decoder.token(), json::token::integer);
    BOOST_REQUIRE_EQUAL(decoder.value<int>(), 1);
    BOOST_REQUIRE_EXCEPTION(decoder.value<std::string>(),
                            boost::system::system_error,
                            test::is_system_error(json::incompatible_type));
}

BOOST_AUTO_TEST_CASE(test_integer_short)
{
    const char input[] = "1";
    json::detail::decoder decoder(input);
    BOOST_REQUIRE_EQUAL(decoder.token(), json::token::integer);
    BOOST_REQUIRE_EQUAL(decoder.value<short>(), 1);
    decoder.next();
    BOOST_REQUIRE_EQUAL(decoder.token(), json::token::end);
}

BOOST_AUTO_TEST_CASE(test_integer_int)
{
    const char input[] = "1";
    json::detail::decoder decoder(input);
    BOOST_REQUIRE_EQUAL(decoder.token(), json::token::integer);
    BOOST_REQUIRE_EQUAL(decoder.value<int>(), 1);
    decoder.next();
    BOOST_REQUIRE_EQUAL(decoder.token(), json::token::end);
}

BOOST_AUTO_TEST_CASE(test_integer_long)
{
    const char input[] = "1";
    json::detail::decoder decoder(input);
    BOOST_REQUIRE_EQUAL(decoder.token(), json::token::integer);
    BOOST_REQUIRE_EQUAL(decoder.value<long>(), 1);
    decoder.next();
    BOOST_REQUIRE_EQUAL(decoder.token(), json::token::end);
}

BOOST_AUTO_TEST_CASE(test_integer_intmax)
{
    const char input[] = "1";
    json::detail::decoder decoder(input);
    BOOST_REQUIRE_EQUAL(decoder.token(), json::token::integer);
    BOOST_REQUIRE_EQUAL(decoder.value<boost::intmax_t>(), 1);
    decoder.next();
    BOOST_REQUIRE_EQUAL(decoder.token(), json::token::end);
}

BOOST_AUTO_TEST_CASE(test_integer_unsigned)
{
    const char input[] = "1";
    json::detail::decoder decoder(input);
    BOOST_REQUIRE_EQUAL(decoder.token(), json::token::integer);
    BOOST_REQUIRE_EQUAL(decoder.value<unsigned int>(), 1);
    decoder.next();
    BOOST_REQUIRE_EQUAL(decoder.token(), json::token::end);
}

BOOST_AUTO_TEST_CASE(fail_unsigned_negative)
{
    const char input[] = "-1";
    json::detail::decoder decoder(input);
    BOOST_REQUIRE_EQUAL(decoder.token(), json::token::integer);
    BOOST_REQUIRE_EXCEPTION(decoder.value<unsigned int>(),
                            boost::system::system_error,
                            test::is_system_error(json::invalid_value));
}

//-----------------------------------------------------------------------------
// Floating
//-----------------------------------------------------------------------------

BOOST_AUTO_TEST_CASE(test_floating_zero)
{
    const char input[] = "0.0";
    json::detail::decoder decoder(input);
    BOOST_REQUIRE_EQUAL(decoder.token(), json::token::floating);
    BOOST_REQUIRE_EQUAL(decoder.value<float>(), 0.0f);
    BOOST_REQUIRE_EQUAL(decoder.value<double>(), 0.0);
    decoder.next();
    BOOST_REQUIRE_EQUAL(decoder.token(), json::token::end);
}

BOOST_AUTO_TEST_CASE(test_floating_one)
{
    const char input[] = "1.0";
    json::detail::decoder decoder(input);
    BOOST_REQUIRE_EQUAL(decoder.token(), json::token::floating);
    BOOST_REQUIRE_EQUAL(decoder.value<float>(), 1.0f);
    BOOST_REQUIRE_EQUAL(decoder.value<double>(), 1.0);
    decoder.next();
    BOOST_REQUIRE_EQUAL(decoder.token(), json::token::end);
}

BOOST_AUTO_TEST_CASE(test_floating_minus_one)
{
    const char input[] = "-1.0";
    json::detail::decoder decoder(input);
    BOOST_REQUIRE_EQUAL(decoder.token(), json::token::floating);
    BOOST_REQUIRE_EQUAL(decoder.value<float>(), -1.0f);
    BOOST_REQUIRE_EQUAL(decoder.value<double>(), -1.0);
    decoder.next();
    BOOST_REQUIRE_EQUAL(decoder.token(), json::token::end);
}

BOOST_AUTO_TEST_CASE(test_floating_half)
{
    const char input[] = "0.5";
    json::detail::decoder decoder(input);
    BOOST_REQUIRE_EQUAL(decoder.token(), json::token::floating);
    BOOST_REQUIRE_EQUAL(decoder.value<float>(), 0.5f);
    BOOST_REQUIRE_EQUAL(decoder.value<double>(), 0.5);
    decoder.next();
    BOOST_REQUIRE_EQUAL(decoder.token(), json::token::end);
}

BOOST_AUTO_TEST_CASE(test_floating_one_exp_one)
{
    const char input[] = "1e1";
    json::detail::decoder decoder(input);
    BOOST_REQUIRE_EQUAL(decoder.token(), json::token::floating);
    BOOST_REQUIRE_EQUAL(decoder.value<float>(), 1e1f);
    BOOST_REQUIRE_EQUAL(decoder.value<double>(), 1e1);
    decoder.next();
    BOOST_REQUIRE_EQUAL(decoder.token(), json::token::end);
}

BOOST_AUTO_TEST_CASE(test_floating_one_upper_exp_one)
{
    const char input[] = "1E1";
    json::detail::decoder decoder(input);
    BOOST_REQUIRE_EQUAL(decoder.token(), json::token::floating);
    BOOST_REQUIRE_EQUAL(decoder.value<float>(), 1e1f);
    BOOST_REQUIRE_EQUAL(decoder.value<double>(), 1e1);
    decoder.next();
    BOOST_REQUIRE_EQUAL(decoder.token(), json::token::end);
}

BOOST_AUTO_TEST_CASE(test_floating_one_dot_exp_one)
{
    const char input[] = "1.0e1";
    json::detail::decoder decoder(input);
    BOOST_REQUIRE_EQUAL(decoder.token(), json::token::floating);
    BOOST_REQUIRE_EQUAL(decoder.value<float>(), 1e1f);
    BOOST_REQUIRE_EQUAL(decoder.value<double>(), 1e1);
    decoder.next();
    BOOST_REQUIRE_EQUAL(decoder.token(), json::token::end);
}

BOOST_AUTO_TEST_CASE(test_floating_one_exp_plus_one)
{
    const char input[] = "1e+1";
    json::detail::decoder decoder(input);
    BOOST_REQUIRE_EQUAL(decoder.token(), json::token::floating);
    BOOST_REQUIRE_EQUAL(decoder.value<float>(), 1e1f);
    BOOST_REQUIRE_EQUAL(decoder.value<double>(), 1e1);
    decoder.next();
    BOOST_REQUIRE_EQUAL(decoder.token(), json::token::end);
}

BOOST_AUTO_TEST_CASE(test_floating_one_exp_minus_one)
{
    const char input[] = "1e-1";
    json::detail::decoder decoder(input);
    BOOST_REQUIRE_EQUAL(decoder.token(), json::token::floating);
    BOOST_REQUIRE_EQUAL(decoder.value<float>(), 1e-1f);
    BOOST_REQUIRE_EQUAL(decoder.value<double>(), 1e-1);
    decoder.next();
    BOOST_REQUIRE_EQUAL(decoder.token(), json::token::end);
}

BOOST_AUTO_TEST_CASE(fail_floating_eof_missing_fraction)
{
    const char input[] = "0.";
    json::detail::decoder decoder(input);
    BOOST_REQUIRE_EQUAL(decoder.token(), json::token::end);
    BOOST_REQUIRE_EQUAL(decoder.literal(), "0.");
}

BOOST_AUTO_TEST_CASE(fail_floating_missing_fraction)
{
    const char input[] = "0. ";
    json::detail::decoder decoder(input);
    BOOST_REQUIRE_EQUAL(decoder.token(), json::token::error_unexpected_token);
    BOOST_REQUIRE_EQUAL(decoder.literal(), "0.");
}

BOOST_AUTO_TEST_CASE(fail_floating_eof_missing_exponent)
{
    const char input[] = "0e";
    json::detail::decoder decoder(input);
    BOOST_REQUIRE_EQUAL(decoder.token(), json::token::end);
    BOOST_REQUIRE_EQUAL(decoder.literal(), "0e");
}

BOOST_AUTO_TEST_CASE(fail_floating_missing_exponent)
{
    const char input[] = "0e ";
    json::detail::decoder decoder(input);
    BOOST_REQUIRE_EQUAL(decoder.token(), json::token::error_unexpected_token);
    BOOST_REQUIRE_EQUAL(decoder.literal(), "0e");
}

BOOST_AUTO_TEST_CASE(fail_floating_eof_missing_exponent_plus)
{
    const char input[] = "0e+";
    json::detail::decoder decoder(input);
    BOOST_REQUIRE_EQUAL(decoder.token(), json::token::end);
    BOOST_REQUIRE_EQUAL(decoder.literal(), "0e+");
}

BOOST_AUTO_TEST_CASE(fail_floating_missing_exponent_plus)
{
    const char input[] = "0e+ ";
    json::detail::decoder decoder(input);
    BOOST_REQUIRE_EQUAL(decoder.token(), json::token::error_unexpected_token);
    BOOST_REQUIRE_EQUAL(decoder.literal(), "0e+");
}

BOOST_AUTO_TEST_CASE(fail_floating_eof_missing_exponent_minus)
{
    const char input[] = "0e-";
    json::detail::decoder decoder(input);
    BOOST_REQUIRE_EQUAL(decoder.token(), json::token::end);
    BOOST_REQUIRE_EQUAL(decoder.literal(), "0e-");
}

BOOST_AUTO_TEST_CASE(fail_floating_missing_exponent_minus)
{
    const char input[] = "0e- ";
    json::detail::decoder decoder(input);
    BOOST_REQUIRE_EQUAL(decoder.token(), json::token::error_unexpected_token);
    BOOST_REQUIRE_EQUAL(decoder.literal(), "0e-");
}

BOOST_AUTO_TEST_CASE(fail_floating_as_int)
{
    const char input[] = "1.0";
    json::detail::decoder decoder(input);
    BOOST_REQUIRE_EQUAL(decoder.token(), json::token::floating);
    BOOST_REQUIRE_EQUAL(decoder.value<double>(), 1.0);
    BOOST_REQUIRE_EXCEPTION(decoder.value<int>(),
                            boost::system::system_error,
                            test::is_system_error(json::incompatible_type));
}

BOOST_AUTO_TEST_CASE(fail_floating_as_string)
{
    const char input[] = "1.0";
    json::detail::decoder decoder(input);
    BOOST_REQUIRE_EQUAL(decoder.token(), json::token::floating);
    BOOST_REQUIRE_EQUAL(decoder.value<double>(), 1.0);
    BOOST_REQUIRE_EXCEPTION(decoder.value<std::string>(),
                            boost::system::system_error,
                            test::is_system_error(json::incompatible_type));
}

//-----------------------------------------------------------------------------
// String
//-----------------------------------------------------------------------------

BOOST_AUTO_TEST_CASE(test_string_empty)
{
    const char input[] = "\"\"";
    json::detail::decoder decoder(input);
    BOOST_REQUIRE_EQUAL(decoder.token(), json::token::string);
    BOOST_REQUIRE_EQUAL(decoder.value<std::string>(), "");
    BOOST_REQUIRE_EQUAL(decoder.literal(), "\"\"");
    decoder.next();
    BOOST_REQUIRE_EQUAL(decoder.token(), json::token::end);
}

BOOST_AUTO_TEST_CASE(test_string_space)
{
    const char input[] = "\" \"";
    json::detail::decoder decoder(input);
    BOOST_REQUIRE_EQUAL(decoder.token(), json::token::string);
    BOOST_REQUIRE_EQUAL(decoder.value<std::string>(), " ");
    BOOST_REQUIRE_EQUAL(decoder.literal(), "\" \"");
    decoder.next();
    BOOST_REQUIRE_EQUAL(decoder.token(), json::token::end);
}

BOOST_AUTO_TEST_CASE(test_string_alpha)
{
    const char input[] = "\"alpha\"";
    json::detail::decoder decoder(input);
    BOOST_REQUIRE_EQUAL(decoder.token(), json::token::string);
    BOOST_REQUIRE_EQUAL(decoder.value<std::string>(), "alpha");
    decoder.next();
    BOOST_REQUIRE_EQUAL(decoder.token(), json::token::end);
}

BOOST_AUTO_TEST_CASE(test_string_alpha_bravo)
{
    const char input[] = "\"alpha bravo\"";
    json::detail::decoder decoder(input);
    BOOST_REQUIRE_EQUAL(decoder.token(), json::token::string);
    BOOST_REQUIRE_EQUAL(decoder.value<std::string>(), "alpha bravo");
    BOOST_REQUIRE_EQUAL(decoder.literal(), input);
    decoder.next();
    BOOST_REQUIRE_EQUAL(decoder.token(), json::token::end);
}

BOOST_AUTO_TEST_CASE(test_string_escape_quote)
{
    const char input[] = "\"\\\"\"";
    json::detail::decoder decoder(input);
    BOOST_REQUIRE_EQUAL(decoder.token(), json::token::string);
    BOOST_REQUIRE_EQUAL(decoder.value<std::string>(), "\"");
    BOOST_REQUIRE_EQUAL(decoder.literal(), "\"\\\"\"");
    decoder.next();
    BOOST_REQUIRE_EQUAL(decoder.token(), json::token::end);
}

BOOST_AUTO_TEST_CASE(test_string_escape_reverse_solidus)
{
    const char input[] = "\"\\\\\"";
    json::detail::decoder decoder(input);
    BOOST_REQUIRE_EQUAL(decoder.token(), json::token::string);
    BOOST_REQUIRE_EQUAL(decoder.value<std::string>(), "\\");
    decoder.next();
    BOOST_REQUIRE_EQUAL(decoder.token(), json::token::end);
}

BOOST_AUTO_TEST_CASE(test_string_escape_solidus)
{
    const char input[] = "\"\\/\"";
    json::detail::decoder decoder(input);
    BOOST_REQUIRE_EQUAL(decoder.token(), json::token::string);
    BOOST_REQUIRE_EQUAL(decoder.value<std::string>(), "/");
    decoder.next();
    BOOST_REQUIRE_EQUAL(decoder.token(), json::token::end);
}

BOOST_AUTO_TEST_CASE(test_string_escape_backspace)
{
    const char input[] = "\"\\b\"";
    json::detail::decoder decoder(input);
    BOOST_REQUIRE_EQUAL(decoder.token(), json::token::string);
    BOOST_REQUIRE_EQUAL(decoder.value<std::string>(), "\b");
    BOOST_REQUIRE_EQUAL(decoder.literal(), "\"\\b\"");
    decoder.next();
    BOOST_REQUIRE_EQUAL(decoder.token(), json::token::end);
}

BOOST_AUTO_TEST_CASE(test_string_escape_formfeed)
{
    const char input[] = "\"\\f\"";
    json::detail::decoder decoder(input);
    BOOST_REQUIRE_EQUAL(decoder.token(), json::token::string);
    BOOST_REQUIRE_EQUAL(decoder.value<std::string>(), "\f");
    decoder.next();
    BOOST_REQUIRE_EQUAL(decoder.token(), json::token::end);
}

BOOST_AUTO_TEST_CASE(test_string_escape_newline)
{
    const char input[] = "\"\\n\"";
    json::detail::decoder decoder(input);
    BOOST_REQUIRE_EQUAL(decoder.token(), json::token::string);
    BOOST_REQUIRE_EQUAL(decoder.value<std::string>(), "\n");
    decoder.next();
    BOOST_REQUIRE_EQUAL(decoder.token(), json::token::end);
}

BOOST_AUTO_TEST_CASE(test_string_escape_carriage_return)
{
    const char input[] = "\"\\r\"";
    json::detail::decoder decoder(input);
    BOOST_REQUIRE_EQUAL(decoder.token(), json::token::string);
    BOOST_REQUIRE_EQUAL(decoder.value<std::string>(), "\r");
    decoder.next();
    BOOST_REQUIRE_EQUAL(decoder.token(), json::token::end);
}

BOOST_AUTO_TEST_CASE(test_string_escape_tab)
{
    const char input[] = "\"\\t\"";
    json::detail::decoder decoder(input);
    BOOST_REQUIRE_EQUAL(decoder.token(), json::token::string);
    BOOST_REQUIRE_EQUAL(decoder.value<std::string>(), "\t");
    decoder.next();
    BOOST_REQUIRE_EQUAL(decoder.token(), json::token::end);
}

BOOST_AUTO_TEST_CASE(test_string_escape_unicode_one)
{
    const char input[] = "\"\\u0001\"";
    json::detail::decoder decoder(input);
    BOOST_REQUIRE_EQUAL(decoder.token(), json::token::string);
    BOOST_REQUIRE_EQUAL(decoder.value<std::string>(), "\x01");
    BOOST_REQUIRE_EQUAL(decoder.literal(), "\"\\u0001\"");
    decoder.next();
    BOOST_REQUIRE_EQUAL(decoder.token(), json::token::end);
}

BOOST_AUTO_TEST_CASE(test_string_escape_unicode_a)
{
    const char input[] = "\"\\u0061\"";
    json::detail::decoder decoder(input);
    BOOST_REQUIRE_EQUAL(decoder.token(), json::token::string);
    BOOST_REQUIRE_EQUAL(decoder.value<std::string>(), "a");
    BOOST_REQUIRE_EQUAL(decoder.literal(), "\"\\u0061\"");
    decoder.next();
    BOOST_REQUIRE_EQUAL(decoder.token(), json::token::end);
}

BOOST_AUTO_TEST_CASE(test_string_escape_unicode_0123)
{
    const char input[] = "\"\\u0123\"";
    json::detail::decoder decoder(input);
    BOOST_REQUIRE_EQUAL(decoder.token(), json::token::string);
    BOOST_REQUIRE_EQUAL(decoder.value<std::string>(), "\u0123");
    decoder.next();
    BOOST_REQUIRE_EQUAL(decoder.token(), json::token::end);
}

BOOST_AUTO_TEST_CASE(test_string_escape_unicode_4567)
{
    const char input[] = "\"\\u4567\"";
    json::detail::decoder decoder(input);
    BOOST_REQUIRE_EQUAL(decoder.token(), json::token::string);
    BOOST_REQUIRE_EQUAL(decoder.value<std::string>(), "\u4567");
    decoder.next();
    BOOST_REQUIRE_EQUAL(decoder.token(), json::token::end);
}

BOOST_AUTO_TEST_CASE(test_string_escape_unicode_89AB)
{
    const char input[] = "\"\\u89AB\"";
    json::detail::decoder decoder(input);
    BOOST_REQUIRE_EQUAL(decoder.token(), json::token::string);
    BOOST_REQUIRE_EQUAL(decoder.value<std::string>(), "\u89AB");
    decoder.next();
    BOOST_REQUIRE_EQUAL(decoder.token(), json::token::end);
}

BOOST_AUTO_TEST_CASE(test_string_escape_unicode_CDEF)
{
    const char input[] = "\"\\uCDEF\"";
    json::detail::decoder decoder(input);
    BOOST_REQUIRE_EQUAL(decoder.token(), json::token::string);
    BOOST_REQUIRE_EQUAL(decoder.value<std::string>(), "\uCDEF");
    decoder.next();
    BOOST_REQUIRE_EQUAL(decoder.token(), json::token::end);
}

BOOST_AUTO_TEST_CASE(fail_string_escape_unicode_missing_one)
{
    const char input[] = "\"\\u000\"";
    json::detail::decoder decoder(input);
    BOOST_REQUIRE_EQUAL(decoder.token(), json::token::error_unexpected_token);
    BOOST_REQUIRE_EQUAL(decoder.literal(), "\"\\u000");
}

BOOST_AUTO_TEST_CASE(fail_string_escape_unicode_missing_two)
{
    const char input[] = "\"\\u00\"";
    json::detail::decoder decoder(input);
    BOOST_REQUIRE_EQUAL(decoder.token(), json::token::error_unexpected_token);
    BOOST_REQUIRE_EQUAL(decoder.literal(), "\"\\u00");
}

BOOST_AUTO_TEST_CASE(fail_string_escape_unicode_missing_three)
{
    const char input[] = "\"\\u0\"";
    json::detail::decoder decoder(input);
    BOOST_REQUIRE_EQUAL(decoder.token(), json::token::error_unexpected_token);
    BOOST_REQUIRE_EQUAL(decoder.literal(), "\"\\u0");
}

BOOST_AUTO_TEST_CASE(fail_string_escape_unicode_missing_four)
{
    const char input[] = "\"\\u\"";
    json::detail::decoder decoder(input);
    BOOST_REQUIRE_EQUAL(decoder.token(), json::token::error_unexpected_token);
    BOOST_REQUIRE_EQUAL(decoder.literal(), "\"\\u");
}

BOOST_AUTO_TEST_CASE(fail_string_escape_unicode_eof)
{
    const char input[] = "\"\\u0000";
    json::detail::decoder decoder(input);
    BOOST_REQUIRE_EQUAL(decoder.token(), json::token::end);
    BOOST_REQUIRE_EQUAL(decoder.literal(), "\"\\u0000");
}

BOOST_AUTO_TEST_CASE(fail_string_escape_unicode_eof_one)
{
    const char input[] = "\"\\u000";
    json::detail::decoder decoder(input);
    BOOST_REQUIRE_EQUAL(decoder.token(), json::token::end);
    BOOST_REQUIRE_EQUAL(decoder.literal(), "\"\\u000");
}

BOOST_AUTO_TEST_CASE(fail_string_escape_unicode_eof_two)
{
    const char input[] = "\"\\u00";
    json::detail::decoder decoder(input);
    BOOST_REQUIRE_EQUAL(decoder.token(), json::token::end);
    BOOST_REQUIRE_EQUAL(decoder.literal(), "\"\\u00");
}

BOOST_AUTO_TEST_CASE(fail_string_escape_unicode_eof_three)
{
    const char input[] = "\"\\u0";
    json::detail::decoder decoder(input);
    BOOST_REQUIRE_EQUAL(decoder.token(), json::token::end);
    BOOST_REQUIRE_EQUAL(decoder.literal(), "\"\\u0");
}

BOOST_AUTO_TEST_CASE(fail_string_escape_unicode_eof_four)
{
    const char input[] = "\"\\u";
    json::detail::decoder decoder(input);
    BOOST_REQUIRE_EQUAL(decoder.token(), json::token::end);
    BOOST_REQUIRE_EQUAL(decoder.literal(), "\"\\u");
}

BOOST_AUTO_TEST_CASE(fail_string_escape)
{
    const char input[] = "\"\\\"";
    json::detail::decoder decoder(input);
    BOOST_REQUIRE_EQUAL(decoder.token(), json::token::end);
    BOOST_REQUIRE_EQUAL(decoder.literal(), "\"\\\"");
}

BOOST_AUTO_TEST_CASE(fail_string_begin)
{
    const char input[] = "\"";
    json::detail::decoder decoder(input);
    BOOST_REQUIRE_EQUAL(decoder.token(), json::token::end);
    BOOST_REQUIRE_EQUAL(decoder.literal(), "\"");
}

BOOST_AUTO_TEST_CASE(fail_string_as_int)
{
    const char input[] = "\"alpha\"";
    json::detail::decoder decoder(input);
    BOOST_REQUIRE_EQUAL(decoder.token(), json::token::string);
    BOOST_REQUIRE_EQUAL(decoder.value<std::string>(), "alpha");
    BOOST_REQUIRE_EXCEPTION(decoder.value<int>(),
                            boost::system::system_error,
                            test::is_system_error(json::incompatible_type));
}

BOOST_AUTO_TEST_CASE(fail_string_as_float)
{
    const char input[] = "\"alpha\"";
    json::detail::decoder decoder(input);
    BOOST_REQUIRE_EQUAL(decoder.token(), json::token::string);
    BOOST_REQUIRE_EQUAL(decoder.value<std::string>(), "alpha");
    BOOST_REQUIRE_EXCEPTION(decoder.value<float>(),
                            boost::system::system_error,
                            test::is_system_error(json::incompatible_type));
}

//-----------------------------------------------------------------------------
// String pangram
//
// Adapted from http://www.cl.cam.ac.uk/~mgk25/ucs/examples/quickbrown.txt
//-----------------------------------------------------------------------------

BOOST_AUTO_TEST_CASE(test_string_pangram_english)
{
    const char input[] = "\"The quick brown fox jumps over the lazy dog\"";
    json::detail::decoder decoder(input);
    BOOST_REQUIRE_EQUAL(decoder.token(), json::token::string);
    BOOST_REQUIRE_EQUAL(decoder.value<std::string>(), "The quick brown fox jumps over the lazy dog");
    decoder.next();
    BOOST_REQUIRE_EQUAL(decoder.token(), json::token::end);
}

BOOST_AUTO_TEST_CASE(test_string_pangram_german)
{
    const char input[] = "\"Falsches \\u00DCben von Xylophonmusik qu\\u00E4lt jeden gr\\u00F6\\u00DFeren Zwerg\"";
    json::detail::decoder decoder(input);
    BOOST_REQUIRE_EQUAL(decoder.token(), json::token::string);
    BOOST_REQUIRE_EQUAL(decoder.value<std::string>(), "Falsches Üben von Xylophonmusik quält jeden größeren Zwerg");
    decoder.next();
    BOOST_REQUIRE_EQUAL(decoder.token(), json::token::end);
}

BOOST_AUTO_TEST_CASE(test_string_pangram_danish)
{
    const char input[] = "\"Quizdeltagerne spiste jordb\\u00E6r med fl\\u00F8de, mens cirkusklovnen Wolther spillede p\\u00E5 xylofon\"";
    json::detail::decoder decoder(input);
    BOOST_REQUIRE_EQUAL(decoder.token(), json::token::string);
    BOOST_REQUIRE_EQUAL(decoder.value<std::string>(), "Quizdeltagerne spiste jordbær med fløde, mens cirkusklovnen Wolther spillede på xylofon");
    decoder.next();
    BOOST_REQUIRE_EQUAL(decoder.token(), json::token::end);
}

BOOST_AUTO_TEST_CASE(test_string_pangram_greek)
{
    const char input[] = "\"\\u0393\\u03B1\\u03B6\\u03AD\\u03B5\\u03C2 \\u03BA\\u03B1\\u1F76 \\u03BC\\u03C5\\u03C1\\u03C4\\u03B9\\u1F72\\u03C2 \\u03B4\\u1F72\\u03BD \\u03B8\\u1F70 \\u03B2\\u03C1\\u1FF6 \\u03C0\\u03B9\\u1F70 \\u03C3\\u03C4\\u1F78 \\u03C7\\u03C1\\u03C5\\u03C3\\u03B1\\u03C6\\u1F76 \\u03BE\\u03AD\\u03C6\\u03C9\\u03C4\\u03BF\"";
    json::detail::decoder decoder(input);
    BOOST_REQUIRE_EQUAL(decoder.token(), json::token::string);
    BOOST_REQUIRE_EQUAL(decoder.value<std::string>(), "Γαζέες καὶ μυρτιὲς δὲν θὰ βρῶ πιὰ στὸ χρυσαφὶ ξέφωτο");
    decoder.next();
    BOOST_REQUIRE_EQUAL(decoder.token(), json::token::end);
}

//-----------------------------------------------------------------------------
// Container
//-----------------------------------------------------------------------------

BOOST_AUTO_TEST_CASE(test_begin_object)
{
    const char input[] = "{";
    json::detail::decoder decoder(input);
    BOOST_REQUIRE_EQUAL(decoder.token(), json::token::begin_object);
    BOOST_REQUIRE_EQUAL(decoder.literal(), "{");
    decoder.next();
    BOOST_REQUIRE_EQUAL(decoder.token(), json::token::end);
}

BOOST_AUTO_TEST_CASE(test_white_begin_object)
{
    const char input[] = " { ";
    json::detail::decoder decoder(input);
    BOOST_REQUIRE_EQUAL(decoder.token(), json::token::begin_object);
    BOOST_REQUIRE_EQUAL(decoder.literal(), "{");
    decoder.next();
    BOOST_REQUIRE_EQUAL(decoder.token(), json::token::end);
}

BOOST_AUTO_TEST_CASE(test_end_object)
{
    const char input[] = "}";
    json::detail::decoder decoder(input);
    BOOST_REQUIRE_EQUAL(decoder.token(), json::token::end_object);
    BOOST_REQUIRE_EQUAL(decoder.literal(), "}");
    decoder.next();
    BOOST_REQUIRE_EQUAL(decoder.token(), json::token::end);
}

BOOST_AUTO_TEST_CASE(test_white_end_object)
{
    const char input[] = " } ";
    json::detail::decoder decoder(input);
    BOOST_REQUIRE_EQUAL(decoder.token(), json::token::end_object);
    BOOST_REQUIRE_EQUAL(decoder.literal(), "}");
    decoder.next();
    BOOST_REQUIRE_EQUAL(decoder.token(), json::token::end);
}

BOOST_AUTO_TEST_CASE(test_object)
{
    const char input[] = "{ \"key\" : false }";
    json::detail::decoder decoder(input);
    BOOST_REQUIRE_EQUAL(decoder.token(), json::token::begin_object);
    BOOST_REQUIRE_EQUAL(decoder.literal(), "{");
    decoder.next();
    BOOST_REQUIRE_EQUAL(decoder.token(), json::token::string);
    BOOST_REQUIRE_EQUAL(decoder.value<std::string>(), "key");
    decoder.next();
    BOOST_REQUIRE_EQUAL(decoder.token(), json::token::name_separator);
    BOOST_REQUIRE_EQUAL(decoder.literal(), ":");
    decoder.next();
    BOOST_REQUIRE_EQUAL(decoder.token(), json::token::false_value);
    decoder.next();
    BOOST_REQUIRE_EQUAL(decoder.token(), json::token::end_object);
    BOOST_REQUIRE_EQUAL(decoder.literal(), "}");
    decoder.next();
    BOOST_REQUIRE_EQUAL(decoder.token(), json::token::end);
}

BOOST_AUTO_TEST_CASE(test_array_begin)
{
    const char input[] = "[";
    json::detail::decoder decoder(input);
    BOOST_REQUIRE_EQUAL(decoder.token(), json::token::begin_array);
    BOOST_REQUIRE_EQUAL(decoder.literal(), "[");
    decoder.next();
    BOOST_REQUIRE_EQUAL(decoder.token(), json::token::end);
}

BOOST_AUTO_TEST_CASE(test_array_white_begin)
{
    const char input[] = " [ ";
    json::detail::decoder decoder(input);
    BOOST_REQUIRE_EQUAL(decoder.token(), json::token::begin_array);
    BOOST_REQUIRE_EQUAL(decoder.literal(), "[");
    decoder.next();
    BOOST_REQUIRE_EQUAL(decoder.token(), json::token::end);
}

BOOST_AUTO_TEST_CASE(test_array_end)
{
    const char input[] = "]";
    json::detail::decoder decoder(input);
    BOOST_REQUIRE_EQUAL(decoder.token(), json::token::end_array);
    BOOST_REQUIRE_EQUAL(decoder.literal(), "]");
    decoder.next();
    BOOST_REQUIRE_EQUAL(decoder.token(), json::token::end);
}

BOOST_AUTO_TEST_CASE(test_array_white_end)
{
    const char input[] = " ] ";
    json::detail::decoder decoder(input);
    BOOST_REQUIRE_EQUAL(decoder.token(), json::token::end_array);
    BOOST_REQUIRE_EQUAL(decoder.literal(), "]");
    decoder.next();
    BOOST_REQUIRE_EQUAL(decoder.token(), json::token::end);
}

BOOST_AUTO_TEST_CASE(test_array)
{
    const char input[] = "[true, false]";
    json::detail::decoder decoder(input);
    BOOST_REQUIRE_EQUAL(decoder.token(), json::token::begin_array);
    BOOST_REQUIRE_EQUAL(decoder.literal(), "[");
    decoder.next();
    BOOST_REQUIRE_EQUAL(decoder.token(), json::token::true_value);
    decoder.next();
    BOOST_REQUIRE_EQUAL(decoder.token(), json::token::value_separator);
    BOOST_REQUIRE_EQUAL(decoder.literal(), ",");
    decoder.next();
    BOOST_REQUIRE_EQUAL(decoder.token(), json::token::false_value);
    decoder.next();
    BOOST_REQUIRE_EQUAL(decoder.token(), json::token::end_array);
    BOOST_REQUIRE_EQUAL(decoder.literal(), "]");
    decoder.next();
    BOOST_REQUIRE_EQUAL(decoder.token(), json::token::end);
}

//-----------------------------------------------------------------------------
// View
//-----------------------------------------------------------------------------

BOOST_AUTO_TEST_CASE(test_view_null)
{
    const char input[] = "null";
    json::detail::decoder decoder(input);
    BOOST_REQUIRE_EQUAL(decoder.token(), json::token::null);
    BOOST_REQUIRE_EQUAL(decoder.literal(), "null");
    decoder.next();
    BOOST_REQUIRE_EQUAL(decoder.token(), json::token::end);
}

BOOST_AUTO_TEST_CASE(test_view_true)
{
    const char input[] = "true";
    json::detail::decoder decoder(input);
    BOOST_REQUIRE_EQUAL(decoder.token(), json::token::true_value);
    BOOST_REQUIRE_EQUAL(decoder.literal(), "true");
    decoder.next();
    BOOST_REQUIRE_EQUAL(decoder.token(), json::token::end);
}

BOOST_AUTO_TEST_CASE(test_view_false)
{
    const char input[] = "false";
    json::detail::decoder decoder(input);
    BOOST_REQUIRE_EQUAL(decoder.token(), json::token::false_value);
    BOOST_REQUIRE_EQUAL(decoder.literal(), "false");
    decoder.next();
    BOOST_REQUIRE_EQUAL(decoder.token(), json::token::end);
}

BOOST_AUTO_TEST_CASE(test_view_integer_zero)
{
    const char input[] = "0";
    json::detail::decoder decoder(input);
    BOOST_REQUIRE_EQUAL(decoder.token(), json::token::integer);
    BOOST_REQUIRE_EQUAL(decoder.literal(), "0");
    BOOST_REQUIRE_EQUAL(decoder.value<boost::intmax_t>(), 0);
    decoder.next();
    BOOST_REQUIRE_EQUAL(decoder.token(), json::token::end);
}

BOOST_AUTO_TEST_CASE(test_view_floating_zero)
{
    const char input[] = "0.0";
    json::detail::decoder decoder(input);
    BOOST_REQUIRE_EQUAL(decoder.token(), json::token::floating);
    BOOST_REQUIRE_EQUAL(decoder.literal(), "0.0");
    BOOST_REQUIRE_EQUAL(decoder.value<double>(), 0.0);
    decoder.next();
    BOOST_REQUIRE_EQUAL(decoder.token(), json::token::end);
}

BOOST_AUTO_TEST_CASE(test_view_floating_float)
{
    const char input[] = "1.0";
    json::detail::decoder decoder(input);
    BOOST_REQUIRE_EQUAL(decoder.token(), json::token::floating);
    BOOST_REQUIRE_EQUAL(decoder.literal(), "1.0");
    BOOST_REQUIRE_EQUAL(decoder.value<float>(), 1.0f);
    decoder.next();
    BOOST_REQUIRE_EQUAL(decoder.token(), json::token::end);
}

BOOST_AUTO_TEST_CASE(test_view_string_empty)
{
    const char input[] = "\"\"";
    json::detail::decoder decoder(input);
    BOOST_REQUIRE_EQUAL(decoder.token(), json::token::string);
    BOOST_REQUIRE_EQUAL(decoder.literal(), "\"\"");
    BOOST_REQUIRE_EQUAL(decoder.value<std::string>(), "");
    decoder.next();
    BOOST_REQUIRE_EQUAL(decoder.token(), json::token::end);
}

BOOST_AUTO_TEST_CASE(test_view_string_alpha)
{
    const char input[] = "\"alpha\"";
    json::detail::decoder decoder(input);
    BOOST_REQUIRE_EQUAL(decoder.token(), json::token::string);
    BOOST_REQUIRE_EQUAL(decoder.literal(), "\"alpha\"");
    BOOST_REQUIRE_EQUAL(decoder.value<std::string>(), "alpha");
    decoder.next();
    BOOST_REQUIRE_EQUAL(decoder.token(), json::token::end);
}

BOOST_AUTO_TEST_SUITE_END()
