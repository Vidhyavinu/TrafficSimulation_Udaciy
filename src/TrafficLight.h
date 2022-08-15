#ifndef TRAFFICLIGHT_H
#define TRAFFICLIGHT_H

#include <mutex>
#include <deque>
#include <condition_variable>
#include "TrafficObject.h"

// forward declarations to avoid include cycle
class Vehicle;


template <class T>
class MessageQueue
{
public:
	 void send(T &&v);
      T receive();
      
private:
    std::mutex _mutex;
    std::condition_variable _cond;
    std::deque<T> _messages; // list of all vehicles waiting to enter this intersection
};


class TrafficLight: public TrafficObject
{
public:
    // constructor / desctructor
	TrafficLight();
    
    // getters / setters

    // typical behaviour methods
	void waitForGreen();
    void simulate();
    TrafficLightPhase getCurrentPhase();
    
private:
    // typical behaviour methods
	void cycleThroughPhases();
    
    std::condition_variable _condition;
    std::mutex _mutex;
    TrafficLightPhase _currentPhase;
    // Message queu used to send and receive TrafficLightPhase
    std::shared_ptr<MessageQueue<TrafficLightPhase>> _queue;
};

#endif