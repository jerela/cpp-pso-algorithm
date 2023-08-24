#include <ParticleSwarmOptimizer.h>
#include <iterator>

using namespace pso;

// initializes all particles
void ParticleSwarmOptimizer::initialize() {
	for (unsigned int i = 0; i < numParticles_; ++i) {
		particles_.push_back(pso::Particle(dimension_, lowerBound_, upperBound_));
	}
	//collectiveLowestErrorPosition_ = std::vector<double>(dimension_);


	for (unsigned int i = 0; i < numParticles_; ++i) {
		//neighbourhoodLowestErrorPosition_.push_back(std::vector<double>(dimension_));
		neighbourhoodLowestErrorPosition_.push_back(particles_[i].getPosition());
		neighbourhoodLowestError_.push_back(INFINITY);
	}

	// set the size of the neighbourhood to approximately one tenth of swarm size
	neighboursPerSide_ = (int)round((int)numParticles_ / 20);

}


// run a single iteration where each particle is updated
void ParticleSwarmOptimizer::update(std::vector<double> input, double targetValue) {

	// prepare a vector of errors for each particle
	std::vector<double> errors(particles_.size());

	// update each particle
	for (int i = 0; i < particles_.size(); ++i) {
		// update a single particle
		errors[i] = particles_[i].update(neighbourhoodLowestErrorPosition_[i], targetValue, input);
	}

	// update neighbourhood lowest error
	for (int i = 0; i < particles_.size(); ++i) {

		for (int j = -neighboursPerSide_; j < neighboursPerSide_ + 1; ++j) {
			if (j == 0) continue;
			int currentIdx = i + j;
			if (currentIdx < 0) currentIdx += particles_.size();
			if (currentIdx > particles_.size() - 1) currentIdx -= particles_.size();
			if (errors[currentIdx] < neighbourhoodLowestError_[i]) {
				neighbourhoodLowestError_[i] = errors[currentIdx];
				neighbourhoodLowestErrorPosition_[i] = particles_[currentIdx].getPosition();
			}
		}

	}

	

	//std::cout << "[" << particles_[0].getPosition()[0] << ", " << particles_[0].getPosition()[1] << "], [" << particles_[1].getPosition()[0] << ", " << particles_[1].getPosition()[1] << "]" << std::endl;;



}


// run a single iteration where each particle is updated
void ParticleSwarmOptimizer::updateMultiple(std::vector<std::vector<double>> inputs, std::vector<double> targetValues) {

	// prepare a vector of errors for each particle
	std::vector<double> errors(particles_.size());

	// update each particle
	for (int i = 0; i < particles_.size(); ++i) {
		// update a single particle
		errors[i] = particles_[i].updateMultiple(neighbourhoodLowestErrorPosition_[i], targetValues, inputs);
	}

	// update neighbourhood lowest error
	for (int i = 0; i < particles_.size(); ++i) {

		for (int j = -neighboursPerSide_; j < neighboursPerSide_ + 1; ++j) {
			if (j == 0) continue;
			int currentIdx = i + j;
			if (currentIdx < 0) currentIdx += particles_.size();
			if (currentIdx > particles_.size() - 1) currentIdx -= particles_.size();
			if (errors[currentIdx] < neighbourhoodLowestError_[i]) {
				neighbourhoodLowestError_[i] = errors[currentIdx];
				neighbourhoodLowestErrorPosition_[i] = particles_[currentIdx].getPosition();
			}
		}

	}



	// update each particle
	for (int i = 0; i < particles_.size(); ++i) {
		// update a single particle
		errors[i] = particles_[i].updateMultiple(neighbourhoodLowestErrorPosition_[i], targetValues, inputs);
	}


}

// gets the position of the global lowest error
std::vector<double> ParticleSwarmOptimizer::getLowestErrorPosition() {
	std::vector<double> lowestErrorPosition;
	double error = INFINITY;
	for (unsigned int i = 0; i < particles_.size(); ++i) {
		if (neighbourhoodLowestError_[i] < error) {
			error = neighbourhoodLowestError_[i];
			lowestErrorPosition = neighbourhoodLowestErrorPosition_[i];
			//std::cout << "Neighbourhood " << i << "/" << particles_.size() << " error: " << error << std::endl;

		}
	}
	return lowestErrorPosition;
}


