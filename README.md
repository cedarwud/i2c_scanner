# I2C Scanner

## 概要
這是一個用於 **Arduino** 的 I2C 掃描器程式，設計用來檢測並列出與 Arduino 相連的所有 I2C 設備。I2C（Inter-Integrated Circuit）是一種常見的通訊協議，通常用於電子模組和感測器之間的通訊。

此程式的主要功能：
1. 掃描所有 I2C 地址範圍（從 0x01 到 0x7F）。
2. 列出檢測到的 I2C 設備地址。
3. 在序列監視器上顯示結果。

## 功能描述
- **掃描範圍**: 遍歷所有有效 I2C 地址，從 0x01 至 0x7F。
- **檢測設備**: 嘗試與每個地址進行通訊，並記錄有響應的設備地址。
- **錯誤處理**: 如果發生未知錯誤，會在序列監視器上顯示對應的地址和錯誤訊息。
- **延遲間隔**: 每次掃描後等待 5 秒，然後重新開始掃描。

## 如何使用
1. **硬體準備**:
   - 使用支援 I2C 的 Arduino 主控板（例如 Arduino Uno、Mega、Leonardo）。
   - 確保已正確連接 I2C 設備到 Arduino 的 SDA 和 SCL 腳位（依據板子型號，腳位可能不同）。
   - 確保設備接地（GND）已連接到 Arduino。

2. **軟體環境**:
   - 使用 Arduino IDE，並確保安裝好最新的 **Wire** 庫（Arduino 內建）。

3. **載入程式**:
   - 將此檔案命名為 `I2C_Scanner.ino`，然後打開 Arduino IDE。
   - 將程式上傳到 Arduino 板。

4. **查看結果**:
   - 打開 Arduino IDE 的序列監視器（快捷鍵 `Ctrl+Shift+M`）。
   - 設定波特率為 9600。
   - 查看掃描結果，包括找到的 I2C 設備地址，或提示未檢測到設備。

## 程式解析
以下是程式的功能點解析：

1. **初始化 I2C 和序列通訊**:
   ```cpp
   Wire.begin();      // 初始化 I2C 通訊
   Serial.begin(9600);// 設定序列監視器的波特率
   ```

2. **掃描所有地址**:
   ```cpp
   for (address = 1; address < 127; address++) {
       Wire.beginTransmission(address);   // 嘗試與該地址進行通訊
       error = Wire.endTransmission();    // 檢查是否有設備響應
   }
   ```

3. **錯誤處理與輸出**:
   - 如果 `Wire.endTransmission()` 返回 `0`，表示找到設備。
   - 如果返回 `4`，則表示發生未知錯誤。
   ```cpp
   if (error == 0) {
       Serial.print("I2C device found at address 0x");
       Serial.println(address, HEX);
   } else if (error == 4) {
       Serial.print("Unknown error at address 0x");
       Serial.println(address, HEX);
   }
   ```

4. **結果顯示**:
   - 找到設備時，輸出其地址。
   - 如果沒有設備，提示 "No I2C devices found"。

5. **延遲與重試**:
   - 每次掃描後等待 5 秒，便於檢測更新的連接狀態。
   ```cpp
   delay(5000);
   ```

## 使用情境
- **設備調試**: 確認 I2C 設備是否正確連接，並找到其 I2C 地址。
- **項目開發**: 用於識別未知的 I2C 設備地址，便於後續程式設計。
- **硬體檢測**: 驗證 I2C 線路是否正常。

## 注意事項
- 確保 I2C 設備的連接無誤，尤其是 SDA 和 SCL 腳位。
- 如果沒有檢測到設備，檢查是否需要上拉電阻（某些模組需要）。
- 不同的 Arduino 主控板 I2C 腳位：
  - Arduino Uno/Nano: SDA=A4, SCL=A5
  - Arduino Mega: SDA=20, SCL=21
  - Arduino Leonardo: SDA=2, SCL=3

## 範例輸出
當連接的設備地址為 0x3C 時，序列監視器可能會顯示：
```
I2C Scanner
Scanning...
I2C device found at address 0x3C
Scanning...
No I2C devices found
```

## 延伸功能建議
1. **保存結果**: 將掃描結果記錄到 SD 卡中。
2. **設備分類**: 根據常見的地址範例，自動標記設備類型（如 OLED 顯示器 0x3C）。