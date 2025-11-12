#pragma once

namespace omusubi {

/**
 * @brief ボタン入力インターフェース
 *
 * ボタンやタッチパネルなどの押下可能な入力デバイスを扱います。
 *
 * 使用例:
 * @code
 * Pressable* button = ctx.get_button(0);
 *
 * // ボタンが押された瞬間を検出
 * if (button->was_pressed()) {
 *     // ボタン押下時の処理
 * }
 *
 * // ボタンが押されている間を検出
 * if (button->is_pressed()) {
 *     // ボタンが押されている間の処理
 * }
 *
 * // ボタンが離された瞬間を検出
 * if (button->was_released()) {
 *     // ボタンリリース時の処理
 * }
 * @endcode
 *
 * @note ctx.update()を呼ばないと状態が更新されないため、loop()内で必ずupdateを呼ぶこと
 */
class Pressable {
public:
    Pressable() = default;
    virtual ~Pressable() = default;
    Pressable(const Pressable&) = delete;
    Pressable& operator=(const Pressable&) = delete;
    Pressable(Pressable&&) = delete;
    Pressable& operator=(Pressable&&) = delete;

    /** @brief 現在押されているか @return 押されていればtrue */
    virtual bool is_pressed() const = 0;

    /** @brief 前回のupdate以降に押されたか @return 押されたならtrue（1回だけtrueを返す） */
    virtual bool was_pressed() = 0;

    /** @brief 前回のupdate以降に離されたか @return 離されたならtrue（1回だけtrueを返す） */
    virtual bool was_released() = 0;
};

}  // namespace omusubi