#include "header.h"
#include "transection.h"

#pragma once

#define FILENAME "resources/customer.dat"

enum AccountTypes {CurrentAccount=1, SavingAccount=2};
enum CredtCardType {MasterCard=1, VisaCard=2, LocalCard=3};
enum WithdrawTypes {CheckBook, CreditCard};

class Customer{
  public:
    char name[20];
    char cnic[16];
    char address[100];
    char telephoneNumber[14];
    char dateOfBirht[15];
    int accountNumber;
    int balance=0;
    AccountTypes accountType;
    CredtCardType credtCardType;
    int cardNumber;
    int limit;
    int intrestRate;
    char password[20];
};
class CustomerManagement{
  private:
    Customer customer, customerSession;
    TransectionManagement transection;
    double tax=0.025;
    char choice;

    void output(Customer);
  public:
    void banner();
    void menu();
    void menuHandler();
    void newRegistration();
    bool login();
    bool accountNumChecker(int);
    int accountNumGenerator();
    bool cardNumChecker(int);
    int cardNumGenerator();
    void listAllAccounts();
    void deposit();
    void withdraw(WithdrawTypes);
    void removeCustomer();
    void updateInfo();
    void getInfo(int);
};
/***********************
        deposit()
************************/
void CustomerManagement::deposit(){
  int money, an, pos;
  char state[10];
  cout << "Enter Account Number: "; cin >> an;
  cout << "Enter Money: "; cin >> money;

  fstream file(FILENAME, ios::in | ios::out | ios::binary);

  if(file.is_open()){
    file.seekp(0);

    while(!file.eof()){
      pos = file.tellg();
      file.read((char*)&customer, sizeof(Customer));
      if(customer.accountNumber==an){
        customer.balance += money;
        file.seekp(pos);

        file.write((char*)&customer, sizeof(Customer));
        TransectionManagement transection;

        strcpy(state, "deposited");
        transection.write(customer.accountNumber, money, state);
        break;
      }
    }
    file.close();
  }
}
/**********************
      withdrow()
***********************/
void CustomerManagement::withdraw(WithdrawTypes wt ){
  int amount, pos, an;
  int ccn;
  TransectionManagement transection;
  char state[10];
  char cnic[16];

  switch(wt){
    case CreditCard:
      {
        int flag;

        cout << "Enter Credit Card Number: "; cin >> ccn;

        cin.clear();
        cin.ignore(124,'\n');
        cout << "Enter Ammount: "; cin >> amount;

        fstream file1(FILENAME, ios::in | ios::out | ios::binary);

        if(file1.is_open()){
          file1.seekp(0);

          while(!file1.eof()){
            pos = file1.tellg();
            file1.read((char*)&customer, sizeof(Customer));
            if(customer.cardNumber==ccn){
              if(amount<=customer.balance && amount<=customer.limit){

                customer.balance -= amount + tax*amount + (customer.intrestRate/100)*amount;
                customerSession.balance = customer.balance;
                file1.seekp(pos);

                file1.write((char*)&customer, sizeof(Customer));
                strcpy(state, "withdraw");
                transection.write(customer.accountNumber, amount, state);

                flag = 2;
                break;
              }
              else if(amount > customer.limit){
                flag = 3;
              }
              else if(amount > customer.balance){
                flag = 1;
              }
              else{
                flag = 0;
              }
            }
          }
          switch(flag){
            case 0:
              cout << "Operation Failed." << endl;
              break;
            case 1:
              cout << "Insufficient Balance." << endl;
              break;
            case 2:
              cout << "Operation Sucessful." << endl;
              break;
            case 3:
              cout << "Limit Exceed." << endl;
              break;
          }
          file1.close();
        }
      }
        break;
    case CheckBook:
      {
        int flag;

        cout << "Enter Account Number: "; cin >> an;
        cout << "Enter CNIC: "; cin.getline(cnic, 16);
        cin.clear();
        cin.ignore(124,'\n');
        cout << "Enter Amount: "; cin >> amount;

        fstream file1(FILENAME, ios::in | ios::out | ios::binary);

        if(file1.is_open()){
          file1.seekp(0);

          while(!file1.eof()){
            pos = file1.tellg();
            file1.read((char*)&customer, sizeof(Customer));
            if(customer.accountNumber==an && strcmp(customer.cnic, cnic)){
              if(amount<=customer.balance){
                customer.balance -= amount+tax*amount;
                customerSession.balance = customer.balance;

                file1.seekp(pos);

                file1.write((char*)&customer, sizeof(Customer));

                strcpy(state, "withdraw");
                transection.write(customer.accountNumber, amount, state);
                flag = 2;
              }
              else if(amount > customer.limit){
                flag = 3;
              }
              else if(amount > customer.balance){
                flag = 1;
              }
              else{
                flag = 0;
              }
            }
          }
          switch(flag){
            case 0:
              cout << "Operation Failed." << endl;
              break;
            case 1:
              cout << "Insufficient Balance." << endl;
              break;
            case 2:
              cout << "Operation Sucessful." << endl;
              break;
            case 3:
              cout << "Limit Exceed." << endl;
              break;
          }
          file1.close();
        }
      }
      break;
  }
  
}
/***********************
        banner()
************************/
void CustomerManagement::banner(){
  system("cls");
  
  cout << "*******************************************************" << endl;
  cout << " Name: " << customerSession.name << "\t\tBalance: Rs. " << customerSession.balance << endl;
  cout << " Account Number: " << customerSession.accountNumber << "\tCredit Card:" << customerSession.cardNumber << endl;
  cout << "*******************************************************" << endl;
}

/***********************
        menu()
************************/
void CustomerManagement::menu(){
  banner();
  cout << "1. Mini Statement" << endl;
  cout << "2. Withdraw Money Via Credit Card" << endl;
  cout << "3. Withdraw Money Via Check Book" << endl;
  cout << "4. Balance Inquiry" << endl;
  cout << "5. Transection History" << endl;
  cout << "0. Logout" << endl;

  do{
    choice = getch();
  }while(choice!='1' && choice!='2' && choice!='3' && choice!='4' && choice!='5' && choice!='0' );
}
/**********************
      menuHandler()
***********************/
void CustomerManagement::menuHandler(){
  menu();
  switch(choice){
    case '1':
      transection.getTrans(customerSession.accountNumber);
      getch();
      menuHandler();
      break;
    case '2':
      withdraw(CreditCard);
      getch();
      menuHandler();
      break;
    case '3':
      withdraw(CheckBook);
      getch();
      menuHandler();
      break;
    case '4':
      cout << "Your Balance is Rs. " << customerSession.balance << endl;
      getch();
      menuHandler();
      break;
    case '5':
      transection.getTrans(customerSession.accountNumber, -1);
      getch();
      menuHandler();
      break;
  }
}
/**********************
    newRegistration()
***********************/
void CustomerManagement::newRegistration(){
  int ct, at;

  cin.clear();
  cin.ignore(124, '\n');
  cout << "Enter Name: "; cin.getline(customer.name,20);
  cout << "Enter CNIC: "; cin.getline(customer.cnic,16);
  cout << "Enter Address: "; cin.getline(customer.address,100);
  cout << "Enter Telephone: "; cin.getline(customer.telephoneNumber,14);
  cout << "Enter Date Of Birth: "; cin.getline(customer.dateOfBirht,15);
  cout << "1. Master Card"<< endl;
  cout << "2. Visa Card"<< endl;
  cout << "3. Local Card"<< endl;
  cin.clear();
  cin.ignore(124, '\n');
  cout << "Enter Credit Card Type: "; cin >> ct;
  cout << "1. Current Account"<< endl;
  cout << "2. Saving Account"<< endl;
  cin.clear();
  cin.ignore(124, '\n');
  cout << "Enter Account Type: "; cin >> at;
  cin.clear();
  cin.ignore(124, '\n');
  cout << "Enter Password: "; cin.getline(customer.password, 20);
  
  switch(ct){
    case MasterCard:
      customer.intrestRate = 18;
      customer.limit = 50000;
      break;
    case VisaCard:
      customer.intrestRate = 10;
      customer.limit = 100000; 
      break;
    case 3:
      customer.intrestRate = 25;
      customer.limit = 10000;
      break;
  }

  customer.cardNumber = cardNumGenerator();
  Sleep(10);
  customer.accountType = static_cast<AccountTypes>(at);

  customer.accountNumber = accountNumGenerator();

  customer.balance = 0;

  // Output to the file
  ofstream outFile(FILENAME, ios::app);

  if(outFile.is_open()){
    outFile.write((char*)&customer, sizeof(Customer));
    outFile.close();
  }
  else{
    cout << "Error: unable to open file" << endl;
  }
}
/**********************
        login()
**********************/
bool CustomerManagement::login(){
  cin.clear();
  cin.ignore(124, '\n');
  cout << "Account Number: "; cin >> customer.accountNumber;
  cin.clear();
  cin.ignore(124, '\n');
  cout << "Password: "; passwdInput(customer.password);

  ifstream inFile(FILENAME, ios::in);

  if(inFile.is_open()){
    while(!inFile.eof()){
      inFile.read((char*)&customerSession, sizeof(Customer));

      // Compare the user's entered information with
      // the information in the file.
      if(customerSession.accountNumber==customer.accountNumber){
        if(!strcmp(customerSession.password, customer.password)){
          inFile.close(); // close file
          return 1; // if sucessfully logged in.
        }
      }
    }
    inFile.close();
  }
  return 0; // if failed to logged in
}
/*********************
  accountNumChecker()
**********************/
bool CustomerManagement::accountNumChecker(int accountNum){
  Customer tmpCustomer;
  ifstream inFile(FILENAME, ios::in);

  if(inFile.is_open()){
    while(!inFile.eof()){
      inFile.read((char*)&tmpCustomer, sizeof(Customer));

      if(accountNum==tmpCustomer.accountNumber){
        inFile.close();
        return 1;
      }
    }
    inFile.close();
  }
  return 0;
}

/************************
  accountNumGenerator()
*************************/
int CustomerManagement::accountNumGenerator(){
  int accountNum;

  srand (time(0));

  while(accountNumChecker(accountNum)){
    accountNum = 111111111 + rand() % (( 999999999 + 1 ) - 111111111);
  }


  return accountNum;
}
/*********************
  cardNumChecker()
**********************/
bool CustomerManagement::cardNumChecker(int cardNum){
  Customer tmpCustomer;
  ifstream inFile(FILENAME, ios::in);

  if(inFile.is_open()){
    while(!inFile.eof()){
      inFile.read((char*)&tmpCustomer, sizeof(Customer));

      if(cardNum==tmpCustomer.cardNumber){
        inFile.close();
        return 1;
      }
    }
    inFile.close();
  }
  return 0;
}

/************************
    cardNumGenerator()
*************************/
int CustomerManagement::cardNumGenerator(){
  int cardNum;

  srand (time(0));

  while(cardNumChecker(cardNum)){
    cardNum = 111111111 + rand() % (( 999999999 + 1 ) - 111111111);
  }


  return cardNum;
}
/*************************
        output()
*************************/
void CustomerManagement::output(Customer c){
  cout << setw(20) << left << c.name
       << setw(10) << right << c.accountNumber
       << setw(20) << c.cnic
       << setw(16) << c.telephoneNumber
       << setw(15) << c.dateOfBirht; 
  // if(c.credtCardType==MasterCard){
  //   cout << setw(13) << "Master Card";
  // }else if(c.credtCardType==VisaCard){
  //   cout << setw(13) << "Visa Card";
  // }else if(c.credtCardType==LocalCard){
  //   cout << setw(13) << "Local Card";
  // }
  // if(c.accountType == CurrentAccount){
  //   cout << setw(16) << "Current Account";
  // }else if(c.accountType == SavingAccount){
  //   cout << setw(16) << "Saving Account";
  // }
  cout << setw(20)<< c.cardNumber;
  cout << setw(20) << c.balance << endl;
}
/************************
      listAllAccount()
************************/
void CustomerManagement::listAllAccounts(){
  Customer tmpCustomer;
  ifstream inFile(FILENAME, ios::in);

  if(inFile.is_open()){
    while(inFile.read((char*)&tmpCustomer, sizeof(Customer))){
      output(tmpCustomer);
    }
    inFile.close();
  }
}
/*************************
      removeCustomer()
**************************/
void CustomerManagement::removeCustomer(){
  int an;
  char TMPFILENAME[] = "resources/tmp.dat";

  cout << "Enter Account Number: "; cin >> an;

  ifstream inFile(FILENAME);
  ofstream outFile(TMPFILENAME);

  while(inFile.read((char*)&customer, sizeof(Customer))){

    if(customer.accountNumber==an){
      cout << "Deleted Sucessfully!" << endl;
    }
    else{
      outFile.write((char*)&customer, sizeof(Customer));
    }
  }
  inFile.close();
  outFile.close();

  remove(FILENAME);
  rename(TMPFILENAME, FILENAME);
}
/*************************
        updateInfo()
**************************/
void CustomerManagement::updateInfo(){
  int an,pos, at;

  cin.clear();
  cin.ignore(124, '\n');
  cout << "Enter Account Number: "; cin >> an;

  fstream file(FILENAME, ios::in | ios::out | ios::binary);

  while(!file.eof()){

    pos = file.tellg();
    file.read((char*)&customer, sizeof(Customer));

    if(customer.accountNumber == an){
      char choice;

      cout << "1. Name" << endl;
      cout << "2. Address" << endl;
      cout << "3. Telephone Number" << endl;
      cout << "4. Account Type" << endl;
      cout << "0. Back" << endl;
      cout << "Choose: "; cin >> choice; 
      switch(choice){
        case '1':
          cin.clear();
          cin.ignore(124, '\n');
          cout << "Enter Name: "; cin.getline(customer.name, 20);
          break;
        case '2':
          cin.clear();
          cin.ignore(124, '\n');
          cout << "Enter Address: "; cin.getline(customer.address, 100);
          break;
        case '3':
          cin.clear();
          cin.ignore(124, '\n');
          cout << "Enter Telephone: "; cin.getline(customer.telephoneNumber, 14);
          break;
        case '4':
          cout << "1. Current Account: " << endl;
          cout << "2. Saving Account: " << endl;
          cin.clear();
          cin.ignore(124, '\n');
          cout << "Enter Account Type: "; cin >> at;
          customer.accountType = static_cast<AccountTypes>(at);
          break;
      }

      file.seekp(pos);

      file.write((char*)&customer, sizeof(Customer));
      
      file.close();

      break;
    }
  }
  file.close();
}
/*************************
        getInfo()
**************************/
void CustomerManagement::getInfo(int accountNum){
  ifstream inFile(FILENAME);

  while(!inFile.eof()){
    inFile.read((char*)&customer, sizeof(Customer));

    if(customer.accountNumber == accountNum){
      output(customer);

      inFile.close();
      return;
    }
  }
}