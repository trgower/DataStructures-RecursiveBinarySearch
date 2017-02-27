/*

  Tanner Gower
  11/7/2016
  Project 7: Recursive Binary Search Algorithm

*/

#include <iostream>
#include <string>
#include <sstream>
#include <cstdlib>
#include <ctime>
#include "Student.h"

using namespace std;

Student::Student()
{
  id = rand() % 9000 + 1000;
  name = "John Doe";
  address = "123 Address Line, San Marcos, TX 78666";

  // Generate random grades, nobody gets below a 60
  grades = new int[10];
  double total = 0.0;
  for (int i = 0; i < 10; i++) {
    grades[i] = (rand() % 40) + 60;
    total += grades[i];
  }

  gpa = (total / 10) / 25.0;
}

Student::Student(string parse)
{

  int lastDelim = 0;
  int token = 0;
  for (int i = 0; i < parse.length(); i++) {
    if (parse[i] == '|') {
      if (token == 0) { // id
        id = atoi(parse.substr(lastDelim, i-lastDelim).c_str());
        token++;
      } else if (token == 1) { // name
        name = parse.substr(lastDelim, i-lastDelim);
        token++;
      } else if (token == 2) { // name
        address = parse.substr(lastDelim, i-lastDelim);
        token++;
      } else if (token == 3) { // grades
        grades = new int[10];
        string sgrades = parse.substr(lastDelim, i-lastDelim);

        int lastComma = 0;
        int gradesNum = 0;
        for (int j = 0; j < sgrades.length(); j++) {
          if (sgrades[j] == ',') {
            grades[gradesNum++] = atoi(sgrades.substr(lastComma, j-lastComma).c_str());
            lastComma = j+1;
          }
        }
        grades[gradesNum] = atoi(sgrades.substr(lastComma, sgrades.size()).c_str());

        token++;
      }
      lastDelim = i+1;
    }
  }
  double total = 0.0;
  for (int i = 0; i < 10; i++) {
    total += grades[i];
  }

  gpa = (total / 10) / 25.0;
}

Student::~Student()
{
  //delete [] grades;
  // caused errors?
}

void Student::setId(int newId) { id = newId; }
void Student::setName(string newName) { name = newName; }
void Student::setAddress(string newAddress) { address = newAddress; }
void Student::setGpa(double newGpa) { gpa = newGpa; }

int Student::getId() { return id; }
string Student::getName() { return name; }
string Student::getAddress() { return address; }
double Student::getGpa() { return gpa; }
string Student::toString() {
  stringstream ss;
  ss << id << "|" << name << "|" << address << "|";
  for (int i = 0; i < 10; i++) {
    ss << grades[i];
    if (i < 9) ss << ", ";
  }
  ss << "|" << gpa;
  return ss.str();
}
