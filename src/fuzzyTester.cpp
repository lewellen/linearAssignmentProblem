#include <cassert>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>

#include "GreedySolver.h"
#include "HungarianMethodSolver.h"
#include "IGreedyLog.h"
#include "ISolver.h"
#include "ISolverFactory.h"
#include "IInputFormat.h"
#include "IInputFormatFactory.h"
#include "IOutputFormat.h"
#include "IOutputFormatFactory.h"
#include "LatexGreedyLog.h"
#include "LatexHungarianLog.h"
#include "RandomMatrix.h"

using std::cout;
using std::endl;
using std::istringstream;
using std::ofstream;
using std::string;

class Settings {
public:
	Settings() { 
		setDefaults();
	}

	void setDefaults() {
		m_size = 6;
		m_maxItr = 100;
		m_underTestSolver = ISolverFactory::SOLVER_HUNGARIAN;
		m_baselineSolver = ISolverFactory::SOLVER_BRUTE;
		m_logPath = "output.tex";
	}

	size_t getSize() const {
		return m_size;
	}

	void setSize(const size_t& value) {
		m_size = value;
	}

	size_t getMaxIterations() const {
		return m_maxItr;
	}

	void setMaxIterations(const size_t& value) {
		m_maxItr = value;
	}

	const string& getBaselineSolver() const {
		return m_baselineSolver;
	}

	void setBaselineSolver(const string& value) {
		m_baselineSolver = value;
	}

	const string& getUnderTestSolver() const {
		return m_underTestSolver;
	}

	void setUnderTestSolver(const string& value) {
		m_underTestSolver = value;
	}

	const string& getLogPath() const {
		return m_logPath;
	}

	void setLogPath(const string& value) {
		m_logPath = value;
	}

private:
	size_t m_size;
	size_t m_maxItr;
	string m_underTestSolver;
	string m_baselineSolver;
	string m_logPath;
};

#define FLAGS \
	X(E_SIZE, "--size") \
	X(E_MAX_ITERATIONS, "--max-itr") \
	X(E_SOLVER_BASE, "--solver-base") \
	X(E_SOLVER_TEST, "--solver-test") \
	X(E_LOG_PATH, "--log-path")

class CLI {
public:
#define X(a, b) , a
	enum FlagEnum { 
		E_NONE FLAGS
	};
#undef X

	static const size_t FlagCount;
	static const string FlagNames[];

	bool parseCLA(int argc, char** argv, Settings& s) {
		string m_flags[FlagCount];
		for(size_t i = 0; i < FlagCount; ++i) {
			m_flags[i].clear();
			assert(m_flags[i].empty());
		}

		FlagEnum f = E_NONE;
		for(int i = 1; i < argc; ++i) {
			string s = string(argv[i]);
			if(s.length() > 2 && s[0] == '-' && s[1] == '-') {
				f = E_NONE;
				for(int j = 1; j < FlagCount; ++j) {
					if( FlagNames[j] == s ) {
						f = (FlagEnum) j;
						break;
					}
				}
			} else {
				if( (f == E_NONE) || !m_flags[f].empty() ) {
					cout << "Unexpected second value for '" << FlagNames[f] << "'." << endl;
					return false;
				} else {
					m_flags[f] = s;
				}
			}
		}

		if(!m_flags[E_SIZE].empty()) {
			size_t size = 0;
			if(!stringToSizeT(m_flags[E_SIZE], size) || size == 0) {
				cout << FlagNames[E_SIZE] << " must be a positive integer value." << endl;
				return false;
			}
			s.setSize(size);
		}

		if(!m_flags[E_MAX_ITERATIONS].empty()) {
			size_t maxIterations = 0;
			if(!stringToSizeT(m_flags[E_MAX_ITERATIONS], maxIterations) || maxIterations == 0) {
				cout << FlagNames[E_MAX_ITERATIONS] << " must be a positive integer value." << endl;
				return false;
			}
			s.setMaxIterations(maxIterations);
		}

		if(!m_flags[E_SOLVER_BASE].empty()) {
			if (!ISolverFactory::isValidName(m_flags[E_SOLVER_BASE]) ) {
				cout << FlagNames[E_SOLVER_BASE] << " " << m_flags[E_SOLVER_BASE] << " is not a valid option." << endl;
				return false;
			}
			s.setBaselineSolver(m_flags[E_SOLVER_BASE]);
		}

		if(!m_flags[E_SOLVER_TEST].empty()) {
			if (!ISolverFactory::isValidName(m_flags[E_SOLVER_TEST]) ) {
				cout << FlagNames[E_SOLVER_TEST] << " " << m_flags[E_SOLVER_TEST] << " is not a valid option." << endl;
				return false;
			}
			s.setUnderTestSolver(m_flags[E_SOLVER_TEST]);
		}

		if(!m_flags[E_LOG_PATH].empty()) {
			s.setLogPath(m_flags[E_LOG_PATH]);
		}

		printUsage(s);

		return true;
	}

	void printUsage(const Settings& s) {
		cout << FlagNames[E_SIZE] << " " << s.getSize() << endl;
		cout << FlagNames[E_MAX_ITERATIONS] << " " << s.getMaxIterations() << endl;
		cout << FlagNames[E_SOLVER_BASE] << " " << s.getBaselineSolver() << endl;
		cout << FlagNames[E_SOLVER_TEST] << " " << s.getUnderTestSolver() << endl;
		cout << FlagNames[E_LOG_PATH] << " " << s.getLogPath() << endl;
	}

private:
	bool stringToSizeT(const string& in, size_t& out) {
		istringstream s(in);
		s >> out;
		return !s.fail();
	}
};

#define X(a, b) + 1
const size_t CLI::FlagCount = 1 FLAGS ;
#undef X

#define X(a, b) , b
const string CLI::FlagNames[] = { "" FLAGS };
#undef X

int main(int argc, char** argv) {
	CLI c;
	Settings s;
	if(!c.parseCLA(argc, argv, s)) {
		s.setDefaults();
		c.printUsage(s);
		return EXIT_FAILURE;
	}

	if(s.getBaselineSolver() == s.getUnderTestSolver()) {
		cout << "Comparing " << s.getUnderTestSolver() << " against itself is meaningless." << endl;
		return EXIT_FAILURE;
	}

	ISolver* baseline = ISolverFactory::make(s.getBaselineSolver());
	assert(baseline != NULL);

	ISolver* underTest = ISolverFactory::make(s.getUnderTestSolver());
	assert(underTest != NULL);

	bool foundCounterExample = false;
	bool logWritten = false;
	size_t i = 0;
	for(; i < s.getMaxIterations(); ++i) {
		RandomMatrix M = RandomMatrix(s.getSize(), s.getSize());

		Assignment baselineA = (*baseline)(M);
		double baselineCost = baselineA.cost(M);

		Assignment underTestA = (*underTest)(M);
		double underTestCost = underTestA.cost(M);

		if( baselineCost != underTestCost) {
			if(s.getUnderTestSolver() == ISolverFactory::SOLVER_HUNGARIAN) {
				HungarianMethodSolver* h = dynamic_cast<HungarianMethodSolver*>(underTest);
				assert(h != NULL);

				ofstream log(s.getLogPath(), ofstream::trunc | ofstream::out);
				assert(log.is_open());

				h->setLog(new LatexHungarianLog(log));
				underTestA = (*underTest)(M);
				underTestCost = underTestA.cost(M);
				h->setLog(NULL);

				log.flush();
				log.close();

				logWritten = true;
			} else if(s.getUnderTestSolver() == ISolverFactory::SOLVER_GREEDY_NAIVE || s.getUnderTestSolver() == ISolverFactory::SOLVER_GREEDY_EFFICIENT) {
				GreedySolver* g = dynamic_cast<GreedySolver*>(underTest);
				assert(g != NULL);

				ofstream log(s.getLogPath(), ofstream::trunc | ofstream::out);
				assert(log.is_open());

				g->setLog(new LatexGreedyLog(log));
				underTestA = (*underTest)(M);
				underTestCost = underTestA.cost(M);
				g->setLog(NULL);

				log.flush();
				log.close();

				logWritten = true;
			}
	
			foundCounterExample = true;
			break;
		}
	}

	if(foundCounterExample) {
		cout << "Found counterexample after " << i << " attempts." << endl;
		if(logWritten) {
			cout << "Wrote log to '" << s.getLogPath() << "'." << endl;
		} else {
			cout << s.getUnderTestSolver() << " does not have logging capabilities." << endl;
		}
	} else {
		cout << "Did not find any counterexamples after " << s.getMaxIterations() << " attempts." << endl;
	}

	delete baseline;
	delete underTest;

	return EXIT_SUCCESS;
}
