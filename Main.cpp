/*

  Tanner Gower
  11/7/2016
  Project 7: Recursive Binary Search Algorithm

*/

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include "Student.h"

using namespace std;

const int kNumStudents = 20;

int binarySearch(vector<Student> list, int target, int f, int l) {
  int m = (f + l) / 2;
  if (list[m].getId() == target)
    return m;
  else if (list[m].getId() > target)
    l = m - 1;
  else
    f = m + 1;
  if (f <= l)
    return binarySearch(list, target, f, l);
  else
    return -1; // not found
}

void sort(Student students[])
{
  bool swapped = true;
  int j = 0;
  Student temp;
  while (swapped) {
    swapped = false;
    j++;
    for (int i = 0; i < kNumStudents - j; i++) {
      if (students[i].getId() > students[i+1].getId()) {
        temp = students[i]; // Should be fine without copy constructor here
        students[i] = students[i+1];
        students[i+1] = temp;
        swapped = true;
      }
    }
  }
}

int main ()
{
  srand(time(0));
  Student students[kNumStudents];

  ifstream infile("students");
  string line = "";
  int i = 0;
  do {
    getline(infile, line);
    Student newStudent(line);
    students[i++] = newStudent; // Should have copy constructor but meh
  } while (i < kNumStudents);

  sort(students);

  vector<Student> students_v;
  for (int i = 0; i < kNumStudents; i++)
    students_v.push_back(students[i]);

  // Print sorted vector elements
  cout << "ID|NAME|ADDRESS|GRADES|GPA" << endl;
  for (int i = 0; i < kNumStudents; i++)
    cout << students_v[i].toString() << endl;
  cout << endl;

  // Search 3 random IDs that are in the vector
  cout << "-----Search 3 random IDs that are in the vector-----" << endl;
  for (int i = 0; i < 3; i++) {
    int s = rand() % kNumStudents;
    cout << "Search target: " << students_v[s].getId() << endl;
    int r = binarySearch(students_v, students_v[s].getId(), 0, kNumStudents);
    if (r != -1)
      cout << "Target found: " << students_v[r].toString() << endl;
    else
      cout << "Target not found!" << endl;
  }
  cout << endl;

  // Search an ID at the end of the vector (in slot kNumStudents - 1)
  cout << "-----Search for ID at the end of the vector-----" << endl;
  cout << "Search target: " << students_v[kNumStudents-1].getId() << endl;
  int r = binarySearch(students_v, students_v[kNumStudents-1].getId(),
    0, kNumStudents);
  if (r != -1)
    cout << "Target found: " << students_v[r].toString() << endl;
  else
    cout << "Target not found!" << endl;
  cout << endl;

  // Search an ID that is NOT in the vector (100, All IDs are at least 4 digits)
  cout << "-----Search for ID that is NOT in the vector (100)-----" << endl;
  cout << "Search target: " << 100 << endl;
  r = binarySearch(students_v, 100, 0, kNumStudents);
  if (r != -1)
    cout << "Target found: " << students_v[r].toString() << endl;
  else
    cout << "Target not found!" << endl;

  return 0;
}
