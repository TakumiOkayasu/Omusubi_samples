// StringView の単体テスト

#define DOCTEST_CONFIG_NO_EXCEPTIONS
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <omusubi/core/string_view.h>

#include "doctest.h"

using namespace omusubi;
using namespace omusubi::literals;

TEST_CASE("StringView - 基本機能") {
    SUBCASE("デフォルトコンストラクタ") {
        StringView empty;
        CHECK_EQ(empty.byte_length(), 0U);
    }

    SUBCASE("文字列リテラルからの構築") {
        StringView sv = "Hello"_sv;
        CHECK_EQ(sv.byte_length(), 5U);
        CHECK(sv == "Hello"_sv);
    }

    SUBCASE("C文字列からの構築") {
        StringView sv2 = StringView::from_c_string("World");
        CHECK_EQ(sv2.byte_length(), 5U);
    }
}

TEST_CASE("StringView - UTF-8処理") {
    SUBCASE("日本語文字列") {
        StringView japanese = "こんにちは"_sv;
        CHECK_EQ(japanese.byte_length(), 15U);
        CHECK_EQ(japanese.char_length(), 5U);
    }

    SUBCASE("混合文字列") {
        StringView mixed = "Hello世界"_sv;
        CHECK_EQ(mixed.byte_length(), 11U);
        CHECK_EQ(mixed.char_length(), 7U);
    }

    SUBCASE("絵文字") {
        StringView emoji = "😀"_sv;
        CHECK_EQ(emoji.byte_length(), 4U);
        CHECK_EQ(emoji.char_length(), 1U);
    }
}

TEST_CASE("StringView - 部分文字列") {
    StringView sv = "Hello World"_sv;

    SUBCASE("substring") {
        auto sub = sv.substring(0, 5);
        CHECK_EQ(sub.byte_length(), 5U);
        CHECK(sub == "Hello"_sv);
    }

    SUBCASE("範囲外アクセス") {
        auto sub2 = sv.substring(100, 5);
        CHECK_EQ(sub2.byte_length(), 0U);
    }

    SUBCASE("超過する長さ") {
        auto sub3 = sv.substring(6, 100);
        CHECK_EQ(sub3.byte_length(), 5U);
    }
}

TEST_CASE("StringView - 文字列比較") {
    StringView s1 = "Hello"_sv;
    StringView s2 = "Hello"_sv;
    StringView s3 = "World"_sv;

    CHECK(s1 == s2);
    CHECK(s1 != s3);
}

TEST_CASE("StringView - 検索機能") {
    StringView sv = "Hello World Hello"_sv;

    SUBCASE("starts_with") {
        CHECK(sv.starts_with("Hello"_sv));
        CHECK_FALSE(sv.starts_with("World"_sv));
    }

    SUBCASE("ends_with") {
        CHECK(sv.ends_with("Hello"_sv));
        CHECK_FALSE(sv.ends_with("World"_sv));
    }

    SUBCASE("contains") {
        CHECK(sv.contains("World"_sv));
        CHECK_FALSE(sv.contains("Goodbye"_sv));
    }
}

TEST_CASE("StringView - イテレータ") {
    StringView sv = "ABC"_sv;

    int count = 0;
    for (char c : sv) {
        CHECK((c == 'A' || c == 'B' || c == 'C'));
        count++;
    }
    CHECK_EQ(count, 3);
}

TEST_CASE("StringView - UTF-8ヘルパー関数") {
    SUBCASE("1バイト文字（ASCII）") {
        CHECK_EQ(utf8::get_char_byte_length('A'), 1U);
    }

    SUBCASE("2バイト文字") {
        CHECK_EQ(utf8::get_char_byte_length(0xC0), 2U);
    }

    SUBCASE("3バイト文字") {
        CHECK_EQ(utf8::get_char_byte_length(0xE0), 3U);
    }

    SUBCASE("4バイト文字") {
        CHECK_EQ(utf8::get_char_byte_length(0xF0), 4U);
    }

    SUBCASE("文字数カウント") {
        const char* str = "Aあ😀"; // 1 + 3 + 4 = 8バイト, 3文字
        uint32_t char_count = utf8::count_chars(str, 8);
        CHECK_EQ(char_count, 3U);
    }
}
