#ifndef STOPWATCH_H
#define STOPWATCH_H

#include <sys/time.h>

class Stopwatch {
public:
	Stopwatch(); 
	~Stopwatch(); 

	void start(); 
	void stop(); 
	double elapsedSec() const; 

private:
	timeval m_start;
	timeval m_stop;
};

#endif
