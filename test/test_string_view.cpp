// StringView の単体テスト

#include <omusubi/core/string_view.h>

#include "test_framework.hpp"

namespace string_view_test {

using namespace omusubi;
using namespace omusubi::literals;
using namespace test;

void test_string_view_basic() {
    test_section("基本機能");

    // デフォルトコンストラクタ
    StringView empty;
    TEST_ASSERT_EQ(empty.byte_length(), 0U, "空のStringViewのバイト長は0");

    // 文字列リテラルからの構築
    StringView sv = "Hello"_sv;
    TEST_ASSERT_EQ(sv.byte_length(), 5U, "文字列リテラルからのバイト長");
    TEST_ASSERT_STR_EQ(sv.data(), "Hello", "文字列リテラルの内容");

    // C文字列からの構築
    StringView sv2 = StringView::from_c_string("World");
    TEST_ASSERT_EQ(sv2.byte_length(), 5U, "C文字列からのバイト長");
}

void test_string_view_utf8() {
    test_section("UTF-8処理");

    // 日本語文字列
    StringView japanese = "こんにちは"_sv;
    TEST_ASSERT_EQ(japanese.byte_length(), 15U, "日本語のバイト長（5文字×3バイト）");
    TEST_ASSERT_EQ(japanese.char_length(), 5U, "日本語の文字数");

    // 混合文字列
    StringView mixed = "Hello世界"_sv;
    TEST_ASSERT_EQ(mixed.byte_length(), 11U, "混合文字列のバイト長（5+6）");
    TEST_ASSERT_EQ(mixed.char_length(), 7U, "混合文字列の文字数");

    // 絵文字
    StringView emoji = "😀"_sv;
    TEST_ASSERT_EQ(emoji.byte_length(), 4U, "絵文字のバイト長");
    TEST_ASSERT_EQ(emoji.char_length(), 1U, "絵文字の文字数");
}

void test_string_view_substring() {
    test_section("部分文字列");

    StringView sv = "Hello World"_sv;

    // substring
    auto sub = sv.substring(0, 5);
    TEST_ASSERT_EQ(sub.byte_length(), 5U, "substringのバイト長");
    TEST_ASSERT(sub == "Hello"_sv, "substringの内容");

    // 範囲外アクセス
    auto sub2 = sv.substring(100, 5);
    TEST_ASSERT_EQ(sub2.byte_length(), 0U, "範囲外substringは空");

    // 超過する長さ
    auto sub3 = sv.substring(6, 100);
    TEST_ASSERT_EQ(sub3.byte_length(), 5U, "超過する長さは切り詰められる");
}

void test_string_view_comparison() {
    test_section("文字列比較");

    StringView s1 = "Hello"_sv;
    StringView s2 = "Hello"_sv;
    StringView s3 = "World"_sv;

    TEST_ASSERT(s1 == s2, "同じ内容の文字列は等しい");
    TEST_ASSERT(s1 != s3, "異なる内容の文字列は等しくない");
}

void test_string_view_search() {
    test_section("検索機能");

    StringView sv = "Hello World Hello"_sv;

    // starts_with
    TEST_ASSERT(sv.starts_with("Hello"_sv), "starts_with: 正しい接頭辞");
    TEST_ASSERT(!sv.starts_with("World"_sv), "starts_with: 誤った接頭辞");

    // ends_with
    TEST_ASSERT(sv.ends_with("Hello"_sv), "ends_with: 正しい接尾辞");
    TEST_ASSERT(!sv.ends_with("World"_sv), "ends_with: 誤った接尾辞");

    // contains
    TEST_ASSERT(sv.contains("World"_sv), "contains: 含まれる文字列");
    TEST_ASSERT(!sv.contains("Goodbye"_sv), "contains: 含まれない文字列");
}

void test_string_view_iteration() {
    test_section("イテレータ");

    StringView sv = "ABC"_sv;

    int count = 0;
    for (char c : sv) {
        TEST_ASSERT(c == 'A' || c == 'B' || c == 'C', "イテレータで各文字にアクセス");
        count++;
    }
    TEST_ASSERT_EQ(count, 3, "イテレータで全要素を走査");
}

void test_utf8_helpers() {
    test_section("UTF-8ヘルパー関数");

    // 1バイト文字（ASCII）
    TEST_ASSERT_EQ(utf8::get_char_byte_length('A'), 1U, "ASCII文字は1バイト");

    // 2バイト文字
    TEST_ASSERT_EQ(utf8::get_char_byte_length(0xC0), 2U, "2バイト文字の判定");

    // 3バイト文字（日本語など）
    TEST_ASSERT_EQ(utf8::get_char_byte_length(0xE0), 3U, "3バイト文字の判定");

    // 4バイト文字（絵文字など）
    TEST_ASSERT_EQ(utf8::get_char_byte_length(0xF0), 4U, "4バイト文字の判定");

    // 文字数カウント
    const char* str = "Aあ😀"; // 1 + 3 + 4 = 8バイト, 3文字
    uint32_t char_count = utf8::count_chars(str, 8);
    TEST_ASSERT_EQ(char_count, 3U, "混合文字列の文字数カウント");
}

int main() {
    begin_tests("StringView");

    test_string_view_basic();
    test_string_view_utf8();
    test_string_view_substring();
    test_string_view_comparison();
    test_string_view_search();
    test_string_view_iteration();
    test_utf8_helpers();

    return end_tests();
}

} // namespace string_view_test
