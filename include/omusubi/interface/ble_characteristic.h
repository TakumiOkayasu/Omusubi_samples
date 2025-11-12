#pragma once

#include <cstdint>
#include "omusubi/core/string_view.hpp"
#include "omusubi/core/fixed_string.hpp"
#include "omusubi/core/fixed_buffer.hpp"

namespace omusubi {

/**
 * @brief BLE Characteristicのプロパティ
 */
enum class BLECharacteristicProperty : uint16_t {
    read         = 0x0002,
    write        = 0x0008,
    notify       = 0x0010,
    indicate     = 0x0020,
    write_no_rsp = 0x0004
};

/**
 * @brief BLE Characteristic インターフェース
 */
class BLECharacteristic {
public:
    BLECharacteristic() = default;
    virtual ~BLECharacteristic() = default;
    BLECharacteristic(const BLECharacteristic&) = delete;
    BLECharacteristic& operator=(const BLECharacteristic&) = delete;
    BLECharacteristic(BLECharacteristic&&) = delete;
    BLECharacteristic& operator=(BLECharacteristic&&) = delete;
    
    /**
     * @brief UUIDを取得
     */
    virtual FixedString<64> get_uuid() const = 0;
    
    /**
     * @brief 値を読み取る
     */
    virtual FixedBuffer<512> read() const = 0;
    
    /**
     * @brief 値を書き込む
     */
    virtual bool write(const uint8_t* data, uint32_t length) = 0;
    
    /**
     * @brief 文字列として読み取る
     */
    virtual FixedString<256> read_string() const = 0;
    
    /**
     * @brief 文字列として書き込む
     */
    virtual bool write_string(StringView value) = 0;
    
    /**
     * @brief 通知を送信（Serverの場合）
     */
    virtual bool notify(const uint8_t* data, uint32_t length) = 0;
    
    /**
     * @brief プロパティを取得
     */
    virtual uint16_t get_properties() const = 0;
    
    /**
     * @brief 読み取り可能か
     */
    bool can_read() const {
        return (get_properties() & static_cast<uint16_t>(BLECharacteristicProperty::read)) != 0;
    }
    
    /**
     * @brief 書き込み可能か
     */
    bool can_write() const {
        return (get_properties() & static_cast<uint16_t>(BLECharacteristicProperty::write)) != 0;
    }
    
    /**
     * @brief 通知可能か
     */
    bool can_notify() const {
        return (get_properties() & static_cast<uint16_t>(BLECharacteristicProperty::notify)) != 0;
    }
};

}  // namespace omusubi