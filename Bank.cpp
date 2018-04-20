#include "Bank.h" 	/* Implementing */
#include <fstream>

#include <iostream>
using std::cout;
using std::endl;

typedef BankSimulation Bank;
	
	//These Global variables are here for TIME (it isn't an intentional
	//design decision). I was thinking of making a BankEvent class which
	//the other event classes could extend. The BankEvent class would have
	//a pointer to the BankSimulation to act as a context. The bankLine
	//in particular is not a part of the process() method because I didn't
	//want the event class to accept any parameters so that it could be
	//more general.
	int currentTime = 0;
	bool tellerAvailible = true;
	queue<Bank::Customer> bankLine = queue<Bank::Customer>();
	int waitTime = 0, peopleHelped = 0;
	
	//Nested Class Constructors:
	Bank::Customer::
		Customer(int at, int tt): arrivalTime(at), transactionTime(tt) {}
	
	Bank::ArrivalEvent::
		ArrivalEvent(int at, int tt): Event(at), transactionTime(tt) {}
	
	Bank::DepartureEvent::
		DepartureEvent(int dt): Event(dt) {}
	
	//Event Processes:
	void Bank::ArrivalEvent::process() {
		cout << "Processing an arrival event at time: " << currentTime << endl;
		
		if (bankLine.empty() && tellerAvailible) {
			eventQueue->addEvent(new DepartureEvent(currentTime + transactionTime));
			tellerAvailible = false;
		} else bankLine.push(Customer(time, transactionTime));
	}
	
	void Bank::DepartureEvent::process() {
		cout << "Processing a departure event at time: " << currentTime << endl;
		
		//Part of calculating the average wait time:
		if (bankLine.front().arrivalTime != 0)
			waitTime += currentTime - bankLine.front().arrivalTime;
		peopleHelped++;
		
		if (!bankLine.empty()) {			
			eventQueue->addEvent(new DepartureEvent(currentTime + bankLine.front().transactionTime));
			bankLine.pop();
		} else tellerAvailible = true;
	}
	
	//Loads and runs a simulation from the text file.
	Bank::BankSimulation(string fileName) throw (FileIOException) {
		cout << "Simulation Begins" << endl;
		std::ifstream in(fileName);
		if (in.fail()) throw FileIOException();
		
		EventQueue *eq = new EventQueue();
		int arrivalTime, transactionTime;
		while (in >> arrivalTime >> transactionTime)
			eq->addEvent(new ArrivalEvent(arrivalTime, transactionTime));
		
		while (!eq->isEmpty()) {
			currentTime = eq->getTimeOfNext();
			eq->processNext();
		}
		
		cout << "Total number of people processed: " << peopleHelped << endl;
		cout << "Average amount of time spent waiting: " << (float) waitTime / peopleHelped << endl;
		
		delete eq;
	}
	