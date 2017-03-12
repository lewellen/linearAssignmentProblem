#include "GreedySolver.h"

GreedySolver::GreedySolver() {
	m_log = NULL;
}

GreedySolver::~GreedySolver() {
	if(m_log != NULL) {
		delete m_log;
		m_log = NULL;
	}
}

void GreedySolver::setLog(IGreedyLog* log) {
	if(log == m_log) {
		return;
	}

	if(m_log != NULL) {
		delete m_log;
		m_log = NULL;
	}

	m_log = log;
}
