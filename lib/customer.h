#include "header.h"

#pragma once

#define FILENAME "resources/customer.dat"

class Customer{
  public:
    char name[50];
    char cnic[16];
};
class CustomerManagement{
  private:
    Customer customer;
  public:
    void newRegistration();
    bool login();
};
/**********************
    newRegistration()
***********************/
void CustomerManagement::newRegistration(){
  cout << "Enter Name: "; cin.getline(customer.name,50);
  cout << "Enter CNIC: "; cin.getline(customer.cnic,16);

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

      if(!strcmp(tmpCustomer.name, customer.name)){
        if(!strcmp(tmpCustomer.cnic, customer.cnic)){
          return 1;
        }
      }
    }
    inFile.close();
  }
  return 0;
}