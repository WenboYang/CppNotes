//This is bad practice, caller don't know that this needs to be released, and
//When?
MyClass *func()
{
   MyClass* pa = new MyClass();
   return pa;
}

//who allocate, who is responsible to release;
//don't return pointer.
//


//O-C, C, C++, memory leakage.
//heap object, pointer stored in stack, point to the real object on heap.


//* Draw the object memory model diagram, when the program is executed in memory,
//how it's stored.    
//
//syntax, rules, tricks, 
//
///////////////////////////////////////////////////////////////////////////////
Variable Model and usage

//3 types of model
MyClass c;   //on stack;
MyClass* pc;

pc = &c; //stack pointer;
pc = new MuClass(); //heap pointer;

Myclass& c2 = c; //Alias, stack ref/
MyClass *pc2 = new MyClass();
MyClass& c3 = *pc2  //heap ref;

//pc can be in stack or heap, the object will be copied;
c = *pc;
//get pointer from a object;
pc = &c;


//3 scenarios
//
//1.delare
//
//2.pass param
//question, how large is a object? C++, O-C, any language
//byte alignment, size 
//a virtual function pointer cost 4 bytes on 32bit MCU, 8 bytes on 64bit MCU
void func1(MyClass c)  //copy costs memory;
{

}

//not recommend, you don't know it's stack or heap pointer.
//undefined behavior if you want to delete a stack object.
//allocation and release should be done by the same owner, not inside this:
void func2(MyClass* pc)
{

}

//recommend practice, the memory cost is the same as pointer.
void func3(MyClass& c)
{
}

//const ref is the recommanded replacement for passing by value.
void func3(const MyClass& c)
{
}


//bad practice
void func3( Myclass& mc )
{
   MyClass *p = &mc;
   delete p;
}

//RETURN VALUE, costly.
//
Myclass func1()
{
   Myclass c1;
   return rc;

   //not recommended, 
   Myclass* pc2 = new MyClass();
   return* pc2; //here the new object will be copied into somewhere else, so the object created here will not be pointed by any pointer and can't be reused anymore.
}


//must be manually cleaned up
MyClass* func2()
{
   //wrong
   Myclass c1;
   return &c1;

   //not recommanded, might be leaked
   Myclass *pc2 = new Myclass();
   return pc2;
}

MyClass& func3()
{
   //wrong
   MyClass c1;
   return c1;

   MyClass *pc2 = new MyClass();
   return *pc2;
}

//memory will be leadked
MyClass c = func3(); //

MyClass& c4 = func3();
//has to been cleaned up by caller by doing this:
delete &c4;

//only *this can be safely returned, 
//this is okay, because we are returning the object that was passed in.
Myclass& func4(Myclass &c )
{
   return c;
}

//stack----function----static characters;
//
//heap ----dynamic-----





