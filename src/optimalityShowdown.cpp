#include <cmath>
#include <cstdlib>
#include <iostream>
#include <list>
#include <map>
#include <utility>

#include "Array2D.h"
#include "Assignment.h"
#include "IObjective.h"
#include "IObjectiveFactory.h"
#include "ISolver.h"
#include "ISolverFactory.h"
#include "Stopwatch.h"

using std::cout;
using std::endl;
using std::list;
using std::map;
using std::pair;

/*
class Interval {
public:
	Interval() {
		initialize(0, 0);
	}

	Interval(const double& lb, const double& ub) {
		initialize(lb, ub);
	}

	Interval(const Interval& other) {
		initialize(other.m_lb, other.m_ub);
	}

	~Interval() {

	}

	const double& getLowerBound() const {
		return m_lb;
	}

	const double& getUpperBound() const {
		return m_ub;
	}

	friend ostream& operator<< (ostream& s, const Interval& I) {
		return s << "[" << I.m_lb << ", " << I.m_ub << "]";
	}

private:
	double m_lb, m_ub;

	void initialize(const double& lb, const double& ub) {
		assert(lb <= ub);
		m_lb = lb;
		m_ub = ub;
	}
};*/

class SampledValue {
public:
	SampledValue() {
		m_numSamples = 0;
		m_sampleMean = 0;
		m_sampleVariance = 0;
	}

	void add(const double& value) {
		// Welford method for variance (Knuth)
		++m_numSamples;

		double oldSampleMean = m_sampleMean;
		m_sampleMean += ( value - m_sampleMean ) / m_numSamples;
		m_sampleVariance += (value - oldSampleMean) * (value - m_sampleMean);
	}

	bool empty() const {
		return m_numSamples == 0;
	}

	double numSamples() const {
		return m_numSamples;
	}

	double sampleMean() const {
		assert(m_numSamples > 0);
		return m_sampleMean;
	}

	double sampleStandardDev() const {
		assert(m_numSamples > 0);
		return sqrt( m_sampleVariance / m_numSamples );
	}

	/*Interval confidenceInterval(const double& confidenceLevel) const {
		assert( (0 < confidenceLevel) && (confidenceLevel <= 1) );
		assert( m_numSamples > 0 );

		double alpha = 0.5 * (1 - confidenceLevel);
		double degreeOfFreedom = m_numSamples - 1;

		TODO: Read up on efficient way to find critical values from t-dist		
	}*/

private:
	double m_numSamples;
	double m_sampleMean;
	double m_sampleVariance;
};

typedef Array2D<double> CostMatrix;

CostMatrix randomMatrix(size_t size) {
	CostMatrix M(size);

	// Initialize random cost matrix
	for(size_t row = 0; row < M.getNumRows(); ++row) {
		for(size_t col = 0; col < M.getNumCols(); ++col) {
			M.getEntry(row, col) = (rand() % 100) + 5;
		}
	}

	return M;
}

int main(int argc, char** argv) {
	map<size_t, map<string, SampledValue> > profile;
	map<size_t, map<string, Stopwatch> > timers;

	size_t numSolvers;
	const string* solverNames = ISolverFactory::getValidNames(numSolvers);

	ISolver* brute = ISolverFactory::make(ISolverFactory::SOLVER_BRUTE);

	size_t sizeMin = 2;
	size_t sizeMax = 10;

	for(size_t size = sizeMin; size <= sizeMax; ++size) {
		bool repeat = true;
		do {
			CostMatrix M = randomMatrix(size);
			Assignment bruteMinA = (*brute)(M);
			double bruteMinACost = bruteMinA.cost(M);

			IObjective* maxObj = IObjectiveFactory::make(IObjectiveFactory::OBJECTIVE_MAXIMIZE);
			CostMatrix N = M;
			(*maxObj)(N);
			delete maxObj;

			Assignment bruteMaxA = (*brute)(N);
			double bruteMaxACost = bruteMaxA.cost(M);

			if(bruteMinACost == bruteMaxACost) {
				continue;
			}

			assert(bruteMaxACost > bruteMinACost);

			repeat = false;
			for(size_t solverIndex = 0; solverIndex < numSolvers; ++solverIndex) {
				const string& solverName = solverNames[solverIndex];
				if(solverName == ISolverFactory::SOLVER_BRUTE) {
					continue;
				}

				SampledValue& samples = profile[size][solverName];
				if(samples.numSamples() >= 60) {
					continue;
				}

				Stopwatch& R = timers[size][solverName];
				if(samples.numSamples() == 0) {
					R.start();
				} else {
					R.stop();
				}

				if(R.elapsedMs() >= 0.5 * 60 * 1000) {
					continue;
				}
		
				ISolver* solver = ISolverFactory::make(solverName);
				assert(solver != NULL);

				Assignment solverA = (*solver)(M);
				double solverACost = solverA.cost(M);

				samples.add( (solverACost - bruteMinACost) / (bruteMaxACost - bruteMinACost) );	
				delete solver;
				repeat = true;
			}
		} while(repeat); 
	}

	delete brute;

	cout << "N\t";
	for(size_t solverIndex = 0; solverIndex < numSolvers; ++solverIndex) {
		const string& solverName = solverNames[solverIndex];
		if(solverName == ISolverFactory::SOLVER_BRUTE) {
			continue;
		}

		cout << solverName << "\tstdDev";
		if(solverIndex + 1 != numSolvers) {
			cout << "\t";
		}
	}
	cout << endl;

	for(size_t size = sizeMin; size <= sizeMax; ++size) {
		cout << size << "\t";
		for(size_t solverIndex = 0; solverIndex < numSolvers; ++solverIndex) {
			const string& solverName = solverNames[solverIndex];
			if(solverName == ISolverFactory::SOLVER_BRUTE) {
				continue;
			}

			double average = 0;
			double stdev = 0;

			const SampledValue& samples = profile[size][solverName];
			if(!samples.empty()) {
				average = samples.sampleMean();
				stdev = samples.sampleStandardDev();
			}

			cout << average << "\t" << stdev;
			if(solverIndex + 1 != numSolvers) {
				cout << "\t";
			}
		}
		cout << endl;
	}

	return EXIT_SUCCESS;
}
