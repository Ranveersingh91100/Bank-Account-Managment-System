#include<iostream>
#include<string>
#include<fstream>
#include<vector>
#include<ctime>



using namespace std;

void Red()      {   cout<<"\033[31m";   } 
void Green()    {   cout<<"\033[32m";   }
void Yellow()   {   cout<<"\033[33m";   }
void Blue()     {   cout<<"\033[34m";   }
void Magenta()  {   cout<<"\033[35m";   }
void Cyan()     {   cout<<"\033[36m";   }
void White()    {   cout<<"\033[37m";   }
void Reset()    {   cout<<"\033[0m";    }  


string generateCardNumber()
{
    string cardNumber;
    srand(time(0));
    for(int i=0; i<16; i++)
    {
        cardNumber += to_string(rand() % 10);
    }
    return cardNumber;
}

string generateExpiryDate()
{
    string expiryDate;
    time_t t = time(0);
    tm *now = localtime(&t);
    int currentMonth = now->tm_mon + 1; //tm+mon is 0-11
    int currentYear = now->tm_year + 1900; //tm_year is year since 1900
    currentYear +=5; // 5 year from now

    expiryDate = (currentMonth > 9 ? to_string(currentMonth) : "0"  +  to_string(currentMonth))
    +"/" + to_string(currentYear);

    return expiryDate;
}

string generateCVV()
{
    string cvv;
    srand(time(0));
    for(int i=0; i<3; i++)
    {
        cvv += to_string(rand() % 10);
    }
    return cvv;
}

string generatePin()
{
    string pin;
    srand(time(0));
    for(int i=0; i< 4; i++)
    {
        pin += to_string(rand() % 10);
    }
    return pin;

}


class bankAccount {
    protected:
         string bankName ="RSBOI";  //RSBOI101
         int bankCode;
         string accountHolderName;
         string accountNumber;
         string accountPassword;
         string addharNumber;
         string email;
         string phoneNumber;
         double balance;

         vector<string> transactionHistory;


    public:
        void savetoFile();
        void loadFromfile();
        void mainMenu();
        void createAccount();
        void loginBankAccount();
        void depositMoney();
        void withdrawMoney();
        void checkBalance();
        void accountDetails();
        void alltransactionHistory();
        void applyDebitCard();
};

void bankAccount::savetoFile(){
    ofstream file(accountNumber+".txt");
    if(file.is_open()){
        file<<accountHolderName << endl;
        file<<accountNumber<< endl;
        file<<accountPassword << endl;
        file<<addharNumber<< endl;
        file<<email << endl;
        file<<phoneNumber << endl;
        file<<balance << endl;
        
        for(auto transaction : transactionHistory){
            file << transaction << endl;
        }
        file.close();
    }else{
        cout << "Error opening file" << endl;
    }

}

void bankAccount::loadFromfile(){
    ifstream file(accountNumber + ".txt");
    if(file.is_open()){
        getline(file,accountHolderName);
        getline(file,accountNumber);
        getline(file,accountPassword);
        getline(file,addharNumber );
        getline(file, email);
        getline(file,phoneNumber);
        file >> balance;
        file.ignore();
        string transaction ;
        while(getline(file,transaction)){
            transactionHistory.push_back(transaction);
        }
        file.close();
    } else{
        cout<< "Error opening file" << endl;
    }
}

  void bankAccount::mainMenu() {
    int choice;
    
    do {
        cout<<"----------------------------------"<<endl;
        cout<<" Enter 1 for Deposit Money "<<endl;
        cout<<" Enter 2 for Withdraw Money "<<endl;
        cout<<" Enter 3 for Check Balance "<<endl;
        cout<<" Enter 4 for Account Details "<<endl;
        cout<<" Enter 5 for All Transaction History "<<endl;
        cout<<" Enter 6 for Apply Debit Card " << endl;
        cout<<" Enter 7 for Logout "<<endl;
        cout<<"----------------------------------"<<endl;
        cout<<" Enter your choice: ";
        cin >> choice;
        cin.ignore();
        system("cls");

        switch (choice)  {
            case 1:
                depositMoney();
                break;
            case 2:
                withdrawMoney();
                break;
            case 3:
                checkBalance();
                break;
            case 4:
                accountDetails();
                break;
            case 5:
                alltransactionHistory();
                break;
            case 6:
                applyDebitCard();
                break;
            case 7:
                cout << "Logging out...!" << endl;
                savetoFile();
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    } while (choice != 6);
}

void bankAccount::createAccount()   {
    Green();
    cout<<"     Create Account    "<<endl;
    cout<<"-----------------------"<<endl;
    cout<<"Enter Your Full Name   : ";
    getline(cin, accountHolderName);
    cout<<"Enter Email Id         : ";
    getline(cin, email);
    cout<<"Enter Phone Number     : ";
    getline(cin, phoneNumber);
    cout<<"Enter Addhar Number    : ";
    getline(cin, addharNumber);
    cout<<"Enter Account Password : ";
    getline(cin, accountPassword);
    cout<<"-----------------------"<<endl;
    Reset();

    balance = 500.0;
    ifstream file("Ranveer-Singh-Bank-Of-India.txt");
    if(file.is_open())  {

        file>>bankCode;
        file.close();
        ofstream output("Ranveer-Singh-Bank-Of-India.txt");

        if(output.is_open())    {

            output<<bankCode+1;
            output.close();
        }
        else {
            cout << "Error opening file!" << endl;
        }
    } else {
        cout << "Error opening file!" << endl;
    }

    accountNumber = bankName+ to_string(bankCode);
    transactionHistory.push_back("Deposit :- " + to_string(balance));
    Yellow();

    cout << "Account Created Successfully!" << endl;
    cout << "Account Number   : " << accountNumber << endl;
    cout << "Account Password : " << accountPassword << endl;
    cout << "Minimum Balance  : 500.0" << endl;
    cout<<"-----------------------"<<endl;

    Reset();
    savetoFile();
}

void bankAccount::loginBankAccount() {
    string enteredAccountNumber;
    string enteredPassword;
    Blue();
    
    cout << "     Login Account     " << endl;
    cout << "-----------------------" << endl;
    cout << "Enter Account Number   : ";
    getline(cin, enteredAccountNumber);
    accountNumber = enteredAccountNumber;
    
    ifstream file(enteredAccountNumber + ".txt");
    if (file.is_open()) {
        loadFromfile();
        
        cout << "Enter Account Password : ";
        getline(cin, enteredPassword);
        
        if (accountPassword == enteredPassword) {
            
            cout << "Login Successful!" << endl;
            mainMenu();
        } else {
            cout << "Invalid Password!" << endl;
        }
        file.close();
    } else {
        cout << "Account not found!" << endl;
    }
}

void bankAccount::depositMoney() {
    double amount;
    cout << "Enter Amount to Deposit : ";
    cin >> amount;
    cin.ignore();
    
    if (amount > 0) {
        
        balance += amount;
        transactionHistory.push_back("Deposit  :- " + to_string(amount));
        ofstream file(accountNumber + ".txt", ios::app);
        
        if(file.is_open()) {
            cout << "Deposit Successful!" << endl;
            cout << "New Balance: " << balance << endl;
            file<<"Deposit  :- " + to_string(amount) + "\n";
            file.close();
        } else {
            cout << "Deposit Not Successful!" << endl;
        }
    } else {
        cout << "Invalid Amount!" << endl;
    }
}

void bankAccount::withdrawMoney() {
    double amount;
    cout << "Enter Amount to Withdraw : ";
    cin >> amount;
    cin.ignore();
   
    if (amount > 0 && amount <= balance) {
        balance -= amount;
        transactionHistory.push_back("Withdraw :- " + to_string(amount));
        ofstream file(accountNumber + ".txt", ios::app);
        if(file.is_open()) {
            cout << "Withdraw Successful!" << endl;
            cout << "New Balance: " << balance << endl;
            file<<"Withdraw :- " + to_string(amount) + "\n";
            file.close();
        } else {
            cout << "Withdraw Not Successful!" << endl;
        }
    } else {
        cout << "Invalid Amount!" << endl;
    }
}

void bankAccount::checkBalance()   {
    cout << "Current Balance : " << balance << endl;
    cout<<"-----------------------"<<endl;
}

void bankAccount::accountDetails() {
    
    Magenta();
    cout<<"|------------------------------|"<<endl;
    cout<<"|  Ranveer Singh Bank Of India   |"<<endl;
    cout<<"|------------------------------|"<<endl;
    Blue();

    cout << "Account Holder Name : " << accountHolderName << endl;
    cout << "Account Number      : " << accountNumber << endl;
    cout << "Addhar Number       : " << addharNumber << endl;
    cout << "Email Id            : " << email << endl;
    cout << "Phone Number        : " << phoneNumber << endl;
    cout << "Current Balance     : " << balance << endl;
    cout<<"-------------------------------"<<endl;
    Reset();
}

void bankAccount::alltransactionHistory() {
    cout << " Transaction History :- " << endl;
    Yellow();
    cout<<"-------------------------------"<<endl;
    cout << "Account Holder Name : " << accountHolderName << endl;
    cout << "Account Number      : " << accountNumber << endl;
    
    for (const auto& transaction : transactionHistory) {
        cout << transaction << endl;
    }
    cout<<"-------------------------------"<<endl;
    Reset();
}

void bankAccount::applyDebitCard()
{
    string cardNumber;
    string expiryDate;
    string cvv;
    string pin;
    string addharNo;
    string accountNo;
    cout << "Apply for Debit Card" << endl;
    cout<<"----------------------------------" << endl;
    cout << "Enter Account Number      : ";
    getline(cin,accountNo);
    cout << "Enter Addhar Number       : ";
    getline(cin,addharNo);
    cout << "--------------------------------"<< endl;
    if(accountNo == accountNumber && addharNo == addharNumber)
    {
        cardNumber = generateCardNumber();
        expiryDate = generateExpiryDate();
        cvv = generateCVV();
        pin = generatePin();

         ofstream file(cardNumber + ".txt");
        if(file.is_open())
        {
            file<<cardNumber << "\n";
            file <<accountNumber <<"\n";
            file <<expiryDate <<"\n";
            file <<cvv <<"\n";
            file <<pin <<"\n";
            file.close();
            cout<<"-------------------------------"<< endl;
            cout<<"Debit Card Apply Successfully!" << endl;
            cout<<"-------------------------------"<< endl;
            cout<<"Debit Card Holder Name  : "<< accountHolderName << endl;
            cout<<"Debit Card Number       : "<< cardNumber << endl;
            cout<<"Expire Date             : "<< expiryDate << endl;
            cout<<"cvv                     : "<< cvv << endl;
            cout<<"pin                     : "<< pin << endl;
            cout<<"-------------------------------"<< endl;
        }
        else
        {
            cout << "Error opening file!" << endl;
            
        }

    }
    else
        {
            cout << " Invalid  AccountNumber or AddharNumber!" << endl;
        }

    }

int main() {
      
    
    
    bankAccount account;
    int choice;
   
    do {
        cout<<" Welcome to Ranveer Singh Bank Of India" << endl;
        cout<<"--------------------------------------"<<endl;
        cout << "1. Create Account" << endl;
        cout << "2. Login" << endl;
        cout << "3. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;
        
        cin.ignore();
        system("cls");
        switch (choice) {
            case 1:
                account.createAccount();
                break;
            case 2:
                account.loginBankAccount();
                break;
            case 3:
                cout << "Exiting..." << endl;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    } while (choice != 3);
    return 0;
}