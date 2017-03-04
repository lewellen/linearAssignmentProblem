#include <cmath>
#include <cstdlib>
#include <iostream>
#include <list>
#include <map>
#include <utility>

#include "Array2D.h"
#include "Assignment.h"
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
	Stopwatch S;

	map<size_t, map<string, SampledValue > > profile;

	size_t numSolvers;
	const string* solverNames = ISolverFactory::getValidNames(numSolvers);
	for(size_t solverIndex = 0; solverIndex < numSolvers; ++solverIndex) {
		const string& solverName = solverNames[solverIndex];
		if(solverName == ISolverFactory::SOLVER_ATRANDOM) {
			continue;
		}

		ISolver* solver = ISolverFactory::make(solverName);
		assert(solver != NULL);

		for(size_t size = 2; size <= 12; ++size) {
			SampledValue& samples = profile[size][solverName];

			Stopwatch R;
			R.start();
			do {
				CostMatrix M = randomMatrix(size);
				S.start();
				Assignment jobsByWorker = (*solver)(M);
				S.stop();
			
				samples.add( S.elapsedMs() );

				R.stop();
			} while(R.elapsedMs() < 1 * 60 * 1000 && samples.numSamples() < 30 ); 
		}

		delete solver;	
	}

	cout << "N\t";
	for(size_t solverIndex = 0; solverIndex < numSolvers; ++solverIndex) {
		const string& solverName = solverNames[solverIndex];
		if(solverName == ISolverFactory::SOLVER_ATRANDOM) {
			continue;
		}

		cout << solverName << "\tstdDev";
		if(solverIndex + 1 != numSolvers) {
			cout << "\t";
		}
	}
	cout << endl;

	for(size_t size = 2; size <= 12; ++size) {
		cout << size << "\t";
		for(size_t solverIndex = 0; solverIndex < numSolvers; ++solverIndex) {
			const string& solverName = solverNames[solverIndex];
			if(solverName == ISolverFactory::SOLVER_ATRANDOM) {
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
