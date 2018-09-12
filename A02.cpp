// Name : Chang Shu
// SSID : 1658068
// Assignment #: 2
// Submission Date : DATE_YOU_SUBMIT
//
// Description of program : Simple program to print out ascii patterns
//

#include <iostream>
using namespace std;

#define WIDTH 8
#define HEIGHT 8

enum Shapes { FILLED , CHECKERBOARD , SQUARE , X , UPPER_LEFT };
enum Colors { BLACK , WHITE };

struct Pixel 
{
    Colors color;
};

void CreateShape ( Pixel p [] , int nPixels , Shapes shape )
{
    switch (shape)
    {
        case Shapes::FILLED:
            break;
         case Shapes::CHECKERBOARD:
            break;
         case Shapes::SQUARE:
            break;
         case Shapes::X:
            break;
         case Shapes::UPPER_LEFT:
            break;
        default:
            break;
    }
}

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
        if(i % 2 == 0)
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
}

int main ()
{
    int nPixels = WIDTH * HEIGHT;
    Pixel pixels [nPixels];
     
    createCheckerBoard(pixels, nPixels);
    Draw (pixels , nPixels );
    return 0;
}