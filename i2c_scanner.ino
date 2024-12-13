#include <Wire.h>  // 引入 Wire 庫，用於 I2C 通訊

void setup() {
  Wire.begin();              // 初始化 I2C 通訊
  Serial.begin(9600);        // 設定序列通訊的波特率為 9600
  while (!Serial);           // 等待序列埠就緒（適用於部分硬件，例如 Arduino Leonardo）
  Serial.println("\nI2C Scanner"); // 在序列埠輸出初始訊息
}

void loop() {
  byte error, address;       // 用於存儲 I2C 傳輸的錯誤代碼和當前掃描的地址
  int nDevices = 0;          // 計算找到的 I2C 設備數量

  Serial.println("Scanning..."); // 輸出掃描開始訊息

  // 掃描 I2C 設備的所有有效地址範圍 (1-127)
  for (address = 1; address < 127; address++) {
    Wire.beginTransmission(address); // 開始向指定地址進行 I2C 通訊
    error = Wire.endTransmission(); // 檢查是否有回應，返回錯誤代碼

    if (error == 0) {
      // 如果錯誤代碼為 0，表示此地址有 I2C 設備響應
      Serial.print("I2C device found at address 0x");
      if (address < 16) Serial.print("0"); // 為小於 16 的地址補零
      Serial.println(address, HEX);       // 以十六進制格式輸出地址
      nDevices++;                         // 計數器加一
    } else if (error == 4) {
      // 如果錯誤代碼為 4，表示未知錯誤
      Serial.print("Unknown error at address 0x");
      if (address < 16) Serial.print("0"); // 為小於 16 的地址補零
      Serial.println(address, HEX);       // 以十六進制格式輸出地址
    }
  }

  if (nDevices == 0) {
    // 如果未找到任何設備，輸出相應訊息
    Serial.println("No I2C devices found\n");
  } else {
    // 如果找到設備，輸出完成訊息
    Serial.println("done\n");
  }

  delay(5000); // 等待 5 秒後重新掃描
}