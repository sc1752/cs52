// Name : Chang Shu
// SSID : 1658068
// Assignment #: 3 part 1
// Submission Date : 9/12/18
//
// Description of program : Data analysis project
//

#include <iostream>
#include <fstream>
#include <string>
using namespace std;

const int NUM_OF_STATES = 51; 
const int NUM_OF_COLUMN = 15;
const std::string INPUT_FILE = "Data2016.csv";

struct EnergyData
{
    string state;
    double coal; // 1
    double naturalGas; // 2
    double petroleum; // 3, 4, 5, 6, 7
    double neuclear; // 8
    double other; // 9 , 10 , 11, 12
    double solar; // 13
    double wind; // 14
};

void ReadData (ifstream &reader, EnergyData data[]);
void printEnergyData (EnergyData data);
int findState(string name, EnergyData data[], int l, int r);

void ReadData (ifstream &reader, EnergyData data[])
{
    reader.open(INPUT_FILE);
    int count = 1;
    int line = 0;
    std::string str;
    double num = 0; 
    std::getline(reader, str);
            
    while(line < NUM_OF_STATES)
    {
        if(!reader.fail())
        {
            std::string::size_type sz;
            
            if(count < 15)
            {
                std::getline(reader, str, ',');
            }
            else
            {
                std::getline(reader, str, '\n');
            }

            if (count == 1)
            {
                data[line].state = str;
            }
            else if (count == 2)
            {
                num = std::stod(str, &sz);
                data[line].coal = num;
            }
            else if (count == 3)
            {
                num = std::stod(str, &sz);
                data[line].naturalGas = num;
            }
            else if (count >= 4 && count <= 8)
            {
                num = std::stod(str, &sz);
                data[line].petroleum += num;
            }
            else if (count == 9)
            {
                num = std::stod(str, &sz);
                data[line].neuclear = num;
            }
            else if (count >=10 && count <= 13)
            {
                num = std::stod(str, &sz);
                data[line].other += num;
            }
            else if (count == 14)
            {
                num = std::stod(str, &sz);
                data[line].solar = num;
            }
            else if (count == 15)
            {
                num = std::stod(str, &sz);
                data[line].wind = num;
            } 
        }
        
        if(count >= NUM_OF_COLUMN)
        {
            count = 1;
            line ++;
        }
        else
        {
            count ++;
        }
    }
    
    reader.close();
    
}

void printEnergyData (EnergyData data)
{
    double total = data.coal + data.naturalGas + data.petroleum + data.neuclear
                    + data.other + data.solar + data.wind;
    //std::cout << data.state << std::endl;
    std::cout.setf(std::ios::fixed);
    std::cout.setf(std::ios::showpoint);
    std::cout.precision(2);
    std::cout << "Coal: " << data.coal * 100 / total << "%" << std::endl;
    std::cout << "Natrual Gas: " << data.naturalGas * 100 / total << "%"<< std::endl;
    std::cout << "Petroleum: " << data.petroleum * 100 / total << "%"<< std::endl;
    std::cout << "Nueclear: " << data.neuclear * 100 / total << "%" << std::endl;
    std::cout << "Other Renewables: " << data.other * 100 / total << "%" << std::endl;
    std::cout << "Solar: " << data.solar * 100 / total << "%" << std::endl;
    std::cout << "Wind: " << data.wind * 100 / total << "%" << std::endl;
    std::cout << std::endl;
}

int findState(string name, EnergyData data[], int l, int r)
{
    int i = (l + r)/2; 
    if (r < l)
    {
        return -1;
    }
    else if(name.compare(data[i].state) == 0)
    {
        return i;
    }
    else if(name.compare(data[i].state) > 0)
    {
        return findState(name, data, i+1, r);
    }
    else
    {
        return findState(name, data, l, i-1);
    }
}

int main()
{
    EnergyData data [NUM_OF_STATES]; 
    std::ifstream f;
    ReadData(f, data);

    bool cont = true;
    while (cout)
    {
        std::string input; 
        std::cout << "Enter a statename or 'q' to exit" << std::endl;
        std::getline(std::cin, input);

        if (input.compare("q") == 0)
        {
            std::cout << "Goodbye" << std::endl;
            break;
        }
        else
        {
           int ind = findState(input, data, 0, NUM_OF_STATES - 1);
           if(ind >= 0 && ind < NUM_OF_STATES)
           {
               printEnergyData(data[ind]);
           }
           else
           {
               std::cout << "Not a valid state" << std::endl;
               std::cout << std::endl;
           }
        }
    }
}