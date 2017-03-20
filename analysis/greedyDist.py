import csv
import sys
import operator

import numpy
from scipy import stats

import matplotlib.pyplot as plt

def matrixArgMin(A):
	minRow = 0
	minCol = 0
	minValue = float("+inf")

	(rows, cols) = A.shape
	for row in xrange(0, rows):
		for col in xrange(0, cols):
			value = A[row, col]
			if(minValue > value):
				minValue = value
				minRow = row
				minCol = col

	for i in xrange(0, rows):
		for j in xrange(0, cols):
			assert minValue <= A[i,j]
				
	return (minRow, minCol, minValue)

def interpretAndersonDarling(samples, distName):
	stat, critValues, sigLevels = confLevel= stats.anderson(samples, distName)

	for (critValue, sigLevel) in zip(critValues, sigLevels):
		if stat >= critValue:
			print ("Rejecting null hypothesis that samples come from %s since statistic %f >= critical value %f at signifigance level %f." % (distName, stat, critValue, sigLevel) )

	print("Failed to reject null hypothesis that samples come from a %s distribution" % (distName))

def verifyScipyExponIsCorrect():
	# Gather empirical samples
	numSamples = 1000
	samples = stats.expon(scale=1).rvs(numSamples)
	plt.hist(samples, bins=20, normed=True, label='Estimate')

	# Construct the theoretical result
	support = numpy.linspace(min(samples), max(samples), num=100)
	pdf = [ stats.expon(scale=1).pdf(x) for x in support ]
	plt.plot(support, pdf, label='Theory')
	
	# anderson-darling
	interpretAndersonDarling(samples, 'expon')	

	plt.title("Distribution of Exp(1)")
	plt.xlabel("$x$")
	plt.ylabel("$f_X(x)$")
	plt.legend(loc="upper right")
	plt.show()

def verifyMinimumDistribution():
	# n x n matrix ~ Exp(1)
	n = 10

	# Gather empirical samples
	numSamples = 1000
	samples = []
	for sample in xrange(0, numSamples):
		xs = stats.expon(scale=1).rvs(n**2)
		samples.append(min(xs))

	plt.hist(samples, bins=20, normed=True, label='Estimate')

	# Construct the theoretical result X_{1:n^2} ~ Exp(n)
	support = numpy.linspace(min(samples), max(samples), num=100)
	pdf = [ stats.expon(scale=1.0 / n**2).pdf(x) for x in support ]
	plt.plot(support, pdf, label='Theory')

	# anderson-darling
	interpretAndersonDarling(samples, 'expon')	

	plt.title("Distribution of minimum entry in $n \\times n$ matrix for n = %d" % n)
	plt.xlabel("$x$")
	plt.ylabel("$f_X(x)$")
	plt.legend(loc="upper right")
	plt.show()


def investigateMinDifferences():
	n = 10
	numSamples = 2000

	samples = []
	for sample in xrange(0, numSamples):
		xs = stats.expon(scale=1).rvs(n**2).reshape((n,n))

		(r, c, u) = matrixArgMin(xs)
		xs = numpy.delete(xs, r, axis=0)
		xs = numpy.delete(xs, c, axis=1)
		assert xs.shape == (n-1, n-1)

		(s, d, v) = matrixArgMin(xs)
		assert v >= u
		samples.append(v - u)

	# anderson-darling
	interpretAndersonDarling(samples, 'expon')	

	plt.hist(samples, bins=20, normed=True, label='Estimate')

	# Construct the theoretical result X_{1:n^2} ~ Exp(n)
	support = numpy.linspace(min(samples), max(samples), num=100)
	pdf = [ stats.expon(scale=1.0 / (n-1)**2).pdf(x) for x in support ]
	plt.plot(support, pdf, label='Theory')

	plt.title("Distribution of $(n-1)^2$ min - $n^2$ min")
	plt.xlabel("$x$")
	plt.ylabel("$f_X(x)$")
	plt.legend(loc="upper right")
	plt.show()


def expectedKthExpOS(_lambda, r, n):
	# Assume F(x) = 1 - e^{-x} => f(x) = e^{-x}
	# Order Statistics from independent exponential random variables and the sum of the top order statistics
	# http://homepages.math.uic.edu/~wangjing/stat416/orderstat-exp1.pdf
	# E( X_{i:n} ) = \frac{1}{\lambda} sum_{j = 1}^{i} \frac{1}{n-j+1}
	#
	# This is a consequence of R{\'e}yni representation
	return _lambda * sum( [1.0 / (n - i + 1.0) for i in xrange(1, r+1)] )

def compareMinCostTheoryToPractice():
	minEdgeSize = 3
	maxEdgeSize = minEdgeSize + 1
	numSamples = 1000

	minBySizeAndItr = {}
	minCostBySize = {}

	for matrixN in xrange(minEdgeSize, maxEdgeSize):
		minBySizeAndItr[matrixN] = {}
		for i in xrange(0, matrixN):
			minBySizeAndItr[matrixN][i] = []

		minCostBySize[matrixN] = []

	for matrixN in xrange(minEdgeSize, maxEdgeSize):
		for sample in xrange(0, numSamples):
			# M_{i,j} \sim Exp(1)
			M = stats.expon(scale=1).rvs(size=matrixN * matrixN).reshape((matrixN, matrixN))

			cost = 0

			for i in xrange(0, matrixN):
				index = M.argmin()
				col = index % (matrixN - i)
				row = (index - col) / (matrixN - i)

				value = M[row, col]
				cost += value
				minBySizeAndItr[matrixN][i].append(value)
				
				M = numpy.delete(M, (row), axis = 0)
				M = numpy.delete(M, (col), axis = 1)

			minCostBySize[matrixN].append(cost)

		for i in xrange(0, matrixN):
			samplesByItr = minBySizeAndItr[matrixN]
			samplesByItr[i] = sum( samplesByItr[i] ) / float( len( samplesByItr[i] ) )

		
		minCostBySize[matrixN] = sum(minCostBySize[matrixN]) / float(len(minCostBySize[matrixN]))

	for matrixN in xrange(minEdgeSize, maxEdgeSize):
		minByItr = minBySizeAndItr[matrixN]

		X = list(minByItr.keys())
		Y = list(minByItr.values())
		plt.plot(X, Y, linestyle='--', marker='o', label="%d" % matrixN)

		ySum = sum(Y)
		print "Empirical: %f" % ySum
		plt.plot([matrixN-1], [ySum], marker='o', label="%d sum" % matrixN)

		for (x,y) in zip(X,Y):
			print("%f %f" % (x, y))

	X = xrange(0, maxEdgeSize-1)

	# Expected minimum value of a n x n matrix (assumes independence of minimums
	# ie, X_{1:n} doesn't impact X_{1:(n-1)^2} (not a valid assumption))
	#Y = [ 1.0 / (maxEdgeSize - x)**2 for x in X ]

	# This assumes a fixed size n^2 matrix for
	#  a(0) = 1; a(k) = a(k-1) + 2(n-k+1) - 1 for k = 0 to n-1
	#Y = [ expectedKthExpOS(1, 2*x*(maxEdgeSize-1)-x**2 + 1, (maxEdgeSize-1)**2) for x in X ]

	Y = [  sum([ 1.0 / ( (maxEdgeSize-1)**2 - 2 * y * (maxEdgeSize - 1) + y*y  )  for y in xrange(0, x+1)  ])   for x in X ]

	#Y = [ 1.0/float(maxEdgeSize - x - 1) for x in X ]

	plt.plot(X, Y, label='Original Theory')

	ySum = sum(Y)
	plt.plot([matrixN-1], [ySum], marker='*', label='Theory sum')

	X = list(minCostBySize.keys())
	Y = list(minCostBySize.values())
	plt.plot(X, Y, linestyle='--', marker='x', label="MinCost")

	plt.yscale('log')	
	plt.legend(loc='upper left')
	plt.show()



if __name__ == '__main__':
	#verifyScipyExponIsCorrect()
	#verifyMinimumDistribution()
	#investigateMinDifferences()

	compareMinCostTheoryToPractice()
