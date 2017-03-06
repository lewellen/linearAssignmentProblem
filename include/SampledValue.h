#ifndef SAMPLEDVALUE_H
#define SAMPLEDVALUE_H

#include "Interval.h"

class SampledValue {
public:
	SampledValue();
	virtual ~SampledValue();
 
	void add(const double& value);
	bool empty() const; 

	double numSamples() const; 
	double sampleMean() const;
	double sampleStandardDev() const;

	//Interval confidenceInterval(const double& confidenceLevel) const;
 
private:
	double m_numSamples;
	double m_sampleMean;
	double m_sampleVariance;
};

#endif
