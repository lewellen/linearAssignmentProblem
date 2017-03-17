#include <cstdlib>
#include <iostream>

#include "Array2D.h"
#include "Assignment.h"
#include "LatexGreedyLog.h"

using std::endl;
using std::ostream;

LatexGreedyLog::LatexGreedyLog(ostream& output) : m_output(output) {
	m_output << "\\documentclass{article}" << endl;
	m_output << "\\usepackage{amsmath}" << endl;
	m_output << "\\usepackage{xcolor}" << endl;
	m_output << "\\usepackage{tikz}" << endl;
	m_output << "\\usetikzlibrary{matrix}" << endl;
	m_output << "\\begin{document}" << endl;
}

LatexGreedyLog::~LatexGreedyLog() {
	m_output << "\\end{document}" << endl;
}

void LatexGreedyLog::input(
	const Array2D<double>& M
) {

	m_output << "\\section{}" << endl;

	//m_output << "\\paragraph{Input:}" << endl;

	//m_output << "\\begin{center}" << endl;
	m_output << "\\begin{tikzpicture}" << endl;
	m_output << "\\matrix (M)[matrix of math nodes, left delimiter={(}, right delimiter={)}] {" << endl;

	for(size_t row = 0; row < M.getNumRows(); ++row) {
		for(size_t col = 0; col < M.getNumCols(); ++col) {
			const double& value = M.getEntry(row, col);
			m_output << value;

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
} 

void LatexGreedyLog::afterAssignment(
	const Array2D<double>& M,
	const Assignment& A,
	const size_t& minRow,
	const size_t& minCol
) {
	bool rowCovered[M.getNumRows()] { false };
	bool colCovered[M.getNumCols()] { false };

	for(size_t row = 0; row < M.getNumRows(); ++row) {
		rowCovered[row] = A[row] < M.getNumRows();
		if(rowCovered[row]) {
			colCovered[A[row]] = true;
		}
	}

	//m_output << "\\paragraph{Assignment:}" << endl;

	//m_output << "\\begin{center}" << endl;
	m_output << "\\begin{tikzpicture}" << endl;
	m_output << "\\matrix (M)[matrix of math nodes, left delimiter={(}, right delimiter={)}] {" << endl;

	for(size_t row = 0; row < M.getNumRows(); ++row) {
		for(size_t col = 0; col < M.getNumCols(); ++col) {
			const double& value = M.getEntry(row, col);
			if(row == minRow && col == minCol) {
				m_output << "\\textbf{";
				m_output << "\\textcolor{red}{";
			}

			if(A[row] == col) {
				m_output << "\\fbox{";
			}

			m_output << value;

			if(A[row] == col) {
				m_output << "}";
			}

			if(row == minRow && col == minCol) {
				m_output << "}}";
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
			m_output << "\\draw[black](M-" << (row + 1) << "-1.west)--(M-" << (row + 1) << "-" << M.getNumCols() << ".east);" << endl;
		}
	}

	for(size_t col = 0; col < M.getNumCols(); ++col) {
		if(colCovered[col]) {
			m_output << "\\draw[black](M-1-" << (col + 1) << ".north)--(M-" << M.getNumRows() << "-" << (col + 1) << ".south);" << endl;

		}
	}

	m_output << "\\end{tikzpicture}" << endl;
	//m_output << "\\end{center}" << endl;
}

void LatexGreedyLog::output(
	const Array2D<double>& M,
	const Assignment& A
) {
	//m_output << "\\paragraph{Output:}" << endl;

	//m_output << "\\begin{center}" << endl;
	m_output << "\\begin{tikzpicture}" << endl;
	m_output << "\\matrix (M)[matrix of math nodes, left delimiter={(}, right delimiter={)}] {" << endl;

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

	m_output << "Cost: " << A.cost(M) << endl;
}
