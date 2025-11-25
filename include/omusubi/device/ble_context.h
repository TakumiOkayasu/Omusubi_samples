#pragma once

#include <omusubi/interface/connectable.h>
#include <omusubi/interface/scannable.h>

namespace omusubi {

/**
 * @brief BLE (Bluetooth Low Energy) 通信デバイス
 */
class BLEContext : public Connectable, public Scannable {
public:
    BLEContext() = default;
    ~BLEContext() override = default;
    BLEContext(const BLEContext&) = delete;
    BLEContext& operator=(const BLEContext&) = delete;
    BLEContext(BLEContext&&) = delete;
    BLEContext& operator=(BLEContext&&) = delete;

    // Connectable interface
    bool connect() override = 0;
    void disconnect() override = 0;
    [[nodiscard]] bool is_connected() const override = 0;

    // Scannable interface
    void start_scan() override = 0;
    void stop_scan() override = 0;
    [[nodiscard]] uint8_t get_found_count() const override = 0;
    [[nodiscard]] std::string_view get_found_name(uint8_t index) const override = 0;
    [[nodiscard]] int32_t get_found_signal_strength(uint8_t index) const override = 0;
};

} // namespace omusubi
