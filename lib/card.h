#pragma once
#define FILENAME "resources/customer.dat"

class Card{
  protected:  
    int intrestRate;
    int limit;
    int number;

  public:
    Card(int i, int l): intrestRate(i), limit(l) { }
    virtual int getIntrestRate() = 0;
    virtual int getLimit() = 0;
    virtual int getNumber() = 0;
    void setNumber(int n){
      number=n;
    }

};
class Master:public Card{
  public:
    Master(): Card(18, 50000) { }

    int getIntrestRate(){
      return intrestRate;
    }
    int getLimit(){
      return limit;
    }
    int getNumber(){
      return number;
    }
};
class Visa: public Card{
  private:
    int points;
  public:
    Visa(): Card(10, 100000) { }
    void addPoint(int p){
      points += p;
    }
    int getIntrestRate(){
      return intrestRate;
    }
    int getLimit(){
      return limit;
    }
    int getNumber(){
      return number;
    }
};
class Local:public Card{
  public:
    Local(): Card(25, 10000) { }
    int getIntrestRate(){
      return intrestRate;
    }
    int getLimit(){
      return limit;
    }
    int getNumber(){
      return number;
    }
};