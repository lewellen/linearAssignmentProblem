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
	m_output << "\\begin{document}" << endl;
}

LatexGreedyLog::~LatexGreedyLog() {
	m_output << "\\end{document}" << endl;
}

void LatexGreedyLog::input(
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

void LatexGreedyLog::afterAssignment(
	const Array2D<double>& M,
	const Assignment& A,
	const size_t& minRow,
	const size_t& minCol
) {
	m_output << "\\paragraph{Assignment:}" << endl;

	m_output << "\\begin{equation}" << endl;
	m_output << "\\begin{pmatrix}" << endl;

	for(size_t row = 0; row < M.getNumRows(); ++row) {
		size_t assignedCol = A[row];
		for(size_t col = 0; col < M.getNumCols(); ++col) {
			const double& value = M.getEntry(row, col);

			if(col == minCol || row == minRow) {
				m_output << "\\colorbox{yellow}{";
			}

			if(col == minCol && row == minRow) {
				m_output << "\\textbf{";
			}

			if(col == assignedCol) {
				m_output << "\\fbox{";
			}

			m_output << value;

			if(col == assignedCol) {
				m_output << "}";
			}

			if(col == minCol && row == minRow) {
				m_output << "}";
			}

			if(col == minCol || row == minRow) {
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

void LatexGreedyLog::output(
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

}
