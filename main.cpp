// #include "lib/bank.h"
#include "lib/customer.h"

int main(){
  CustomerManagement customer;

  // customer.newRegistration();

  if(customer.login()){
    cout << "Sucessful" << endl;
  }
  else{
    cout << "Failed." << endl;
  }
  return 0;
}