// format関数の使用例

#include <iostream>
#include <omusubi/core/format.hpp>

using namespace omusubi;

int main() {
    std::cout << "=== Format Example ===\n\n";

    std::cout << "--- テンプレート引数を明示する方法 ---\n";

    // 基本的な使用例
    auto msg1 = format<128>("Hello, {}!", "World");
    std::cout << msg1.c_str() << "\n";

    // 複数の引数
    auto msg2 = format<128>("Name: {}, Age: {}", "Alice", 25);
    std::cout << msg2.c_str() << "\n";

    // 様々な型
    auto msg3 = format<128>("Int: {}, Bool: {}, Char: {}", 42, true, 'X');
    std::cout << msg3.c_str() << "\n";

    // 16進数フォーマット
    auto hex1 = format_hex<64>(255);
    std::cout << hex1.c_str() << "\n";

    auto hex2 = format_hex<64>(0xDEADBEEF, true);
    std::cout << hex2.c_str() << "\n";

    std::cout << "\n--- テンプレート引数を隠蔽する方法（推奨） ---\n";

    // FixedStringを事前に宣言してformat_toを使用
    FixedString<128> str;

    // 基本的な使用
    format_to(str, "Hello, {}!", "World");
    std::cout << str.c_str() << "\n";

    // 複数の引数
    format_to(str, "Name: {}, Age: {}", "Bob", 30);
    std::cout << str.c_str() << "\n";

    // 様々な型
    format_to(str, "Int: {}, Bool: {}, Char: {}", 99, false, 'Z');
    std::cout << str.c_str() << "\n";

    // 16進数フォーマット
    FixedString<64> hex_str;
    format_hex_to(hex_str, 0xCAFEBABE);
    std::cout << hex_str.c_str() << "\n";

    format_hex_to(hex_str, 0xFEED, true);
    std::cout << hex_str.c_str() << "\n";

    // エスケープ
    format_to(str, "Escaped: {{}} and value: {}", 100);
    std::cout << str.c_str() << "\n";

    std::cout << "\n--- デフォルト容量ラッパー関数（最も簡潔） ---\n";

    // fmt() - Capacity指定不要（デフォルト256）
    auto simple1 = fmt("Hello, {}!", "World");
    std::cout << simple1.c_str() << "\n";

    // 複数の引数
    auto simple2 = fmt("x={}, y={}, z={}", 1, 2, 3);
    std::cout << simple2.c_str() << "\n";

    // 様々な型
    auto simple3 = fmt("String: {}, Int: {}, Bool: {}", "test", 42, true);
    std::cout << simple3.c_str() << "\n";

    // 16進数フォーマット（デフォルト容量）
    auto hex_simple1 = fmt_hex(255);
    std::cout << hex_simple1.c_str() << "\n";

    auto hex_simple2 = fmt_hex(0xDEADBEEF, true);
    std::cout << hex_simple2.c_str() << "\n";

    std::cout << "\n--- パフォーマンス重視の使用例 ---\n";

    // 再利用可能なバッファ
    FixedString<256> buffer;

    for (uint32_t i = 0; i < 5; ++i) {
        format_to(buffer, "Iteration: {}, Value: {}", i, i * 10);
        std::cout << buffer.c_str() << "\n";
    }

    std::cout << "\n--- 型安全なformat_string（C++23互換） ---\n";

    // basic_format_stringを使った型安全なフォーマット
    // テンプレート引数で型を明示することで、コンパイル時に型チェックが可能
    {
        format_string<const char*> fs("Hello, {}!");
        auto result = fmt(fs, "World");
        std::cout << result.c_str() << "\n";
    }

    // 複数の型を指定
    {
        format_string<const char*, int, bool> fs("Name: {}, Age: {}, Active: {}");
        auto result = fmt(fs, "Alice", 25, true);
        std::cout << result.c_str() << "\n";
    }

    // 引数数の取得
    {
        format_string<int, int, int> fs("x={}, y={}, z={}");
        std::cout << format("This format string expects {} arguments\n", fs.arg_count()).c_str();
    }

    std::cout << "\n--- 使い分けのガイドライン ---\n";
    std::cout << "1. fmt() - 最も簡潔、一般的な用途向け（容量256で十分な場合）\n";
    std::cout << "2. format_to() - バッファ再利用、パフォーマンス重視\n";
    std::cout << "3. format<N>() - 容量を厳密に制御したい場合\n";
    std::cout << "4. format_string<Args...> - 型安全性が必要な場合（C++23互換）\n";

    return 0;
}
