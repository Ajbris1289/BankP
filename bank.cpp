#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <fstream>

using namespace std;

// constant variables
const string ACCOUNT_FILE_NAME("accounts.dat");
const int MAX_TRANSACTIONS(3);
// accont structure
struct Account{
    string aName; // name of the account
    string uName; // user name of the account
    string pWord; // password of the account
    long sAcc;// savings balance in the account
    long cAcc; // checking balance in the account
    int tCount; // number of transactions performed in that day

    // constructor
    Account(){ 
        sAcc = 0;
        cAcc = 0;
        tCount = 0;
    }

    // prints the details
    void display(){
        cout << "|===============================================|" << endl;
        cout << "Name: " << aName << "\nSaving Account Balance: $" << sAcc << "\nChecking Account Balance: $" << cAcc << endl;
        cout << "|===============================================|" << endl;
    }
};

// read from csv file. it is assumed that each line represents an account and they have the format,"Robert Brown,rbrown,blue123,2500,350".
void getData(string fName, vector<Account>& accounts){
    ifstream input(fName);
    string line;
    while (!input.eof()){
        Account ac;
        getline(input, ac.aName, ',');
        getline(input, ac.uName, ',');
        getline(input, ac.pWord, ',');
        getline(input, line, ',');
        ac.sAcc = stol(line);
        getline(input, line);
        ac.cAcc = stol(line);
        accounts.push_back(ac);
    }
}

// verifies the password. Entry of password as * is not supported it will show the password.
// returns true if password is correct else false
bool credCheck(const Account& acc){
    string pass;
    cout << "Enter Password : ";
        cin >> pass;
    if (acc.pWord == pass){
        return true;
    }
    cout << "Credentials are incorrect!!" << endl;
    return false;
}

// get the account to be used for transaction.
// if the password entered is wrong 3 times then returns -2
// if user name doesnt exist then returns -1;
// else returns 0.
int getAccount(vector<Account>& accounts)
{
    string username;
    cout << "User Name:";
    cin >> username;
    int ret = -1;
    // check user name
    for (int i = 0; i < accounts.size(); i++){
        if (accounts[i].uName == username){
            ret = i;
            break;
        }
    }
    if (ret == -1){
        cout << "Invalid User Name Entered..." << endl;
        return ret;
    }

    // check password.
    bool p = false;
    int count = 0;
    while (!p){
        if (count == 3){
            cout << "Wrong Password Entered three times..." << endl;
            ret = -2;
            break;
        }
        p = credCheck(accounts[ret]);
        count++; 
    }
    return ret;
}


// deposit amount to account.
int Deposit(Account& acc)
{
    int acco = 0;
    int amount;
    acc.tCount++; // increment the number of transactions of th account.
    // read account type   
    cout << "1. Savings Account\n2. Checking Account\nSelect Account Type:";
    cin >> acco;
    if (acco != 1 && acco != 2){
        cout << "Wrong Account type!!" << endl;
        return -1;
    }
    // get amount to be deposited.
    cout << "Please Enter the amount to be deposited: ";
    cin >> amount;
    
    // deposit the amount if valid.
    if (acco == 1){
        if (abs(amount - int(amount)) > 0){
            cout << "Please enter the integer values"<< endl<<"ATM does not deposit coins\n";
        }
        else{
        acc.sAcc += amount;
        cout << "$" << amount << "Deposited to Savings account of " << acc.aName << endl;    
        }    
    }
    else{
        if (abs(amount - int(amount)) > 0){
            cout << "Please enter the integer values"<< endl<<"ATM does not deposit coins\n";
        }
        else{
        acc.cAcc += amount;
        cout << "$" << amount << "Deposited to Checking account of " << acc.aName << endl;   
        } 
    }
    acc.display();
    return 0;
}

// withdraw amount from account.
int Withdraw(Account& acc){
    int acco = 0;
    long amount;
    acc.tCount++; // increment the number of transactions of th account.
    cout << "1. Savings Account\n2. Checking Account\nSelect Account Type:";
    cin >> acco;
    // get account type.
    if (acco != 1 && acco != 2){
        cout << "Wrong Account type!!" << endl;
        return -1;
    }
    cout << "Please Enter the amount to be withdrawn: ";
    cin >> amount;
    // withdraw money.
    if (amount < 0) {
        return -1;
    }
    if (acco == 1){
        if (amount <= acc.sAcc){
            acc.sAcc -= amount;
            cout << "$" << amount << "WithDrawn from Saving account of " << acc.aName << endl;
        }
        else
            cout << "Not enough money in the account!!" << endl;
    }
    else{
        if (amount <= acc.cAcc){
            acc.cAcc -= amount;
            cout << "$" << amount << "WithDrawn from Checking account of " << acc.aName << endl;
        }
        else
            cout << "Not enough money in the account!!" << endl;
    }
    acc.display();
    return 0;
}

// shows the balance if account is valid.
int bInquiry(Account& acc){
    acc.tCount++; // increment the number of transactions of th account.
    acc.display();
    return 0;
}

// Transfers the amount to another account
int TransferBalance(vector<Account>& accounts, Account& acc){
    int accRec = -1;
    string receiver;
    int acco;
    long amount;

    acc.tCount++; // increment the number of transactions of th account.
    cout<< "Username of receiver: ";
    cin >> receiver;
    // get payee account
    for (int i = 0; i < accounts.size(); i++){
        if (receiver == accounts[i].uName){
            accRec = i;
            break;
        }
    }
    // if payee is same as self the return
    if (receiver == acc.uName || accRec < 0){
        cout << "Invalid receiver account! " << endl;
        return -1;
    }
    // get the account type , assumption is that transfer can happen between accounts of same type.
    cout << "1. Savings Account\n2. Checking Account\nSelect Account Type:";
    cin >> acco;
    if (acco != 1 && acco != 2){
        cout << "Wrong Account type!!" << endl;
        return -1;
    }
    cout << "Please Enter the amount to be withdrawn: ";
    cin >> amount;
    if (amount < 0){
        return -1;
    }
    // transfer the amount.
    if (acco == 1){
        if (acco <= acc.sAcc){
            acc.sAcc -= amount;
            accounts[accRec].sAcc += amount;
            cout << "$" << amount << " Transferred from Saving account of " << acc.aName << " to Saving account of " << accounts[accRec].aName << endl;
        }
        else
            cout << "Not enough money in the account!!" << endl;
    }
    else{
        if (amount <= acc.cAcc){
            acc.cAcc -= amount;
            accounts[accRec].cAcc += amount;
            cout << "$" << amount << " Transferred from Checking account of " << acc.aName << " to Checking account of " << accounts[accRec].aName << endl;
        }
        else
        cout << "Not enough money in the account!!" << endl;
    }
    acc.display();
    return 0;
}

// print the menu.
void displayT(){
    cout << "|===============================================|" << endl;
    cout << "1. Deposit" << endl;
    cout << "2. Withdraw" << endl;
    cout << "3. Balance Enquiry" << endl;
    cout << "4. Transfer Balance" << endl;
    cout << "5. Log Out" << endl;
    cout << "|===============================================|" << endl;
    cout<<"Pick a transaction from above: ";
}

// mainapp
int main()
{
    cout << fixed;
    cout << setprecision(2);
    vector<Account> accounts;
    getData(ACCOUNT_FILE_NAME, accounts);
    int choice;
    int ret = -1;
    // loop infinitely till exit is pressed
    // user completes 3 transactions

    int acc = 0;
    // loop till valid user name is entered.
    acc = getAccount(accounts);
    // if password is wrong for 3 times the exit the application.
    if (acc < 0)
        return -2;
    while (1)
    {
        displayT();
        cin >> choice;
        if (choice == 5)
            break;
        
        if (choice == 1)
            Deposit(accounts[acc]);
        
        if (choice == 2)
            Withdraw(accounts[acc]);
        
        if (choice == 3)
            bInquiry(accounts[acc]);
        
        if (choice == 4)
            TransferBalance(accounts, accounts[acc]);
        
        if (accounts[acc].tCount == 3){
            cout << "3 Transactions completed!!" << endl;
            break;
        }
    }
    cout << "Good Bye!!" << endl;
    return 0;
}
