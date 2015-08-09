## Write the "big four" for Rectangle class:
   constructor
   copy constructor
   copy assignment
   destructor
   

~~~~C++
class Shape
{
   int no;
};

class Point
{
   int x;
   int y;
}

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

