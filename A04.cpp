// Name : Chang Shu
// SSID : 1658068
// Assignment #: 4
// Submission Date : 10/21/18
//
// Description of program : Data analysis project part 2
//

#include <iostream>
#include <fstream>
#include <string>
# include <cmath>
using namespace std;

# define PI 3.14159265358979323846

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

struct Color
{
    unsigned char r;
    unsigned char g;
    unsigned char b;
};

const int NUM_OF_STATES = 51; 
const int NUM_OF_COLUMN = 15;
const std::string INPUT_FILE = "Data2016.csv";
enum Coord { X, Y };
const int HEIGHT = 500, WIDTH = 500, DEPTH = 3;
const double RADIUS = 240.0;
const Color WHITE = {255,255,255}, RED={255,0,0}, GREEN={0,255,0}, BLUE={0,0,255},YELLOW={255,255,0},
            CYAN={0,255,255},PINK={255,0,255}, GREY={128,128,128};
const Color COLORS[7] = {RED,GREEN,BLUE,YELLOW,CYAN,PINK,GREY};

// Definition of functions
void ReadData (ifstream &reader, EnergyData data[]);
void printEnergyData (EnergyData data);
int findState(string name, EnergyData data[], int l, int r);
double get_theta (int x, int y, int center [2]);
double quadrant_converter (int x, int y, int center [2] , double theta );
double get_distance_from_center (int x, int y, int center [2] , double theta );
void CreatePieChart(unsigned char *pixels, const int dims[3], double percentages[7], double radius);
void getPercentage(EnergyData data, double percentages[7]);
int findColorInd(double percentages[7], double percentage);
void WriteImage(std::ofstream &out, unsigned char *pixels, const int dims[3]);

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

double quadrant_converter (int x, int y, int center [2] , double theta )
{
    //1st quadrant
    double deg = theta * 180. / PI;
    //2nd quadrant
    if ((( y - center [ Coord ::Y]) < 0) && (( center [ Coord ::X] - x) > 0))
        deg = 180 + ( theta * 180. / PI );
    //3rd quadrant
    if ((( y - center [ Coord ::Y]) < 0) && (( center [ Coord ::X] - x) < 0))
        deg = 180 + ( theta * 180. / PI );
    //4th quadrant
    if ((( y - center [ Coord ::Y]) >= 0) &&(( center [ Coord ::X] - x) < 0))
        deg = 360 + ( theta * 180. / PI );
    return deg ;
}

double get_theta (int x, int y, int center [2])
{
    double theta = std :: atan ( static_cast <double >( center [ Coord ::X] - x)
    / static_cast <double >(y - center [ Coord ::Y ]));
    if (( center [ Coord ::X] - x) == 0 && (y - center [ Coord ::Y]) < 0)
        theta = PI;
    else if (( center [ Coord ::X] - x) == 0 && (y - center [ Coord ::Y]) >= 0)
        theta = 0;
    return theta ;
}

double get_distance_from_center (int x, int y, int center [2] , double theta )
{
    double hyp = 0.0;
    if (( center [ Coord ::X] - x) == 0)
        hyp = static_cast <double >(y - center [ Coord ::Y]);
    else
        hyp = static_cast <double >( center [ Coord ::X] - x) / sin( theta );
    return std :: abs (hyp );
}

int findColorInd(double percentages[7], double percentage)
{
    int ind = 0;
    if (percentage <= percentages[0])
    {
        ind = 0;
    }
    else
    {
        for (int i = 1; i <= 6; i++)
        {
            if (percentage > percentages[i-1] && percentage <= percentages[i])
            {
                ind = i;
                break;
            }
        }
    }
    
    return ind;
}

void CreatePieChart(unsigned char *pixels, const int dims[3], double percentages[7], double radius)
{
    int w=dims[0], h=dims[1], d=dims[2];
    int center[2] = { w / 2, h / 2 };
    for (int y = 0; y < h; y++)
    {
        for (int x = 0; x < w; x++)
        {
            int offset = d * (y * w + x);
            
            double theta = get_theta (x, y, center );
            double hyp = get_distance_from_center (x, y, center , theta );
            double deg = quadrant_converter (x, y, center , theta );
            //cout << "x" << x << "y" << y<< "deg" << deg << endl;
            
            if(hyp <= radius)
            {
                double percentage = deg * 100 / 360;
                int colorInd = findColorInd(percentages, percentage);
                
                Color col = COLORS[colorInd];
                pixels [ offset + 0] = col.r; 
                pixels [ offset + 1] = col.g; 
                pixels [ offset + 2] = col.b;
                //std::cout << colorInd;
            }
            else
            {
                pixels [ offset + 0] = WHITE.r; 
                pixels [ offset + 1] = WHITE.g; 
                pixels [ offset + 2] = WHITE.b;
                //std::cout<<"W";
            }
        }
        //std::cout << std::endl;
    }
}

void WriteImage(std::ofstream &out, unsigned char *pixels, const int dims[3])
{
    out.open ("output.ppm");
    if (out.is_open())
    {
        std::cout << "Writing pie chart image to output.ppm." << std::endl;
        out <<  "P3" << std::endl;
        out << "# output image" << std::endl;
        out <<  dims[0] << " " << dims[1] << std::endl;
        out << 255 << std::endl;
        
        //Flipping x and y so the image look the same as the hand outs
        for (int x = 0; x < dims[1]; x++)
        {
            for (int y = 0; y < dims[0]; y++)
            {
                int offset = dims[2] * (y * dims[0] + x);
                unsigned int r = pixels [ offset + 0];
                unsigned int g = pixels [ offset + 1];
                unsigned int b = pixels [ offset + 2];
                out << r << " " << g << " " << b << std::endl ;
            }
        }
    }
    out.close();
}

void getPercentage(EnergyData data, double percentages[7])
{
    double total = data.coal + data.naturalGas + data.petroleum + data.neuclear
                + data.other + data.solar + data.wind;
    
    double cumulative = data.coal * 100 / total;
    percentages[0] = cumulative;
    cumulative += data.naturalGas * 100 / total;
    percentages[1] = cumulative;
    cumulative += data.petroleum * 100 / total;
    percentages[2] = cumulative;
    cumulative += data.neuclear * 100 / total;
    percentages[3] = cumulative;
    cumulative += data.other * 100 / total;
    percentages[4] = cumulative;
    cumulative += data.solar * 100 / total;
    percentages[5] = cumulative;
    cumulative += data.wind * 100 / total;
    percentages[6] = cumulative;
}

int main()
{
    int dims[3] = {WIDTH, HEIGHT, DEPTH};
    unsigned char * pixels = new unsigned char [HEIGHT * WIDTH * DEPTH];
    EnergyData data [NUM_OF_STATES]; 
    std::ifstream f;
    std::ofstream out;
    ReadData(f, data);
    double percentages[7];
    
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
               getPercentage(data[ind], percentages);
               CreatePieChart(pixels, dims, percentages, RADIUS);
               WriteImage(out, pixels, dims);
           }
           else
           {
               std::cout << "Not a valid state" << std::endl;
               std::cout << std::endl;
           }
        }
    }
}