/* File: NavigationEntry.cpp
Project Name: Browser History Simulator
Description: This file controls the implementation of the NavigationEntry Class

*/

#include "NavigationEntry.h"
#include <iostream>
#include <iomanip>

using namespace std;

NavigationEntry::NavigationEntry() : m_url(""), m_timeStamp(0) {

}

// Name: NavigationEntry (Overloaded constructor)
  // Description: Creates a new NavigationEntry with a string and an int timestamp
  // Preconditions: None
  // Postconditions: Creates a new NavigationEntry object
NavigationEntry::NavigationEntry(const string& url, const int& timestamp) : m_url(url), m_timeStamp(timestamp) {

}

// Accessors (Getters)
string NavigationEntry::GetURL() const {
    return m_url;
}
// Accessors (Getters)
int NavigationEntry::GetTimeStamp() const {
    return m_timeStamp;
}


 // Mutators (Setters)
void NavigationEntry::SetURL(const string& url) {
    m_url = url;

}

 // Mutators (Setters)
void NavigationEntry::SetTimeStamp(const int& time) {
    m_timeStamp = time;

}

// Name: IsEmpty
  // Description: Returns true if m_url is empty
  // Preconditions: None
  // Postconditions: Returns true if m_url is empty else false
bool NavigationEntry::IsEmpty() const {
    return m_url.empty();

}

// Name: Overloaded <<
  // Description: Prints the details of a navigation entry
  // Preconditions: None
  // Postconditions: Returns an ostream with output of a navigation entry
  // Sample output: URL:http://daler.org/ Visited On: 2018-03-02 16:48:00
ostream& operator<<(ostream& cout, NavigationEntry& entry) {
    cout << "URL:" << entry.GetURL() 
       << " Visited On: " << entry.DisplayTimeStamp(entry.GetTimeStamp());
    return cout;
}