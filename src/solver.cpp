#include <cstdlib>
#include <fstream>
#include <iostream>
#include <limits>

#include "Array2D.h"
#include "Assignment.h"

#include "ISolver.h"
#include "ISolverFactory.h"

#include "IInputFormat.h"
#include "IInputFormatFactory.h"

#include "IOutputFormat.h"
#include "IOutputFormatFactory.h"

using std::cout;
using std::endl;
using std::ifstream;
using std::numeric_limits;
using std::ofstream;

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
	}

private:

};
*/

class CLI {
public:
	CLI(int argc, char** argv) {
		m_input = NULL;
		m_inputFormat = NULL;
		m_output = NULL;
		m_outputFormat = NULL;
		m_solver = NULL;
		m_isMaxProblem = false;
		m_isValid = false;
	}

	const char* getInput() const {
		return m_input;
	}

	const char* getInputFormat() const {
		return m_inputFormat;
	}

	const char* getOutput() const {
		return m_output;
	}

	const char* getOutputFormat() const {
		return m_outputFormat;
	}

	const char* getSolver() const {
		return m_solver;
	}

	bool isMaxProblem() const {
		return m_isMaxProblem;
	}

	bool isValid() const {
		return m_isValid;
	}

	void printUsage() const {
		/*
		cout << "solver " << INPUT << " file " << OUTPUT << " file " << endl;
		cout << "\t" << INPUT << " file" << endl;
		cout << "\t" << INPUT_FORMAT << " [matrix] | array" << endl;
		cout << "\t" << OBJECTIVE << " [minimize] | maximize"; << endl;
		cout << "\t" << SOLVER << " [hungarian] | brute | alternative" << endl;
		cout << "\t" << OUTPUT << " file" << endl;
		cout << "\t" << OUTPUT_FORMAT << " [matrix] | array" << endl;
		*/
	}

private:
	const char* m_input;
	const char* m_inputFormat;
	const char* m_output;
	const char* m_outputFormat;
	const char* m_solver;
	bool m_isMaxProblem;
	bool m_isValid;
};

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
	CLI c(argc, argv);
	if(!c.isValid()) {
		c.printUsage();
		return EXIT_FAILURE;
	}

	IInputFormat* inputFormat = IInputFormatFactory::make(c.getInputFormat());
	assert(inputFormat != NULL);

	ifstream inputFile(c.getInput(), ifstream::in);
	assert(inputFile.is_open());

	Array2D<double> M;
	bool read = inputFormat->read(inputFile, M);

	inputFile.close();

	delete inputFormat;
	inputFormat = NULL;

	if(!read) {
		return EXIT_FAILURE;
	}

	if(c.isMaxProblem()) {
		convertToMaximizationProblem(M);
	}

	ISolver* solver = ISolverFactory::make(c.getSolver());
	assert(solver != NULL);

	Assignment A = (*solver)(M);

	delete solver;
	solver = NULL;
	
	IOutputFormat* outputFormat = IOutputFormatFactory::make(c.getOutputFormat());
	assert(outputFormat != NULL);

	ofstream outputFile(c.getOutput(), ofstream::out | ofstream::trunc);
	assert(outputFile.is_open());

	bool write = outputFormat->write(outputFile, M, A);

	outputFile.close();

	delete outputFormat;
	outputFormat = NULL;

	if(!write) {
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}
