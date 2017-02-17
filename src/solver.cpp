#include <cstdlib>
#include <iostream>
#include <limits>

#include "Array2D.h"
#include "Assignment.h"
#include "ISolver.h"
#include "ISolverFactory.h"

using std::cout;
using std::endl;
using std::numeric_limits;

typedef Array2D<double> CostMatrix;

#define FLAGS \
	X(INPUT, "--input") \
	X(INPUT_FORMAT, "--input-format") \
	X(OBJECTIVE, "--objective") \
	X(SOLVER, "--solver") \
	X(OUTPUT, "--output") \
	X(OUTPUT_FORMAT, "--output-format")

/*
class CLArguments {
public:

#define X(a, b) E_#a,
	enum FlagEnum {	FLAGS, E_NONE };
#undef X

#define X(a, b) b,
	const char*[] FlagNames { FLAGS }
#undef X

#define X(a, b) + 1
	const size_t FlagCount = FLAGS ;
#undef X

	CLArguments(int argc, char** argv) {
		char* const[FlagCount] options;
		for(size_t i = 0; i < FlagCount; ++i) {
			options[i] = NULL;
		}

		Flags f = E_NONE;
		for(int i = 1; i < argc; ++i) {
			size_t len = strlen(argv[i]);
			if(len > 2 && argv[i][0] == '-' && argv[i][1] == '-') {

				f = E_NONE;
				for(size_t j = 0; j < FlagCount; ++j) {
					if(strmp( argv[i], FlagNames[j] ) == 0) {
						f = j;
						found = true;
						break;
					}
				}

			} else {
				if(f == E_NONE) {
					// a ; with out --x
					cout << "Unknown option: " << argv[i] << endl;
					return EXIT_FAILURE;
				} else if(options[f] == NULL) {
					options[f] = argv[i];
				} else {
					// --x a b
					cout << "Unknown option: " << argv[i] << endl;
					return EXIT_FAILURE;
				}
			}
		}
	}

	void printUsage() const {
		cout << "solver " << INPUT << " file " << OUTPUT << " file " << endl;
		cout << "\t" << INPUT << " file" << endl;
		cout << "\t" << INPUT_FORMAT << " [matrix] | array" << endl;
		cout << "\t" << OBJECTIVE << " [minimize] | maximize"; << endl;
		cout << "\t" << SOLVER << " [hungarian] | brute | alternative" << endl;
		cout << "\t" << OUTPUT << " file" << endl;
		cout << "\t" << OUTPUT_FORMAT << " [matrix] | array" << endl;
	}

private:

};
*/

void convertToMaximizationProblem(CostMatrix& M) {
	double maxValue = -numeric_limits<double>::infinity();
	for(size_t row = 0; row < M.getNumRows(); ++row) {
		for(size_t col = 0; col < M.getNumCols(); ++col) {
			const double& value = M.getEntry(row, col);
			if(maxValue < value) {
				maxValue = value;
			}
		}
	}

	for(size_t row = 0; row < M.getNumRows(); ++row) {
		for(size_t col = 0; col < M.getNumCols(); ++col) {
			double& value = M.getEntry(row, col);
			value = maxValue - value;
		}
	}
}

int main(int argc, char** argv) {

	return EXIT_SUCCESS;
}
