#ifndef EVENT_H
#define EVENT_H 

#include <queue>
#include <vector>

using std::priority_queue;
using std::queue;
using std::vector;

//foward declaration of Event so that I can use it before defining it fully
class Event;
typedef Event* EventRef;

class EventTimeComparator {
	public:
	bool operator() (EventRef, EventRef) const;
};

//Event Queue is a class which encapsulates a priority queue. It's main
//purpose is to process events and then remove them from the queue.
class EventQueue {
	
	typedef vector<EventRef> Container;
	
	//The first parameter tells what the queue contains
	//The second parameter tells what structure the queue has. (this
	//is vector by default, but I need to include it so that I can set
	//the third parameter)
	//The third parameter is the comparator. Comparators are defined
	//as classes which overload the () operator for two objects
	//(events) in this case. The class "Event" could do this itself,
	//but I wanted to show I could do it with a separate class.
	priority_queue<EventRef, Container, EventTimeComparator> events;
	
	public:
	EventQueue() {
		events = priority_queue<EventRef, Container, EventTimeComparator>();
	}
	
	void addEvent(Event*);
	int getTimeOfNext();
	void processNext();
	bool isEmpty();
};

class Event {
	protected:
	//The Event class contains the eventQueue so that it can generate new events.
	//This variable is accessible to all subclasses of this event class.
	EventQueue *eventQueue;
	
	public:
	//The time must be set in the constructor as time is constant.
	/*const*/ int time;
	
	Event(int time): time(time) {}
	virtual ~Event() {}
	
	void setContext(EventQueue *eq) {
		eventQueue = eq;
	}
	
	//The generic method any event is guaranteed to have
	virtual void process() = 0;
};

#endif