// span<T> の単体テスト

#include <omusubi/core/span.hpp>

#include "test_framework.hpp"

namespace span_test {

using namespace omusubi;
using namespace test;

void test_span_basic() {
    test_section("基本機能");

    // デフォルトコンストラクタ
    span<int> empty_span;
    TEST_ASSERT(empty_span.empty(), "空のspanはempty()がtrue");
    TEST_ASSERT_EQ(empty_span.size(), 0U, "空のspanのサイズは0");

    // 配列からの構築
    int arr[] = {1, 2, 3, 4, 5};
    span<int> s(arr);
    TEST_ASSERT_EQ(s.size(), 5U, "配列からのspan構築でサイズが正しい");
    TEST_ASSERT_EQ(s[0], 1, "要素アクセス [0]");
    TEST_ASSERT_EQ(s[4], 5, "要素アクセス [4]");

    // ポインタと長さからの構築
    span<int> s2(arr, 3);
    TEST_ASSERT_EQ(s2.size(), 3U, "ポインタと長さからの構築");
    TEST_ASSERT_EQ(s2[2], 3, "範囲内の要素アクセス");
}

void test_span_iteration() {
    test_section("イテレータ");

    int arr[] = {10, 20, 30};
    span<int> s(arr);

    // 範囲for文
    int sum = 0;
    for (int val : s) {
        sum += val;
    }
    TEST_ASSERT_EQ(sum, 60, "範囲for文での要素アクセス");

    // begin/end
    TEST_ASSERT_EQ(*s.begin(), 10, "begin()で最初の要素にアクセス");
    TEST_ASSERT_EQ(*(s.end() - 1), 30, "end()で最後の要素にアクセス");
}

void test_span_subspan() {
    test_section("部分span操作");

    int arr[] = {1, 2, 3, 4, 5};
    span<int> s(arr);

    // subspan
    auto sub = s.subspan(1, 3);
    TEST_ASSERT_EQ(sub.size(), 3U, "subspanのサイズ");
    TEST_ASSERT_EQ(sub[0], 2, "subspanの最初の要素");
    TEST_ASSERT_EQ(sub[2], 4, "subspanの最後の要素");

    // first
    auto first = s.first(2);
    TEST_ASSERT_EQ(first.size(), 2U, "first()のサイズ");
    TEST_ASSERT_EQ(first[0], 1, "first()の最初の要素");

    // last
    auto last = s.last(2);
    TEST_ASSERT_EQ(last.size(), 2U, "last()のサイズ");
    TEST_ASSERT_EQ(last[1], 5, "last()の最後の要素");
}

void test_span_conversion() {
    test_section("型変換");

    char str[] = "test";
    span<char> char_span(str, 4);

    // as_bytes
    auto bytes = as_bytes(char_span);
    TEST_ASSERT_EQ(bytes.size(), 4U, "as_bytes()でバイト列に変換");
    TEST_ASSERT_EQ(bytes[0], static_cast<uint8_t>('t'), "バイト列の内容が正しい");

    // as_chars
    uint8_t byte_arr[] = {65, 66, 67}; // 'A', 'B', 'C'
    span<uint8_t> byte_span(byte_arr);
    auto chars = as_chars(byte_span);
    TEST_ASSERT_EQ(chars.size(), 3U, "as_chars()で文字列に変換");
    TEST_ASSERT_EQ(chars[0], 'A', "文字列の内容が正しい");
}

void test_span_const() {
    test_section("const span");

    const int arr[] = {1, 2, 3};
    span<const int> cs(arr);

    TEST_ASSERT_EQ(cs.size(), 3U, "const spanのサイズ");
    TEST_ASSERT_EQ(cs[1], 2, "const spanの要素アクセス");
    TEST_ASSERT(!cs.empty(), "const spanのempty()");
}

int main() {
    begin_tests("span<T>");

    test_span_basic();
    test_span_iteration();
    test_span_subspan();
    test_span_conversion();
    test_span_const();

    return end_tests();
}

} // namespace span_test
