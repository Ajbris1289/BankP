#include <iostream>
#include <iomanip>

using namespace std;

string cus = "Robert Brown";
string uName = "rbrown";
string pWord = "blue123";

double sAcc = 2500.00;
double cAcc = 35.00;

double deposit(double amt, double bal){
    return amt + bal;
}

double withdrawal(double amt, double bal){
    //check overdraft limit
    if(amt <= bal){
        return bal - amt;
    }
    cout<<"Too much to withdrawl!!"<<endl;
    cout<<"|====================================|"<<endl;
    return bal;
}

int tCount = 0;
void display(){
    cout<<"Customer: "<<cus<<"\nSaving Account: "<<sAcc<<"\nChecking Account: "<<cAcc<<"\nTotal Transactions: "<<tCount<<endl;
    cout<<"|====================================|"<<endl;
}



int main() {
    string user;
    string pass;
    cout<<"What is your Username: ";
        cin>>user;
    cout<<"What is your password: ";
        cin>>pass;
    cout<<"|====================================|"<<endl;
    while(user != uName || pass != pWord){
        cout<<"Credentials are incorrect!!"<<endl;
        cout<<"username: ";
            cin>>user;
        cout<<"password: ";
            cin>>pass;
        cout<<"|====================================|"<<endl;
    }

    display();
    while(true){
        //Choose transaction
        cout<<"1.Deposit\n2.Withdrawal\n3.Balance Inquiry\n4.Transfer Balance\n5.Log Out"<<endl;
        cout<<"|====================================|"<<endl;
        int ch, account, transfer, amt;
        cout<<"Pick a transaction from above: ";
        cin>>ch;
        switch(ch){
        case 1: {
        double amt;
        cout<<"Amount: ";
        cin>>amt;
        cout << "Deposit into: \n1.Savings \n2.Checking"<<endl;
        cin >> account;
            if(account == 1){
                if (abs(amt - int(amt)) > 0) {
                        cout << "Please enter the integer values"<< endl<<
                                "ATM does not deposit coins\n";
                    } 
                    else
                        sAcc = deposit(amt, sAcc);
            }
            else
                if (abs(amt - int(amt)) > 0) {
                        cout << "Please enter the integer values"<< endl<<
                                "ATM does not deposit coins\n";
                    } 
                    else
                        cAcc = deposit(amt, cAcc);
            tCount = tCount + 1;
            cout<<"|====================================|"<<endl;
        display();
        break;
        }

        case 2: {
        double amt;
        cout<<"Amount: ";
        cin>>amt;
        cout << "Withdrawl from: \n1.Savings \n2.Checking"<<endl;
        cin >> account;
            if(account == 1)
                if (abs(amt - int(amt)) > 0) {
                        cout << "Please enter the integer values"<< endl<<
                                "ATM does not deposit coins\n";
                        tCount++;
                    } 
                    else
                sAcc = withdrawal(amt, sAcc);

            else
                if (abs(amt - int(amt)) > 0) {
                        cout << "Please enter the integer values"<< endl<<
                                "ATM does not deposit coins\n"; 
                    } 
                    else
                cAcc = withdrawal(amt, cAcc);
            tCount = tCount + 1;
            cout<<"|====================================|"<<endl;
        display();
        break;
        }
        case 3: display(); break;
        case 4: {
            double amt;
            cout<<"Amount: ";
                cin>>amt;
            cout<<"Transfer to: \n1.Savings \n2.Checking"<<endl;
                cin >>transfer;

                if(transfer == 1){
                    if (abs(amt - int(amt)) > 0) {
                        cout << "Please enter the integer values"<< endl<<
                                "ATM does not deposit coins\n";
                        tCount++;
                    } 
                    else{
                    cAcc = cAcc - amt;
                    sAcc = sAcc + amt;
                    }
                }
                else{
                    if (abs(amt - int(amt)) > 0) {
                        cout << "Please enter the integer values"<< endl<<
                                "ATM does not deposit coins\n";
                        tCount++;
                    } 
                    else{
                    cAcc = cAcc + amt;
                    sAcc = sAcc - amt;
                    }
                }
            cout<<"|====================================|"<<endl;
          tCount = tCount + 1;
            display();
          break;    
        } 

        case 5: exit(0);
        }
    }
}