#include<iostream>
#include<string>
using namespace std;
class account{
    private:
    int balance;
    public:
    account(int initialbalance)
    {
        if(initialbalance>=0)
        {
          balance=initialbalance;
        }
        else
        {   initialbalance=0;
            cout<<"error. initial balance was incorrect. balance set upto 0"<<endl;        }}
    void credit(int amount)
    {
     if(amount>0)   balance=balance+amount;
    else cout<<"amount must be +ve:"<<endl;
    }
 void debit(int amount)
    {
     if(amount>balance)
     {
         amount=balance;
         cout<<"debit amount exceeded"<<endl;  }
     else if (amount<=0)
     {
         cout<<"debit amount must be +ve:"<<endl; }
     else
     {
         balance=balance-amount; }}
    int getbalance()
    {
        return balance;  }
};
int main ()
{   int balance1 , balance2;
    cout<<"enter balance amount of person 1 and 2: ";
    cin>>balance1 >>balance2 ;

    account a1(balance1);
    account a2(balance2);
    cout<<"account of person 1 and 2 balance are: "<<a1.getbalance() << " "<< a2.getbalance() <<endl;

    int credit1,credit2;
    cout<<"enter credit of person 1 and 2 amount:";
    cin>>credit1 >>credit2 ;

    a1.credit(credit1);
    a2.credit(credit2);

    cout<<"After crediting:\n"<<endl;
    cout<<" Account of person 1 and 2 balance are : "<<a1.getbalance() << " "<<a2.getbalance() <<endl;

    int debit1,debit2;
    cout<<"enter debit of person 1 and 2 amount: ";
    cin>>debit1 >> debit2 ;

    a1.debit(debit1);
    a2.debit(debit2);

    cout<<"After debiting . Final balances\n";
    cout<<"Account 1 and 2: "<<a1.getbalance() <<" "<< a2.getbalance() <<endl;
}

