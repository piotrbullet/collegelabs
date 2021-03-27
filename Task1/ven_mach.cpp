#include <iostream>
#include <stdlib.h>
#include <limits>
#include <string>
#include <fstream>

using namespace std;

//global variables used in functions
int notenough=0;
//int notint=0;
fstream products_file;

//function definitions
int ReadInt(const string & prompt);
int selection(int item, int no);

int main(){
    string line,names[5]={"KREMOWKA","BAJADERKA","SERNIK","WUZETKA","SZARLOTKA"};
    float price[5]={2.1, 1.5, 3, 4.5, 2.8};
    int coin_qty[6]={2, 8, 12, 14, 15, 20};
    int notint=0;

    string coin_names[6]={"5 PLN", "2 PLN", "1 PLN", "0.5 PLN", "0.2 PLN", "0.1 PLN"};
    int choice,qty,var[5];
    int n=0,invalidcode=0,firstiter=0,credit=0;

    while(n<1){

        int k=0;
        fstream file ("variables.txt");
        while(getline(file,line)){
            var[k]=stoi(line);
            if(firstiter==0){
                if(var[k]==0){
                    var[k]=10;
                    cout << "There as not enough of " << names[k] << ", added 10 to stock.\n\n";
                }
            }
            k++;
        }
        file.close();
        firstiter=1;

        system("clear"); //clear in putty
        cout <<"    VENDING MASHINE    \n";
        cout <<"    Products:\n";
        cout <<"1 - Kremowka \t\t 2.10 PLN \t"<<var[0]<<" in stock\n";
        cout <<"2 - Bajaderka \t\t 1.50 PLN \t"<<var[1]<<" in stock\n";
        cout <<"3 - Sernik \t\t 3.00 PLN \t"<<var[2]<<" in stock\n";
        cout <<"4 - Wuzetka \t\t 4.50 PLN \t"<<var[3]<<" in stock\n";
        cout <<"5 - Szarlotka \t\t 2.80 PLN \t"<<var[4]<<" in stock\n\n";

        if(notenough==1){
            cout<<"\nThere was not enough stock of your product, sori.\n\n";
            notenough=0;
        }
        if(invalidcode==1){
            cout<<"\nInput a valid number.\n\n";
            invalidcode=0;
        }

        choice = ReadInt("Please select your product: ");

        switch(choice){
        case 1:
            var[0]=selection(var[0],qty);
            break;
        case 2:
            var[1]=selection(var[1],qty);
            break;
        case 3:
            var[2]=selection(var[2],qty);
            break;
        case 4:
            var[3]=selection(var[3],qty);
            break;
        case 5:
            var[4]=selection(var[4],qty);
            break;
        case 2137: //super special code
            n++;
            break;
        default:
            invalidcode++;
            break;
        }

        ofstream out_file ("variables.txt");
        for(int i=0;i<5;i++){
            out_file << var[i] << endl;
        }
        out_file.close();

        //system("clear"); //clear in putty
    }

    cout<<"\nShutting down :<\n";
    return 0;
}

// Function section

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

// Function that checks if there is enough quantity of the product
int selection(int item, int no){
    no=ReadInt("\nSelect the quantity: ");
    if((item-no)>-1)
        item=item-no;
    else
        notenough++;
    return item;
}
