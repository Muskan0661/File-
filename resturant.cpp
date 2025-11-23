#include<iostream>
#include<string>
#include<limits>
using namespace std;

const int MAX_CUSTOMERS = 100;
const int MAX_ORDERS = 200;
const int MAX_ORDER_ITEMS = 50;
const int MAX_MENU_ITEMS = 50;
const int MAX_TABLES = 20;

class order;

class Person{

protected:
string name;
string phoneNo;
string cnic;

public:
virtual void getInfo()=0;

};

class Order;

class Customer:public Person{
private:
int customerID;
Order* orderHistory[100];
int orderCount;
public:
Customer(){ int orderCount; }
Customer(string n,string phone,string cnic,int id){
name=n;
phoneNo=phone;
this->cnic=cnic;
customerID=id;
orderCount=0;
}
void addOrder(Order* o){
if(orderCount<100){
    orderHistory[orderCount++]=o;
}
}
void saveToFile();//incomp
void loadFromFile();//incomp
void getInfo() override{
cout<<"Customer ID: "<<customerID<<", Name: "<<name<<", Phone: "<<phoneNo<<endl;
}
};

enum class ItemCategory{
Beverage,FastFood,Dessert,MainCourse,Appetizer//enum is better for definig lists.(cleaner version)
};

class Item{
    private:
    string name;
    double price;
    ItemCategory category;
    public:
    Item(string n="",double p=0, ItemCategory c=ItemCategory::Appetizer):name(n),price(p),category(c){}
   double getPrice(){
    return price;
   }
   ItemCategory getCategory(){
    return category;
   }
};

class Payment{
    protected:
    bool success;
    public:
    virtual void pay(double amount)=0;
    bool isSuccess(){
    return success;
    }
};

class CashPayment: public Payment{
public:
void pay(double amount)override{
    cout<<"Paid "<<amount<<"$ in cash."<<endl;
    success=true;
}
};

class CardPayment : public Payment {
private:
double availableBalance;
string cardNumber;
public:
CardPayment(double balance, const string &card) : availableBalance(balance), cardNumber(card) {}
void pay(double amount) override {
if (cardNumber.length() != 16) {
cout << "Card payment failed: Invalid card number." << endl;
success = false;
return;
}

double discounted = amount * 0.90;
if (discounted > availableBalance) {
cout << "Card payment failed: Insufficient balance after discount. Required: " << fixed << setprecision(2) << discounted << "\n";
success = false;
return;
}
availableBalance -= discounted;
cout << "Paid " << fixed << setprecision(2) << discounted << " by card (10% discount applied)." << endl;
success = true;
}
};

class OnlineCardPayment : public Payment {
private:
double onlineBalance;
string correctCVV;
public:
OnlineCardPayment(double balance, const string &cvv) : onlineBalance(balance), correctCVV(cvv) {}
void pay(double amount) override {

double discounted = amount * 0.90;
if (discounted > onlineBalance) {
cout << "Online payment failed: Insufficient balance after discount. Required: " << fixed << setprecision(2) << discounted << "\n";
success = false;
return;
}
string enteredCVV;
cout << "Enter CVV to confirm online payment of " << fixed << setprecision(2) << discounted << " : ";
cin >> enteredCVV;
clearInput();
if (enteredCVV == correctCVV) {
onlineBalance -= discounted;
cout << "Online payment successful, Order placed! (10% discount applied)" << endl;
success = true;
} else {
cout << "Incorrect CVV. Online payment failed!" << endl;
success = false;
}
}
};


class CODPayment : public Payment{
    public:
    void pay(double amount)override{
        cout<<"Cash on delivery: "<<amount<<"$ to be paid on delivery"<<endl;
        success=true;
    }
};

enum class TableCategory{
    SMALL, MEDIUM, LARGE
};

class Table{
    private:
    int tableID;
    int capacity;
    TableCategory category;
    bool isOccupied;
    public:
    Table(){

        tableID=capacity=0;
        occupied=false;
    }
    Table(int id, int cap): tableID(id), capacity(cap), isOccupied(false){

     if(capacity>0 && capacity <=2){
     category=TableCategory::SMALL;
     }else if(capacity<=4){
        category=TableCategory::MEDIUM;
     }else{
        category=TableCategory::LARGE;
     }
    }
int getCapacity(){
    return capacity;
}
TableCategory getCategory(){
    return category;
}
 bool getOccupied(){
    return isOccupied;
 }
 void occupy(){
 isOccupied=true;
 }
 void free(){
    isOccupied=false;
 }
 int getID(){
    return tableID;
 }
};

class TableManager{
    private:
    Table tables[20];
    int tableCount=0;
    public:
    void addTable(Table t){
        tables[tableCount++]=t;}
    int getFreeTable(int numPersons){
        for(int i=0;i<tableCount;i++){
            if(!tables[i].getOccupied()&& tables[i].getCapacity()>=numPersons){
                tables[i].occupy();
                return tables[i].getCapacity();
            }
        }
        return -1;
    }
};

class Order{
protected:
int orderID;
Item items[50];
int itemCount=0;
Payment* payment;
static int getNextOrderID(){
    static int nextID=1;
    return nextID++;
}
public:
Order(){
    orderID=getNextOrderID();
    itemCount=0;
    payment=nullptr;
}
int getOrderID(){
return orderID;
}
void addItem(Item i){
    if(itemCount<50)
    {
    items[itemCount++]=i;
}}
virtual double calculateTotal()=0;
void setPaymentMethod(Payment* p){
    payment=p;
}
Payment* getPaymentMethod(){
    return payment;
}
virtual void processPayment()=0;
};
//continue from here
class DineInOrder:public Order{
private:
int tableID;
bool isReserved;
int numPersons;
public:

DineInOrder(int persons,int tabID=-1,bool reserved=false):numPersons(persons),tableID(tabID),isReserved(reserved){}

void assignTable(TableManager &tm){
    tableID=tm.getFreeTable(numPersons);
    if(tableID==-1){
        cout<<"No table available for "<<numPersons<<" persons"<<endl;
    }
    else{
        cout <<"Table "<<tableID<<" assigned."<<endl;
        }
}
double calculateTotal()override{
double sum=0;
for(int i=0; i<itemCount; i++)
{
    sum+=items[i].getprice();
    return sum;
}
}
void processPayment()override{
double total=calculateTotal();
payment->pay(total);
}
};

class OnlineOrder : public Order {
private:
string address;
public:
OnlineOrder(const string &a = "") : address(a) {}
double calculateTotal() const override {
double itemsTotal = 0.0;
for (const auto &it : items) itemsTotal += it.getPrice();

double delivery = (itemsTotal < 1000.0 ? 200.0 : 0.0);
return itemsTotal + delivery;
}
void processPayment() override { Order::processPayment(); }
string getTypeName() const override { return "Online"; }
};

class ReservationOrder:public Order{

private:
string reservationTime;
int tableID;
int numPersons;

public:
ReservationOrder(int persons, int tabID=-1, string time=""):numPersons(persons),tableID(tabID),reservationTime(time){}

void assignTable(TableManager &tm){
    tableID=tm.getFreeTable(numPersons);
    if(tableID==-1){
        cout<<"No table available for "<<numPersons<<" persons."<<endl;
    }
    else{
        cout<<"Table: "<<tableID<<" reserved at: "<<reservationTime<<endl;
    }
}
double calculateTotal()override{
double sum=0;
for(int i=0l i<itemCount; i++)
{
	sum+=items[i].getPrice();
return sum;
	}
}
void processPayment()override{

double total=calculateTotal();
payment->pay(total);
}
};

class RestaurantSystem {
private:
    Customer customers[100];
    int customerCount;
    Order* orders[200];
    int orderCount;
    TableManager tableManager;

public:

    RestaurantSystem() {
        customerCount = 0;
        orderCount = 0;


        tableManager.addTable(Table(1, 2));
        tableManager.addTable(Table(2, 4));
        tableManager.addTable(Table(3, 6));
    }

    void placeDineInOrder() {
        int numPersons;
        cout << "Enter number of persons for Dine-in: ";
        cin >> numPersons;

        DineInOrder* order = new DineInOrder(numPersons);
        order->assignTable(tableManager);


        order->addItem(Item("Burger", 550));
        order->addItem(Item("Cola", 150));


        order->setPayment(new CashPayment());
        order->processPayment();

        orders[orderCount++] = order;
        cout << "Dine-in Order Placed Successfully.\n";
    }

    void placeOnlineOrder() {
        string address;
        cout << "Enter delivery address: ";
        cin.ignore();
        getline(cin, address);

        OnlineOrder* order = new OnlineOrder(address, 150);

        order->addItem(Item("Pizza", 999));
        order->addItem(Item("Fries", 250));

        order->setPayment(new CardPayment(5000, "2323232323"));
        order->processPayment();

        orders[orderCount++] = order;
        cout << "Online Order Placed Successfully.\n";
    }

    void makeReservation() {
        int persons;
        string time;

        cout << "Enter number of persons: ";
        cin >> persons;

        cout << "Enter reservation time: ";
        cin >> time;

        ReservationOrder* order = new ReservationOrder(persons, time);

        order->reserveTable(tableManager);
        order->addItem(Item("Steak", 1600));

        order->setPayment(new CODPayment());
        order->processPayment();

        orders[orderCount++] = order;
        cout << "Reservation Order Created Successfully.\n";
    }

    void saveAllData() {
        ofstream fout("orders_summary.txt");

        if (!fout) {
            cout << "Error opening file.\n";
            return;
        }

        for (int i = 0; i < orderCount; i++) {
            fout << "Order ID: " << orders[i]->getOrderID() << endl;
        }

        fout.close();
        cout << "All data saved successfully.\n";
    }

    void mainMenu() {
        while (true) {
            cout << "\n===== Restaurant Management System =====\n";
            cout << "1. Register Customer\n";
            cout << "2. List Customers\n";
            cout << "3. Place Dine-in Order\n";
            cout << "4. Place Online Order\n";
            cout << "5. Make Reservation\n";
            cout << "6. List Orders Summary\n";
            cout << "7. List Tables\n";
            cout << "8. Save All Data\n";
            cout << "9. Load Customers from File\n";
            cout << "0. Exit\n";
            cout << "Choose an option: ";
            int opt; if (!(cin >> opt)) { clearInput(); continue; }
            switch (opt) {
                case 1: registerCustomer(); break;
                case 2: listCustomers(); break;
                case 3: placeDineInOrder(); break;
                case 4: placeOnlineOrder(); break;
                case 5: makeReservation(); break;
                case 6: listOrdersSummary(); break;
                case 7: listTables(); break;
                case 8: saveAllData(); break;
                case 9: loadCustomers(); break;
                case 0: cout << "Goodbye!\n"; return;
                default: cout << "Invalid option.\n"; break;
            }
};
int main()
{

}