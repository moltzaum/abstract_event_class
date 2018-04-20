#include "Event.h"	/* Implementing */

typedef Event* EventRef;

void EventQueue::addEvent(EventRef event) {
	event->setContext(this);
	events.push(event);
}

int EventQueue::getTimeOfNext() {
	return events.top()->time;
}

void EventQueue::processNext() {
	EventRef event = events.top();
	event->process();
	events.pop(); //this should delete the event
}

bool EventQueue::isEmpty() {
	return events.empty();
}

bool EventTimeComparator::operator() (EventRef first, EventRef second) const {
	return first->time > second->time;
}
