#include <cassert>
#include <cmath>

#include "Interval.h"
#include "SampledValue.h"

SampledValue::SampledValue() {
	m_numSamples = 0;
	m_sampleMean = 0;
	m_sampleVariance = 0;
}

SampledValue::~SampledValue() {

}

void SampledValue::add(const double& value) {
	// Welford method for variance (Knuth)
	++m_numSamples;

	double oldSampleMean = m_sampleMean;
	m_sampleMean += ( value - m_sampleMean ) / m_numSamples;
	m_sampleVariance += (value - oldSampleMean) * (value - m_sampleMean);
}

bool SampledValue::empty() const {
	return m_numSamples == 0;
}

double SampledValue::numSamples() const {
	return m_numSamples;
}

double SampledValue::sampleMean() const {
	assert(m_numSamples > 0);
	return m_sampleMean;
}

double SampledValue::sampleStandardDev() const {
	assert(m_numSamples > 0);
	return sqrt( m_sampleVariance / m_numSamples );
}

/*Interval SampledValue::confidenceInterval(const double& confidenceLevel) const {
	assert( (0 < confidenceLevel) && (confidenceLevel <= 1) );
	assert( m_numSamples > 0 );

	double alpha = 0.5 * (1 - confidenceLevel);
	double degreeOfFreedom = m_numSamples - 1;

	TODO: Read up on efficient way to find critical values from t-dist		
}*/

