///////////////////////////////////////////////////////////////////////////////
//
// Copyright (C) 2017 Bjorn Reese <breese@users.sourceforge.net>
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
///////////////////////////////////////////////////////////////////////////////

#include <numeric>
#include <trial/protocol/core/detail/lightweight_test.hpp>
#include <trial/dynamic/variable.hpp>

using namespace trial::dynamic;

//-----------------------------------------------------------------------------
// std::accumulate
//-----------------------------------------------------------------------------

namespace accumulate_suite
{

void accumulate_null()
{
    variable data;
    variable result = std::accumulate(data.begin(), data.end(), variable());
    TRIAL_PROTOCOL_TEST_EQUAL(result.is<nullable>(), true);
}

void accumulate_null_with_boolean()
{
    variable data;
    variable result = std::accumulate(data.begin(), data.end(), variable(true));
    TRIAL_PROTOCOL_TEST_EQUAL(result.is<bool>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(result.value<bool>(), true);
}

void accumulate_boolean()
{
    variable data(true);
    variable result = std::accumulate(data.begin(), data.end(), variable(false));
    TRIAL_PROTOCOL_TEST_EQUAL(result.is<bool>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(result.value<bool>(), true);
}

void accumulate_integer()
{
    variable data(2);
    variable result = std::accumulate(data.begin(), data.end(), variable(0));
    TRIAL_PROTOCOL_TEST_EQUAL(result.is<int>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(result.value<int>(), 2);
}

void accumulate_number()
{
    variable data(3.0);
    variable result = std::accumulate(data.begin(), data.end(), variable(0.0));
    TRIAL_PROTOCOL_TEST_EQUAL(result.is<float>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(result.value<double>(), 3.0);
}

void accumulate_string()
{
    variable data("alpha");
    variable result = std::accumulate(data.begin(), data.end(), variable("prefix"));
    TRIAL_PROTOCOL_TEST_EQUAL(result.is<string>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(result.value<string>(), "prefixalpha");
}

void accumulate_wstring()
{
    variable data(L"bravo");
    variable result = std::accumulate(data.begin(), data.end(), variable(L"prefix"));
    TRIAL_PROTOCOL_TEST_EQUAL(result.is<wstring>(), true);
    TRIAL_PROTOCOL_TEST(result.value<std::wstring>() == L"prefixbravo");
}

void accumulate_u16string()
{
    variable data(u"charlie");
    variable result = std::accumulate(data.begin(), data.end(), variable(u"prefix"));
    TRIAL_PROTOCOL_TEST_EQUAL(result.is<u16string>(), true);
    TRIAL_PROTOCOL_TEST(result.value<std::u16string>() == u"prefixcharlie");
}

void accumulate_u32string()
{
    variable data(U"delta");
    variable result = std::accumulate(data.begin(), data.end(), variable(U"prefix"));
    TRIAL_PROTOCOL_TEST_EQUAL(result.is<u32string>(), true);
    TRIAL_PROTOCOL_TEST(result.value<std::u32string>() == U"prefixdelta");
}

void accumulate_array_null()
{
    variable data = array::make({ null, null });
    variable result = std::accumulate(data.begin(), data.end(), variable());
    TRIAL_PROTOCOL_TEST_EQUAL(result.is<nullable>(), true);
}

void accumulate_array_null_with_boolean()
{
    variable data = array::make({ null, null });
    variable result = std::accumulate(data.begin(), data.end(), variable(true));
    TRIAL_PROTOCOL_TEST_EQUAL(result.is<bool>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(result.value<bool>(), true);
}

void accumulate_array_boolean()
{
    variable data = array::make({ false, false, true, true });
    variable result = std::accumulate(data.begin(), data.end(), variable());
    TRIAL_PROTOCOL_TEST_EQUAL(result.is<bool>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(result.value<bool>(), true);
}

void accumulate_array_integer()
{
    variable data = array::make({ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 });
    variable result = std::accumulate(data.begin(), data.end(), variable());
    TRIAL_PROTOCOL_TEST_EQUAL(result.is<int>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(result.value<int>(), 55);
}

void accumulate_array_integer_with_number()
{
    variable data = array::make({ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 });
    variable result = std::accumulate(data.begin(), data.end(), variable(0.0));
    TRIAL_PROTOCOL_TEST_EQUAL(result.is<float>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(result.value<double>(), 55.0);
}

void accumulate_array_number()
{
    variable data = array::make({ 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0 });
    variable result = std::accumulate(data.begin(), data.end(), variable());
    TRIAL_PROTOCOL_TEST_EQUAL(result.is<float>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(result.value<double>(), 55.0);
}

void accumulate_array_number_with_integer()
{
    variable data = array::make({ 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0 });
    variable result = std::accumulate(data.begin(), data.end(), variable(0));
    TRIAL_PROTOCOL_TEST_EQUAL(result.is<int>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(result.value<int>(), 55);
}

void accumulate_array_string()
{
    variable data = array::make({ "alpha", "bravo", "charlie" });
    variable result = std::accumulate(data.begin(), data.end(), variable());
    TRIAL_PROTOCOL_TEST_EQUAL(result.is<string>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(result.value<string>(), "alphabravocharlie");
}

void accumulate_array_wstring()
{
    variable data = array::make({ L"alpha", L"bravo", L"charlie" });
    variable result = std::accumulate(data.begin(), data.end(), variable());
    TRIAL_PROTOCOL_TEST_EQUAL(result.is<wstring>(), true);
    TRIAL_PROTOCOL_TEST(result.value<std::wstring>() == L"alphabravocharlie");
}

void accumulate_array_u16string()
{
    variable data = array::make({ u"alpha", u"bravo", u"charlie" });
    variable result = std::accumulate(data.begin(), data.end(), variable());
    TRIAL_PROTOCOL_TEST_EQUAL(result.is<u16string>(), true);
    TRIAL_PROTOCOL_TEST(result.value<std::u16string>() == u"alphabravocharlie");
}

void accumulate_array_u32string()
{
    variable data = array::make({ U"alpha", U"bravo", U"charlie" });
    variable result = std::accumulate(data.begin(), data.end(), variable());
    TRIAL_PROTOCOL_TEST_EQUAL(result.is<u32string>(), true);
    TRIAL_PROTOCOL_TEST(result.value<std::u32string>() == U"alphabravocharlie");
}

void accumulate_array_array()
{
    // Array flattening
    variable data = array::make({ array::make({ "alpha", "bravo" }), array::make({ "charlie", "delta" }) });
    variable result = std::accumulate(data.begin(), data.end(), variable());
    TRIAL_PROTOCOL_TEST_EQUAL(result.is<array>(), true);
    variable expect = array::make({ "alpha", "bravo", "charlie", "delta" });
    TRIAL_PROTOCOL_TEST_ALL_WITH(result.begin(), result.end(),
                                 expect.begin(), expect.end(),
                                 std::equal_to<variable>());
}

void accumulate_map()
{
    // Iterates over values
    variable data = map::make(
        {
            { "alpha", "hydrogen" },
            { "bravo", "helium" }
        });
    variable result = std::accumulate(data.begin(), data.end(), variable());
    TRIAL_PROTOCOL_TEST_EQUAL(result.is<string>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(result.value<string>(), "hydrogenhelium");
}

void run()
{
    accumulate_null();
    accumulate_null_with_boolean();
    accumulate_boolean();
    accumulate_integer();
    accumulate_number();
    accumulate_string();
    accumulate_wstring();
    accumulate_u16string();
    accumulate_u32string();

    accumulate_array_null();
    accumulate_array_null_with_boolean();
    accumulate_array_boolean();
    accumulate_array_integer();
    accumulate_array_integer_with_number();
    accumulate_array_number();
    accumulate_array_number_with_integer();
    accumulate_array_string();
    accumulate_array_wstring();
    accumulate_array_u16string();
    accumulate_array_u32string();
    accumulate_array_array();

    accumulate_map();
}

} // namespace accumulate_suite

//-----------------------------------------------------------------------------
// std::iota
//-----------------------------------------------------------------------------

namespace iota_suite
{

void test_array_boolean()
{
    variable data = array::repeat(4, null);
    std::iota(data.begin(), data.end(), false);
    variable result = array::make({ false, true, true, true });
    TRIAL_PROTOCOL_TEST_ALL_WITH(data.begin(), data.end(),
                                 result.begin(), result.end(),
                                 std::equal_to<variable>());
}

void test_array_integer()
{
    variable data = array::repeat(4, null);
    std::iota(data.begin(), data.end(), 1);
    variable result = array::make({ 1, 2, 3, 4 });
    TRIAL_PROTOCOL_TEST_ALL_WITH(data.begin(), data.end(),
                                 result.begin(), result.end(),
                                 std::equal_to<variable>());
}

void test_array_number()
{
    variable data = array::repeat(4, null);
    std::iota(data.begin(), data.end(), 1.0);
    variable result = array::make({ 1.0, 2.0, 3.0, 4.0 });
    TRIAL_PROTOCOL_TEST_ALL_WITH(data.begin(), data.end(),
                                 result.begin(), result.end(),
                                 std::equal_to<variable>());
}

void run()
{
    test_array_boolean();
    test_array_integer();
    test_array_number();
}

} // namespace iota_suite

//-----------------------------------------------------------------------------
// std::partial_sum
//-----------------------------------------------------------------------------

namespace partial_sum_suite
{

void sum_null()
{
    variable data;
    std::vector<variable> result;
    std::partial_sum(data.begin(), data.end(), std::back_inserter(result));
    TRIAL_PROTOCOL_TEST_EQUAL(result.size(), 0);
}

void sum_boolean()
{
    variable data(true);
    std::vector<variable> result;
    std::partial_sum(data.begin(), data.end(), std::back_inserter(result));
    variable expect = array::make({ 1 });
    TRIAL_PROTOCOL_TEST_ALL_WITH(result.begin(), result.end(),
                                 expect.begin(), expect.end(),
                                 std::equal_to<variable>());
}

void sum_integer()
{
    variable data(2);
    std::vector<variable> result;
    std::partial_sum(data.begin(), data.end(), std::back_inserter(result));
    variable expect = array::make({ 2 });
    TRIAL_PROTOCOL_TEST_ALL_WITH(result.begin(), result.end(),
                                 expect.begin(), expect.end(),
                                 std::equal_to<variable>());
}

void sum_number()
{
    variable data(3.0);
    std::vector<variable> result;
    std::partial_sum(data.begin(), data.end(), std::back_inserter(result));
    variable expect = array::make({ 3.0 });
    TRIAL_PROTOCOL_TEST_ALL_WITH(result.begin(), result.end(),
                                 expect.begin(), expect.end(),
                                 std::equal_to<variable>());
}

void sum_string()
{
    {
        variable data("alpha");
        std::vector<variable> result;
        std::partial_sum(data.begin(), data.end(), std::back_inserter(result));
        variable expect = array::make({ "alpha" });
        TRIAL_PROTOCOL_TEST_ALL_WITH(result.begin(), result.end(),
                                     expect.begin(), expect.end(),
                                     std::equal_to<variable>());
    }
    {
        variable data(L"bravo");
        std::vector<variable> result;
        std::partial_sum(data.begin(), data.end(), std::back_inserter(result));
        variable expect = array::make({ L"bravo" });
        TRIAL_PROTOCOL_TEST_ALL_WITH(result.begin(), result.end(),
                                     expect.begin(), expect.end(),
                                     std::equal_to<variable>());
    }
    {
        variable data(u"charlie");
        std::vector<variable> result;
        std::partial_sum(data.begin(), data.end(), std::back_inserter(result));
        variable expect = array::make({ u"charlie" });
        TRIAL_PROTOCOL_TEST_ALL_WITH(result.begin(), result.end(),
                                     expect.begin(), expect.end(),
                                     std::equal_to<variable>());
    }
    {
        variable data(U"delta");
        std::vector<variable> result;
        std::partial_sum(data.begin(), data.end(), std::back_inserter(result));
        variable expect = array::make({ U"delta" });
        TRIAL_PROTOCOL_TEST_ALL_WITH(result.begin(), result.end(),
                                     expect.begin(), expect.end(),
                                     std::equal_to<variable>());
    }
}

void sum_array_null()
{
    variable data = array::make({ null, null, null });
    std::vector<variable> result;
    std::partial_sum(data.begin(), data.end(), std::back_inserter(result));
    variable expect = array::make({ null, null, null });
    TRIAL_PROTOCOL_TEST_ALL_WITH(result.begin(), result.end(),
                                 expect.begin(), expect.end(),
                                 std::equal_to<variable>());
}

void sum_array_boolean()
{
    variable data = array::make({ true, false, true });
    std::vector<variable> result;
    std::partial_sum(data.begin(), data.end(), std::back_inserter(result));
    variable expect = array::make({ true, true, true });
    TRIAL_PROTOCOL_TEST_ALL_WITH(result.begin(), result.end(),
                                 expect.begin(), expect.end(),
                                 std::equal_to<variable>());
}

void sum_array_integer()
{
    variable data = array::make({ 1, 20, 300 });
    std::vector<variable> result;
    std::partial_sum(data.begin(), data.end(), std::back_inserter(result));
    variable expect = array::make({ 1, 21, 321 });
    TRIAL_PROTOCOL_TEST_ALL_WITH(result.begin(), result.end(),
                                 expect.begin(), expect.end(),
                                 std::equal_to<variable>());
}

void sum_array_number()
{
    variable data = array::make({ 1.0, 20.0, 300.0 });
    std::vector<variable> result;
    std::partial_sum(data.begin(), data.end(), std::back_inserter(result));
    variable expect = array::make({ 1.0, 21.0, 321.0 });
    TRIAL_PROTOCOL_TEST_ALL_WITH(result.begin(), result.end(),
                                 expect.begin(), expect.end(),
                                 std::equal_to<variable>());
}

void sum_array_string()
{
    {
        variable data = array::make({ "one", "two", "three" });
        std::vector<variable> result;
        std::partial_sum(data.begin(), data.end(), std::back_inserter(result));
        variable expect = array::make({ "one", "onetwo", "onetwothree" });
        TRIAL_PROTOCOL_TEST_ALL_WITH(result.begin(), result.end(),
                                     expect.begin(), expect.end(),
                                     std::equal_to<variable>());
    }
    {
        variable data = array::make({ L"one", L"two", L"three" });
        std::vector<variable> result;
        std::partial_sum(data.begin(), data.end(), std::back_inserter(result));
        variable expect = array::make({ L"one", L"onetwo", L"onetwothree" });
        TRIAL_PROTOCOL_TEST_ALL_WITH(result.begin(), result.end(),
                                     expect.begin(), expect.end(),
                                     std::equal_to<variable>());
    }
    {
        variable data = array::make({ u"one", u"two", u"three" });
        std::vector<variable> result;
        std::partial_sum(data.begin(), data.end(), std::back_inserter(result));
        variable expect = array::make({ u"one", u"onetwo", u"onetwothree" });
        TRIAL_PROTOCOL_TEST_ALL_WITH(result.begin(), result.end(),
                                     expect.begin(), expect.end(),
                                     std::equal_to<variable>());
    }
    {
        variable data = array::make({ U"one", U"two", U"three" });
        std::vector<variable> result;
        std::partial_sum(data.begin(), data.end(), std::back_inserter(result));
        variable expect = array::make({ U"one", U"onetwo", U"onetwothree" });
        TRIAL_PROTOCOL_TEST_ALL_WITH(result.begin(), result.end(),
                                     expect.begin(), expect.end(),
                                     std::equal_to<variable>());
    }
}

void fail_array_string()
{
    variable data = array::make({ "alpha", L"bravo", u"charlie", U"delta" });
    std::vector<variable> result;
    TRIAL_PROTOCOL_TEST_THROW_EQUAL(std::partial_sum(data.begin(), data.end(), std::back_inserter(result)),
                                    error,
                                    "incompatible type");
}

void run()
{
    sum_null();
    sum_boolean();
    sum_integer();
    sum_number();
    sum_string();
    sum_array_null();
    sum_array_boolean();
    sum_array_integer();
    sum_array_number();
    sum_array_string();
    fail_array_string();
}

} // namespace partial_sum_suite

//-----------------------------------------------------------------------------
// main
//-----------------------------------------------------------------------------

int main()
{
    accumulate_suite::run();
    iota_suite::run();
    partial_sum_suite::run();

    return boost::report_errors();
}
