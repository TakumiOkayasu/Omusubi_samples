#pragma once

namespace omusubi {

/**
 * @brief 接続管理インターフェース
 *
 * シリアル、Bluetooth、WiFiなどのデバイスの接続・切断を管理します。
 *
 * 使用例:
 * @code
 * Connectable* device = ctx.get_bluetooth();
 *
 * // 接続
 * if (device->connect()) {
 *     // 接続成功
 * }
 *
 * // 接続状態を確認
 * if (device->is_connected()) {
 *     // データ送受信など
 * }
 *
 * // 切断
 * device->disconnect();
 * @endcode
 *
 * @note このインターフェースを実装するクラス: SerialCommunication, BluetoothCommunication, WiFiCommunication, BLECommunication
 */
class Connectable {
public:
    Connectable() = default;
    virtual ~Connectable() = default;
    Connectable(const Connectable&) = delete;
    Connectable& operator=(const Connectable&) = delete;
    Connectable(Connectable&&) = delete;
    Connectable& operator=(Connectable&&) = delete;

    /** @brief デバイスに接続 @return 接続成功ならtrue */
    virtual bool connect() = 0;

    /** @brief デバイスから切断 */
    virtual void disconnect() = 0;

    /** @brief 接続中かどうか確認 @return 接続中ならtrue */
    virtual bool is_connected() const = 0;
};

}  // namespace omusubi