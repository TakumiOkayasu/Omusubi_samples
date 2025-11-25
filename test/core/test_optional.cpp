// std::optional のユニットテスト

#include <optional>

#include "../test_framework.hpp"

using namespace test;

// テスト用の構造体
struct TestStruct {
    int value;

    constexpr TestStruct(int v) : value(v) {}

    constexpr bool operator==(const TestStruct& other) const { return value == other.value; }
};

void test_optional_default_constructor() {
    std::optional<int> opt;
    TEST_ASSERT(!opt.has_value(), "デフォルトコンストラクタで値なし");
    TEST_ASSERT(!static_cast<bool>(opt), "bool変換でfalse");
}

void test_optional_value_constructor() {
    std::optional<int> opt(42);
    TEST_ASSERT(opt.has_value(), "値コンストラクタで値あり");
    TEST_ASSERT(static_cast<bool>(opt), "bool変換でtrue");
    TEST_ASSERT_EQ(opt.value(), 42, "値が正しい");
}

void test_optional_copy_constructor() {
    std::optional<int> opt1(42);
    std::optional<int> opt2(opt1);
    TEST_ASSERT(opt2.has_value(), "コピーコンストラクタで値あり");
    TEST_ASSERT_EQ(opt2.value(), 42, "コピーされた値が正しい");
}

void test_optional_copy_constructor_empty() {
    std::optional<int> opt1;
    std::optional<int> opt2(opt1);
    TEST_ASSERT(!opt2.has_value(), "空のOptionalをコピー");
}

void test_optional_copy_assignment() {
    std::optional<int> opt1(42);
    std::optional<int> opt2(10);
    opt2 = opt1;
    TEST_ASSERT(opt2.has_value(), "コピー代入で値あり");
    TEST_ASSERT_EQ(opt2.value(), 42, "コピー代入された値が正しい");
}

void test_optional_copy_assignment_empty() {
    std::optional<int> opt1;
    std::optional<int> opt2(10);
    opt2 = opt1;
    TEST_ASSERT(!opt2.has_value(), "空をコピー代入");
}

void test_optional_value_or() {
    std::optional<int> opt1(42);
    std::optional<int> opt2;
    TEST_ASSERT_EQ(opt1.value_or(0), 42, "value_or: 値ありの場合");
    TEST_ASSERT_EQ(opt2.value_or(99), 99, "value_or: 値なしの場合");
}

void test_optional_operator_arrow() {
    std::optional<TestStruct> opt(TestStruct(42));
    TEST_ASSERT_EQ(opt->value, 42, "operator->で値アクセス");
}

void test_optional_operator_dereference() {
    std::optional<int> opt(42);
    TEST_ASSERT_EQ(*opt, 42, "operator*で値アクセス");
}

void test_optional_reset() {
    std::optional<int> opt(42);
    TEST_ASSERT(opt.has_value(), "reset前は値あり");
    opt.reset();
    TEST_ASSERT(!opt.has_value(), "reset後は値なし");
}

void test_optional_emplace() {
    std::optional<int> opt;
    TEST_ASSERT(!opt.has_value(), "emplace前は値なし");
    opt.emplace(42);
    TEST_ASSERT(opt.has_value(), "emplace後は値あり");
    TEST_ASSERT_EQ(opt.value(), 42, "emplaceした値が正しい");
}

void test_optional_equality_both_empty() {
    std::optional<int> opt1;
    std::optional<int> opt2;
    TEST_ASSERT(opt1 == opt2, "両方空で等価");
    TEST_ASSERT(!(opt1 != opt2), "両方空で非等価でない");
}

void test_optional_equality_both_value() {
    std::optional<int> opt1(42);
    std::optional<int> opt2(42);
    TEST_ASSERT(opt1 == opt2, "同じ値で等価");
    TEST_ASSERT(!(opt1 != opt2), "同じ値で非等価でない");
}

void test_optional_equality_different_values() {
    std::optional<int> opt1(42);
    std::optional<int> opt2(10);
    TEST_ASSERT(opt1 != opt2, "異なる値で非等価");
    TEST_ASSERT(!(opt1 == opt2), "異なる値で等価でない");
}

void test_optional_equality_one_empty() {
    std::optional<int> opt1(42);
    std::optional<int> opt2;
    TEST_ASSERT(opt1 != opt2, "片方空で非等価");
    TEST_ASSERT(!(opt1 == opt2), "片方空で等価でない");
}

void test_optional_value_equality() {
    std::optional<int> opt(42);
    TEST_ASSERT(opt == 42, "値との等価比較: 等しい");
    TEST_ASSERT(!(opt != 42), "値との非等価比較: 等しい場合");
    TEST_ASSERT(opt != 10, "値との非等価比較: 異なる");
    TEST_ASSERT(!(opt == 10), "値との等価比較: 異なる場合");
}

void test_optional_value_equality_empty() {
    std::optional<int> opt;
    TEST_ASSERT(opt != 42, "空と値の非等価");
    TEST_ASSERT(!(opt == 42), "空と値は等価でない");
}

int main() {
    begin_tests("std::optional");

    test_optional_default_constructor();
    test_optional_value_constructor();
    test_optional_copy_constructor();
    test_optional_copy_constructor_empty();
    test_optional_copy_assignment();
    test_optional_copy_assignment_empty();
    test_optional_value_or();
    test_optional_operator_arrow();
    test_optional_operator_dereference();
    test_optional_reset();
    test_optional_emplace();
    test_optional_equality_both_empty();
    test_optional_equality_both_value();
    test_optional_equality_different_values();
    test_optional_equality_one_empty();
    test_optional_value_equality();
    test_optional_value_equality_empty();

    return end_tests();
}
