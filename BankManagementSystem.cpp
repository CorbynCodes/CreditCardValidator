#include <iostream>
using namespace std;

class bank {
    private:
        string name;
        double balance;
    public:
        bank::bankAccount(string accountName, double intialBalance)
            : name(accountName), balance(intialBalance) {}
        
        void deposit(double amount) {
            if(amount > 0) {
                balance += amount;
            }
        }

        void withdraw(double amount) {
            if(amount <= balance) {
                balance -= amount;
            }
            else {
                cout << "Sorry, you do not have enough money in your account." << endl;
            }
        }

        void display() {
            cout << "Account Holder: " << name << endl;
        }

};

int main() {

    string name;
    double intialDeposit;

    cout << "Enter your name: ";
    getline(cin, name);
    cout << "Enter inital Deposit: ";
    cin >> intialDeposit;

    bankAccount account(name, intialDeposit);

    int choice;
    double amount;

    do {
        cout << "\n1. Deposit" << endl;
        cout << "2. Withdraw" << endl;
        cout << "3. Display Account" << endl;
        cout << "4. Exit" << endl;
        cout << "Enter Choice: ";
        cin >> choice;

        switch (choice) {

            case 1:
                cout << "Enter deposit amount: ";
                cin >> amount;
                account.deposit(amount);
                break;
            case 2:
                cout << "Enter withdrawal amount: ";
                cin >> amount;
                account.withdraw(amount);
                break;
            case 3:
                account.display();
                break;
            case 4:
                break;
            default:
                cout << "Invaild input. " << endl;           
            }
    } while (choice != 4);

    return 0;
}