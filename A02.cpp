// Name : Chang Shu
// SSID : 1658068
// Assignment #: 2
// Submission Date : 9/12/18
//
// Description of program : Simple program to print out ascii patterns
//

#include <iostream>
#include <string>
using namespace std;

#define WIDTH 10
#define HEIGHT 10

enum Shapes { FILLED , CHECKERBOARD , SQUARE , X , UPPER_LEFT };
enum Colors { BLACK , WHITE };

struct Pixel 
{
    Colors color;
};

void createFilled(Pixel p [], int nPixels)
{
    for(int i = 0; i < nPixels ; i++)
    {
        p[i].color = Colors::WHITE;
    }
}

void createCheckerBoard(Pixel p [], int nPixels)
{
    for(int i = 0; i < nPixels ; i++)
    {
        int number = (i / WIDTH) % 2;
        
        if(i % 2 == number)
        {
            p[i].color = Colors::WHITE;            
        }
        else
        {
            p[i].color = Colors::BLACK; 
        }
    }
}

void createSquare(Pixel p [], int nPixels)
{
    for(int i = 0; i < nPixels ; i++)
    {
        if(i % WIDTH == 0 || i % WIDTH == WIDTH -1 
           || i / WIDTH == 0 || i / WIDTH == HEIGHT - 1)
        {
            p[i].color = Colors::WHITE;
        }
        else
        {
             p[i].color = Colors::BLACK;
        }
    }
}


void createX(Pixel p [], int nPixels)
{
    for(int i = 0; i < nPixels ; i++)
    {
        int x = i % WIDTH;
        int y = i / WIDTH; 
        if (x - y == 0 || x + y == WIDTH - 1)
        {
            p[i].color = Colors::WHITE;
        }
        else
        {
            p[i].color = Colors::BLACK;
        }
    }
}

void createFlag(Pixel p [], int nPixels)
{
    for(int i = 0; i < nPixels ; i++)
    {
        int x = i % WIDTH;
        int y = i / WIDTH; 
        if (x < WIDTH - y)
        {
            p[i].color = Colors::WHITE;
        }
        else
        {
            p[i].color = Colors::BLACK;
        }
    }
}

void Draw ( Pixel p [] , int nPixels )
{
    for(int i = 0; i < nPixels ; i++)
    {
        if(i % WIDTH == 0)
        {
            std::cout << "\n";
        }
        
        if(p[i].color == Colors::BLACK)
        {
            std::cout << "   ";
        }
        else if(p[i].color == Colors::WHITE)
        {
            std::cout << "|||";
        }
    }
    std::cout << std::endl;
}

void CreateShape ( Pixel p [] , int nPixels , Shapes shape )
{
    switch (shape)
    {
        case Shapes::FILLED:
            createFilled(p, nPixels);
            break;
         case Shapes::CHECKERBOARD:
            createCheckerBoard(p, nPixels);
            break;
         case Shapes::SQUARE:
            createSquare(p, nPixels);
            break;
         case Shapes::X:
            createX(p, nPixels);
            break;
         case Shapes::UPPER_LEFT:
            createFlag(p, nPixels);
            break;
        default:
            break;
    }
}

int main ()
{
    int nPixels = WIDTH * HEIGHT;
    Pixel pixels [nPixels];
    bool cont = true;
    while (cout)
    {
        std::string input; 
        std::cout << "What shape to draw ((f)ill, checkerboard (cb), (sq)uare, (x), or upper-left tri (ul) )? Enter ’q’ to exit.:\n";
        std:cin >> input;
        Shapes shape; 
        if (input.compare("f") == 0)
        {
            shape = Shapes::FILLED;
        }
        else if(input.compare("cb") == 0)
        {
            shape = Shapes::CHECKERBOARD;
        }
        else if(input.compare("sq") == 0)
        {
            shape = Shapes::SQUARE;
        }
        else if(input.compare("x") == 0)
        {
            shape = Shapes::X;
        }
        else if(input.compare("ul") == 0)
        {
            shape = Shapes::UPPER_LEFT;
        }
        else if(input.compare("q") == 0)
        {
            break;
        }
        else
        {
            continue;
        }
        CreateShape(pixels, nPixels, shape);
        Draw (pixels , nPixels );
    }
    return 0;
}

//if std::cin.fail
//  cin.clear
//std::ignore