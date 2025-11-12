#pragma once

#include <cstdint>
#include "writable.h"

namespace omusubi {

/**
 * @brief ディスプレイ出力インターフェース
 *
 * LCD、OLED、TFTなどのディスプレイに文字や図形を表示する機能を提供します。
 * Writableインターフェースを継承しているため、write()メソッドも使用できます。
 *
 * 使用例:
 * @code
 * Displayable* display = ctx.get_display();
 *
 * if (display) {
 *     // 画面クリア
 *     display->clear();
 *
 *     // カーソル位置を設定
 *     display->set_cursor(0, 0);
 *
 *     // テキストサイズと色を設定
 *     display->set_text_size(2);
 *     display->set_text_color(0xFFFF);  // 白
 *
 *     // 文字列を表示（Writableから継承）
 *     display->write_line("Hello, World!"_sv);
 *     display->write("Temperature: "_sv);
 *     display->write(25.5f);
 *     display->write_line(" °C"_sv);
 *
 *     // 画面サイズを取得
 *     uint16_t width = display->get_width();
 *     uint16_t height = display->get_height();
 * }
 * @endcode
 *
 * @note カラーコードは16ビットRGB565形式（例: 0xFFFF=白、0xF800=赤、0x07E0=緑、0x001F=青）
 */
class Displayable : public Writable {
public:
    Displayable() = default;
    ~Displayable() override = default;
    Displayable(const Displayable&) = delete;
    Displayable& operator=(const Displayable&) = delete;
    Displayable(Displayable&&) = delete;
    Displayable& operator=(Displayable&&) = delete;

    /** @brief 画面をクリア */
    virtual void clear() = 0;

    /** @brief カーソル位置を設定 @param x X座標 @param y Y座標 */
    virtual void set_cursor(int32_t x, int32_t y) = 0;

    /** @brief テキストサイズを設定 @param size サイズ（1=標準、2=2倍など） */
    virtual void set_text_size(uint8_t size) = 0;

    /** @brief テキスト色を設定 @param color RGB565形式のカラーコード */
    virtual void set_text_color(uint32_t color) = 0;

    /** @brief 背景色を設定 @param color RGB565形式のカラーコード */
    virtual void set_background_color(uint32_t color) = 0;

    /** @brief 画面幅を取得 @return 幅（ピクセル） */
    virtual uint16_t get_width() const = 0;

    /** @brief 画面高さを取得 @return 高さ（ピクセル） */
    virtual uint16_t get_height() const = 0;
};

}  // namespace omusubi