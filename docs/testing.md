# テストガイド

このドキュメントでは、Omusubiフレームワークにおけるテストの書き方と実行方法を定義します。

## 目次

1. [テスト方針](#テスト方針)
2. [テストフレームワーク](#テストフレームワーク)
3. [テストの書き方](#テストの書き方)
4. [命名規則](#命名規則)
5. [テスト構造](#テスト構造)
6. [アサーション](#アサーション)
7. [テストカバレッジ](#テストカバレッジ)
8. [モックとスタブ](#モックとスタブ)
9. [組み込み環境でのテスト](#組み込み環境でのテスト)
10. [実機テスト](#実機テスト)

---

## テスト方針

### 1. 単体テストの重要性

**Omusubiはヘッダーオンリーの抽象化フレームワークのため、単体テストが品質保証の要。**

**テストが必要な理由:**
- コンパイル時エラーを早期検出
- `constexpr`関数の正しさを検証
- 型安全性の保証
- リファクタリング時の回帰防止

### 2. テストファースト開発

**新機能実装前にテストを書く習慣を推奨。**

```cpp
// 1. テストを先に書く
void test_new_feature() {
    test_section("新機能");

    FixedString<32> s;
    TEST_ASSERT(s.starts_with("H"_sv), "starts_with()が動作する");
}

// 2. 実装を追加
// 3. テストが通ることを確認
```

**利点:**
- 要件を明確化できる
- 実装の設計が改善される
- テスト可能なコードになる

### 3. テスト範囲

**単体テスト対象:**
- Core types (`span<T>`, `StringView`, `FixedString<N>`, `FixedBuffer<N>`, `Vector3`)
- Utility functions
- Interface contracts

**統合テスト対象:**
- Platform implementations (M5Stack, Arduino, etc.)
- Device contexts (Serial, WiFi, Bluetooth, etc.)
- System context

**テスト不要:**
- Pure virtual interfaces (コンパイル時にチェック済み)
- Trivial getters/setters (実装がほぼない)

---

## テストフレームワーク

Omusubiは独自の軽量テストフレームワーク `test_framework.hpp` を使用します。

### フレームワークの特徴

```cpp
namespace test {

// テストスイート開始
void begin_tests(const char* suite_name);

// テストスイート終了 (失敗数を返す)
int end_tests();

// テストセクション表示
void test_section(const char* section_name);

// アサーションマクロ
TEST_ASSERT(condition, message);
TEST_ASSERT_EQ(actual, expected, message);
TEST_ASSERT_STR_EQ(actual, expected, message);
TEST_ASSERT_FLOAT_EQ(actual, expected, epsilon, message);

} // namespace test
```

**利点:**
- ヘッダーオンリー (依存関係なし)
- 組み込みシステムで動作 (例外不要)
- シンプルで理解しやすい
- 日本語メッセージ対応

---

## テストの書き方

### 基本パターン

**すべてのテストファイルはこのパターンに従う:**

```cpp
// test_example.cpp

#include <omusubi/core/example.hpp>

#include "test_framework.hpp"

namespace example_test {

using namespace omusubi;
using namespace test;

// テスト関数1
void test_basic_functionality() {
    test_section("基本機能");

    // Arrange (準備)
    Example obj;

    // Act (実行)
    auto result = obj.do_something();

    // Assert (検証)
    TEST_ASSERT(result, "do_something()が成功する");
}

// テスト関数2
void test_edge_cases() {
    test_section("エッジケース");

    // ...
}

// main関数
int main() {
    begin_tests("Example");

    test_basic_functionality();
    test_edge_cases();

    return end_tests();
}

} // namespace example_test
```

### AAA パターン (Arrange-Act-Assert)

**すべてのテストケースはAAA パターンに従う:**

```cpp
void test_fixed_string_append() {
    test_section("追加操作");

    // Arrange - テスト準備
    FixedString<32> s;

    // Act - 操作実行
    bool success = s.append("Hello"_sv);

    // Assert - 結果検証
    TEST_ASSERT(success, "追加が成功する");
    TEST_ASSERT_EQ(s.byte_length(), 5U, "バイト長が正しい");
}
```

**AAA の利点:**
- テストの意図が明確
- 読みやすい構造
- デバッグが容易

---

## 命名規則

### テストファイル名

**`test_[対象].cpp` の形式:**

```
test/
├── test_span.cpp           # span<T>のテスト
├── test_string_view.cpp    # StringViewのテスト
├── test_fixed_string.cpp   # FixedString<N>のテスト
├── test_fixed_buffer.cpp   # FixedBuffer<N>のテスト
└── test_vector3.cpp        # Vector3のテスト
```

### テスト関数名

**`test_[対象]_[機能]()` の形式:**

```cpp
// ✅ 良い例: 明確で具体的
void test_span_basic();
void test_span_iteration();
void test_span_subspan();
void test_fixed_string_append();
void test_fixed_string_capacity();
void test_fixed_string_utf8();

// ❌ 悪い例: 抽象的で不明確
void test1();
void test_misc();
void test_everything();
```

### テストセクション名

**日本語で機能を説明:**

```cpp
test_section("基本機能");
test_section("追加操作");
test_section("容量制限");
test_section("UTF-8処理");
test_section("constexpr対応");
```

### アサーションメッセージ

**期待される動作を日本語で記述:**

```cpp
// ✅ 良い例: 何をテストしているか明確
TEST_ASSERT_EQ(s.byte_length(), 5U, "バイト長が5である");
TEST_ASSERT(s.append("Hello"_sv), "追加が成功する");
TEST_ASSERT_STR_EQ(s.c_str(), "Hello", "内容が一致する");

// ❌ 悪い例: メッセージが無い、または不明確
TEST_ASSERT_EQ(s.byte_length(), 5U, "test");
TEST_ASSERT(s.append("Hello"_sv), "ok");
```

---

## テスト構造

### テストスイート構成

```cpp
namespace example_test {

using namespace omusubi;
using namespace test;

// ========================================
// テスト関数群
// ========================================

void test_basic() {
    test_section("基本機能");
    // テストケース
}

void test_advanced() {
    test_section("高度な機能");
    // テストケース
}

// ========================================
// main関数
// ========================================

int main() {
    begin_tests("Example");

    // テスト関数を呼び出す
    test_basic();
    test_advanced();

    return end_tests();
}

} // namespace example_test
```

### テストセクションの分割

**機能ごとにテスト関数とセクションを分ける:**

```cpp
void test_fixed_string_basic() {
    test_section("基本機能");

    // デフォルトコンストラクタ
    FixedString<32> s1;
    TEST_ASSERT_EQ(s1.byte_length(), 0U, "デフォルト構築の文字列は空");

    // C文字列からの構築
    FixedString<32> s2("Hello");
    TEST_ASSERT_EQ(s2.byte_length(), 5U, "C文字列からのバイト長");
}

void test_fixed_string_append() {
    test_section("追加操作");

    FixedString<32> s;
    TEST_ASSERT(s.append("Hello"_sv), "StringView追加成功");
    TEST_ASSERT(s.append(" World"), "C文字列追加成功");
}

void test_fixed_string_utf8() {
    test_section("UTF-8処理");

    FixedString<64> s;
    s.append("こんにちは"_sv);
    TEST_ASSERT_EQ(s.byte_length(), 15U, "日本語のバイト長（5文字×3バイト）");
    TEST_ASSERT_EQ(s.char_length(), 5U, "日本語の文字数");
}
```

**分割の基準:**
- 1つのテスト関数は1つの機能に集中
- 5〜15個のアサーションを目安に
- 長すぎる場合は細分化する

---

## アサーション

### 基本アサーション

**`TEST_ASSERT(condition, message)`**

```cpp
// 条件が真であることを検証
TEST_ASSERT(s.empty(), "文字列が空である");
TEST_ASSERT(!s.empty(), "文字列が空でない");
TEST_ASSERT(result, "操作が成功する");
```

### 等価比較アサーション

**`TEST_ASSERT_EQ(actual, expected, message)`**

```cpp
// 数値の等価性
TEST_ASSERT_EQ(s.byte_length(), 5U, "バイト長が5");
TEST_ASSERT_EQ(count, 3, "カウントが3");
TEST_ASSERT_EQ(index, 0U, "インデックスが0");
```

**注意:**
- 符号付き/符号なし比較に注意 (`5U` vs `5`)
- `expected`を右側に配置 (読みやすさ)

### 文字列比較アサーション

**`TEST_ASSERT_STR_EQ(actual, expected, message)`**

```cpp
// C文字列の比較
TEST_ASSERT_STR_EQ(s.c_str(), "Hello", "内容が'Hello'");
TEST_ASSERT_STR_EQ(buffer, "", "バッファが空");
```

### 浮動小数点比較アサーション

**`TEST_ASSERT_FLOAT_EQ(actual, expected, epsilon, message)`**

```cpp
// 浮動小数点の比較 (誤差許容)
TEST_ASSERT_FLOAT_EQ(v.x, 1.0F, 0.0001F, "x座標が1.0");
TEST_ASSERT_FLOAT_EQ(angle, 3.14159F, 0.00001F, "角度がπ");
```

**epsilon の選び方:**
- 単精度float: `0.0001F` 〜 `0.00001F`
- 倍精度double: `0.0000001` 〜 `0.00000001`
- センサー値: `0.01F` 〜 `0.1F` (ハードウェアの精度に依存)

### アサーション使い分け

```cpp
// ✅ 良い例: 適切なアサーションを使用
TEST_ASSERT_EQ(count, 5, "カウントが5");              // 整数比較
TEST_ASSERT_STR_EQ(s.c_str(), "Hello", "文字列一致"); // 文字列比較
TEST_ASSERT_FLOAT_EQ(x, 1.0F, 0.001F, "浮動小数点");  // 浮動小数点比較

// ❌ 悪い例: 不適切なアサーション
TEST_ASSERT(count == 5, "カウントが5");  // TEST_ASSERT_EQを使うべき
TEST_ASSERT(strcmp(s.c_str(), "Hello") == 0, "文字列一致");  // TEST_ASSERT_STR_EQを使うべき
```

---

## テストカバレッジ

### カバレッジ目標

**コアライブラリ:**
- ステートメントカバレッジ: **90%以上**
- ブランチカバレッジ: **80%以上**

**プラットフォーム実装:**
- ステートメントカバレッジ: **70%以上**
- ブランチカバレッジ: **60%以上**

### テストすべきケース

**1. 正常系 (Happy Path)**

```cpp
void test_normal_case() {
    test_section("正常系");

    FixedString<32> s;
    TEST_ASSERT(s.append("Hello"_sv), "通常の追加が成功");
    TEST_ASSERT_EQ(s.byte_length(), 5U, "正しいバイト長");
}
```

**2. 境界値 (Boundary)**

```cpp
void test_boundary() {
    test_section("境界値");

    FixedString<10> s;

    // 容量いっぱい
    TEST_ASSERT(s.append("1234567890"), "容量いっぱいまで追加成功");
    TEST_ASSERT_EQ(s.byte_length(), 10U, "バイト長が容量と一致");

    // 容量超過
    TEST_ASSERT(!s.append("X"), "容量超過は失敗");
}
```

**3. エラー系 (Error Cases)**

```cpp
void test_error_cases() {
    test_section("エラー処理");

    span<int> empty_span;
    TEST_ASSERT(empty_span.empty(), "空のspanはempty()がtrue");

    // 範囲外アクセス (デバッグビルドでassertされるべき)
    // リリースビルドでは未定義動作のためテストしない
}
```

**4. エッジケース (Edge Cases)**

```cpp
void test_edge_cases() {
    test_section("エッジケース");

    // 空文字列
    FixedString<32> empty;
    TEST_ASSERT_EQ(empty.byte_length(), 0U, "空文字列のバイト長は0");
    TEST_ASSERT_STR_EQ(empty.c_str(), "", "空文字列の内容");

    // 1文字
    FixedString<32> single("A");
    TEST_ASSERT_EQ(single.byte_length(), 1U, "1文字のバイト長");

    // UTF-8マルチバイト文字
    FixedString<32> multibyte("あ");
    TEST_ASSERT_EQ(multibyte.byte_length(), 3U, "マルチバイト文字のバイト長");
    TEST_ASSERT_EQ(multibyte.char_length(), 1U, "マルチバイト文字の文字数");
}
```

**5. constexpr 検証**

```cpp
void test_constexpr() {
    test_section("constexpr対応");

    // コンパイル時計算
    {
        constexpr auto s = fixed_string("Hello");
        static_assert(s.byte_length() == 5, "constexpr byte_length()");
        static_assert(s.capacity() == 5, "constexpr capacity()");
    }

    // コンパイル時UTF-8処理
    {
        constexpr auto s = fixed_string("こんにちは");
        static_assert(s.byte_length() == 15, "constexpr UTF-8バイト長");
        static_assert(s.char_length() == 5, "constexpr UTF-8文字数");
    }

    // 実行時検証も追加
    auto runtime_str = fixed_string("Hello");
    TEST_ASSERT_EQ(runtime_str.byte_length(), 5U, "constexpr関数の実行時使用");
}
```

---

## モックとスタブ

### モックの基本方針

**組み込み環境でのモックは軽量に保つ。**

**モック実装パターン:**

```cpp
// テスト用モック実装
namespace test {

class MockSerialContext : public SerialContext {
private:
    FixedBuffer<256> read_buffer_;
    FixedBuffer<256> write_buffer_;
    bool connected_ = false;

public:
    // Connectable interface
    bool connect() override {
        connected_ = true;
        return true;
    }

    void disconnect() override {
        connected_ = false;
    }

    bool is_connected() const override {
        return connected_;
    }

    // ByteReadable interface
    size_t read(span<uint8_t> buffer) override {
        auto count = (buffer.size() < read_buffer_.size())
            ? buffer.size()
            : read_buffer_.size();
        for (size_t i = 0; i < count; ++i) {
            buffer[i] = read_buffer_[i];
        }
        return count;
    }

    size_t available() const override {
        return read_buffer_.size();
    }

    // ByteWritable interface
    size_t write(span<const uint8_t> data) override {
        write_buffer_.clear();
        for (auto byte : data) {
            write_buffer_.append(byte);
        }
        return data.size();
    }

    // テスト用ヘルパー
    void set_read_data(StringView data) {
        read_buffer_.clear();
        for (char c : data) {
            read_buffer_.append(static_cast<uint8_t>(c));
        }
    }

    StringView get_written_data() const {
        return StringView(
            reinterpret_cast<const char*>(write_buffer_.data()),
            write_buffer_.size()
        );
    }
};

} // namespace test
```

### モックを使ったテスト

```cpp
void test_with_mock() {
    test_section("モックを使ったテスト");

    // Arrange
    test::MockSerialContext mock_serial;
    mock_serial.set_read_data("Hello"_sv);

    // Act
    uint8_t buffer[10];
    size_t bytes_read = mock_serial.read(span<uint8_t>(buffer, 10));

    // Assert
    TEST_ASSERT_EQ(bytes_read, 5U, "5バイト読み取り");
    TEST_ASSERT_EQ(buffer[0], 'H', "最初の文字が'H'");
}
```

### スタブの使用

**外部依存を排除したい場合にスタブを使用:**

```cpp
// スタブ: 常に固定値を返す
class StubSensorContext : public AccelerometerContext {
public:
    Vector3 get_values() const override {
        return Vector3{0.0F, 0.0F, 9.8F};  // 常に静止状態
    }
};

void test_with_stub() {
    test_section("スタブを使ったテスト");

    StubSensorContext stub;
    auto values = stub.get_values();

    TEST_ASSERT_FLOAT_EQ(values.z, 9.8F, 0.1F, "重力加速度が正しい");
}
```

---

## 組み込み環境でのテスト

### 組み込み環境の制約

**組み込みシステムでのテストは以下の制約を考慮:**

1. **メモリ制約**: ヒープアロケーション禁止
2. **実行時間**: リアルタイム性を損なわない
3. **ハードウェア依存**: モック/スタブで分離
4. **例外なし**: エラーは戻り値で通知

### ホスト環境でのテスト (推奨)

**開発マシン (Linux/macOS/Windows) でテストを実行:**

```bash
# ホスト環境でビルド・実行
cd test
clang++ -std=c++14 -Wall -Wextra -I../include \
    test_all.cpp \
    test_span.cpp \
    test_string_view.cpp \
    test_fixed_string.cpp \
    test_fixed_buffer.cpp \
    test_vector3.cpp \
    -o test_runner

# テスト実行
./test_runner

# 出力例:
# ╔═══════════════════════════════════════╗
# ║  Omusubi フレームワーク 単体テスト    ║
# ╚═══════════════════════════════════════╝
#
# ========================================
# テストスイート: span<T>
# ========================================
# [基本機能]
#   ✓ 空のspanはempty()がtrue
#   ✓ 空のspanのサイズは0
#   ...
# 結果: 127 / 127 テスト成功
```

**利点:**
- 高速なイテレーション
- デバッガが使える
- メモリチェッカー (Valgrind, ASan) が使える

---

## 実機テスト

### ターゲット環境でのテスト

**実機 (M5Stack, Arduino) でのテスト:**

```cpp
// examples/platform/m5stack/test_on_device.cpp

#include <omusubi/omusubi.h>
#include "test_framework.hpp"

using namespace omusubi;
using namespace test;

SystemContext& ctx = get_system_context();
SerialContext* serial = nullptr;

void test_serial_loopback() {
    test_section("シリアル通信テスト");

    serial->write("Hello"_sv);
    ctx.delay(100);

    uint8_t buffer[10];
    size_t bytes = serial->read(span<uint8_t>(buffer, 10));
    TEST_ASSERT_EQ(bytes, 5U, "5バイト読み取り");
}

void setup() {
    ctx.begin();
    serial = ctx.get_connectable_context()->get_serial_context(0);
    serial->connect();

    begin_tests("実機テスト");
    test_serial_loopback();
    end_tests();
}

void loop() {
    ctx.update();
}
```

**実機テストの用途:**
- ハードウェア統合テスト
- タイミング検証
- リソース使用量測定

### PlatformIOでの実機テスト実行

```bash
# ビルド
pio run -e m5stack

# アップロード
pio run -e m5stack --target upload

# シリアルモニタで結果確認
pio device monitor
```

---

## ベストプラクティス

### 1. 1つのテストは1つのことを検証

```cpp
// ✅ 良い例: 1つの機能を検証
void test_append_success() {
    FixedString<32> s;
    TEST_ASSERT(s.append("Hello"_sv), "追加が成功する");
}

void test_append_capacity() {
    FixedString<10> s("1234567890");
    TEST_ASSERT(!s.append("X"), "容量超過時は失敗する");
}

// ❌ 悪い例: 複数の機能を混在
void test_append() {
    FixedString<32> s1;
    TEST_ASSERT(s1.append("Hello"_sv), "追加成功");

    FixedString<10> s2("1234567890");
    TEST_ASSERT(!s2.append("X"), "容量超過");
    // 2つの異なるケースが混在している
}
```

### 2. テストは独立させる

```cpp
// ✅ 良い例: 各テストで新しいオブジェクトを作成
void test_clear() {
    FixedString<32> s("Hello");
    s.clear();
    TEST_ASSERT_EQ(s.byte_length(), 0U, "クリア後は空");
}

void test_append() {
    FixedString<32> s;  // 新しいオブジェクト
    TEST_ASSERT(s.append("World"_sv), "追加成功");
}

// ❌ 悪い例: グローバル変数でテスト間に依存
FixedString<32> global_str;  // テスト間で共有

void test_append() {
    global_str.append("Hello");  // 前のテストの状態に依存
}
```

### 3. 明確なエラーメッセージ

```cpp
// ✅ 良い例: 何が期待されるか明確
TEST_ASSERT_EQ(s.byte_length(), 5U, "バイト長が5である");
TEST_ASSERT(result, "connect()が成功する");
TEST_ASSERT(!buffer.full(), "バッファが満杯でない");

// ❌ 悪い例: メッセージが不明確
TEST_ASSERT_EQ(s.byte_length(), 5U, "test");
TEST_ASSERT(result, "ok");
TEST_ASSERT(!buffer.full(), "check");
```

### 4. constexpr 関数は static_assert でも検証

```cpp
void test_constexpr() {
    // コンパイル時検証
    constexpr auto s = fixed_string("Hello");
    static_assert(s.byte_length() == 5, "constexpr計算");
    static_assert(s.capacity() == 5, "constexpr容量");

    // 実行時検証 (必須)
    TEST_ASSERT_EQ(s.byte_length(), 5U, "実行時のバイト長");
    TEST_ASSERT_EQ(s.capacity(), 5U, "実行時の容量");
}
```

### 5. テストコードも読みやすく

```cpp
// ✅ 良い例: AAA パターンで構造化
void test_example() {
    test_section("例");

    // Arrange
    FixedString<32> s;

    // Act
    auto result = s.append("Hello"_sv);

    // Assert
    TEST_ASSERT(result, "追加が成功する");
    TEST_ASSERT_EQ(s.byte_length(), 5U, "バイト長が正しい");
}
```

---

## テスト実行

### ホスト環境でのテスト実行

```bash
# テストをビルド
cd test
clang++ -std=c++14 -Wall -Wextra -I../include \
    test_all.cpp \
    test_span.cpp \
    test_string_view.cpp \
    test_fixed_string.cpp \
    test_fixed_buffer.cpp \
    test_vector3.cpp \
    -o test_runner

# テスト実行
./test_runner

# 出力例:
# ╔═══════════════════════════════════════╗
# ║  Omusubi フレームワーク 単体テスト    ║
# ╚═══════════════════════════════════════╝
#
# ========================================
# テストスイート: span<T>
# ========================================
# [基本機能]
#   ✓ 空のspanはempty()がtrue
#   ✓ 空のspanのサイズは0
#   ...
# 結果: 127 / 127 テスト成功
```

### CI での自動テスト

**GitHub Actions で自動実行:**

```yaml
# .github/workflows/test.yml
name: Run Tests

on: [push, pull_request]

jobs:
  test:
    runs-on: ubuntu-latest
    steps:
      - uses: actions/checkout@v3
      - name: Install Clang
        run: sudo apt-get install -y clang
      - name: Run Tests
        run: |
          cd test
          make
          ./test_runner
```

---

## チェックリスト

テスト作成時のチェックリスト:

- [ ] 正常系をテストしている
- [ ] 境界値をテストしている
- [ ] エラー系をテストしている
- [ ] エッジケースをテストしている
- [ ] constexpr 関数を static_assert で検証している
- [ ] AAA パターンに従っている
- [ ] テストは独立している
- [ ] エラーメッセージが明確である
- [ ] テスト関数名が適切である
- [ ] テストセクションで分類している
- [ ] ホスト環境でテストが通る
- [ ] 実機でも検証した (プラットフォーム実装の場合)

---

## 関連ドキュメント

- [エラーハンドリングガイド](error-handling.md) - テスト時のエラーケース検証
- CLAUDE.md - コーディング規約全般
- [デバッグガイド](debug.md) - テスト失敗時のデバッグ手法

---

**Version:** 2.0.0
**Last Updated:** 2025-11-17
