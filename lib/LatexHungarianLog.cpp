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
	m_output << "\\usepackage{tikz}" << endl;
	m_output << "\\usetikzlibrary{matrix}" << endl;
	m_output << "\\usepackage{geometry}" << endl;
	m_output << "\\newgeometry{margin=1.25in}" << endl;
	m_output << "\\begin{document}" << endl;
}

LatexHungarianLog::~LatexHungarianLog() {
	m_output << "\\end{document}" << endl;
}

void LatexHungarianLog::input(
	const Array2D<double>& M
) {
	m_output << "\\section{}" << endl;

	//m_output << "\\paragraph{Input:}" << endl;

	bool colCovered[M.getNumCols()] { false };
	bool rowCovered[M.getNumRows()] { false };

	size_t rowsStarredCol[M.getNumRows()];
	for(size_t row = 0; row < M.getNumRows(); ++row) {
		rowsStarredCol[row] = M.getNumCols();
	}

	size_t rowsPrimedCol[M.getNumRows()];
	for(size_t row = 0; row < M.getNumRows(); ++row) {
		rowsPrimedCol[row] = M.getNumCols();
	}

	list< pair<size_t, size_t> > starred, primed;

	renderTikzMatrix(
		M, 
		colCovered, rowCovered, 
		rowsStarredCol, rowsPrimedCol, 
		starred, primed
	);
} 

void LatexHungarianLog::afterDeductRowAndColMin(
	const Array2D<double>& M
) {
	//m_output << "\\paragraph{After deducting row and col minimums:}" << endl;

	bool colCovered[M.getNumCols()] { false };
	bool rowCovered[M.getNumRows()] { false };

	size_t rowsStarredCol[M.getNumRows()];
	for(size_t row = 0; row < M.getNumRows(); ++row) {
		rowsStarredCol[row] = M.getNumCols();
	}

	size_t rowsPrimedCol[M.getNumRows()];
	for(size_t row = 0; row < M.getNumRows(); ++row) {
		rowsPrimedCol[row] = M.getNumCols();
	}

	list< pair<size_t, size_t> > starred, primed;

	renderTikzMatrix(
		M, 
		colCovered, rowCovered, 
		rowsStarredCol, rowsPrimedCol, 
		starred, primed
	);
} 

void LatexHungarianLog::afterInitAssignment(
	const Array2D<double>& M, 
	const size_t* rowsStarredCol, 
	const bool* colCovered
) {
	//m_output << "\\paragraph{After init assignment:}" << endl;

	bool rowCovered[M.getNumRows()] { false };

	size_t rowsPrimedCol[M.getNumRows()];
	for(size_t row = 0; row < M.getNumRows(); ++row) {
		rowsPrimedCol[row] = M.getNumCols();
	}

	list< pair<size_t, size_t> > starred, primed;

	renderTikzMatrix(
		M, 
		colCovered, rowCovered, 
		rowsStarredCol, rowsPrimedCol, 
		starred, primed
	);
} 

void LatexHungarianLog::afterPrime(
	const Array2D<double>& M,
	const size_t* rowsStarredCol,
	const bool* colCovered,
	const bool* rowCovered,
	const size_t* rowsPrimedCol
) {
	//m_output << "\\paragraph{After priming:}" << endl;

	list< pair<size_t, size_t> > starred, primed;

	renderTikzMatrix(
		M, 
		colCovered, rowCovered, 
		rowsStarredCol, rowsPrimedCol, 
		starred, primed
	);
} 

void LatexHungarianLog::afterStep2(
	const Array2D<double>& M,
	const size_t* rowsStarredCol,
	const bool* colCovered,
	const bool* rowCovered,
	const size_t* rowsPrimedCol
) {
	//m_output << "\\paragraph{After step 2:}" << endl;

	list< pair<size_t, size_t> > starred, primed;

	renderTikzMatrix(
		M, 
		colCovered, rowCovered, 
		rowsStarredCol, rowsPrimedCol, 
		starred, primed
	);
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
	///m_output << "\\paragraph{Before step 2:}" << endl;

	renderTikzMatrix(
		M, 
		colCovered, rowCovered, 
		rowsStarredCol, rowsPrimedCol, 
		starred, primed
	);
} 


void LatexHungarianLog::afterDeductUncoveredMin(
	const Array2D<double>& M,
	const size_t* rowsStarredCol,
	const bool* colCovered,
	const bool* rowCovered,
	const size_t* rowsPrimedCol,
	const double& minValue
) {
	//m_output << "\\paragraph{After deduct uncovered min:}" << endl;

	list< pair<size_t, size_t> > starred, primed;

	renderTikzMatrix(
		M, 
		colCovered, rowCovered, 
		rowsStarredCol, rowsPrimedCol, 
		starred, primed
	);
} 

void LatexHungarianLog::output(
	const Array2D<double>& M,
	const Assignment& A
) {
	//m_output << "\\paragraph{Output:}" << endl;

	//m_output << "\\begin{center}" << endl;
	m_output << "\\begin{tikzpicture}" << endl;
	m_output << "\\matrix (M)[";
	m_output << "matrix of math nodes, ";
	m_output << "column sep=-\\pgflinewidth, row sep=-\\pgflinewidth, ";
	m_output << "left delimiter={(}, right delimiter={)}, ";
	m_output << "nodes={anchor=center, align=center, minimum height=0.55cm, text width=0.55cm}";
	m_output << "] {" << endl;

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

		m_output << " \\\\";
		m_output << endl;
	}

	m_output << "};" << endl;

	m_output << "\\end{tikzpicture}" << endl;
	//m_output << "\\end{center}" << endl;

	//m_output << "Cost: " << A.cost(M) << endl;
}

void LatexHungarianLog::renderTikzMatrix(
	const Array2D<double>& M,
	const bool* colCovered,
	const bool* rowCovered,
	const size_t* rowsStarredCol,
	const size_t* rowsPrimedCol,
	const list< pair<size_t, size_t> >& starred,
	const list< pair<size_t, size_t> >& primed
) {
	//m_output << "\\begin{center}" << endl;
	m_output << "\\begin{tikzpicture}" << endl;
	m_output << "\\matrix (M)[";
	m_output << "matrix of math nodes, ";
	m_output << "column sep=-\\pgflinewidth, row sep=-\\pgflinewidth, ";
	m_output << "left delimiter={(}, right delimiter={)}, ";
	m_output << "nodes={anchor=center, align=center, minimum height=0.55cm, text width=0.55cm}";
	m_output << "] {" << endl;

	for(size_t row = 0; row < M.getNumRows(); ++row) {
		for(size_t col = 0; col < M.getNumCols(); ++col) {
			const double& value = M.getEntry(row, col);

			if(rowsStarredCol[row] == col) {
				m_output << "\\textcolor{red}{";
			} else if(rowsPrimedCol[row] == col) {
				m_output << "\\textcolor{green}{";
			}

			if(value == 0) { 
				m_output << "\\textbf{";
			}

			m_output << value;

			if(value == 0) {
				m_output << "}";
			}

			if(rowsPrimedCol[row] == col) {
				m_output << "}";
			} else if (rowsStarredCol[row] == col) {
				m_output << "}";
			}


			if(col + 1 != M.getNumCols()) {
				m_output << " & ";
			}
		}

		m_output << " \\\\";
		m_output << endl;
	}

	m_output << "};" << endl;

	for(size_t row = 0; row < M.getNumRows(); ++row) {
		if(rowCovered[row]) {
			m_output << "\\draw[black] ";
			m_output << "(M-" << (row + 1) << "-" << 1 << ".west)";
			m_output << " -- ";
			m_output << "(M-" << (row + 1) << "-" << M.getNumCols() << ".east)";
			m_output << ";" << endl;
		}
	}

	for(size_t col = 0; col < M.getNumCols(); ++col) {
		if(colCovered[col]) {
			m_output << "\\draw[black] ";
			m_output << "(M-" << 1 << "-" << (col + 1) << ".north)";
			m_output << " -- ";
			m_output << "(M-" << M.getNumRows() << "-" << (col + 1) << ".south)";
			m_output << ";" << endl;

		}
	}

	if(!primed.empty()) {
		typedef pair<size_t, size_t> Point;
		typedef pair<Point, Point> Segment;
 
		list<Point>::const_iterator s = starred.begin();
		list<Point>::const_iterator p = primed.begin();

		bool isPrime = true;

		list<Segment> segments;

		Point start, end;
		bool hasStart = false, hasEnd = false;

		while(true) {
			list<Point>::const_iterator* i;

			if(isPrime) {
				if(p == primed.end()) {
					break;
				}
				i = &p;
			} else {
				if(s == starred.end()) {
					break;
				}
				i = &s;
			}

			if(!hasStart && !hasEnd) {
				start = *(*i);
				hasStart = true;
			} else if(hasStart && !hasEnd) {
				end = *(*i);
				hasEnd = true;
			}

			if(hasStart && hasEnd) {
				segments.push_back(Segment(start, end));
				start = end;

				hasStart = true;
				hasEnd = false;
			}

			++(*i);

			isPrime = !isPrime;
		}

		for(list<Segment>::const_iterator i = segments.begin(); i != segments.end(); ++i) {
			const Point& from = (*i).first;
			const Point& to = (*i).second;

			m_output << "\\draw[blue, ultra thick] ";
			m_output << "(M-" << (from.first + 1) << "-" << (from.second + 1) << ".center)";
			m_output << " -- ";
			m_output << "(M-" << (to.first + 1) << "-" << (to.second + 1) << ".center)";
			m_output << ";" << endl;
		}
	}

	m_output << "\\end{tikzpicture}" << endl;
	//m_output << "\\end{center}" << endl;
}

