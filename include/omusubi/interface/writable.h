#pragma once

#include "omusubi/core/string_view.h"

namespace omusubi {

/**
 * @brief データ書き込みインターフェース
 *
 * シリアル通信、Bluetooth、ディスプレイなどにデータを出力する機能を提供します。
 *
 * 使用例:
 * @code
 * Writable* device = ctx.get_serial(0);
 *
 * // 文字列を出力
 * device->write("Hello"_sv);
 *
 * // 数値を出力
 * device->write(42);
 * device->write(3.14f);
 *
 * // 改行付きで出力
 * device->write_line("World"_sv);
 *
 * // バイナリデータを出力
 * const uint8_t data[] = {0x01, 0x02, 0x03};
 * device->write_bytes(data, 3);
 * @endcode
 *
 * @note このインターフェースを実装するクラス: SerialCommunication, BluetoothCommunication, Displayable
 */
class Writable {
public:
    Writable() = default;
    virtual ~Writable() = default;
    Writable(const Writable&) = delete;
    Writable& operator=(const Writable&) = delete;
    Writable(Writable&&) = delete;
    Writable& operator=(Writable&&) = delete;

    /** @brief 文字列を出力 */
    virtual void write(StringView text) = 0;

    /** @brief バイナリデータを出力 */
    virtual void write_bytes(const uint8_t* data, uint32_t length) = 0;

    /** @brief 符号付き整数を出力 */
    virtual void write(int32_t value) = 0;

    /** @brief 符号なし整数を出力 */
    virtual void write(uint32_t value) = 0;

    /** @brief 浮動小数点数を出力 */
    virtual void write(float value) = 0;

    /** @brief 文字列を出力して改行 */
    void write_line(StringView text) {
        write(text);
        write(StringView("\r\n", 2));
    }

    /** @brief 改行のみ出力 */
    void write_line() {
        write(StringView("\r\n", 2));
    }
};

}  // namespace omusubi