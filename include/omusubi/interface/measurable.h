#pragma once

#include "omusubi/core/types.h"

namespace omusubi {

/**
 * @brief 1次元センサーインターフェース
 *
 * 温度、湿度、気圧など、単一の値を持つセンサーを扱います。
 *
 * 使用例:
 * @code
 * Measurable1D* sensor = ctx.get_temperature_sensor();
 *
 * if (sensor) {
 *     float temperature = sensor->get_value();
 *     serial->write("Temperature: "_sv);
 *     serial->write(temperature);
 *     serial->write_line(" °C"_sv);
 * }
 * @endcode
 */
class Measurable1D {
public:
    Measurable1D() = default;
    virtual ~Measurable1D() = default;
    Measurable1D(const Measurable1D&) = delete;
    Measurable1D& operator=(const Measurable1D&) = delete;
    Measurable1D(Measurable1D&&) = delete;
    Measurable1D& operator=(Measurable1D&&) = delete;

    /** @brief センサー値を取得 @return センサーの測定値 */
    virtual float get_value() const = 0;
};

/**
 * @brief 3次元センサーインターフェース
 *
 * 加速度センサー、ジャイロスコープ、磁気センサーなど、X/Y/Z軸の3次元データを持つセンサーを扱います。
 *
 * 使用例:
 * @code
 * Measurable3D* accel = ctx.get_accelerometer();
 *
 * if (accel) {
 *     // 3軸まとめて取得
 *     Vector3 acc = accel->get_values();
 *     serial->write("X: "_sv);
 *     serial->write(acc.x);
 *     serial->write(", Y: "_sv);
 *     serial->write(acc.y);
 *     serial->write(", Z: "_sv);
 *     serial->write_line(acc.z);
 *
 *     // 個別に取得
 *     float x = accel->get_x();
 *     float y = accel->get_y();
 *     float z = accel->get_z();
 * }
 * @endcode
 *
 * @note このインターフェースを実装するクラス: 加速度センサー、ジャイロスコープ
 */
class Measurable3D {
public:
    Measurable3D() = default;
    virtual ~Measurable3D() = default;
    Measurable3D(const Measurable3D&) = delete;
    Measurable3D& operator=(const Measurable3D&) = delete;
    Measurable3D(Measurable3D&&) = delete;
    Measurable3D& operator=(Measurable3D&&) = delete;

    /** @brief X/Y/Z軸の値をまとめて取得 @return 3次元ベクトル */
    virtual Vector3 get_values() const = 0;

    /** @brief X軸の値を取得 @return X軸の測定値 */
    virtual float get_x() const = 0;

    /** @brief Y軸の値を取得 @return Y軸の測定値 */
    virtual float get_y() const = 0;

    /** @brief Z軸の値を取得 @return Z軸の測定値 */
    virtual float get_z() const = 0;
};

}  // namespace omusubi