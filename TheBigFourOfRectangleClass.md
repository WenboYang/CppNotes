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

** Mind set: write your C++ program as a library builder **, so think your program will run on server millions of times, your class can be inherited, or be used to compose much larger classes.
