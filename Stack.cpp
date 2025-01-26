/*Title: Stack.cpp
  Author: Prof. Dixon
  Date: 11/14/2024
  Description: This class defines a templated stack using a linked list
*/
#include <iostream>
#include <stdexcept>
using namespace std;

//Templated node class used in templated linked list
template <class T>
class Node {
public:
  Node( const T& data ); //Constructor
  T& GetData(); //Gets data from node
  void SetData( const T& data ); //Sets data in node
  Node<T>* GetNext(); //Gets next pointer
  void SetNext( Node<T>* next ); //Sets next pointer
private:
  T m_data;
  Node<T>* m_next;
};

//Overloaded constructor for Node
template <class T>
Node<T>::Node( const T& data ) {
  m_data = data;
  m_next = NULL;
}

//Returns the data from a Node
template <class T>
T& Node<T>::GetData() {
  return m_data;
}


//Sets the data in a Node
template <class T>
void Node<T>::SetData(const T& data ) {
  m_data = data;
}

//Gets the pointer to the next Node
template <class T>
Node<T>* Node<T>::GetNext() {
  return m_next;
}

//Sets the next Node
template <class T>
void Node<T>::SetNext( Node<T>* next ) {
  m_next = next;
}

//**********Stack Class Declaration***********
template <typename T> //Indicates linked list is templated
class Stack {
public:
  // Name: Stack (Default constructor)
  // Description: Creates a new Stack object
  // Preconditions: None
  // Postconditions: Creates a new Stack object
  Stack();
  // Name: ~Stack
  // Description: Stack destructor - deallocates all nodes in linked list
  // Preconditions: None
  // Postconditions: All nodes are deleted. Size is 0. No memory leaks.
  ~Stack();
  // Name: Stack (Copy constructor)
  // Description: Creates a new Stack object based on existing stack
  // Preconditions: None
  // Postconditions: Creates a new Stack object from existing stack
  //                 in separate memory space
  Stack(const Stack& source);
  // Name: Stack<T>& operator= (Assignment operator)
  // Description: Makes two stacks identical based on source.
  // Preconditions: None
  // Postconditions: Two stacks with same number of nodes and same values
  //                 in each node in a separate memory space
  Stack<T>& operator=(const Stack& other);
  // Name: Push
  // Description: Adds a new node to the top of the stack
  // Preconditions: None
  // Postconditions: Adds a new node to the top of the stack
  void Push(const T& value);
  // Name: Pop
  // Description: If stack is empty, throw runtime_error("Stack is empty");
  //              Temporarily stores data from node at the top of the stack.
  //              Removes the node from the top of the stack. Returns the stored data.
  // Preconditions: Stack has at least one node
  // Postconditions: See description 
  T Pop();
  // Name: Peek
  // Description: If stack is empty, throw runtime_error("Stack is empty");
  //              Returns the stored data from top node.
  // Preconditions: Stack has at least one node
  // Postconditions: See description
  T Peek() const;
  // Name: At
  // Description: If stack is empty, throw runtime_error("Stack is empty")
  //              Returns stored data from number of the node passed to function.
  //              At(3) would return the data from the fourth node.
  // Preconditions: Stack has at least one node
  // Postconditions: Returns data from number of node starting at m_top
  T At(int num);
  // Name: IsEmpty
  // Description: Returns if the stack has any nodes.
  // Preconditions: Stack has at least one node
  // Postconditions: If stack has no nodes, returns true. Else false.
  bool IsEmpty() const;
  // Name: RemoveBottom
  // Description: If stack is empty, throw runtime_error("Stack is empty")
  //              Temporarily stores data from node at the bottom of the stack.
  //              Removes node from bottom of the stack. Returns the stored data.
  //              Similar to Pop but opposite end of stack
  // Preconditions: Stack has at least one node
  // Postconditions: Removes node from bottom of stack and returns data
  T RemoveBottom();
  // Name: Display
  // Description: If stack is empty, outputs that the stack is empty
  //              Otherwise, iterates through stack and displays data in each node
  // Preconditions: Stack has at least one node
  // Postconditions: Displays data from each node in stack
  void Display();
  // Name: GetSize
  // Description: Returns the number of nodes in the stack
  // Preconditions: None
  // Postconditions: Returns the number of nodes in the stack.
  size_t GetSize() const;  
private:
  Node<T>* m_top; //Top node in stack
  size_t m_size; //Number of nodes in stack
};

//*********************STACK FUNCTIONS IMPLEMENTED HERE******************


 // Name: Stack (Default constructor)
  // Description: Creates a new Stack object
  // Preconditions: None
  // Postconditions: Creates a new Stack object
template <typename T> 
Stack<T>::Stack() : m_top(nullptr), m_size(0) {

}


 // Name: ~Stack
  // Description: Stack destructor - deallocates all nodes in linked list
  // Preconditions: None
  // Postconditions: All nodes are deleted. Size is 0. No memory leaks.
template <typename T>
Stack<T>::~Stack() {


  // deallocates while iterating through stack
  while (m_top != nullptr) {
    Node<T>* temp = m_top;
    m_top = m_top->GetNext();
    delete temp; 
  }

  m_size = 0;

}

  // Name: Stack (Copy constructor)
  // Description: Creates a new Stack object based on existing stack
  // Preconditions: None
  // Postconditions: Creates a new Stack object from existing stack
  //                 in separate memory space
template <typename T>
Stack<T>::Stack(const Stack& source) : m_top(nullptr), m_size(0) {

  //Check if the stack is not empty
  if (source.m_top != nullptr) {
    Node<T>* curr = source.m_top;
    Node<T>* newNode =  new Node<T>(curr->GetData());
    m_top = newNode;
    curr = curr->GetNext();
    Node<T>* tail = m_top;

    //Copies remaining nodes of the source stack
    while (curr != nullptr) {
      newNode = new Node<T>(curr->GetData());
      tail->SetNext(newNode);
      tail = newNode;
      curr = curr->GetNext();

    }

    m_size = source.m_size;
  }

}

  // Name: Stack<T>& operator= (Assignment operator)
  // Description: Makes two stacks identical based on source.
  // Preconditions: None
  // Postconditions: Two stacks with same number of nodes and same values
  //                 in each node in a separate memory space
template <typename T> 
Stack<T>& Stack<T>::operator=(const Stack& other) {

  if (this != &other) {
    //Clears content of the stack by dellocating
    while (m_top != nullptr) {
      Node<T>* temp = m_top;
      m_top = m_top->GetNext();
      delete temp;
    }
    //reset size of stack
    m_size = 0;


    if (other.m_top != nullptr) {
      Node<T>* curr = other.m_top;
      Node<T>* newNode = new Node<T>(curr->GetData());
      m_top = newNode;
      curr = curr->GetNext();
      Node<T>* tail = m_top;

      //copies remaining nodes of the source stack
      while (curr != nullptr) {
        newNode = new Node<T>(curr->GetData());
        tail->SetNext(newNode);
        tail = newNode;
        curr = curr->GetNext();

      }

      m_size = other.m_size;

    }
  }

  return *this;
}

 // Name: Push
  // Description: Adds a new node to the top of the stack
  // Preconditions: None
  // Postconditions: Adds a new node to the top of the stack
template <typename T>
void Stack<T>::Push(const T& value) {

  Node<T>* newNode = new Node<T>(value);
  newNode->SetNext(m_top);
  m_top = newNode;
  ++m_size;
}

 // Name: Pop
  // Description: If stack is empty, throw runtime_error("Stack is empty");
  //              Temporarily stores data from node at the top of the stack.
  //              Removes the node from the top of the stack. Returns the stored data.
  // Preconditions: Stack has at least one node
  // Postconditions: See description 
template <typename T>
T Stack<T>::Pop() {
  if (IsEmpty()) {
    throw runtime_error("Stack is empty");

  }

  Node<T>* temp = m_top;
  T data = temp->GetData();

  m_top = m_top->GetNext();
  delete temp;

  --m_size;
  return data;

}


  // Name: Peek
  // Description: If stack is empty, throw runtime_error("Stack is empty");
  //              Returns the stored data from top node.
  // Preconditions: Stack has at least one node
  // Postconditions: See description
template <typename T> 
T Stack<T>::Peek() const {
  if (IsEmpty()) {
    throw runtime_error("Stack is empty");

  }

  return m_top->GetData();
}


 // Name: At
  // Description: If stack is empty, throw runtime_error("Stack is empty")
  //              Returns stored data from number of the node passed to function.
  //              At(3) would return the data from the fourth node.
  // Preconditions: Stack has at least one node
  // Postconditions: Returns data from number of node starting at m_top
template <typename T>
T Stack<T>::At(int num) {
  if (IsEmpty()) {
    throw runtime_error("Stack is empty");

  }

  int intSize = m_size;
  if (num < 0 || num >= intSize) {
    throw out_of_range("This index is out of range");

  }

  // traverse the stack to the specified node
  Node<T>* curr = m_top;
  for (int i = 0; i < num; ++i) {
    curr = curr->GetNext();

  }
  return curr->GetData();
}


 // Name: IsEmpty
  // Description: Returns if the stack has any nodes.
  // Preconditions: Stack has at least one node
  // Postconditions: If stack has no nodes, returns true. Else false.
template <typename T>
bool Stack<T>::IsEmpty() const {

  bool nulltop = (m_top == nullptr);
  return nulltop;
}


 // Name: RemoveBottom
  // Description: If stack is empty, throw runtime_error("Stack is empty")
  //              Temporarily stores data from node at the bottom of the stack.
  //              Removes node from bottom of the stack. Returns the stored data.
  //              Similar to Pop but opposite end of stack
  // Preconditions: Stack has at least one node
  // Postconditions: Removes node from bottom of stack and returns data
template <typename T>
T Stack<T>::RemoveBottom() {

  if (IsEmpty()) {
    throw runtime_error("Stack is empty");

  }
  
  //Handles case of one node in stack
  if (m_top->GetNext() == nullptr) {
    T data = m_top->GetData();
    delete m_top;
    m_top = nullptr;
    --m_size;
    return data;
  }

  Node<T>* curr = m_top;
  while (curr->GetNext()->GetNext() != nullptr) {
    curr = curr->GetNext();

  }

  //Removes bottom node 
  Node<T>* bottomNode = curr->GetNext();
  T data = bottomNode->GetData();

  curr->SetNext(nullptr);
  delete bottomNode;

  //decrease stack size after removing
  --m_size;

  return data;
}

 // Name: Display
  // Description: If stack is empty, outputs that the stack is empty
  //              Otherwise, iterates through stack and displays data in each node
  // Preconditions: Stack has at least one node
  // Postconditions: Displays data from each node in stack
template <typename T>
void Stack<T>::Display() {

  if (IsEmpty()) {
    cout << "The stack is empty." << endl;
    return;
  }

  //Starts displaying stack contents 
  Node<T>* curr = m_top;
  cout << "Stack contents (top to bottom):" << endl;
  while (curr != nullptr) {
    //current nodes' data is printed
    cout << curr->GetData() << endl; 
    curr = curr->GetNext(); 
  }
}


 // Name: GetSize
  // Description: Returns the number of nodes in the stack
  // Preconditions: None
  // Postconditions: Returns the number of nodes in the stack.
template <typename T>
size_t Stack<T>::GetSize() const {

  return m_size;

}