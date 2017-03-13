#include <cstdlib>
#include <sys/time.h>

#include <cstdlib>
#include <iostream>
using std::cout;
using std::endl;

#include "Stopwatch.h"

Stopwatch::Stopwatch() {

}

Stopwatch::~Stopwatch() {

}

void Stopwatch::start() {
	gettimeofday(&m_start, NULL);
}

void Stopwatch::stop() {
	gettimeofday(&m_stop, NULL);
}

double Stopwatch::elapsedSec() const {
	double sec = m_stop.tv_sec - m_start.tv_sec;
	double usec = m_stop.tv_usec - m_start.tv_usec;
	if(m_stop.tv_sec > m_start.tv_sec) {
		if(m_start.tv_usec > m_stop.tv_usec) {
			sec = sec - 1;
			usec = 1e6 - m_start.tv_usec;
			usec += m_stop.tv_usec;
		}
	}

	return sec + (usec * 1e-6);
}

