#include <iostream>
#include <string>
using namespace std;
#include "Stack.cpp"

// To test just queue follow these instructions:
//   1. make stest
//   2. make stest2
// This tests some of the important functions in Stack.
// You should add additional tests to make sure everything in the class works.
// During grading, we will test all functions in the Stack class.

int main () {
  //Test 1 - Default Constructor, Push, and Display
  cout << "Test 1 - Default Constructor, Push, and Display Test" << endl;
  int test1 = 10;
  int test2 = 20;
  int test3 = 30;
  //Test Default Constructor
  Stack <int> *newLS1 = new Stack <int>();
  //Push 3 nodes into Stack
  newLS1->Push(test1);
  newLS1->Push(test2);
  newLS1->Push(test3);
  cout << "After 3 Pushs size: " << newLS1->GetSize() << endl;
  newLS1->Display();
  cout << "End Test 1 - Constructor, Push, and Display Test" << endl << endl;
    
  //Test 2 - Copy Constructor and Assignment Operator
  cout << "Test 2 - Copy Constructor Running" << endl;
  //Test Copy constructor
  Stack <int> *newLS2 = new Stack <int>(*newLS1);
  newLS2->Display();
  cout << "size below should match. Location should not" << endl;
  cout << "Source size: " << newLS1->GetSize() << " and Copied size: "
       << newLS2->GetSize() << endl;
  cout << "Source location: " << &newLS1 << " and Copied location: " << &newLS2 << endl;
  cout << "End Test 2 - Copy Constructor" << endl << endl;
  
  //Test 3 - Overloaded Assignment Operator
  cout << "Test 3 - Overloaded Assignment Operator Running" << endl;
  //Create new Stack using constructor
  Stack <int> *newLS3 = new Stack <int>();
  //Update using overloaded assignment operator
  *newLS3 = *newLS1;
  newLS3->Display(); //Display contents of newLS3
  cout << "size below should match. Location should not" << endl;
  cout << "Source size: " << newLS1->GetSize() << " and Assigned size: " << newLS3->GetSize() << endl;
  cout << "Source location: " << &newLS1 << " and Assigned location: " << &newLS3 << endl;
  cout << "End Test 3 - Assignment" << endl << endl;
  
  //Test 4 - Test Pop
  cout << "Test 4 - Pop" << endl;
  cout << "size before: " << newLS1->GetSize() << " ";
  newLS1->Pop();
  cout << "size after: " << newLS1->GetSize() << endl;
  cout << "End Test 4 - Pop" << endl << endl;
  
  //Test 5 - Test GetSize
  cout << "Test 5 - GetSize Running" << endl;
  //Test size()
  cout << "Outputting GetSize" << endl;
  cout << newLS2->GetSize() << endl;
  cout << "End Test 5 - GetSize" << endl << endl;
  
  //Test 6 - Test Destructor
  cout << "Test 6 - Test Destructor" << endl;
  cout << "delete newLS1" << endl;
  delete newLS1;
  cout << "delete newLS2" << endl;
  delete newLS2;
  cout << "delete newLS3" << endl;
  delete newLS3;
  cout << "End Test 6 - Destructors" << endl;
  

  //Test 7 - Test RemoveBottom
  cout << "Test 7 - Test RemoveBottom" << endl;
  Stack<int> stackRemove;
  stackRemove.Push(10);
  stackRemove.Push(20);
  stackRemove.Push(30);
  stackRemove.Display();
  cout << "Size before removing: " << stackRemove.GetSize() << endl;
  cout << "Bottom element removed: " << stackRemove.RemoveBottom() << endl;
  stackRemove.Display();
  cout << "Size after removing: " << stackRemove.GetSize() << endl;
  cout << "Test 7 complete" << endl;


  //Test 8 - Test Peek
  cout << "Test 8 - Test Peek" << endl;
  Stack<int> stackPeek;
  stackPeek.Push(40);
  stackPeek.Push(50);
  stackPeek.Push(60);
  stackPeek.Display();
  cout << "Peek value: " << stackPeek.Peek() << endl;
  cout << "Test 8 completed";


  //Test 9 - Test At
  cout << "Test 9 - Test At " << endl;
  Stack<string> stackAt;
  stackAt.Push("ten");
  stackAt.Push("twenty");
  stackAt.Push("thirty");
  stackAt.Display();
  cout << "Position 0: " << stackAt.At(0) << endl;
  cout << "Position 2: " << stackAt.At(2) << endl;
  try {
    cout << "Position 3: " << stackAt.At(3) << endl;

  } catch (out_of_range const& ex){
    cerr << "Caught Exception: " << ex.what() << endl;

  }
  cout << "Test 9 completed" << endl;



  //Test 10 - Test IsEmpty
  cout << "Test 10 - Test IsEmpty";
  Stack<char> stackEmpty;

  cout << "Is the stack empty? ";
  if (stackEmpty.IsEmpty()) {
    cout << "Yes";
  }else{
    cout << "No";
  }
  cout << endl;

  stackEmpty.Push('A');
  cout << "Is the stack empty after the Push? ";
  if (stackEmpty.IsEmpty()) {
    cout << "Yes";
  }else{
    cout << "No";

  }
  cout << endl;

  stackEmpty.Pop();
  cout << "Is the stack empty after the Pop? ";
  if (stackEmpty.IsEmpty()) {
    cout << "Yes";

  }else{
    cout << "No";

  }
  cout << endl;

  cout << "Test 10 completed" << endl;

  return 0;
}

