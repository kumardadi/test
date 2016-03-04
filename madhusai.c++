#include <iostream>
#include <Date.h>

int main()
{

  Date d(1,1,12);
  cout<<"Enter a Date ";
  cin>>d;
  cout<<d<<endl;
  d++;
  cout<<d<<endl;
  ++d;
  cout<<d<<endl;
  d=d+123;
  cout<<d<<endl;
}
