#include <iostream>
#include <fstream>
#include <sstream>
#include <windows.h>
using namespace std;

class Bill{
    private:
        string Item;
        int Rate;
        int Quantity;
    public:
        Bill():Item(""), Rate(0), Quantity(0){ }   
    
    void setItem(string item){
        Item = item;
    }
    void setRate(int rate){
        Rate = rate;
    }
    void setQuantity(int quantity){
        Quantity = quantity;
    }

    string getItem(){
        return Item;
    }
    int getRate(){
        return Rate;
    }
    int getQuantity(){
        return Quantity;
    }
};

  void addItem(Bill b){
       bool close = false;
       while(!close){
        int choice;
        cout<<"1.Add Item"<<endl;
        cout<<"2.Close"<<endl;
        cout<<"Enter Choice"<<endl;
        cin>>choice;

        if(choice == 1){
            string item;
            int rate,quantity;
            cout<<"Enter the item name"<<endl;
            cin>>item;
            b.setItem(item);

            cout<<"Enter the rate"<<endl;
            cin>>rate;
            b.setRate(rate);

            cout<<"Enter the quantity"<<endl;
            cin>>quantity;
            b.setQuantity(quantity);

            ofstream out("./bill.txt",ios::app);
            if(!out){
                cout<<"Error in opening the file"<<endl;
            }else{
                out<<"\t"<<b.getItem()<<" : "<<b.getRate()<<" : "<<b.getQuantity()<<endl<<endl;
            }
            out.close();
            cout<<"Item Added Successfully"<<endl;
        }else if(choice == 2){
            close = true;
            cout<<"Back to main menu"<<endl;
        }
       } 
    }


void printBill(){
    int count=0;
    bool close = false;
    while(!close){
        int choice;
        cout<<"1.Add Bill"<<endl;
        cout<<"2.Close Session"<<endl;
        cout<<"Enter Choice"<<endl;
        cin>>choice;

        if(choice == 1){
            string item;
            int quantity;
            cout<<"Enter the item"<<endl;
            cin>>item;
            cout<<"Enter the quantity"<<endl;
            cin>>quantity;

            ifstream in("./bill.txt");
            ofstream out("./temp.txt");

            string line;
            bool found = false;
            while(getline(in,line)){
                stringstream ss;
                ss<<line;
                string itemName;
                int itemRate,itemQuantity;
                char delimiter;
                ss>>itemName>>delimiter>>itemRate>>delimiter>>itemQuantity;

                if(item == itemName){
                    found=true;
                    if(quantity <= itemQuantity){
                        int amount = itemRate * quantity;
                        cout<<"Item | Rate | Quantity | Amount"<<endl;
                        cout<<itemName<<"\t "<<itemRate<<"\t "<<quantity<<"\t "<<amount<<endl;
                        int newQuantity = itemQuantity - quantity;
                        itemQuantity = newQuantity;
                        count += amount;

                        out<<"\t"<<itemName<<" : "<<itemRate<<" : "<<itemQuantity<<endl;
                    }else{
                        cout<<"Sorry we ran out of "<<item<<endl;
                    }
                }else{
                    out<<line<<endl;
                }
            }
            if(!found){
                cout<<"Item not available"<<endl;
            }
            out.close();
            in.close();
            remove("./bill.txt");
            rename("./temp.txt","./bill.txt");
        }else if(choice == 2){
            close = true;
            cout<<"Counting the bill"<<endl;
        }
        Sleep(2000);
    }
    cout<<endl<<endl;
    cout<<"Total Bill : "<<count<<endl;
    cout<<"Thanks for shopping"<<endl;
}

int main(){
    Bill b;
    bool exit = false;
    while(!exit){
        int choice;
        cout<<"Welcome to the super market billing system"<<endl;
        cout<<"******************************************"<<endl;
        cout<<"1.Add Item"<<endl;
        cout<<"2.Print Bill"<<endl;
        cout<<"3.Exit"<<endl;
        cout<<"Enter your choice"<<endl;
        cin>>choice;

        if(choice==1){
            addItem(b);
        }else if(choice == 2){
            printBill();
        }else if(choice == 3){
            exit = true;
            cout<<"Thank you"<<endl;
        }else{
            cout<<"Please enter a valid choice"<<endl;
        }
    }
}
