#include "customer.h"

#pragma once

enum EmployeeType {Simple, Manager};

class Employee{
  public:
    char name[20];
    int empId;
    EmployeeType employeeType=Simple;

};
class EmployeeManagement{
  private:
    Employee employee, employeeSession;
    CustomerManagement customer;
    char choice;

  public:
    void menu();
    void menuHandler();
    bool login();
};
/***********************
        menu()
***********************/
void EmployeeManagement::menu(){
  system("cls");
  cout << "1. New Account" << endl;
  cout << "2. Update Account" << endl;
  cout << "3. Remove Account" << endl;
  // Skipped
  cout << "4. Get Infomation of an account" << endl;
  cout << "5. Display All Accounts" << endl;
  cout << "6. Withdraw Money" << endl;
  cout << "7. Deposit Money" << endl;
  cout << "0. Logout" << endl;

  do{
  choice = getch();
  }
  while(choice!='1' && choice!='2' && choice!='3' && choice!='4' && choice!='5' && choice!='6' && choice!='7' && choice!='0');
} 
/***********************
      menuHandler()
***********************/
void EmployeeManagement::menuHandler(){
  menu();
  switch(choice){
    case '1':
      customer.newRegistration();
      getch();
      menuHandler();
      break;
    case '2':
      customer.updateInfo();
      getch();
      menuHandler();
      break;
    case '3':
      customer.removeCustomer();
      getch();
      menuHandler();
      break;
    case '4':
      int an;
      cin.clear();
      cin.ignore(124, '\n');
      cout << "Enter Account Number: "; cin >> an;
      customer.getInfo(an);
      getch();
      menuHandler();
      break;
    case '5':
      customer.listAllAccounts();
      getch();
      menuHandler();
      break;
    case '6':
      cout << "1. Checkbook" << endl;
      cout << "2. Credit Card" << endl;
      do{
        choice = getch();
      }
      while(choice!='1' && choice!='2');
      switch(choice){
        case '1':
          customer.withdraw(CheckBook);
          break;
        case '2':
          customer.withdraw(CreditCard);
          break;
      }
      getch();
      menuHandler();
      break;
    case '7':
      customer.deposit();
      getch();
      menuHandler();
      break;
    case '0':
      break;
  }
}
/**********************
        login()
***********************/
bool EmployeeManagement::login(){
  char name[20];
  char password[20];

  cin.clear();
  cin.ignore(124, '\n');

  cout << "Name: ";cin.getline(name,20) ;
  cout << "Password: "; cin.getline(password, 20);

  if(!strcmp(name,"employee") && !strcmp(password, "bank123")){
    return 1;
  }
  return 0;
}