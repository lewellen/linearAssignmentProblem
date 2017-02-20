#include <limits>

#include "Array2D.h"
#include "MaximizeObjective.h"

using std::numeric_limits;

MaximizeObjective::MaximizeObjective() {

}

MaximizeObjective::~MaximizeObjective() {

}

void MaximizeObjective::operator() (Array2D<double>& M) const {
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
