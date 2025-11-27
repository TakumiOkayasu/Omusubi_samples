// すべてのテストを実行するメインプログラム

#include <iostream>
#include <omusubi/core/format.hpp>

using namespace omusubi;

// 各テストのmain関数を外部宣言
namespace span_test {
extern int main();
}

namespace string_view_test {
extern int main();
}

namespace fixed_string_test {
extern int main();
}

namespace fixed_buffer_test {
extern int main();
}

namespace vector3_test {
extern int main();
}

int main() {
    std::cout << "\n";
    std::cout << "╔═══════════════════════════════════════╗\n";
    std::cout << "║  Omusubi フレームワーク 単体テスト    ║\n";
    std::cout << "╚═══════════════════════════════════════╝\n";

    int total_failures = 0;

    // 各テストを実行
    total_failures += span_test::main();
    total_failures += string_view_test::main();
    total_failures += fixed_string_test::main();
    total_failures += fixed_buffer_test::main();
    total_failures += vector3_test::main();

    // 最終結果
    std::cout << "\n";
    std::cout << "╔═══════════════════════════════════════╗\n";
    if (total_failures == 0) {
        std::cout << "║  ✓ すべてのテストが成功しました       ║\n";
    } else {
        std::cout << format("║  ✗ {} 個のテストが失敗しました         ║\n", total_failures).c_str();
    }
    std::cout << "╚═══════════════════════════════════════╝\n";
    std::cout << "\n";

    return total_failures;
}
