#include "header.h"
#include "customer.h"
#include "employee.h"

class Bank{
  private:
    char choice;
    EmployeeManagement employee;
    CustomerManagement customer;
  public: 
    void menu();
    void menuHandler();
};

/******************
      menu()
******************/
void Bank::menu(){
  system("cls");
  cout << "1. Login as Bank Employee." << endl;
  cout << "2. Login as Bank Customer." << endl;
  cout << "0. Exit" << endl;

  do{
    choice = getch();
  }
  while(choice!='1' && choice!='2' && choice!='0');
}
/******************
    menuHandler()
******************/
void Bank::menuHandler(){
  menu();
  switch(choice){
    case '1':
      if(employee.login()){
        employee.menuHandler();
      }
      menuHandler();
      break;
    case '2':
      if(customer.login()){
        customer.menuHandler();
      }
      menuHandler();
      break;
  }
}
