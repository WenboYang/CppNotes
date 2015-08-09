#The Task: write the "big four" for Rectangle class:
* constructor
* copy constructor
* copy assignment
* destructor
   

~~~~C++
class Shape
{
   int no;
};

class Point
{
   int x;
   int y;
};

class Rectangle:public Shape
{
   int width;
   int height;
   Point* leftUp;

public:
   Rectangle( int width, int height, int x, int y);
   Rectangle( const Rectangle& other );
   Rectangle& operator=( const Rectangle& other );
   ~Rectangle();
};
~~~~

**Mind set: a good C++ programer should always think as a library builder**, think your program will run on server many many times, your class will be inherited, or be used as a component of other classes by many many different people.



What's the problem of this constructor?
~~~~C++
inline Rectangle::Rectangle( const int width, const int height, const int x, const int y )
{
   this->width = ( width > 0 )? width : 0;
   this->width = ( height > 0 )? height : 0;
   
   this->leftUp = new Point();
   this->leftUp->x=x;
   this->leftUp->y=y;
}
~~~~

It might work. But its correctness now relies on the internal implemenation of class Point. It will break when somebody updates the Point class by adding a private member "z", which is calculated from x and y when a Point object is constructed.
   
A better one:
~~~~C++
inline Rectangle::Rectangle( const int width, const int height, const int x, const int y )
{
   this->width = ( width > 0 )? width : 0;
   this->width = ( height > 0 )? height : 0;
   
   this->leftUp = new Point( x, y );
}
~~~~
