// FixedBuffer<N> の単体テスト

#include <omusubi/core/fixed_buffer.hpp>

#include "test_framework.hpp"

namespace fixed_buffer_test {

using namespace omusubi;
using namespace test;

void test_fixed_buffer_basic() {
    test_section("基本機能");

    // デフォルトコンストラクタ
    FixedBuffer<32> buf;
    TEST_ASSERT_EQ(buf.size(), 0U, "デフォルト構築のバッファは空");
    TEST_ASSERT(buf.is_empty(), "is_empty()がtrue");
    TEST_ASSERT_EQ(buf.capacity(), 32U, "容量は32");
}

void test_fixed_buffer_append() {
    test_section("追加操作");

    FixedBuffer<16> buf;

    // 1バイト追加
    TEST_ASSERT(buf.append(0x42), "1バイト追加成功");
    TEST_ASSERT_EQ(buf.size(), 1U, "追加後のサイズ");
    TEST_ASSERT_EQ(buf[0], 0x42, "追加した値が正しい");

    // 複数バイト追加
    TEST_ASSERT(buf.append(0x43), "2バイト目追加");
    TEST_ASSERT(buf.append(0x44), "3バイト目追加");
    TEST_ASSERT_EQ(buf.size(), 3U, "複数追加後のサイズ");
    TEST_ASSERT_EQ(buf[2], 0x44, "最後に追加した値");
}

void test_fixed_buffer_capacity() {
    test_section("容量制限");

    FixedBuffer<4> buf;

    // 容量いっぱいまで追加
    TEST_ASSERT(buf.append(0x01), "1バイト目追加");
    TEST_ASSERT(buf.append(0x02), "2バイト目追加");
    TEST_ASSERT(buf.append(0x03), "3バイト目追加");
    TEST_ASSERT(buf.append(0x04), "4バイト目追加");
    TEST_ASSERT_EQ(buf.size(), 4U, "容量いっぱい");

    // 容量超過
    TEST_ASSERT(!buf.append(0x05), "容量超過の追加は失敗");
    TEST_ASSERT_EQ(buf.size(), 4U, "容量超過後もサイズは変わらない");
}

void test_fixed_buffer_clear() {
    test_section("クリア操作");

    FixedBuffer<16> buf;
    buf.append(0x01);
    buf.append(0x02);
    buf.append(0x03);
    TEST_ASSERT_EQ(buf.size(), 3U, "クリア前のサイズ");

    buf.clear();
    TEST_ASSERT_EQ(buf.size(), 0U, "クリア後のサイズは0");
    TEST_ASSERT(buf.is_empty(), "クリア後はis_empty()がtrue");

    // クリア後の再利用
    TEST_ASSERT(buf.append(0xFF), "クリア後に再度追加可能");
    TEST_ASSERT_EQ(buf.size(), 1U, "再追加後のサイズ");
}

void test_fixed_buffer_access() {
    test_section("アクセス操作");

    FixedBuffer<8> buf;
    buf.append(0x10);
    buf.append(0x20);
    buf.append(0x30);

    // []演算子
    TEST_ASSERT_EQ(buf[0], 0x10, "要素アクセス [0]");
    TEST_ASSERT_EQ(buf[1], 0x20, "要素アクセス [1]");
    TEST_ASSERT_EQ(buf[2], 0x30, "要素アクセス [2]");

    // 範囲外アクセス（0を返す）
    TEST_ASSERT_EQ(buf[100], 0, "範囲外アクセスは0を返す");

    // data()
    const uint8_t* data = buf.data();
    TEST_ASSERT_EQ(data[0], 0x10, "data()でポインタアクセス");
}

void test_fixed_buffer_iteration() {
    test_section("イテレータ");

    FixedBuffer<8> buf;
    buf.append(0x01);
    buf.append(0x02);
    buf.append(0x03);

    // 範囲for文
    int sum = 0;
    for (uint8_t val : buf) {
        sum += val;
    }
    TEST_ASSERT_EQ(sum, 6, "範囲for文での要素アクセス");

    // begin/end
    TEST_ASSERT_EQ(*buf.begin(), 0x01, "begin()で最初の要素");
    TEST_ASSERT_EQ(buf.end() - buf.begin(), 3, "end() - begin()はサイズと一致");
}

void test_fixed_buffer_span_conversion() {
    test_section("span変換");

    FixedBuffer<16> buf;
    buf.append(0xAA);
    buf.append(0xBB);
    buf.append(0xCC);

    // as_span (読み取り専用)
    auto span_const = buf.as_span();
    TEST_ASSERT_EQ(span_const.size(), 3U, "const spanのサイズ");
    TEST_ASSERT_EQ(span_const[0], 0xAA, "const spanの要素アクセス");

    // from_span
    FixedBuffer<16> buf2;
    uint8_t data[] = {0x11, 0x22, 0x33, 0x44};
    span<const uint8_t> s(data);
    buf2.from_span(s);

    TEST_ASSERT_EQ(buf2.size(), 4U, "from_span後のサイズ");
    TEST_ASSERT_EQ(buf2[0], 0x11, "from_span後の要素");
    TEST_ASSERT_EQ(buf2[3], 0x44, "from_span後の最後の要素");
}

void test_fixed_buffer_from_span_truncate() {
    test_section("from_spanの切り詰め");

    FixedBuffer<4> buf;
    uint8_t data[] = {0x01, 0x02, 0x03, 0x04, 0x05, 0x06};
    span<const uint8_t> s(data);

    // 容量を超えるデータは切り詰められる
    buf.from_span(s);
    TEST_ASSERT_EQ(buf.size(), 4U, "容量を超える部分は切り詰め");
    TEST_ASSERT_EQ(buf[3], 0x04, "切り詰め後の最後の要素");
}

int main() {
    begin_tests("FixedBuffer<N>");

    test_fixed_buffer_basic();
    test_fixed_buffer_append();
    test_fixed_buffer_capacity();
    test_fixed_buffer_clear();
    test_fixed_buffer_access();
    test_fixed_buffer_iteration();
    test_fixed_buffer_span_conversion();
    test_fixed_buffer_from_span_truncate();

    return end_tests();
}

} // namespace fixed_buffer_test
