#include "Square.h"


Square::Square() : Square(0,0){

}

Square::Square(int x,int y):x(x),y(y)
{

}

Square::Square(string position)
{
	conversion(position);
}

int Square::getX() const
{
    return this->x;
}

int Square::getY() const
{
    return this->y;
}

void Square::setSquare(int x,int y)
{
    this->x = x;
    this->y = y;
}

void Square::setSquare(Square const &position)
{
    this->setSquare(position.getX(),position.getY());
}

void Square::conversion(string position)
{
    
    char positions[8]={'a','b','c','d','e','f','g','h'};
    for (int i = 0; i < 8; i++)
    {
        size_t res = position.substr(0,1).find(positions[i]);
        if(res != string::npos)
        {
            this->y=i;
            break;
        }
    }

    this->x = stoi(position.substr(1,1))-1;

  
}

string Square::to_string()
{
    
    int x = getX()+1;
    string positions[8]={"a","b","c","d","e","f","g","h"};
    string y= positions[getY()];

    return y+std::to_string(x);
}