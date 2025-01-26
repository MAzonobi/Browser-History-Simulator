/* File: Browser.cpp
Project Name: Browser History Simulator
Description: This file controls the implementation of the Browser Class

*/

#include "Browser.h"
#include <fstream>
#include <iostream>
#include <iomanip>

using namespace std;


// Name: Browser (Overloaded constructor)
  // Description: Creates a new Browser with the filename passed
  // Preconditions: None
  // Postconditions: Sets m_fileName and m_currentPage to nullptr
Browser::Browser(string filename) {
    m_fileName = filename;
    m_currentPage = nullptr;
}

// Name: ~Browser (Destructor)
  // Description: Deallocates the items in m_backStack, m_forwardStack and
  //              m_currentPage
  // Preconditions: None
  // Postconditions: Deallocates all dynamically allocated memory
Browser::~Browser() {

    delete m_currentPage;
  m_currentPage = nullptr;

  // Deallocates back stack
  while (!m_backStack.IsEmpty()) {
    delete m_backStack.Pop();
  }

  // Deallocates forward stack
  while (!m_forwardStack.IsEmpty()) {
    delete m_forwardStack.Pop();
  }

}


  // Name: StartBrowser
  // Description: Loads the file and calls the menu
  // Preconditions: None
  // Postconditions: Menu keeps running until exited
void Browser::StartBrowser() {

    //Browser starts by loading file and mainmenu
    LoadFile();
    Menu();
}

// Name: Menu
  // Description: Menu that allows browser history to be displayed, go back,
  //              go forward, visit a site or quit.
  // Preconditions: None
  // Postconditions: When exiting, thanks user.
void Browser::Menu() {
  int choice;

    //Will prompt mainmenu at least once 
  do {
   
    cout << "Welcome to the Browser History Simulator" << endl;
    cout << "What would you like to do?" << endl;
    cout << "1. Display Browser History" << endl;
    cout << "2. Go Back (1)" << endl;
    cout << "3. Go Forward (1)" << endl;
    cout << "4. Visit Site" << endl;
    cout << "5. Quit" << endl;
    cin >> choice;

    
    switch (choice) {
      case 1:
        Display();
        break;
      case 2:
        Back(1);
        break;
      case 3:
        Forward(1);
        break;
      case 4:
        NewVisit();
        break;
      case 5:
        cout << "Thank you for using the Browser History Simulator!" << endl;
        break;
      default:
        cout << "Invalid choice. Select one of the following " << endl;
    }

    cout << endl; 
    // continues to prompt until the user quits out 
  } while (choice != 5); 

}


// Name: Visit
  // Description: Dynamically allocates a new NavigationEntry (NE).
  //              If m_currentPage is nullptr, assigns new NE to the currentPage
  //              Otherwise, pushes the currentPage into the history and updates
  //              m_currentPage to new NE
  // Preconditions: None
  // Postconditions: Adds things to m_backStack or m_currentPage
void Browser::Visit(const string& url, int timestamp) {
  NavigationEntry* newEntry = new NavigationEntry(url, timestamp);

  if (m_currentPage == nullptr) {
    m_currentPage = newEntry; 
  } else {
    m_backStack.Push(m_currentPage); 
    m_currentPage = newEntry; 
    
    //clears forward stack with no site visited 
    while (!m_forwardStack.IsEmpty()) {
      delete m_forwardStack.Pop(); 
    }
  }
}


// Name: NewVisit
  // Description: User enters the URL of the site visited and populates the
  //              timestamp based on the current system time (below)
  //              auto now = chrono::system_clock::now();
  //              time_t nowAsTimeT = std::chrono::system_clock::to_time_t(now);
  //              int64_t timestamp = static_cast<int64_t>(nowAsTimeT);
  // Preconditions: None
  // Postconditions: Adds new URL to m_backStack or m_currentPage
void Browser::NewVisit() {
  
  string url;
  cout << "Enter the URL of the site you visited: ";
  cin >> url;

  auto now = chrono::system_clock::now();
  time_t nowAsTimeT = chrono::system_clock::to_time_t(now);
  int64_t timestamp = static_cast<int64_t>(nowAsTimeT);

  Visit(url, timestamp);
}


  // Name: Display
  // Description: Display all of then entires in the back stack and front stack
  // Preconditions: None
  // Postconditions: None
void Browser:: Display() {

    cout << "**Back Stack**" << endl;
    if (m_backStack.IsEmpty()) {
        cout << "Empty" << endl;

    }else{
        //Iterates through the back stack and displays contents
        for (unsigned int i = 0; i < m_backStack.GetSize(); ++i) {
            cout << (i + 1) << ". " << *(m_backStack.At(i)) << endl;
        }
    }
    cout << "**Forward Stack**" << endl;
    if (m_forwardStack.IsEmpty()) {
        cout << "Empty" << endl;

    }else{
        //Iterates through forward stack and displays contents
        for (unsigned int i = 0; i < m_forwardStack.GetSize(); ++i) {
            cout << (i +1) << ". " << *(m_forwardStack.At(i)) << endl;
        }
    }

    cout << "Current Website: " << endl;
    if (m_currentPage == nullptr) {
        cout << "No current page" << endl;

    }else{
        cout << *m_currentPage << endl;

    }
}


 // Name: Back (steps)
  // Description: Moves item from m_currentPage to m_forwardStack
  //              Moves item from m_backStack to m_currentPage
  //              If m_backStack is empty, does not fail but does nothing.
  //              While can do more than one step, normally only moves one.
  // Preconditions: m_backStack must not be empty.
  // Postconditions: Rotates items as above
NavigationEntry Browser::Back(int steps) {

    //Checks for empty back stack
  if (m_backStack.IsEmpty()) {
    cout << "Back stack is empty. Cannot go back." << endl;
    return *m_currentPage; 
  }

  for (int i = 0; i < steps && !m_backStack.IsEmpty(); ++i) {
    m_forwardStack.Push(m_currentPage); 
    m_currentPage = m_backStack.Pop(); 
  }

  return *m_currentPage;
}


 // Name: Forward (steps)
  // Description: Moves item from m_backStack to m_currentPage
  //              Moves item from m_currentPage to m_forwardStack
  //              If m_forwardStack is empty, does not fail but does nothing.
  //              While can do more than one step, normally only moves one.
  // Preconditions: m_forwardStack must not be empty
  // Postconditions: Rotates items as above
NavigationEntry Browser::Forward(int steps) {
  if (m_forwardStack.IsEmpty()) {
    cout << "Forward stack is empty. Cannot go forward." << endl;
    return *m_currentPage; 
  }
    // Moves by specified number of steps until stack is empty
  for (int i = 0; i < steps && !m_forwardStack.IsEmpty(); ++i) {
    m_backStack.Push(m_currentPage); 
    m_currentPage = m_forwardStack.Pop(); 
  }

  return *m_currentPage;
}

  // Name: GetCurrentPage
  // Description: Returns the current page
  // Preconditions: None
  // Postconditions: None
NavigationEntry Browser::GetCurrentPage() const {
  if (m_currentPage == nullptr) {
    throw runtime_error("No current page.");
  }
  return *m_currentPage;
  
}


  // Name: LoadFile
  // Description: Loads the file using Visit
  // Preconditions: None
  // Postconditions: Adds things to m_backStack or m_currentPage
void Browser::LoadFile() {
    ifstream file(m_fileName);

    if (!file.is_open()) {
        cerr << "Unable to open file " << m_fileName << endl;
        return;
    }

    string line;
    while (getline(file, line)) {
        unsigned int delimiterPos = line.find(DELIMITER);
        if (delimiterPos < line.size()) { 
            string url = line.substr(0, delimiterPos);

            int timestamp = stoi(line.substr(delimiterPos + 1));
            Visit(url, timestamp);
        }
    }

    file.close();
}





