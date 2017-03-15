# Input: data file where each row is a sample, first column is size, 
# each column thereafter corresponds to min cost found by a solver.
#
# Want to look at minCost / baseline minCost (all entries should be >= 1);
# Want confidence interval around each
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
		solvers.remove('RANDOM')
		solvers.remove('HUNGARIAN')
		solvers.remove('')

		alphaBySizeSolver = {}
		for row in inputReader:
			size = int(row['size'])
			if not size in alphaBySizeSolver:
				alphaBySizeSolver[size] = { solver : [] for solver in solvers };
 
			minCost = float(row['HUNGARIAN'])
			for solver in solvers:
				cost = float(row[solver])
				#alphaBySizeSolver[size][solver].append( cost )
				alphaBySizeSolver[size][solver].append( cost / minCost )
				#alphaBySizeSolver[size][solver].append( (cost - minCost) / (maxCost - minCost) )


	print("size "),
	for solver in solvers:
		print("%s %s-CILB %s-CIUB" % (solver, solver, solver)),
	print("")
	
	sortedSizes = sorted(alphaBySizeSolver.keys())
	for size in sortedSizes:
		print size,
		for solver in solvers:
			xs = numpy.array( alphaBySizeSolver[size][solver] )

			sampleMean = numpy.mean(xs)
			sampleStd = numpy.std(xs)
			confInt = stats.norm.interval(0.95, sampleMean, sampleStd)

			print("%f %f %f" % (sampleMean, confInt[0], confInt[1])),
		print("")
