#include <cstdlib>
#include <fstream>
#include <iostream>
#include <limits>

#include "Array2D.h"
#include "Assignment.h"

#include "IInputFormat.h"
#include "IInputFormatFactory.h"

#include "IOutputFormat.h"
#include "IOutputFormatFactory.h"

#include "IObjective.h"
#include "IObjectiveFactory.h"

#include "ISolver.h"
#include "ISolverFactory.h"

using std::cout;
using std::endl;
using std::ifstream;
using std::numeric_limits;
using std::ofstream;

typedef Array2D<double> CostMatrix;

#define FLAGS \
	X(E_INPUT, "--input") \
	X(E_INPUT_FORMAT, "--input-format") \
	X(E_OBJECTIVE, "--objective") \
	X(E_SOLVER, "--solver") \
	X(E_OUTPUT, "--output") \
	X(E_OUTPUT_FORMAT, "--output-format")

class CLI {
public:

#define X(a, b) , a
	enum FlagEnum { 
		E_NONE FLAGS
	};
#undef X

	static const size_t FlagCount;
	static const string FlagNames[];

	CLI() {
		m_flags = new string[FlagCount];
		for(size_t i = 0; i < FlagCount; ++i) {
			m_flags[i].clear();
			assert(m_flags[i].empty());
		}
	}

	~CLI() {
		delete[] m_flags;
		m_flags = NULL;
	}

	bool load(int argc, char** argv) {
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
					cout << "Unexpected second value for " << FlagNames[f] << endl;
					return false;
				} else {
					m_flags[f] = s;
				}
			}
		}

		if( m_flags[E_INPUT].empty() || m_flags[E_OUTPUT].empty() ) {
			cout << FlagNames[E_INPUT] << " and " << FlagNames[E_OUTPUT] << " are required." << endl;
			return false;
		}

		if(m_flags[E_INPUT_FORMAT].empty()) {
			m_flags[E_INPUT_FORMAT] = IInputFormatFactory::I_FORMAT_MATRIX;
		} else if (!IInputFormatFactory::isValidName(m_flags[E_INPUT_FORMAT]) ) {
			cout << FlagNames[E_INPUT_FORMAT] << m_flags[E_INPUT_FORMAT] << " is not a valid option." << endl;
			return false;
		}

		if(m_flags[E_OUTPUT_FORMAT].empty()) {
			m_flags[E_OUTPUT_FORMAT] = IOutputFormatFactory::O_FORMAT_MATRIX;
		} else if (!IOutputFormatFactory::isValidName(m_flags[E_OUTPUT_FORMAT]) ) {
			cout << FlagNames[E_OUTPUT_FORMAT] << m_flags[E_OUTPUT_FORMAT] << " is not a valid option." << endl;
			return false;
		}

		if(m_flags[E_SOLVER].empty()) {
			m_flags[E_SOLVER] = ISolverFactory::SOLVER_BRUTE;
		} else if (!ISolverFactory::isValidName(m_flags[E_SOLVER]) ) {
			cout << FlagNames[E_SOLVER] << m_flags[E_SOLVER] << " is not a valid option." << endl;
			return false;
		}

		if(m_flags[E_OBJECTIVE].empty()) {
			m_flags[E_OBJECTIVE] = IObjectiveFactory::OBJECTIVE_MINIMIZE;
		} else if (!IObjectiveFactory::isValidName(m_flags[E_OBJECTIVE]) ) {
			cout << FlagNames[E_OBJECTIVE] << m_flags[E_OBJECTIVE] << " is not a valid option." << endl;
			return false;
		}

		return true;
	}

	const string& getInput() const {
		return m_flags[E_INPUT];
	}

	const string& getInputFormat() const {
		return m_flags[E_INPUT_FORMAT];
	}

	const string& getOutput() const {
		return m_flags[E_OUTPUT];
	}

	const string& getOutputFormat() const {
		return m_flags[E_OUTPUT_FORMAT];
	}

	const string& getSolver() const {
		return m_flags[E_SOLVER];
	}

	const string& getObjective() const {
		return m_flags[E_OBJECTIVE];
	}

	void printConfiguration() const {
		for(size_t i = 1; i < FlagCount; ++i) {
			cout << FlagNames[i] << " = \"" << ( m_flags[i].empty() ? "NULL" : m_flags[i] ) << "\"" << endl;
		}
	}

	void printUsage() const {
		cout << "solver " << FlagNames[E_INPUT] << " file " << FlagNames[E_OUTPUT] << " file " << endl;


		cout << "\t" << FlagNames[E_INPUT] << " file" << endl;


		size_t inputFormatCount;
		const string* inputFormatNames = IInputFormatFactory::getValidNames(inputFormatCount);
		cout << "\t" << FlagNames[E_INPUT_FORMAT] << " ";
		for(size_t i = 0; i < inputFormatCount; ++i) {
			cout << inputFormatNames[i];
			if(i + 1 != inputFormatCount) {
				cout << " | ";
			}
		}
		cout << endl;


		cout << "\t" << FlagNames[E_OUTPUT] << " file" << endl;


		size_t outputFormatCount;
		const string* outputFormatNames = IOutputFormatFactory::getValidNames(outputFormatCount);
		cout << "\t" << FlagNames[E_OUTPUT_FORMAT] << " ";
		for(size_t i = 0; i < outputFormatCount; ++i) {
			cout << outputFormatNames[i];
			if(i + 1 != outputFormatCount) {
				cout << " | ";
			}
		}
		cout << endl;

		
		size_t objectiveCount;
		const string* objectiveNames = IObjectiveFactory::getValidNames(objectiveCount);
		cout << "\t" << FlagNames[E_OBJECTIVE] << " ";
		for(size_t i = 0; i < objectiveCount; ++i) {
			cout << objectiveNames[i];
			if(i + 1 != objectiveCount) {
				cout << " | ";
			}
		}
		cout << endl;


		size_t solverCount;
		const string* solverNames = ISolverFactory::getValidNames(solverCount);
		cout << "\t" << FlagNames[E_SOLVER] << " ";
		for(size_t i = 0; i < solverCount; ++i) {
			cout << solverNames[i];
			if(i + 1 != solverCount) {
				cout << " | ";
			}
		}
		cout << endl;
	}

private:
	string* m_flags;
};

#define X(a, b) + 1
const size_t CLI::FlagCount = 1 FLAGS ;
#undef X

#define X(a, b) , b
const string CLI::FlagNames[] = { "" FLAGS };
#undef X

int main(int argc, char** argv) {
	CLI c;
	bool loaded = c.load(argc, argv);
	if(!loaded) {
		c.printUsage();
		return EXIT_FAILURE;
	}

	IInputFormat* inputFormat = IInputFormatFactory::make(c.getInputFormat());
	assert(inputFormat != NULL);

	ifstream inputFile(c.getInput().c_str(), ifstream::in);
	assert(inputFile.is_open());

	Array2D<double> M;
	bool read = inputFormat->read(inputFile, M);

	inputFile.close();

	delete inputFormat;
	inputFormat = NULL;

	if(!read) {
		return EXIT_FAILURE;
	}

	IObjective* objective = IObjectiveFactory::make(c.getObjective());
	assert(objective != NULL);

	(*objective)(M);

	delete objective;
	objective = NULL;


	ISolver* solver = ISolverFactory::make(c.getSolver());
	assert(solver != NULL);

	Assignment A = (*solver)(M);

	delete solver;
	solver = NULL;
	
	IOutputFormat* outputFormat = IOutputFormatFactory::make(c.getOutputFormat());
	assert(outputFormat != NULL);

	ofstream outputFile(c.getOutput().c_str(), ofstream::out | ofstream::trunc);
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
