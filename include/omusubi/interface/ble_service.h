#pragma once

#include <cstdint>
#include "omusubi/core/string_view.hpp"
#include "omusubi/core/fixed_string.hpp"
#include "ble_characteristic.hpp"

namespace omusubi {

/**
 * @brief BLE Service インターフェース
 */
class BLEService {
public:
    BLEService() = default;
    virtual ~BLEService() = default;
    BLEService(const BLEService&) = delete;
    BLEService& operator=(const BLEService&) = delete;
    BLEService(BLEService&&) = delete;
    BLEService& operator=(BLEService&&) = delete;
    
    /**
     * @brief Service UUIDを取得
     */
    virtual FixedString<64> get_uuid() const = 0;
    
    /**
     * @brief Characteristicを追加
     */
    virtual BLECharacteristic* add_characteristic(
        StringView uuid,
        uint16_t properties
    ) = 0;
    
    /**
     * @brief UUIDでCharacteristicを取得
     */
    virtual BLECharacteristic* get_characteristic(StringView uuid) = 0;
    
    /**
     * @brief Characteristic数を取得
     */
    virtual uint8_t get_characteristic_count() const = 0;
    
    /**
     * @brief インデックスでCharacteristicを取得
     */
    virtual BLECharacteristic* get_characteristic_at(uint8_t index) = 0;
};

}  // namespace omusubi