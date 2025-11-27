// Capacity自動計算のデモ

#include <iostream>
#include <omusubi/core/format.hpp>

using namespace omusubi;

int main() {
    std::cout << "=== Auto Capacity Demo ===\n\n";

    std::cout << "--- 基本的な使用法 ---\n";
    {
        // Capacity指定なし - 自動計算
        auto str1 = format("Value: {}", 42);
        std::cout << format("{} (capacity={})\n", str1.c_str(), str1.capacity()).c_str();

        auto str2 = format("Hello, {}!", "World");
        std::cout << format("{} (capacity={})\n", str2.c_str(), str2.capacity()).c_str();

        auto str3 = format("x={}, y={}, z={}", 1, 2, 3);
        std::cout << format("{} (capacity={})\n", str3.c_str(), str3.capacity()).c_str();
    }

    std::cout << "\n--- 明示的指定との比較 ---\n";
    {
        // 明示的にCapacityを指定
        auto str1 = format<128>("Value: {}", 42);
        std::cout << format("Explicit: {} (capacity={})\n", str1.c_str(), str1.capacity()).c_str();

        // 自動計算
        auto str2 = format("Value: {}", 42);
        std::cout << format("Auto:     {} (capacity={})\n", str2.c_str(), str2.capacity()).c_str();

        std::cout << "\n自動計算により、必要最小限のメモリで済む\n";
    }

    std::cout << "\n--- 様々な型での自動計算 ---\n";
    {
        auto str1 = format("Bool: {}", true);
        std::cout << format("{} (capacity={})\n", str1.c_str(), str1.capacity()).c_str();

        auto str2 = format("Char: {}", 'A');
        std::cout << format("{} (capacity={})\n", str2.c_str(), str2.capacity()).c_str();

        auto str3 = format("String: {}, Int: {}, Bool: {}", "test", 123, false);
        std::cout << format("{} (capacity={})\n", str3.c_str(), str3.capacity()).c_str();
    }

    std::cout << "\n--- 容量計算の仕組み ---\n";
    std::cout << "必要容量 = フォーマット文字列の長さ + 各引数の最大文字列長 + null終端\n\n";

    {
        // "Value: {}" = 8文字（{}は除く）
        // int32_tの最大長 = 11文字（"-2147483648"）
        // 合計 = 8 + 11 + 1 = 20
        auto str = format("Value: {}", 42);
        std::cout << "例: \"Value: {}\" + int32_t\n";
        std::cout << "  フォーマット文字列: 8文字（'Value: '）\n";
        std::cout << "  int32_t最大長: 11文字\n";
        std::cout << "  null終端: 1文字\n";
        std::cout << format("  合計容量: {}\n", str.capacity()).c_str();
        std::cout << format("  実際の長さ: {} ('{}')\n", str.byte_length(), str.c_str()).c_str();
    }

    std::cout << "\n--- format_toでの自動計算 ---\n";
    {
        // 出力先バッファを指定する場合
        FixedString<128> buffer;
        format_to(buffer, "Value: {}", 42);
        std::cout << format("Buffer指定: {}\n", buffer.c_str()).c_str();

        // 自動計算版（新しいFixedStringを返す）
        auto result = format_to("Value: {}", 42);
        std::cout << format("Auto: {} (capacity={})\n", result.c_str(), result.capacity()).c_str();
    }

    std::cout << "\n--- 使い分けのガイドライン ---\n";
    std::cout << "1. 自動計算 format(...)\n";
    std::cout << "   - 最小限のメモリ使用\n";
    std::cout << "   - 容量を気にする必要なし\n";
    std::cout << "   - 推奨される使用法\n";
    std::cout << "\n";
    std::cout << "2. 明示的指定 format<N>(...)\n";
    std::cout << "   - 大きめのバッファを確保したい場合\n";
    std::cout << "   - 容量を厳密に制御したい場合\n";
    std::cout << "\n";
    std::cout << "3. fmt(...)\n";
    std::cout << "   - デフォルト容量256\n";
    std::cout << "   - 簡潔な記述\n";
    std::cout << "   - 一般的な用途向け\n";

    std::cout << "\n--- メモリ効率の比較 ---\n";
    {
        // 短い文字列の場合
        auto auto_str = format("ID: {}", 1);
        auto fixed_str = format<256>("ID: {}", 1);
        auto fmt_str = fmt("ID: {}", 1);

        std::cout << "短い文字列 'ID: 1' のメモリ使用量:\n";
        std::cout << format("  自動計算:     {} bytes\n", auto_str.capacity()).c_str();
        std::cout << format("  明示的(256):  {} bytes\n", fixed_str.capacity()).c_str();
        std::cout << format("  fmt(256):     {} bytes\n", fmt_str.capacity()).c_str();
        std::cout << "  → 自動計算が最も効率的\n";
    }

    std::cout << "\n--- 制限事項 ---\n";
    std::cout << "・const char*やstd::string_viewは最大64文字と仮定\n";
    std::cout << "・実際の文字列長が64文字を超える場合、切り詰められる可能性\n";
    std::cout << "・その場合は明示的にCapacityを指定することを推奨\n";

    return 0;
}
