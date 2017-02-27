project7: Main.o Student.o
	g++ Main.o Student.o -o project7

Main.o: Main.cpp Student.h
	g++ -c Main.cpp

Student.o: Student.cpp Student.h
	g++ -c Student.cpp
