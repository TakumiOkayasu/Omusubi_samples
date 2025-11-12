#pragma once

#include <cstdint>
#include "omusubi/core/string_view.hpp"
#include "omusubi/core/fixed_string.hpp"
#include "omusubi/interface/connectable.hpp"
#include "omusubi/interface/scannable.hpp"
#include "omusubi/interface/ble_service.hpp"

namespace omusubi {

/**
 * @brief BLE動作モード
 */
enum class BLEMode : uint8_t {
    idle,       ///< 未初期化
    central,    ///< Centralモード（クライアント）
    peripheral  ///< Peripheralモード（サーバー）
};

/**
 * @brief BLE通信インターフェース
 */
class BLECommunication
    : public Connectable
    , public Scannable {
public:
    BLECommunication() = default;
    ~BLECommunication() override = default;
    BLECommunication(const BLECommunication&) = delete;
    BLECommunication& operator=(const BLECommunication&) = delete;
    BLECommunication(BLECommunication&&) = delete;
    BLECommunication& operator=(BLECommunication&&) = delete;
    
    // ========================================
    // モード管理
    // ========================================
    
    /**
     * @brief Centralモードで初期化（クライアント）
     */
    virtual bool begin_central(StringView device_name) = 0;
    
    /**
     * @brief Peripheralモードで初期化（サーバー）
     */
    virtual bool begin_peripheral(StringView device_name) = 0;
    
    /**
     * @brief 現在のモードを取得
     */
    virtual BLEMode get_mode() const = 0;
    
    /**
     * @brief BLEを停止
     */
    virtual void end() = 0;
    
    // ========================================
    // Central（クライアント）モード
    // ========================================
    
    /**
     * @brief デバイス名で接続
     */
    virtual bool connect_to(StringView device_name, uint32_t timeout_ms = 0) = 0;
    
    /**
     * @brief MACアドレスで接続
     */
    virtual bool connect_to_address(StringView address, uint32_t timeout_ms = 0) = 0;
    
    /**
     * @brief スキャンで見つけたデバイスに接続
     */
    virtual bool connect_to_found(uint8_t index) = 0;
    
    /**
     * @brief 接続済みデバイスのサービスを取得
     */
    virtual BLEService* get_service(StringView uuid) = 0;
    
    /**
     * @brief 接続済みデバイスのサービス数を取得
     */
    virtual uint8_t get_service_count() const = 0;
    
    /**
     * @brief インデックスでサービスを取得
     */
    virtual BLEService* get_service_at(uint8_t index) = 0;
    
    // ========================================
    // Peripheral（サーバー）モード
    // ========================================
    
    /**
     * @brief サービスを追加
     */
    virtual BLEService* add_service(StringView uuid) = 0;
    
    /**
     * @brief Advertisingを開始
     */
    virtual bool start_advertising() = 0;
    
    /**
     * @brief Advertisingを停止
     */
    virtual void stop_advertising() = 0;
    
    /**
     * @brief Advertising中か確認
     */
    virtual bool is_advertising() const = 0;
    
    // ========================================
    // 共通情報
    // ========================================
    
    /**
     * @brief ローカルデバイス名を設定
     */
    virtual void set_local_name(StringView name) = 0;
    
    /**
     * @brief ローカルデバイス名を取得
     */
    virtual FixedString<64> get_local_name() const = 0;
    
    /**
     * @brief 接続済みデバイス名を取得
     */
    virtual FixedString<64> get_connected_device_name() const = 0;
    
    /**
     * @brief 接続済みデバイスのMACアドレスを取得
     */
    virtual FixedString<32> get_connected_device_address() const = 0;
    
    /**
     * @brief スキャンで見つけたデバイスのMACアドレスを取得
     */
    virtual FixedString<32> get_found_address(uint8_t index) const = 0;
    
    /**
     * @brief スキャンで見つけたデバイスの信号強度を取得
     */
    virtual int32_t get_found_signal_strength(uint8_t index) const = 0;
    
    /**
     * @brief スキャンで見つけたデバイスがConnectable広告か確認
     */
    virtual bool is_found_connectable(uint8_t index) const = 0;
};

}  // namespace omusubi