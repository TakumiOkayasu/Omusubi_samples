#pragma once

#include <cstdint>
#include "omusubi/core/fixed_string.hpp"

namespace omusubi {

/**
 * @brief スキャン機能インターフェース
 *
 * Bluetooth、WiFi、BLEなどの周辺デバイス・ネットワークをスキャンする機能を提供します。
 *
 * 使用例:
 * @code
 * Scannable* device = ctx.get_wifi();
 *
 * // スキャン開始
 * device->start_scan();
 *
 * // 3秒間スキャン
 * ctx.delay(3000);
 *
 * // スキャン停止
 * device->stop_scan();
 *
 * // 見つかったデバイス数を取得
 * uint8_t count = device->get_found_count();
 *
 * // デバイス情報を取得
 * for (uint8_t i = 0; i < count; ++i) {
 *     FixedString<64> name = device->get_found_name(i);
 *     // デバイス名を表示など
 * }
 * @endcode
 *
 * @note このインターフェースを実装するクラス: BluetoothCommunication, WiFiCommunication, BLECommunication
 */
class Scannable {
public:
    Scannable() = default;
    virtual ~Scannable() = default;
    Scannable(const Scannable&) = delete;
    Scannable& operator=(const Scannable&) = delete;
    Scannable(Scannable&&) = delete;
    Scannable& operator=(Scannable&&) = delete;

    /** @brief スキャンを開始 */
    virtual void start_scan() = 0;

    /** @brief スキャンを停止 */
    virtual void stop_scan() = 0;

    /** @brief スキャン中かどうか確認 @return スキャン中ならtrue */
    virtual bool is_scanning() const = 0;

    /** @brief 見つかったデバイス・ネットワークの数 @return デバイス数 */
    virtual uint8_t get_found_count() const = 0;

    /** @brief 見つかったデバイス名を取得 @param index デバイスインデックス @return デバイス名 */
    virtual FixedString<64> get_found_name(uint8_t index) const = 0;
};

}  // namespace omusubi