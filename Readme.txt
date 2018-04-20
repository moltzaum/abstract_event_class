*******************************************************
*  Name      : Matthew Moltzau
*  Class     :    CSC 2421           
*  HW#       :       7          
*  Due Date  : March, 15th 2017
*******************************************************

                 	Read Me

*******************************************************
*  Description of the program
*******************************************************

Runs a simulation using an event design pattern which
is implemented using an interface (abstract class).

*******************************************************
*  Source files
*******************************************************

Name: main.cpp
	Runs the BankSimulation object. Catches a
	FileIOException if the file doesn't exist.
	
Name: Event.h and Event.cpp
	EventQueue
		priority_queue<Event, vec, EventTimeComparator>
		addEvent()
		processNext()
	Event
		EventQueue *context
		abstract process()
	EventTimeComparator
		()

Name: Bank.h and Bank.cpp
	struct Customer
	ArrivalEvent implements Event
	DepartureEvent implements Event
	BankSimulation();
	
*******************************************************
*  Circumstances of programs
*******************************************************

Compiled and ran using the makefile from the terminal.

*******************************************************
*  How to build and run the program
*******************************************************

Navigate to the directory that contains all program
files and call "make". Then run by doing "./a.out"
