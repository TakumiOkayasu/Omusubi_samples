#include <omusubi/omusubi.hpp>

using namespace omusubi;
using namespace omusubi::literals;

// カスタムサービスUUID
constexpr const char* SERVICE_UUID = "4fafc201-1fb5-459e-8fcc-c5c9c331914b";
constexpr const char* CHAR_UUID = "beb5483e-36e1-4688-b7f5-ea07361b26a8";

void setup() {
    SystemContext& ctx = get_system_context();
    ctx.begin();
    
    SerialCommunication* serial = ctx.get_serial(0);
    BLECommunication* ble = ctx.get_ble();
    Displayable* display = ctx.get_display();
    
    if (serial) {
        serial->write_line("=== BLE Peripheral ==="_sv);
    }
    
    if (display) {
        display->clear();
        display->set_cursor(0, 0);
        display->set_text_size(2);
        display->write_line("BLE Server"_sv);
        display->set_text_size(1);
    }
    
    if (ble) {
        // Peripheralモードで初期化
        ble->begin_peripheral("M5Stack-BLE-Server"_sv);
        
        // サービスを追加
        BLEService* service = ble->add_service(
            StringView::from_c_string(SERVICE_UUID)
        );
        
        if (service) {
            // Characteristicを追加
            BLECharacteristic* characteristic = service->add_characteristic(
                StringView::from_c_string(CHAR_UUID),
                static_cast<uint16_t>(BLECharacteristicProperty::read) |
                static_cast<uint16_t>(BLECharacteristicProperty::write) |
                static_cast<uint16_t>(BLECharacteristicProperty::notify)
            );
            
            if (characteristic) {
                // 初期値を設定
                characteristic->write_string("Hello from M5Stack!"_sv);
                
                if (serial) {
                    serial->write_line("Characteristic added"_sv);
                }
            }
            
            // Advertisingを開始
            if (ble->start_advertising()) {
                if (serial) {
                    serial->write_line("Advertising started"_sv);
                }
                
                if (display) {
                    display->write_line();
                    display->write_line("Advertising..."_sv);
                    display->write_line(ble->get_local_name());
                }
            }
        }
    }
}

void loop() {
    SystemContext& ctx = get_system_context();
    ctx.update();
    
    SerialCommunication* serial = ctx.get_serial(0);
    BLECommunication* ble = ctx.get_ble();
    Displayable* display = ctx.get_display();
    Pressable* button_a = ctx.get_button(0);
    
    // ボタンAで通知送信
    if (button_a && button_a->was_pressed()) {
        if (ble && ble->is_connected()) {
            BLEService* service = ble->get_service(
                StringView::from_c_string(SERVICE_UUID)
            );
            
            if (service) {
                BLECharacteristic* characteristic = service->get_characteristic(
                    StringView::from_c_string(CHAR_UUID)
                );
                
                if (characteristic && characteristic->can_notify()) {
                    char msg[] = "Button pressed!";
                    characteristic->notify(
                        reinterpret_cast<uint8_t*>(msg),
                        sizeof(msg) - 1
                    );
                    
                    if (serial) {
                        serial->write_line("Notification sent"_sv);
                    }
                    
                    if (display) {
                        display->write_line("Notified!"_sv);
                    }
                }
            }
        }
    }
    
    // 接続状態を表示
    static bool last_connected = false;
    bool current_connected = ble && ble->is_connected();
    
    if (current_connected != last_connected) {
        if (serial) {
            serial->write("Connection: "_sv);
            serial->write_line(current_connected ? "Connected"_sv : "Disconnected"_sv);
        }
        
        last_connected = current_connected;
    }
    
    ctx.delay(10);
}