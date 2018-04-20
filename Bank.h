#ifndef BANK_SIMULATION_H
#define BANK_SIMULATION_H

#include <string>
#include "Event.h"

using std::string;

//This exception class is pretty much standalone. I have it here because it
//seems like a waste for it to have its own file and the program is small
//enough that this is the only place it will be used. If it is in main the
//BankSimulation won't be able to access it either.
class FileIOException { /*empty exception*/ };

class BankSimulation {
	
public:

//A customer struct for basic information:
struct Customer {
	int arrivalTime;
	int transactionTime;
	Customer(int, int);
};
	
	BankSimulation(string fileName = "simulation.txt") throw (FileIOException);

//The following nested classes are able to access the private members of BankSimulation
private:

//Implementations of the Event interface:

//arrivalTime for ArrivalEvent is implicitly time from Event
class ArrivalEvent: public Event {
	public:
	int transactionTime;
	ArrivalEvent(int, int);
	void process();
};

//departureTime for DepartueEvent is implicitly time from Event
class DepartureEvent: public Event {
	public:
	DepartureEvent(int);
	void process();
};

};

#endif