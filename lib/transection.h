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
    void getTrans(int accountNum){
      int count=0; 
      ifstream inFile(FILENAME);

      while(inFile.read((char*)&transection, sizeof(Transection))&&count<10){
        output(transection);
        count++;
      }
    }
};
#undef FILENAME