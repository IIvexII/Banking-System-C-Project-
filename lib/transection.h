#include "header.h"
#define FILENAME "resources/transections.dat"

class Transection{
  public:
    int accountNumber;
    int amount;
    char state[10]; // deposited or withdraw 
};

class TransectionManagement{
  private:
    Transection transection;
  public:
    void write(int accountNum, int am, char* st ){
      transection.accountNumber = accountNum;
      transection.amount = am;
      strcpy(transection.state, st);
      ofstream outFile(FILENAME, ios::app);

      if(outFile.is_open()){
        outFile.write((char*)&transection, sizeof(Transection));
        outFile.close();
      }
    }
    void output(Transection t){
      cout << "| " << setw(18) << left << t.accountNumber
           << "| " << setw(11) << t.amount
           << "| " << setw(13) << t.state
           <<  "|"  << endl;
    }
    void getTrans(int accountNum, int limit=10){
      system("cls");
      int count=1;
      ifstream inFile(FILENAME);

      tranHeader();

      if(limit==10){
        while(inFile.read((char*)&transection, sizeof(Transection))){
          if(transection.accountNumber==accountNum && count<=limit){
            output(transection);
            count++;
          }
        }
      }else{
        while(inFile.read((char*)&transection, sizeof(Transection))){
          if(transection.accountNumber==accountNum){
            output(transection);
          }
        }
      }
      tranFooter();
      inFile.close();
    }
    void tranHeader(){
      cout << " _______________________________________________" << endl;
      cout  << "| " << left << setw(18) << "Account No."
            << setw(13) << "| Amount"
            << setw(15) << "| Status"
            << "|" <<endl;
      cout << "|___________________|____________|______________|" << endl;
    }
    void tranFooter(){
      cout << "|_______________________________________________|" << endl;
    }
};
#undef FILENAME