#pragma once

#include "omusubi/core/fixed_string.hpp"
#include "omusubi/core/fixed_buffer.hpp"

namespace omusubi {

/**
 * @brief データ読み取りインターフェース
 *
 * シリアル通信、Bluetooth、WiFiなどのデバイスからデータを読み取る機能を提供します。
 *
 * 使用例:
 * @code
 * Readable* device = ctx.get_serial(0);
 *
 * // データの有無を確認
 * if (device->has_data()) {
 *     // 1行読み取り
 *     FixedString<256> line = device->read_line();
 *
 *     // バイナリデータ読み取り
 *     FixedBuffer<256> data = device->read_bytes();
 * }
 *
 * // データが来るまで待機
 * FixedString<256> text = device->read_string_wait();
 * @endcode
 *
 * @note このインターフェースを実装するクラス: SerialCommunication, BluetoothCommunication
 */
class Readable {
public:
    Readable() = default;
    virtual ~Readable() = default;
    Readable(const Readable&) = delete;
    Readable& operator=(const Readable&) = delete;
    Readable(Readable&&) = delete;
    Readable& operator=(Readable&&) = delete;

    /** @brief バッファ内の文字列を読み取る（非ブロッキング） */
    virtual FixedString<256> read_string() = 0;

    /** @brief 改行まで読み取る（非ブロッキング） */
    virtual FixedString<256> read_line() = 0;

    /** @brief データが来るまで待機して文字列を読み取る（ブロッキング） */
    virtual FixedString<256> read_string_wait() = 0;

    /** @brief データが来るまで待機して1行読み取る（ブロッキング） */
    virtual FixedString<256> read_line_wait() = 0;

    /** @brief バイナリデータを読み取る */
    virtual FixedBuffer<256> read_bytes() = 0;

    /** @brief 読み取り可能なデータがあるか確認 */
    virtual bool has_data() const = 0;
};

}  // namespace omusubi