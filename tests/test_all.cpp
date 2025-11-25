// すべてのテストを実行するメインプログラム

#include <cstdio>

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
    printf("\n");
    printf("╔═══════════════════════════════════════╗\n");
    printf("║  Omusubi フレームワーク 単体テスト    ║\n");
    printf("╚═══════════════════════════════════════╝\n");

    int total_failures = 0;

    // 各テストを実行
    total_failures += span_test::main();
    total_failures += string_view_test::main();
    total_failures += fixed_string_test::main();
    total_failures += fixed_buffer_test::main();
    total_failures += vector3_test::main();

    // 最終結果
    printf("\n");
    printf("╔═══════════════════════════════════════╗\n");
    if (total_failures == 0) {
        printf("║  ✓ すべてのテストが成功しました       ║\n");
    } else {
        printf("║  ✗ %d 個のテストが失敗しました         ║\n", total_failures);
    }
    printf("╚═══════════════════════════════════════╝\n");
    printf("\n");

    return total_failures;
}
