#include <cstdlib>
#include <sys/time.h>

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

double Stopwatch::elapsedMs() const {
	return (m_stop.tv_sec - m_start.tv_sec) * 1e3 + (m_stop.tv_usec - m_start.tv_usec) * 1e-3;
}

