#pragma once

#include <cstdint>

namespace omusubi {

// 前方宣言
class ConnectableContext;
class ScannableContext;
class SensorContext;
class InputContext;
class OutputContext;
class SystemInfoContext;
class PowerContext;

/**
 * @brief システムコンテキスト
 */
class SystemContext {
public:
    virtual ~SystemContext() = default;

    SystemContext(const SystemContext&) = delete;
    SystemContext& operator=(const SystemContext&) = delete;
    SystemContext(SystemContext&&) = delete;
    SystemContext& operator=(SystemContext&&) = delete;

    // ========================================
    // システム制御
    // ========================================

    /** @brief システムを初期化 */
    virtual void begin() = 0;

    /** @brief システム状態を更新 */
    virtual void update() = 0;

    /** @brief 待機（ミリ秒） */
    virtual void delay(uint32_t ms) = 0;

    /** @brief システムをリセット */
    virtual void reset() = 0;

    // ========================================
    // カテゴリ別コンテキストアクセス
    // ========================================

    /** @brief 接続可能なデバイスのコンテキスト */
    [[nodiscard]] virtual ConnectableContext& get_connectable_context() const = 0;

    /** @brief スキャン可能なデバイスのコンテキスト */
    [[nodiscard]] virtual ScannableContext& get_scannable_context() const = 0;

    /** @brief センサーデバイスのコンテキスト */
    [[nodiscard]] virtual SensorContext& get_sensor_context() const = 0;

    /** @brief 入力デバイスのコンテキスト */
    [[nodiscard]] virtual InputContext& get_input_context() const = 0;

    /** @brief 出力デバイスのコンテキスト */
    [[nodiscard]] virtual OutputContext& get_output_context() const = 0;

    /** @brief システム情報コンテキスト */
    [[nodiscard]] virtual SystemInfoContext& get_system_info_context() const = 0;

    /** @brief 電源管理コンテキスト */
    [[nodiscard]] virtual PowerContext& get_power_context() const = 0;

protected:
    SystemContext() = default;
};

/**
 * @brief グローバルSystemContextを取得
 */
SystemContext& get_system_context();

} // namespace omusubi
