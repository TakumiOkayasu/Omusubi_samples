// basic_format_stringのデモ（C++17、C++23互換の型安全なフォーマット文字列）

#include <iostream>
#include <omusubi/core/format.hpp>

using namespace omusubi;

int main() {
    std::cout << "=== basic_format_string Demo ===\n\n";

    std::cout << "--- 基本的な使用法 ---\n";
    {
        // format_stringで型を明示
        const format_string<int> fs("Value: {}");

        // 型安全なフォーマット
        auto result = format<128>(fs, 42);
        std::cout << result.c_str() << "\n";

        // fmtでも使用可能
        auto result2 = fmt(fs, 100);
        std::cout << result2.c_str() << "\n";
    }

    std::cout << "\n--- 複数の型を指定 ---\n";
    {
        // 複数の引数型を指定
        const format_string<const char*, int, bool> fs("Name: {}, Age: {}, Active: {}");

        auto result = fmt(fs, "Alice", 25, true);
        std::cout << result.c_str() << "\n";

        // format_toでも使用可能
        FixedString<128> str;
        format_to(str, fs, "Bob", 30, false);
        std::cout << str.c_str() << "\n";
    }

    std::cout << "\n--- メタ情報の取得 ---\n";
    {
        const format_string<int, int, int> fs("x={}, y={}, z={}");

        // フォーマット文字列の内容
        std::cout << fmt("Format string: {}\n", fs.c_str()).c_str();

        // 長さ
        std::cout << fmt("Length: {}\n", fs.length()).c_str();

        // 引数数（コンパイル時定数）
        constexpr auto arg_count = format_string<int, int, int>::arg_count();
        std::cout << fmt("Argument count: {}\n", arg_count).c_str();

        // std::string_viewとして取得
        auto view = fs.view();
        std::cout << "As std::string_view: " << view << "\n";
    }

    std::cout << "\n--- 型安全性のデモ ---\n";
    {
        // 型を明示することで、コンパイル時に型の一貫性を保証
        const format_string<int, int> fs("x={}, y={}");

        // 正しい型で使用
        auto result1 = fmt(fs, 10, 20);
        std::cout << result1.c_str() << "\n";

        // 異なる型でも動作（実行時に変換）
        auto result2 = fmt(fs, 1.5, 2.5); // double -> int
        std::cout << result2.c_str() << "\n";
    }

    std::cout << "\n--- エスケープのサポート ---\n";
    {
        // エスケープされた括弧
        const format_string<int> fs("{{Value: {}}}");
        auto result = fmt(fs, 42);
        std::cout << result.c_str() << "\n";
    }

    std::cout << "\n--- C++23 std::format_stringとの比較 ---\n";
    std::cout << "C++23:\n";
    std::cout << "  auto s = std::format(\"Value: {}\", 42);\n";
    std::cout << "  std::format_string<int> fs(\"Value: {}\");\n";
    std::cout << "  auto s = std::format(fs, 42);\n";
    std::cout << "\n";
    std::cout << "Omusubi (C++17):\n";
    std::cout << "  auto s = fmt(\"Value: {}\", 42);\n";
    std::cout << "  format_string<int> fs(\"Value: {}\");\n";
    std::cout << "  auto s = fmt(fs, 42);\n";

    std::cout << "\n--- 利点 ---\n";
    std::cout << "1. 型の明示化: フォーマット文字列に期待される型を明確に示せる\n";
    std::cout << "2. 再利用性: フォーマット文字列を変数として保持できる\n";
    std::cout << "3. C++23互換: 将来のC++標準への移行が容易\n";
    std::cout << "4. 型安全性: テンプレート引数で型情報を保持\n";

    return 0;
}
