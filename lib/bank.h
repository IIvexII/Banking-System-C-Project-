#include "header.h"

class Bank{
  private:
    char choice;

  public: 
    void menu();
    void menuHandler();
};

/******************
      menu()
******************/
void Bank::menu(){
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
        cout << "Sucessfully Logged in as employee." << endl;
      }
    case '2':
      if(customer.login()){
        cout << "Sucessfully Logged in as Customer." << endl;
      }
  }
}
