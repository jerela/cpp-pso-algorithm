#include <Particle.h>

using namespace pso;


// constructor
Particle::Particle(size_t dim, double lb, double ub) {

	// set dimension of particle
	dimension_ = dim;

	upperBound_ = ub;
	lowerBound_ = lb;

	currentPosition_ = std::vector<double>(dimension_,0.0);
	velocity_ = std::vector<double>(dimension_,0.0);
	lowestErrorPosition_ = std::vector<double>(dimension_,0.0);
	neighbourhoodLowestErrorPosition_ = std::vector<double>(dimension_, 0.0);

	// generate random starting position in the given search space and initialize other vectors to 0
	randomizePosition();

};
//~Particle();

// (re)initialize particle position randomly
void Particle::randomizePosition() {
	if (verbose_)
		std::cout << "Initialized particle at ";
	/*for (unsigned int i = 0; i < dimension_; ++i) {
		currentPosition_[i] = generateRandomNumber((int)round(lowerBound_), (int)round(upperBound_));
		if (verbose_)
			std::cout << currentPosition_[i] << " ";

	}*/


	for (auto it = currentPosition_.begin(); it < currentPosition_.end(); ++it) {
		*it = generateRandomNumber((int)round(lowerBound_), (int)round(upperBound_));
		if (verbose_)
			std::cout << *it << " ";
	}


	if (verbose_)
		std::cout << std::endl;
}

// updates the particle's velocity and current position
double Particle::update(const double targetValue, const std::vector<double>& input) {

	// generate random factors for velocity changes
	double randomFactorIndividual = generateRandomNumber(0, 1); //((double)(rand() % 101) / 100);
	double randomFactorCollective = generateRandomNumber(0, 1); //((double)(rand() % 101) / 100);
	//std::cout << "random number: " << randomFactorIndividual << std::endl;

	// update each dimension of direction
	for (unsigned int i = 0; i < velocity_.size(); ++i) {
		// update velocity
		velocity_[i] = a_ * velocity_[i] + b_ * randomFactorIndividual * (lowestErrorPosition_[i] - currentPosition_[i]) + c_ * randomFactorCollective * (neighbourhoodLowestErrorPosition_[i] - currentPosition_[i]);

		// update position
		currentPosition_[i] = currentPosition_[i] + velocity_[i];

	}

	// evaluate error in new position
	double error = evaluate(targetValue, input);
	if (error < lowestError_) {
		lowestError_ = error;
		lowestErrorPosition_ = currentPosition_;
		updatesSinceMinimum_ = 0;
	}
	else {
		updatesSinceMinimum_ += 1;
	}

	// give the particle a slight chance to be reinitialized each run; it is more likely when the particle hasn't reduced its error in a while
	// NOTE: this sends the particle into a frenzy of randomization if it cannot find a minimum
	if (generateRandomNumber(0, 1) < 0.001 * (double)updatesSinceMinimum_) {
		randomizePosition();
	}

	// vibrate particles slightly to "shake off" local minima
	for (unsigned int i = 0; i < dimension_; ++i) {
		currentPosition_[i] += generateRandomNumber(-1,1)*(upperBound_ - lowerBound_)*0.001;
	}

	return lowestError_;

}


// calculate error
double Particle::evaluate(const double targetValue, const std::vector<double>& input) {
	double result = 0;
	for (unsigned int i = 0; i < input.size(); ++i) {
		result += currentPosition_[i] * input[i];
	}

	double error = abs(result - targetValue);

	if (verbose_) {
		std::cout << "POSITION: ";
		for (unsigned int i = 0; i < input.size(); ++i) {
			std::cout << currentPosition_[i] << " ";
		}
		std::cout << "ERROR: " << error << std::endl;
	}

	return error;
}

// generate random numbers between lb and ub
double Particle::generateRandomNumber(int lb, int ub) {
	int range = ub - lb;
	return ((double)(rand() % ((range * 1000 + 1))) / 1000 + lb);
}



