#pragma once 

void passwdInput(char *password){
  int index=0; 
  char character;

  while(character!='\r' && index<100){
    character = getch();
    if(character!='\r'){
        if(character!='\b' && character!='\t'){
            cout << "*";
            password[index] = character;
            index++;
        }
        else if(index!=0 && character!='\t'){
            index--;
            password[index]= '\0';
            cout << '\b' << " " << '\b';
        }
    }
  }
  password[index] = '\0';
  cout << endl;
}