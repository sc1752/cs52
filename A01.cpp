// Name : Chang Shu
// SSID : 1658068
// Assignment #: 1 
// Submission Date : 9/5/18
//
// Program Description : This program prints the
// maximum value of five numbers input by a user .

#include <iostream>
using namespace std;

int main (int argc , char * argv [])
{
  int current, max;
  bool firstTime = true;
  int count = 5;
  
  std::cout << "Enter five space separated numbers, then press enter to display the max:" << endl;
  
  do
  {
    std::cin >> current;
    if(firstTime)
    {
      max = current;
      firstTime = false;
    }
    else if(current > max)
    {
      max = current;
    }
    count--;
  }while(count > 0);
  
  std::cout << "The largest number you entered was: " << max << ".\n";
  std::cout << "Enter any key to exit:" << endl;
  
  char any;
  std::cin >> any;
  return 0;
}// main