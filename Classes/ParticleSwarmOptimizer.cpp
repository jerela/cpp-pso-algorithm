#include <ParticleSwarmOptimizer.h>
#include <iterator>

using namespace pso;









template <class anyType>
void printVector(std::vector<anyType> vec, std::string label) {
	std::cout << label << ": ";
	for (unsigned int i = 0; i < vec.size(); ++i) {
		std::cout << vec[i];
		if (i < vec.size() - 1) {
			std::cout << ", ";
		}
	}
	std::cout << std::endl;
}














void ParticleSwarmOptimizer::optimizeParameters(const std::vector<std::vector<double>>& inputs, const std::vector<double>& targets, size_t dim, double lowerBound, double upperBound, unsigned int nParticles, unsigned int maxEpochs, double threshold) {

	auto rng = std::default_random_engine{};

	std::vector<size_t> indices;
	for (unsigned int i = 0; i < inputs.size(); ++i) {
		indices.push_back(i);
	}

	size_t nSamples = targets.size();

	
	// dimension of particles is the number of parameters
	size_t inputSize = inputs[0].size();

	// set values for PSO
	setDimension(dim);
	setNumParticles(nParticles);
	setBounds(lowerBound, upperBound);
	initialize();

	unsigned int epoch = 1;

	std::vector<double> estimatedParams;

	double bestError = INFINITY;
	std::vector<double> bestParams;

	double err = 0;

	// for each epoch
	for (unsigned int currentEpoch = 0; currentEpoch < maxEpochs; ++currentEpoch) {

		// shuffle indices so that data samples are picked in a random order when updating particles
		std::shuffle(std::begin(indices), std::end(indices), rng);

		// initialize the error sum of all data samples to 0
		err = 0;

		// calculate error over all inputs and targets at once

		// iterate through all data samples to update parameters
		for (unsigned int i = 0; i < inputs.size(); ++i) {
			std::vector<double> currentInput = inputs[indices[i]];
			double currentTarget = targets[indices[i]];
			update(currentInput, currentTarget);
		}
		//PSO.updateMultiple(inputs, targets);

		// get estimated parameters as the position corresponding to global lowest error
		estimatedParams = getLowestErrorPosition();

		// iterate through all data samples to calculate error in target value
		for (unsigned int i = 0; i < inputs.size(); ++i) {
			std::vector<double> currentInput = inputs[indices[i]];
			double currentTarget = targets[indices[i]];


			// calculate an estimate of the output value to calculate error
			double estimatedTarget = 0;
			for (unsigned int j = 0; j < inputSize; ++j) {
				estimatedTarget += estimatedParams[j] * currentInput[j];
			}

			err += abs(currentTarget - estimatedTarget);

		}
		err = err / inputs.size();

		std::cout << "Epoch " << currentEpoch << ", mean error over all inputs: " << err << std::endl;

		if (err < bestError) {
			bestError = err;
			bestParams = estimatedParams;
		}

		epoch += 1;
		if (epoch > maxEpochs) {
			break;
		}

		if (err < threshold) {
			break;

		}

	} // end iteration through epochs

	std::cout << "Best mean error: " << bestError << std::endl;
	printVector(bestParams, "Best parameters considering mean error");

	std::cout << "Final error: " << err << std::endl;
	printVector(estimatedParams, "Final params: ");

}





























// initializes all particles
void ParticleSwarmOptimizer::initialize() {
	for (unsigned int i = 0; i < numParticles_; ++i) {
		particles_.push_back(pso::Particle(dimension_, lowerBound_, upperBound_));
	}

	// set the size of the neighbourhood to approximately one tenth of swarm size
	neighboursPerSide_ = (int)round((int)numParticles_ / 20);

}


// run a single iteration where each particle is updated
void ParticleSwarmOptimizer::update(const std::vector<double>& input, const double targetValue) {



	// prepare a vector of errors for each particle
	std::vector<double> errors(numParticles_);

	// update each particle
	for (int i = 0; i < numParticles_; ++i) {
		// update a single particle
		errors[i] = particles_[i].update(targetValue, input);
	}

	// update neighbourhood lowest error
	for (int i = 0; i < numParticles_; ++i) {

		double neighbourhoodLowestError = particles_[i].getNeighbourhoodLowestError();

		for (int j = -neighboursPerSide_; j < neighboursPerSide_ + 1; ++j) {
			if (j == 0) continue;
			int currentIdx = i + j;
			if (currentIdx < 0)
				currentIdx += numParticles_;
			if (currentIdx > numParticles_ - 1)
				currentIdx -= numParticles_;
			if (errors[currentIdx] < neighbourhoodLowestError) {
				particles_[i].setNeighbourhoodLowestError(errors[currentIdx]);
				particles_[i].setNeighbourhoodLowestErrorPosition(particles_[currentIdx].getPosition());
			}
		}

	}

	

	//std::cout << "[" << particles_[0].getPosition()[0] << ", " << particles_[0].getPosition()[1] << "], [" << particles_[1].getPosition()[0] << ", " << particles_[1].getPosition()[1] << "]" << std::endl;;



}


// gets the position of the global lowest error
const std::vector<double> ParticleSwarmOptimizer::getLowestErrorPosition() {
	std::vector<double> lowestErrorPosition(2,0);
	double error = INFINITY;
	/*for (unsigned int i = 0; i < particles_.size(); ++i) {
		if (particles_[i].getNeighbourhoodLowestError() < error) {
			error = particles_[i].getNeighbourhoodLowestError();
			lowestErrorPosition = particles_[i].getNeighbourhoodLowestErrorPosition();
			//std::cout << "Neighbourhood " << i << "/" << particles_.size() << " error: " << error << std::endl;

		}
	}*/
	for (auto it = particles_.begin(); it < particles_.end(); ++it) {
		if (it->getNeighbourhoodLowestError() < error) {
			error = it->getNeighbourhoodLowestError();
			lowestErrorPosition = it->getNeighbourhoodLowestErrorPosition();
		}
	}
	return lowestErrorPosition;
}


