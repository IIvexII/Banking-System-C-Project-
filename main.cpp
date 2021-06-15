// #include "lib/bank.h"
#include "lib/customer.h"
#include "lib/card.h"

int main(){
  CustomerManagement customer;

  // customer.newRegistration();
  customer.listAllAccounts();
  // customer.deposit();
  // customer.withdrow(CreditCard);
  // customer.removeCustomer();
  customer.updateInfo();

  return 0;
}