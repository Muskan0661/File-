#include<iostream>
using namespace std;
class print
{
    public:

void volume(double side)   // Cube
{
    cout<<"volume of cube is: "<<side*side*side<<endl;
}

void volume(double length, double width, double height) // Cuboid
{
    cout<<"volume of cuboid is: "<<length*width*height<<endl;
}

void volume(float radius, float height)  // Cylinder
{
    cout<<"volume of cylinder is: "<<radius*radius*3.14*height<<endl;
}

void volume(float radius, double height, bool isCone) // Cone (using a flag to differentiate)
{
    if(isCone)
    {
    cout<<"volume of cone is: "<<(radius*radius*height)/3<<endl;
}
else
{
    cout<<"flag is false , now back to cylinder:\n";
    volume(radius,height);
} }
};
int main()
{
    print p;
    double side,height,width,length;
    bool isCone;
    float radius;

    cout<<"enter value of side: ";
    cin>>side;
    p.volume(side);
    cout<<endl;
    cout<<"enter value of length: ";
    cin>>length;
     cout<<"enter value of width: ";
    cin>>width;
     cout<<"enter value of height: ";
    cin>>height;
    p.volume(length,width,height);
    cout<<endl;
     cout<<"enter value of radius: ";
    cin>>radius;
    p.volume(radius,height);
    cout<<endl;
     cout << "Is it a cone? (1 for yes, 0 for no): ";
    cin >> isCone;
    p.volume(radius,height,isCone);
}