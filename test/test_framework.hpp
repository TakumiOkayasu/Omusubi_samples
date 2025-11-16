#pragma once

#include <cstdio>
#include <cstring>

namespace test {

// テスト結果カウンタ
struct TestResults {
    int total = 0;
    int passed = 0;
    int failed = 0;
};

static TestResults g_results;

// テスト開始
inline void begin_tests(const char* suite_name) {
    printf("\n========================================\n");
    printf("テストスイート: %s\n", suite_name);
    printf("========================================\n");
    g_results = TestResults {};
}

// テスト終了とサマリー表示
inline int end_tests() {
    printf("\n========================================\n");
    printf("結果: %d / %d テスト成功\n", g_results.passed, g_results.total);
    if (g_results.failed > 0) {
        printf("失敗: %d テスト\n", g_results.failed);
    }
    printf("========================================\n\n");
    return g_results.failed;
}

// アサーション実装
#define TEST_ASSERT(condition, message)                                                                                                                                            \
    do {                                                                                                                                                                           \
        g_results.total++;                                                                                                                                                         \
        if (condition) {                                                                                                                                                           \
            g_results.passed++;                                                                                                                                                    \
            printf("  ✓ %s\n", message);                                                                                                                                           \
        } else {                                                                                                                                                                   \
            g_results.failed++;                                                                                                                                                    \
            printf("  ✗ %s (行 %d)\n", message, __LINE__);                                                                                                                         \
        }                                                                                                                                                                          \
    } while (0)

#define TEST_ASSERT_EQ(actual, expected, message)                                                                                                                                  \
    do {                                                                                                                                                                           \
        g_results.total++;                                                                                                                                                         \
        if ((actual) == (expected)) {                                                                                                                                              \
            g_results.passed++;                                                                                                                                                    \
            printf("  ✓ %s\n", message);                                                                                                                                           \
        } else {                                                                                                                                                                   \
            g_results.failed++;                                                                                                                                                    \
            printf("  ✗ %s (行 %d) - 期待値: %d, 実際: %d\n", message, __LINE__, (int)(expected), (int)(actual));                                                                  \
        }                                                                                                                                                                          \
    } while (0)

#define TEST_ASSERT_STR_EQ(actual, expected, message)                                                                                                                              \
    do {                                                                                                                                                                           \
        g_results.total++;                                                                                                                                                         \
        if (strcmp(actual, expected) == 0) {                                                                                                                                       \
            g_results.passed++;                                                                                                                                                    \
            printf("  ✓ %s\n", message);                                                                                                                                           \
        } else {                                                                                                                                                                   \
            g_results.failed++;                                                                                                                                                    \
            printf("  ✗ %s (行 %d) - 期待値: \"%s\", 実際: \"%s\"\n", message, __LINE__, expected, actual);                                                                        \
        }                                                                                                                                                                          \
    } while (0)

#define TEST_ASSERT_FLOAT_EQ(actual, expected, epsilon, message)                                                                                                                   \
    do {                                                                                                                                                                           \
        g_results.total++;                                                                                                                                                         \
        const float diff = (actual) - (expected);                                                                                                                                  \
        if (diff < 0.0f ? -diff < (epsilon) : diff < (epsilon)) {                                                                                                                  \
            g_results.passed++;                                                                                                                                                    \
            printf("  ✓ %s\n", message);                                                                                                                                           \
        } else {                                                                                                                                                                   \
            g_results.failed++;                                                                                                                                                    \
            printf("  ✗ %s (行 %d) - 期待値: %f, 実際: %f\n", message, __LINE__, (double)(expected), (double)(actual));                                                            \
        }                                                                                                                                                                          \
    } while (0)

// テストセクション表示
inline void test_section(const char* section_name) {
    printf("\n[%s]\n", section_name);
}

} // namespace test
