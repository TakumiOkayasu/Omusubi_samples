// Vector3 の単体テスト

#include <omusubi/core/types.h>

#include "test_framework.hpp"

namespace vector3_test {

using namespace omusubi;
using namespace test;

void test_vector3_basic() {
    test_section("基本機能");

    // デフォルトコンストラクタ
    Vector3 v1;
    TEST_ASSERT_FLOAT_EQ(v1.x, 0.0f, 0.001f, "デフォルトコンストラクタ x = 0");
    TEST_ASSERT_FLOAT_EQ(v1.y, 0.0f, 0.001f, "デフォルトコンストラクタ y = 0");
    TEST_ASSERT_FLOAT_EQ(v1.z, 0.0f, 0.001f, "デフォルトコンストラクタ z = 0");

    // 値指定コンストラクタ
    Vector3 v2(1.0f, 2.0f, 3.0f);
    TEST_ASSERT_FLOAT_EQ(v2.x, 1.0f, 0.001f, "値指定コンストラクタ x = 1.0");
    TEST_ASSERT_FLOAT_EQ(v2.y, 2.0f, 0.001f, "値指定コンストラクタ y = 2.0");
    TEST_ASSERT_FLOAT_EQ(v2.z, 3.0f, 0.001f, "値指定コンストラクタ z = 3.0");
}

void test_vector3_constexpr() {
    test_section("constexpr対応");

    // コンパイル時定数として使用可能
    constexpr Vector3 v1;
    constexpr Vector3 v2(1.0f, 2.0f, 3.0f);

    TEST_ASSERT_FLOAT_EQ(v1.x, 0.0f, 0.001f, "constexpr デフォルト x");
    TEST_ASSERT_FLOAT_EQ(v2.x, 1.0f, 0.001f, "constexpr 値指定 x");
    TEST_ASSERT_FLOAT_EQ(v2.y, 2.0f, 0.001f, "constexpr 値指定 y");
    TEST_ASSERT_FLOAT_EQ(v2.z, 3.0f, 0.001f, "constexpr 値指定 z");
}

void test_vector3_assignment() {
    test_section("代入操作");

    Vector3 v1(1.0f, 2.0f, 3.0f);
    Vector3 v2;

    // コピー代入
    v2 = v1;
    TEST_ASSERT_FLOAT_EQ(v2.x, 1.0f, 0.001f, "コピー代入 x");
    TEST_ASSERT_FLOAT_EQ(v2.y, 2.0f, 0.001f, "コピー代入 y");
    TEST_ASSERT_FLOAT_EQ(v2.z, 3.0f, 0.001f, "コピー代入 z");

    // 個別の値変更
    v2.x = 10.0f;
    v2.y = 20.0f;
    v2.z = 30.0f;
    TEST_ASSERT_FLOAT_EQ(v2.x, 10.0f, 0.001f, "個別変更 x");
    TEST_ASSERT_FLOAT_EQ(v2.y, 20.0f, 0.001f, "個別変更 y");
    TEST_ASSERT_FLOAT_EQ(v2.z, 30.0f, 0.001f, "個別変更 z");
}

void test_vector3_sensor_use_case() {
    test_section("センサーデータのユースケース");

    // 加速度センサーのデータ
    Vector3 accel(0.0f, 0.0f, 9.81f); // 重力加速度
    TEST_ASSERT_FLOAT_EQ(accel.z, 9.81f, 0.01f, "重力加速度のz成分");

    // ジャイロセンサーのデータ
    Vector3 gyro(0.1f, -0.2f, 0.05f); // 回転速度
    TEST_ASSERT_FLOAT_EQ(gyro.x, 0.1f, 0.001f, "ジャイロx成分");
    TEST_ASSERT_FLOAT_EQ(gyro.y, -0.2f, 0.001f, "ジャイロy成分（負の値）");

    // 磁気センサーのデータ
    Vector3 mag(25.5f, -10.3f, 40.2f);
    TEST_ASSERT_FLOAT_EQ(mag.x, 25.5f, 0.01f, "磁気センサーx成分");
}

void test_vector3_negative_values() {
    test_section("負の値のテスト");

    Vector3 v(-1.0f, -2.0f, -3.0f);
    TEST_ASSERT_FLOAT_EQ(v.x, -1.0f, 0.001f, "負の値 x");
    TEST_ASSERT_FLOAT_EQ(v.y, -2.0f, 0.001f, "負の値 y");
    TEST_ASSERT_FLOAT_EQ(v.z, -3.0f, 0.001f, "負の値 z");
}

void test_vector3_zero_and_small_values() {
    test_section("ゼロと極小値");

    Vector3 v1(0.0f, 0.0f, 0.0f);
    TEST_ASSERT_FLOAT_EQ(v1.x, 0.0f, 0.001f, "ゼロベクトル x");
    TEST_ASSERT_FLOAT_EQ(v1.y, 0.0f, 0.001f, "ゼロベクトル y");
    TEST_ASSERT_FLOAT_EQ(v1.z, 0.0f, 0.001f, "ゼロベクトル z");

    Vector3 v2(0.001f, 0.002f, 0.003f);
    TEST_ASSERT_FLOAT_EQ(v2.x, 0.001f, 0.0001f, "極小値 x");
    TEST_ASSERT_FLOAT_EQ(v2.y, 0.002f, 0.0001f, "極小値 y");
    TEST_ASSERT_FLOAT_EQ(v2.z, 0.003f, 0.0001f, "極小値 z");
}

int main() {
    begin_tests("Vector3");

    test_vector3_basic();
    test_vector3_constexpr();
    test_vector3_assignment();
    test_vector3_sensor_use_case();
    test_vector3_negative_values();
    test_vector3_zero_and_small_values();

    return end_tests();
}

} // namespace vector3_test
