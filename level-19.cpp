#include <iostream>
#include <limits>
#include <queue>
#include <string>

using namespace std;

struct Customer {
    int number;
    string name;
    string phone;
};

void printCustomer(const Customer& customer) {
    cout << "候位單 #" << customer.number
         << " | 姓名：" << customer.name
         << " | 電話：" << customer.phone << '\n';
}

void printQueue(queue<Customer> customers) {
    if (customers.empty()) {
        cout << "目前沒有候位客人。\n";
        return;
    }

    cout << "候位名單（由前到後）：\n";
    int position = 1;
    while (!customers.empty()) {
        cout << position++ << ". ";
        printCustomer(customers.front());
        customers.pop();
    }
}

bool readPositiveNumber(int& number, const string& prompt) {
    cout << prompt;
    if (cin >> number && number > 0) {
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return true;
    }

    cout << "請輸入大於 0 的整數。\n";
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    return false;
}

void registerCustomer(queue<Customer>& waiting, int& nextNumber) {
    Customer customer{};
    customer.number = nextNumber;

    cout << "姓名：";
    getline(cin, customer.name);
    cout << "電話：";
    getline(cin, customer.phone);

    if (customer.name.empty() || customer.phone.empty()) {
        cout << "姓名和電話都不能空白，未建立候位單。\n";
        return;
    }

    waiting.push(customer);
    ++nextNumber;
    cout << "登記完成！";
    printCustomer(customer);
    cout << "目前排在第 " << waiting.size() << " 位。\n";
}

void callNext(queue<Customer>& waiting) {
    if (waiting.empty()) {
        cout << "目前沒有候位客人，無法叫號。\n";
        return;
    }

    cout << "請 " << waiting.front().name << " 入座！\n";
    printCustomer(waiting.front());
    waiting.pop();
}

void showNext(const queue<Customer>& waiting) {
    if (waiting.empty()) {
        cout << "目前沒有下一位候位客人。\n";
        return;
    }

    cout << "下一位（目前候位最前面）：\n";
    printCustomer(waiting.front());
}

void findRank(queue<Customer> customers, int number) {
    int position = 1;
    while (!customers.empty()) {
        if (customers.front().number == number) {
            cout << "候位單 #" << number << " 目前排在第 "
                 << position << " 位。\n";
            return;
        }
        customers.pop();
        ++position;
    }

    cout << "找不到候位單 #" << number
         << "；可能已入座或編號不存在。\n";
}

int main() {
    queue<Customer> waiting;
    int nextNumber = 1;
    int choice = 0;

    cout << "====================================\n";
    cout << "  海大餐廳排隊系統｜第 19 關\n";
    cout << "  FIFO：先登記的客人先入座\n";
    cout << "====================================\n";

    while (true) {
        cout << "\n[1] 登記候位  [2] 叫下一位  [3] 看下一位\n"
             << "[4] 候位名單  [5] 查順位  [6] 打烊清空  [0] 離開\n";
        cout << "請選擇功能：";
        if (!(cin >> choice) || choice < 0 || choice > 6) {
            cout << "請輸入 0 到 6 的整數。\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        if (choice == 0) {
            cout << "已離開海大餐廳排隊系統。\n";
            break;
        }

        switch (choice) {
        case 1:
            registerCustomer(waiting, nextNumber);
            break;
        case 2:
            callNext(waiting);
            break;
        case 3:
            showNext(waiting);
            break;
        case 4:
            printQueue(waiting);
            break;
        case 5: {
            int number = 0;
            if (readPositiveNumber(number, "請輸入候位編號：")) {
                findRank(waiting, number);
            }
            break;
        }
        case 6:
            cout << "打烊完成，已清空 " << waiting.size()
                 << " 張候位單。下一輪編號從 1 開始。\n";
            waiting = queue<Customer>{};
            nextNumber = 1;
            break;
        default:
            cout << "沒有這個功能，請選擇 0 到 6。\n";
        }
    }

    return 0;
}