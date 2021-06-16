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
      cout << t.accountNumber << " " << t.state << " " << t.amount << endl;
    }
    void getTrans(int accountNum, int limit=10){
      int count=1;
      ifstream inFile(FILENAME);

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
      
      inFile.close();
    }
};
#undef FILENAME