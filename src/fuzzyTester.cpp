#include <cstdlib>
#include <iostream>

#include "ISolver.h"
#include "ISolverFactory.h"

#include "IInputFormat.h"
#include "IInputFormatFactory.h"

#include "IOutputFormat.h"
#include "IOutputFormatFactory.h"

using std::cout;
using std::endl;

class CLI {
public:
	CLI(int argc, char** argv) {

	}

	size_t getSize() const {
		return 6;
	}

	size_t getMaxIterations() const {
		return 3;
	}

	const char* getSolver() const {
		return "HUNGARIAN";
	}

	bool isValid() const {
		return true;
	}

	void printUsage() const {
		
	}
};

int main(int argc, char** argv) {
	CLI c(argc, argv);
	if(!c.isValid()) {
		c.printUsage();
		return EXIT_FAILURE;
	}

	ISolver* brute = ISolverFactory::make(ISolverFactory::SOLVER_BRUTE);
	ISolver* other = ISolverFactory::make(c.getSolver());

	IInputFormat* inputFormat = IInputFormatFactory::make(IInputFormatFactory::I_FORMAT_MATRIX);
	IOutputFormat* outputFormat = IOutputFormatFactory::make(IOutputFormatFactory::O_FORMAT_MATRIX);

	bool foundCounterExample = false;
	for(size_t i = 0; i < c.getMaxIterations(); ++i) {
		Array2D<double> M( c.getSize() );
		for(size_t row = 0; row < M.getNumRows(); ++row) {
			for(size_t col = 0; col < M.getNumCols(); ++col) {
				M.getEntry(row, col) = (rand() % 100) + 10;
			}
		}

		Assignment bruteA = (*brute)(M);
		Assignment otherA = (*other)(M);

		double bruteCost = bruteA.cost(M);
		double otherCost = otherA.cost(M);

		if( bruteCost != otherCost ) {
			cout << "Found counter example after " << i << " attempts." << endl;
			cout << "Cost matrix: " << endl;
			inputFormat->write(cout, M);
			cout << endl;

			cout << "Brute force: " << bruteCost << endl;
			outputFormat->write(cout, M, bruteA);
			cout << endl;

			cout << c.getSolver() << ": " << otherCost << endl;
			outputFormat->write(cout, M, otherA);
			cout << endl;
	
			foundCounterExample = true;
			break;
		}
	}

	if(!foundCounterExample) {
		cout << "Did not find any counter examples after " << c.getMaxIterations() << " attempts." << endl;
	}

	delete brute;
	delete other;
	delete inputFormat;
	delete outputFormat;

	return EXIT_SUCCESS;
}
