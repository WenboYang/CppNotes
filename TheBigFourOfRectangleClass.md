##Write the "big four" for Rectangle class.

A brief note for the C++ offline class this weekend, mainly based on Jianzhong's teaching:


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
   ... ...;
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
   ... ...;  
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
By doing this, when another guy(or myself in another day) does stupid things like this, he will find out this wont' work very soon and he will have to fix this dangling pointer before it damages something:
~~~~C++
Rectangle* Foo()
{
   Rectangle square(1, 10, 10, 3, 10);
   Rectangle* pSquare=&square;
   return pSquare;
}
~~~~

###Copy constructor
Principle is to let each class take care of its own internal states and implementations. We just stick to the interface, which is kind of a contract between different classes. Therefor, when buiilding our copy constructor, we prefer to use the constructor of member/parent classes, like this. 
~~~~C++
Rectangle( const Rectangle& other )
: Shape(other),
  width(other.width),
  height(other.height)
{
   if ( other.leftUp != NULL )
   {
      this->leftUp = new Point( *other.leftUp ); 
   }
   else
   {
      this->leftUp = NULL;
   }
}

~~~~
Now if we want to add some members in Point class and also in parent class Shape, like this. What do we do for the Rectangle class's copy constructor?
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
The answer is nothing. Of course the owner of Shape and Point have the responsibility to properly implement their constructors. This is cool because the ownership and responsiblity is clearer.

And also, what is the evaluation order of the initialization-list? Not by the order of how you write down them in the constuctor's initliazation list. The answer is firstly the parent Shape, then follow the order of declaration, why it's designed like this?...read the standard: 

![init order](https://github.com/WenboYang/CppNotes/blob/master/initOrder.png)

Luckliy, the compiler I am using will give this kind of warning when we open the -Wall option, this is cool:
>bo@bo-buntu:~/ws/CppNotes$ g++ -Wall RecTangle.cpp -o RecTangle

>RecTangle.cpp: 在复制构造函数‘Rectangle::Rectangle(const Rectangle&)’:

>RecTangle.cpp:31:8: 警告： ‘Rectangle::height’将在 [-Wreorder]

>RecTangle.cpp:30:8: 警告：   ‘int Rectangle::width’ [-Wreorder]

>RecTangle.cpp:78:1: 警告：   在此处初始化后被初始化 [-Wreorder]

###Copy assignment
Similarly, always prefer the assigment operator of parent and component classes:
~~~~C++
inline Rectangle &Rectangle::operator=(const Rectangle &other )
{
   if ( this == &other )
   {
      return *this;
   }
   
   this->Shape::operator=(other);
   this->width = other.width;
   this->height = other.height;
   
   if( other.leftUp != NULL )
   {
      if( this->leftUp != NULL )
      {
         *leftUp = *other.leftUp;
      }
      else
      {
         leftUp = new Point(*other.leftUp);
      }
   }
   else
   {
      delte this->leftUp;
      this->leftUp = NULL;
   }
   
   return *this;
}
~~~~
         
A great notes by my classmate:
(http://www.jianshu.com/p/629c743b0fd3?utm_campaign=maleskine&utm_content=note&utm_medium=reader_share&utm_source=weixin&from=groupmessage&isappinstalled=0)

