##Write the "big four" for Rectangle class.

A brief note for the C++ offline class this weekend, mainly based on Jianzhong's teaching:

A more detailed note for this class:

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

**Mind set: a good C++ programer should always think as a library builder**. Design your class and write your code as if they will run on server many many times, as they will be inherited, or be re-used as a component of many many other classes maintained by many different people.


###Constructor

What is the problem of this constructor? 
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


###Destructor
Is this destructor OKAY?
~~~~C++
inline Rectangle::~Rectangle()
{
   delete leftUp;
}
~~~~

Again, this will work, but it won't hurt to do this, what's the benefit?
~~~~C++
inline Rectangle::~Rectangle()
{
   delete leftUp;
   leftUp = NULL;
}
~~~~
By doing this, when another guy(or myself in another day) does stupid things like this, he will instantly find out this wont' work and fix this dangling pointer:
~~~~C++
Foo()
{
   Rectangle square();
   pSquare=&square;
   return pSquare;

}
~~~~

###Copy constructor
Principle is to let each class take care of its own internal states. We just stick to the interface, which is kind of a contract between different classes. Therefor, when buiilding our copy constructor, we prefer to use the constructor of member/parent classes, like this. 
~~~~C++
Rectangle( const Rectangle& other ):
width(other.width),
height(other.height),
Shape(other)
{
   if ( other.leftUp != NULL )
   {
      this->leftUp = new Pointer( *other.leftUp );
   }
   else
   {
      this->leftUp = NULL;
   }
}
~~~~
Now if we want to add some members in Point class and also in parent class Shape, like this. What do we do for our copy constructor?
~~~~C++
class Shape
{
   int no;
   Mass* pMass;
};

class Point
{
   int x;
   int y;
   time* ptime;
};
~~~~~
The answer is nothing. Of course the owner of Shape and Point have the responsibility to properly implement their constructors. This is cool because the ownership and responsiblity is more clear.

And also, what the order of initilaziion order of the weight, height and parent class Shape in the int list? The answer is Shape first, then follow the order of declaration, quote C++ standard:

(initOrder.png)


A side note, Jianzhong wrote this >=10 years ago. I incidently found this online:
(http://www.cnblogs.com/k-eckel/archive/2005/07/08/188281.html)


