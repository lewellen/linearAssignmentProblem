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
from scipy import stats, optimize

def loadData(inputFilePath):
	solvers = []
	runtimeBySizeSolver = {}

	with open(inputFilePath, 'r') as inputFile:
		inputReader = csv.DictReader(inputFile, delimiter=' ')

		solvers += inputReader.fieldnames
		solvers.remove('size')
		solvers.remove('')

		for row in inputReader:
			size = int(row['size'])
			if not size in runtimeBySizeSolver:
				runtimeBySizeSolver[size] = { solver : [] for solver in solvers };
 
			for solver in solvers:
				cost = float(row[solver])
				runtimeBySizeSolver[size][solver].append( cost )

	return (solvers, runtimeBySizeSolver) 

def cubicFit(x, a, b, c, d):
	return d + c * x + b * x**2 + a * x**3

def quadLogFit(x, a, b):
	return a * (x**2) * numpy.log(x) + b

def mseBySolverGivenSizeMean(solvers, runtimeBySizeSolver):
	sortedSizes = sorted(runtimeBySizeSolver.keys())
	for solver in solvers:
		X = []
		Y = []
		for size in sortedSizes:
			X.append(size)
			Y.append(numpy.mean(runtimeBySizeSolver[size][solver]))

		objective = cubicFit
		if solver == "GREEDY-EFFICIENT":
			objective = quadLogFit

		popt, pcov = optimize.curve_fit(objective, X, Y)

		fitY = None
		if objective == cubicFit:
			fitY = [objective(x, popt[0], popt[1], popt[2], popt[3]) for x in X]
		else:
			fitY = [objective(x, popt[0], popt[1]) for x in X]

		mse = sum ( (predict - act)**2 for (predict, act) in zip(fitY, Y) )
		print ("%s %f" % (solver, mse))

if __name__ == '__main__':
	if (len(sys.argv) < 2):
		print("%s <file>" % sys.argv[0])
		exit(1)

	(solvers, runtimeBySizeSolver) = loadData(sys.argv[1])

	#mseBySolverGivenSizeMean(solvers, runtimeBySizeSolver)

	print("size "),
	for solver in solvers:
		print("%s %s-CILB %s-CIUB" % (solver, solver, solver)),
	print("")
	
	sortedSizes = sorted(runtimeBySizeSolver.keys())
	for size in sortedSizes:
		print size,
		for solver in solvers:
			xs = numpy.array( runtimeBySizeSolver[size][solver] )
			xs = sorted(xs)
			xs = xs[0:int(0.95 * len(xs))]

			sampleMean = numpy.mean(xs)
			sampleStd = numpy.std(xs)
			confInt = stats.norm.interval(0.95, sampleMean, sampleStd)

			print("%f %f %f" % (sampleMean, max(0, confInt[0]), max(0, confInt[1]))),
		print("")

