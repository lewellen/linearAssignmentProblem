# Input: data file where each row is a sample, first column is size, every 
# column thereafter is runtime in seconds of a solver.

# Want to look at want confidence interval around each mean
#
# Output a Gnuplot .dat formated file where first column is size, then for each 
# solver: CI LB, Mean, CI UB

import csv
import sys
import operator

import numpy
from scipy import stats

if __name__ == '__main__':
	if (len(sys.argv) < 2):
		print("%s <file>" % sys.argv[0])
		exit(1)

	solvers = []

	inputFilePath = sys.argv[1]
	with open(inputFilePath, 'r') as inputFile:
		inputReader = csv.DictReader(inputFile, delimiter=' ')

		solvers += inputReader.fieldnames
		solvers.remove('size')
		solvers.remove('')

		runtimeBySizeSolver = {}
		for row in inputReader:
			size = int(row['size'])
			if not size in runtimeBySizeSolver:
				runtimeBySizeSolver[size] = { solver : [] for solver in solvers };
 
			for solver in solvers:
				cost = float(row[solver])
				runtimeBySizeSolver[size][solver].append( cost )


	print("size "),
	for solver in solvers:
		print("%s %s-CILB %s-CIUB" % (solver, solver, solver)),
	print("")
	
	sortedSizes = sorted(runtimeBySizeSolver.keys())
	for size in sortedSizes:
		print size,
		for solver in solvers:
			xs = numpy.array( runtimeBySizeSolver[size][solver] )

			sampleMean = numpy.mean(xs)
			sampleStd = numpy.std(xs)
			confInt = stats.norm.interval(0.95, sampleMean, sampleStd)

			print("%f %f %f" % (sampleMean, confInt[0], confInt[1])),
		print("")
