#include <iostream>
#include <fstream>
using namespace std;

class Account {
private:
    string username;
    string pin;
    double balance;

public:
    Account() {
        username = "";
        pin = "";
        balance = 0.0;
    }

    void createAccount() {
        cout << "Enter username: ";
        cin >> username;
        cout << "Set PIN: ";
        cin >> pin;
        balance = 0.0;
        saveAccount();
        cout << "Account created successfully!\n";
    }

    bool login(string u, string p) {
        ifstream fin("accounts.txt");
        string user, pass;
        double bal;
        while (fin >> user >> pass >> bal) {
            if (user == u && pass == p) {
                username = user;
                pin = pass;
                balance = bal;
                fin.close();
                return true;
            }
        }
        fin.close();
        return false;
    }

    void saveAccount() {
        // Save or update current account details in file
        ifstream fin("accounts.txt");
        ofstream fout("temp.txt");

        string user, pass;
        double bal;
        bool updated = false;

        while (fin >> user >> pass >> bal) {
            if (user == username && pass == pin) {
                fout << username << " " << pin << " " << balance << "\n";
                updated = true;
            } else {
                fout << user << " " << pass << " " << bal << "\n";
            }
        }
        fin.close();

        if (!updated) {
            fout << username << " " << pin << " " << balance << "\n";
        }
        fout.close();

        remove("accounts.txt");
        rename("temp.txt", "accounts.txt");
    }

    void menu() {
        int choice;
        do {
            cout << "\n===== ATM MENU =====\n";
            cout << "1. Check Balance\n";
            cout << "2. Deposit Money\n";
            cout << "3. Withdraw Money\n";
            cout << "4. Logout\n";
            cout << "Enter choice: ";
            cin >> choice;

            switch (choice) {
                case 1:
                    cout << "Current Balance: " << balance << endl;
                    break;

                case 2: {
                    double amount;
                    cout << "Enter amount to deposit: ";
                    cin >> amount;
                    if (amount > 0) {
                        balance += amount;
                        saveAccount();
                        cout << "Deposit successful.\n";
                    } else {
                        cout << "Invalid amount.\n";
                    }
                    break;
                }

                case 3: {
                    double amount;
                    cout << "Enter amount to withdraw: ";
                    cin >> amount;
                    if (amount > 0 && amount <= balance) {
                        balance -= amount;
                        saveAccount();
                        cout << "Withdrawal successful.\n";
                    } else {
                        cout << "Insufficient balance or invalid amount.\n";
                    }
                    break;
                }

                case 4:
                    cout << "Logging out...\n";
                    break;

                default:
                    cout << "Invalid choice.\n";
            }
        } while (choice != 4);
    }
};

int main() {
    int choice;
    Account acc;

    do {
        cout << "\n===== SIMPLE ATM INTERFACE =====\n";
        cout << "1. Login\n";
        cout << "2. Create Account\n";
        cout << "3. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        if (choice == 1) {
            string user, pass;
            cout << "Enter username: ";
            cin >> user;
            cout << "Enter PIN: ";
            cin >> pass;
            if (acc.login(user, pass)) {
                cout << "Login successful!\n";
                acc.menu();
            } else {
                cout << "Invalid username or PIN.\n";
            }

        } else if (choice == 2) {
            acc.createAccount();

        } else if (choice == 3) {
            cout << "Exiting... Goodbye!\n";
        } else {
            cout << "Invalid choice. Try again.\n";
        }
    } while (choice != 3);

    return 0;
}