#!/bin/bash

# すべてのユニットテストを実行
# 注意: プロジェクトルートから `make test` を使用することを推奨
# このスクリプトはテストのサブセットを直接ビルド・実行するためのものです

echo "========================================"
echo "Omusubi Framework - All Unit Tests"
echo "========================================"
echo ""

# テスト結果を追跡
FAILED_TESTS=""

# テストファイルのリスト（doctest使用）
TESTS=(
    "test/core/test_result.cpp"
    "test/core/test_logger.cpp"
)

# 各テストをビルド・実行
for TEST_FILE in "${TESTS[@]}"; do
    TEST_NAME=$(basename "$TEST_FILE" .cpp)
    TEST_BIN="/tmp/${TEST_NAME}"

    echo "----------------------------------------"
    echo "Building: $TEST_NAME"
    echo "----------------------------------------"

    # ビルド（C++17、doctest使用）
    if ! clang++ -std=c++17 -I/workspace/include "/workspace/$TEST_FILE" -o "$TEST_BIN" 2>&1; then
        echo "Build failed: $TEST_FILE"
        FAILED_TESTS="${FAILED_TESTS}${TEST_NAME} (build failed)\n"
        continue
    fi

    echo "Build successful"
    echo ""

    # 実行
    echo "Running: $TEST_NAME"
    echo ""

    if ! "$TEST_BIN" 2>&1; then
        echo "Test failed: $TEST_NAME"
        FAILED_TESTS="${FAILED_TESTS}${TEST_NAME}\n"
    else
        echo "Test passed: $TEST_NAME"
    fi

    echo ""
done

# 最終結果
echo "========================================"
echo "Final Results"
echo "========================================"
echo ""

if [ -z "$FAILED_TESTS" ]; then
    echo "All tests passed!"
    exit 0
else
    echo "Some tests failed:"
    echo -e "$FAILED_TESTS"
    exit 1
fi
