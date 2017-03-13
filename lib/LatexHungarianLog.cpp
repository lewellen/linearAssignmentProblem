#include <cstdlib>
#include <iostream>
#include <list>
#include <utility>

#include "Array2D.h"
#include "Assignment.h"
#include "LatexHungarianLog.h"

using std::endl;
using std::list;
using std::ostream;
using std::pair;

LatexHungarianLog::LatexHungarianLog(ostream& output) : m_output(output) {
	m_output << "\\documentclass{article}" << endl;
	m_output << "\\usepackage{amsmath}" << endl;
	m_output << "\\usepackage{xcolor}" << endl;
	m_output << "\\begin{document}" << endl;
}

LatexHungarianLog::~LatexHungarianLog() {
	m_output << "\\end{document}" << endl;
}

void LatexHungarianLog::input(
	const Array2D<double>& M
) {
	m_output << "\\section{}" << endl;

	m_output << "\\paragraph{Input:}" << endl;

	m_output << "\\begin{equation}" << endl;
	m_output << "\\begin{pmatrix}" << endl;

	for(size_t row = 0; row < M.getNumRows(); ++row) {
		for(size_t col = 0; col < M.getNumCols(); ++col) {
			const double& value = M.getEntry(row, col);
			if(value == 0) {
				m_output << "\\textbf{";
			}

			m_output << value;

			if(value == 0) {
				m_output << "}";
			}

			if(col + 1 != M.getNumCols()) {
				m_output << " & ";
			}
		}

		if(row + 1 != M.getNumRows()) {
			m_output << " \\\\";
		}
		m_output << endl;
	}

	m_output << "\\end{pmatrix}" << endl;
	m_output << "\\end{equation}" << endl;
} 

void LatexHungarianLog::afterDeductRowAndColMin(
	const Array2D<double>& M
) {
	m_output << "\\paragraph{After deducting row and col minimums:}" << endl;

	m_output << "\\begin{equation}" << endl;
	m_output << "\\begin{pmatrix}" << endl;

	for(size_t row = 0; row < M.getNumRows(); ++row) {
		for(size_t col = 0; col < M.getNumCols(); ++col) {
			const double& value = M.getEntry(row, col);
			if(value == 0) {
				m_output << "\\textbf{";
			}

			m_output << value;

			if(value == 0) {
				m_output << "}";
			}

			if(col + 1 != M.getNumCols()) {
				m_output << " & ";
			}
		}

		if(row + 1 != M.getNumRows()) {
			m_output << " \\\\";
		}
		m_output << endl;
	}

	m_output << "\\end{pmatrix}" << endl;
	m_output << "\\end{equation}" << endl;
} 

void LatexHungarianLog::afterInitAssignment(
	const Array2D<double>& M, 
	const size_t* rowsStarredCol, 
	const bool* colCovered
) {
	m_output << "\\paragraph{After init assignment:}" << endl;

	m_output << "\\begin{equation}" << endl;
	m_output << "\\begin{pmatrix}" << endl;

	for(size_t row = 0; row < M.getNumRows(); ++row) {
		size_t colStar = rowsStarredCol[row];

		for(size_t col = 0; col < M.getNumCols(); ++col) {
			if(colCovered[col]) {
				m_output << "\\colorbox{yellow}{";
			}

			if( colStar == col) {
				m_output << "\\textcolor{red}{";
			}

			const double& value = M.getEntry(row, col);
			if(value == 0) {
				m_output << "\\textbf{";
			}

			m_output << value;

			if(value == 0) {
				m_output << "}";
			}

			if( colStar == col) { 
				m_output << "}";
			}

			if(colCovered[col]) {
				m_output << "}";
			}

			if(col + 1 != M.getNumCols()) {
				m_output << " & ";
			}
		}

		if(row + 1 != M.getNumRows()) {
			m_output << " \\\\";
		}
		m_output << endl;
	}

	m_output << "\\end{pmatrix}" << endl;
	m_output << "\\end{equation}" << endl;
} 

void LatexHungarianLog::afterPrime(
	const Array2D<double>& M,
	const size_t* rowsStarredCol,
	const bool* colCovered,
	const bool* rowCovered,
	const size_t* rowsPrimedCol
) {
	m_output << "\\paragraph{After priming:}" << endl;

	m_output << "\\begin{equation}" << endl;
	m_output << "\\begin{pmatrix}" << endl;

	for(size_t row = 0; row < M.getNumRows(); ++row) {
		size_t colStar = rowsStarredCol[row];
		size_t colPrime = rowsPrimedCol[row];

		for(size_t col = 0; col < M.getNumCols(); ++col) {
			if(colCovered[col] || rowCovered[row]) {
				m_output << "\\colorbox{yellow}{";
			}

			if( colStar == col) {
				m_output << "\\textcolor{red}{";
			} else if( colPrime == col) {
				m_output << "\\textcolor{green}{";
			}

			const double& value = M.getEntry(row, col);
			if(value == 0) {
				m_output << "\\textbf{";
			}

			m_output << value;

			if(value == 0) {
				m_output << "}";
			}

			if( colStar == col ||  colPrime == col ) {
				m_output << "}";
			}

			if(colCovered[col] || rowCovered[row] ) {
				m_output << "}";
			}

			if(col + 1 != M.getNumCols()) {
				m_output << " & ";
			}
		}

		if(row + 1 != M.getNumRows()) {
			m_output << " \\\\";
		}
		m_output << endl;
	}

	m_output << "\\end{pmatrix}" << endl;
	m_output << "\\end{equation}" << endl;
} 

void LatexHungarianLog::afterStep2(
	const Array2D<double>& M,
	const size_t* rowsStarredCol,
	const bool* colCovered,
	const bool* rowCovered,
	const size_t* rowsPrimedCol
) {
	m_output << "\\paragraph{After step 2:}" << endl;

	m_output << "\\begin{equation}" << endl;
	m_output << "\\begin{pmatrix}" << endl;

	for(size_t row = 0; row < M.getNumRows(); ++row) {
		size_t colStar = rowsStarredCol[row];
		size_t colPrime = rowsPrimedCol[row];

		for(size_t col = 0; col < M.getNumCols(); ++col) {
			if(colCovered[col] || rowCovered[row]) {
				m_output << "\\colorbox{yellow}{";
			}

			if( colStar == col) {
				m_output << "\\textcolor{red}{";
			} else if( colPrime == col) {
				m_output << "\\textcolor{green}{";
			}

			const double& value = M.getEntry(row, col);
			if(value == 0) {
				m_output << "\\textbf{";
			}

			m_output << value;

			if(value == 0) {
				m_output << "}";
			}

			if( colStar == col ||  colPrime == col ) {
				m_output << "}";
			}

			if(colCovered[col] || rowCovered[row] ) {
				m_output << "}";
			}

			if(col + 1 != M.getNumCols()) {
				m_output << " & ";
			}
		}

		if(row + 1 != M.getNumRows()) {
			m_output << " \\\\";
		}
		m_output << endl;
	}

	m_output << "\\end{pmatrix}" << endl;
	m_output << "\\end{equation}" << endl;
} 
 
void LatexHungarianLog::beforeStep2(
	const Array2D<double>& M,
	const size_t* rowsStarredCol,
	const bool* colCovered,
	const bool* rowCovered,
	const size_t* rowsPrimedCol,
	const list< pair<size_t, size_t> >& starred,
	const list< pair<size_t, size_t> >& primed
) {
	m_output << "\\paragraph{Before step 2:}" << endl;

	list< pair<size_t, size_t> >::const_iterator s = starred.begin();
	list< pair<size_t, size_t> >::const_iterator p = primed.begin();

	bool isPrime = true;

	m_output << "\\begin{equation}" << endl;
	while(true) {
		if(isPrime) {
			m_output << "\\textcolor{green}{" <<  (*p).first << ", " << (*p).second << "}";
			++p;

			if(s != starred.end()) {
				m_output << " \\rightarrow ";
			} else {
				m_output << endl;
				break;
			}
		} else {
			m_output << "\\textcolor{red}{" << (*s).first << ", " << (*s).second << "}";
			++s;

			if(p != primed.end()) {
				m_output << " \\rightarrow ";
			} else {
				m_output << endl;
				break;
			}
		}
		isPrime = !isPrime;
	}
	m_output << "\\end{equation}" << endl;
} 

void LatexHungarianLog::afterDeductUncoveredMin(
	const Array2D<double>& M,
	const size_t* rowsStarredCol,
	const bool* colCovered,
	const bool* rowCovered,
	const size_t* rowsPrimedCol,
	const double& minValue
) {
	m_output << "\\paragraph{After deduct uncovered min:}" << endl;

	m_output << "\\begin{equation}" << endl;
	m_output << "\\begin{pmatrix}" << endl;

	for(size_t row = 0; row < M.getNumRows(); ++row) {
		size_t colStar = rowsStarredCol[row];
		size_t colPrime = rowsPrimedCol[row];

		for(size_t col = 0; col < M.getNumCols(); ++col) {
			if(colCovered[col] || rowCovered[row]) {
				m_output << "\\colorbox{yellow}{";
			}

			if( colStar == col) {
				m_output << "\\textcolor{red}{";
			} else if( colPrime == col) {
				m_output << "\\textcolor{green}{";
			}

			const double& value = M.getEntry(row, col);
			if(value == 0) {
				m_output << "\\textbf{";
			}

			m_output << value;

			if(value == 0) {
				m_output << "}";
			}

			if( colStar == col ||  colPrime == col ) {
				m_output << "}";
			}

			if(colCovered[col] || rowCovered[row] ) {
				m_output << "}";
			}

			if(col + 1 != M.getNumCols()) {
				m_output << " & ";
			}
		}

		if(row + 1 != M.getNumRows()) {
			m_output << " \\\\";
		}
		m_output << endl;
	}

	m_output << "\\end{pmatrix}" << endl;
	m_output << "\\end{equation}" << endl;

} 

void LatexHungarianLog::output(
	const Array2D<double>& M,
	const Assignment& A
) {
	m_output << "\\paragraph{Output:}" << endl;

	m_output << "\\begin{equation}" << endl;
	m_output << "\\begin{pmatrix}" << endl;

	for(size_t row = 0; row < M.getNumRows(); ++row) {
		for(size_t col = 0; col < M.getNumCols(); ++col) {
			const double& value = M.getEntry(row, col);
			if(A[row] == col) {
				m_output << "\\fbox{";
			}

			m_output << value;

			if(A[row] == col) {
				m_output << "}";
			}

			if(col + 1 != M.getNumCols()) {
				m_output << " & ";
			}
		}

		if(row + 1 != M.getNumRows()) {
			m_output << " \\\\";
		}
		m_output << endl;
	}

	m_output << "\\end{pmatrix}" << endl;
	m_output << "\\end{equation}" << endl;

	m_output << "Cost: " << A.cost(M) << endl;
}
