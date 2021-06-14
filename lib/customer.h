#include "header.h"

#pragma once

#define FILENAME "resources/customer.dat"

class Customer{
  public:
    char name[20];
    char cnic[16];
    char address[100];
    char telephoneNumber[14];
    char dateOfBirht[15];
    int accountNumber;
};
class CustomerManagement{
  private:
    Customer customer;

    void output(Customer);
  public:
    void newRegistration();
    bool login();
    bool accountNumChecker(int);
    int accountNumGenerator();
    void listAllAccounts();
};
/**********************
    newRegistration()
***********************/
void CustomerManagement::newRegistration(){
  cout << "Enter Name: "; cin.getline(customer.name,20);
  cout << "Enter CNIC: "; cin.getline(customer.cnic,16);
  cout << "Enter Address: "; cin.getline(customer.address,100);
  cout << "Enter Telephone: "; cin.getline(customer.telephoneNumber,14);
  cout << "Enter Date Of Birth: "; cin.getline(customer.dateOfBirht,15);

  customer.accountNumber = accountNumGenerator();

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
  Customer tmpCustomer;
  cout << "Enter Name: "; cin.getline(customer.name,50);
  cout << "Enter CNIC: "; cin.getline(customer.cnic,16);

  ifstream inFile(FILENAME, ios::in);

  if(inFile.is_open()){
    while(!inFile.eof()){
      inFile.read((char*)&tmpCustomer, sizeof(Customer));

      // Compare the user's entered information with
      // the information in the file.
      if(!strcmp(tmpCustomer.name, customer.name)){
        if(!strcmp(tmpCustomer.cnic, customer.cnic)){
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

  srand (time(NULL));

  while(accountNumChecker(accountNum)){
    accountNum = rand() % 999999999 + 485611111;
  }

  return accountNum;
}
/*************************
        output()
*************************/
void CustomerManagement::output(Customer c){
  cout << setw(20) << left << c.name
       << setw(10) << right << c.accountNumber
       << setw(20) << c.cnic
       << setw(16) << c.telephoneNumber
       << setw(15) << c.dateOfBirht << endl; 
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