#include <iostream>
#include <stdlib.h>
#include <limits>
#include <string>
#include <fstream>

using namespace std;

//global variables
int product_id[5];string product_name[5];int product_quantity[5];float product_price[5];int product_refill[5];
int coin_quantity[6];
string coin_name[6]={"5 PLN","2 PLN","1 PLN","0.5 PLN","0.2 PLN","0.1 PLN"};float coin_value[6]={5,2,1,0.5,0.2,0.1};
string line;
int choice,qty,n=0,k=0,cont=0;
bool invalidcode=0,firstiter=1,not_enough_product=0,notint=0,not_enough_credit=0;
float credit=0;

//function definitions
int ReadInt(const string & prompt);
void products_read();
void products_save();
float product_purchase(float crdt, int product_number);
float money_input(float cred);
float money_return(float crdt);
void money_read();
void money_save();
void money_edit();
void product_purchase_pointer(float *crdt, int *stock, float price);

// MAIN function
int main(){

    while(n<1){

        products_read();
        money_read();
        firstiter=0;

        system("clear");
        cout <<"    VENDING MACHINE    \n";
        cout <<"    Products:\n";
        cout <<"1 - "<<product_name[0]<<"\t\t"<<product_price[0]<<" PLN\t\t"<<product_quantity[0]<<" in stock\n";
        cout <<"2 - "<<product_name[1]<<"\t\t"<<product_price[1]<<" PLN\t\t"<<product_quantity[1]<<" in stock\n";
        cout <<"3 - "<<product_name[2]<<"\t\t"<<product_price[2]<<" PLN\t\t"<<product_quantity[2]<<" in stock\n";
        cout <<"4 - "<<product_name[3]<<"\t\t"<<product_price[3]<<" PLN\t\t"<<product_quantity[3]<<" in stock\n";
        cout <<"5 - "<<product_name[4]<<"\t\t"<<product_price[4]<<" PLN\t\t"<<product_quantity[4]<<" in stock\n\n";
        cout <<"6 - INPUT MONEY\n";
        cout <<"7 - RETURN MONEY\n\n";
        cout <<"Your current credit is: "<<credit<<" PLN.\n\n";

        // flags
        if(not_enough_product==1){
            cout<<"There was not enough stock of your product, sori.\n\n";
            not_enough_product=0;
        }
        if(invalidcode==1){
            cout<<"Input a valid number.\n\n";
            invalidcode=0;
        }
        if(not_enough_credit==1){
            cout<<"Not enough credit to make the purchase.\n\n";
            not_enough_credit=0;
        }


        choice = ReadInt("Please select your product: ");

        switch(choice){
        case 1:
            product_purchase_pointer(&credit, &product_quantity[0], product_price[0]);
            break;
        case 2:
            product_purchase_pointer(&credit, &product_quantity[1], product_price[1]);
            break;
        case 3:
            product_purchase_pointer(&credit, &product_quantity[2], product_price[2]);
            break;
        case 4:
            product_purchase_pointer(&credit, &product_quantity[3], product_price[3]);
            break;
        case 5:
            product_purchase_pointer(&credit, &product_quantity[4], product_price[4]);
            break;
        case 6:
            credit=money_input(credit);
            break;
        case 7:
            credit=money_return(credit);
            break;
        case 2137: //super special code
            n++;
            break;
        case 1234:
            money_edit();
            break;
        default:
            invalidcode=1;
            break;
        }
        products_save();
        money_save();
    }
    cout<<"\nInitiating self-destruct.\n";
    return 0;
}

// Function section
//--------------------------------------------------

// Function making sure that the input is an intiger
int ReadInt( const string & prompt  ) {
    int n;
    while( (cout << prompt) && ! (cin>> n) ) {
        cout << "invalid input!\n";
        cin.clear();
        cin.ignore( numeric_limits<int>::max(), '\n' );
    }
    return n;
}

// Function to read the products files
void products_read(){
    string name; int i=0, quantity, refill; float price;
    ifstream inFile ("products.txt");
    while(inFile >> name >> quantity >> price >> refill){
      product_name[i]=name;
      product_quantity[i]=quantity;
      product_price[i]=price;
      product_refill[i]=refill;
      if (firstiter){
        if (product_refill[i]){
          product_quantity[i]=10;
        }
      }
      //cout << name << '\t' << quantity << '\t' << price << '\t' << refill << '\n';
      i++;
    }
    inFile.close();
}

// Function to save the products files
void products_save(){
  ofstream outFile ("products.txt");
  for(int i=0;i<5;i++){
    if(product_quantity[i]==0){
      product_refill[i]=1;
    }
    outFile<<product_name[i]<<" "<<product_quantity[i]<<" "<<product_price[i]<<" "<<product_refill[i]<<"\n";
  }
  outFile.close();
}

// Function to purchase products
float product_purchase(float crdt, int product_number){
    int order_qty=ReadInt("\nSelect the quantity: ");
    if((product_quantity[product_number]-order_qty)>=1){ //quantity check
        float cost = order_qty*product_price[product_number];
        if (crdt > cost){ //credit check
          product_quantity[product_number] -= order_qty;
          crdt -= cost;
        }
        else{
          not_enough_credit=1;
        }
    }
    else{
        not_enough_product=1;
    }
    return crdt;
}

// purchase with pointers
void product_purchase_pointer(float *crdt, int *stock, float price){
    int order_qty=ReadInt("\nSelect the quantity: ");
    if((*stock-order_qty)>=1){ //quantity check
        float cost = order_qty*price;
        if (*crdt > cost){ //credit check
          *stock -= order_qty;
          *crdt -= cost;
        }
        else{
          not_enough_credit=1;
        }
    }
    else{
        not_enough_product=1;
    }
}

// Function to input money
float money_input(float cred){
  while(cont<1){
    system("clear");//clear in putty
    cout<<"ENTER MONEY\n";
    cout<<"1 - 5 PLN"<<"\n";
    cout<<"2 - 2 PLN"<<"\n";
    cout<<"3 - 1 PLN"<<"\n";
    cout<<"4 - 0.5 PLN"<<"\n";
    cout<<"5 - 0.2 PLN"<<"\n";
    cout<<"6 - 0.1 PLN"<<"\n";
    cout<<"7 - finish entering money and go back to the product selection"<<"\n\n";
    cout<<"Your current credit is: " << cred << " PLN.\n";

    choice = ReadInt("Your choice: ");

    switch(choice){
      case 1:
        cred+=5;
        coin_quantity[0]++;
        break;
      case 2:
        cred+=2;
        coin_quantity[1]++;
        break;
      case 3:
        cred+=1;
        coin_quantity[2]++;
        break;
      case 4:
        cred+=0.5;
        coin_quantity[3]++;
        break;
      case 5:
        cred+=0.2;
        coin_quantity[4]++;
        break;
      case 6:
        cred+=0.1;
        coin_quantity[5]++;
        break;
      case 7:
        cont++;
        break;
    }
  }
  cont=0;
  return cred;
}

// Function to give out the change
float money_return(float crdt){
  int change[6]={0,0,0,0,0,0};
  for(int i=0;i<6;i++){
    while(crdt-coin_value[i]>=0){
      if(coin_quantity[i]>0){
        change[i]+=1;
        crdt-=coin_value[i];
        coin_quantity[i]--;
      }
    }
  }
  system("clear");
  cout << "Your change:\n";
  for(int i=0;i<6;i++){
    cout << change[i] << "\t" << coin_name[i] << "\n";
  }
  crdt=0;
  cout << "\nPress any key and ENTER to continue";
  string x;
  cin >> x;
  return crdt;
}

// Function to read current amount of coins from a files
void money_read(){
    int i=0, quantity;
    ifstream inFile ("coins.txt");
    while(inFile >> quantity){
      coin_quantity[i]=quantity;
      i++;
    }
    inFile.close();
}

// Function to save current amount of coins to file
void money_save(){
  ofstream outFile ("coins.txt");
  for(int i=0;i<6;i++){
    outFile<<coin_quantity[i]<<"\n";
  }
  outFile.close();
}

// Function to edit the money pool
void money_edit(){
  k=0;
  while(k<1){
    system("clear");
    cout << "Current amount of coins in the machine:\n";
    for(int i=0;i<6;i++){
      cout << i+1 << " - " << coin_name[i] << ":\t" << coin_quantity[i] << "\n";
    }
    cout << "7 - main menu\n\n";
    if(invalidcode==1){
      cout << "Your input was invalid.\n\n";
      invalidcode=0;
    }
    choice = ReadInt("Select your choice: ");
    switch(choice){
      case 1:
        coin_quantity[0]=ReadInt("\nInput a quantity of coin: ");
        break;
      case 2:
        coin_quantity[1]=ReadInt("\nInput a quantity of coin: ");
        break;
      case 3:
        coin_quantity[2]=ReadInt("\nInput a quantity of coin: ");
        break;
      case 4:
        coin_quantity[3]=ReadInt("\nInput a quantity of coin: ");
        break;
      case 5:
        coin_quantity[4]=ReadInt("\nInput a quantity of coin: ");
        break;
      case 6:
        coin_quantity[5]=ReadInt("\nInput a quantity of coin: ");
        break;
      case 7:
        k++;
        break;
      default:
        invalidcode=1;
        break;
    }
  }
}
