# 資料結構闖關：第 19 關

## 海大餐廳排隊系統

以餐廳候位流程認識 FIFO 佇列。每張候位單包含排隊編號、姓名和電話；先登記的客人先入座。

## 課程路線

- [課程首頁](index.html)：資料結構支線與第 19 關卡片。
- [第 19 關：海大餐廳排隊系統](level-19.html)：操作佇列示意台，查看 FIFO 變化。
- [完整 C++ 主控台程式](level-19.cpp)：使用 `struct Customer` 與 `queue<Customer>`。

## 功能

1. 登記候位：輸入姓名與電話，自動取得候位編號並加入隊尾。
2. 叫下一位：顯示隊首客人並移出候位隊伍。
3. 看下一位：查看隊首，不移除候位資料。
4. 候位名單：依入隊順序列出編號、姓名與電話。
5. 查順位：依候位編號搜尋目前位置。
6. 打烊清空：清除候位單，下一輪編號重設為 1。

## 執行 C++ 程式

需要支援 C++17 的編譯器，例如 g++、Clang 或 Visual C++。

```sh
g++ -std=c++17 -Wall -Wextra -pedantic level-19.cpp -o level-19
./level-19
```

Windows 使用 MinGW g++ 時：

```powershell
g++ -std=c++17 -Wall -Wextra -pedantic level-19.cpp -o level-19.exe
./level-19.exe
```

也可以直接用瀏覽器開啟 `index.html`，從首頁進入互動操作台。網頁版是教學示意介面，資料只保存在目前頁面；C++ 程式則在主控台執行。

## 資料結構重點

```cpp
struct Customer {
    int number;
    string name;
    string phone;
};

queue<Customer> waiting;
```

`push` 將客人加入隊尾，`front` 查看隊首，`pop` 移除隊首。這三種佇列操作為 $O(1)$；列出候位名單或查詢順位需逐筆檢查，為 $O(n)$。