#pragma once

#include <vector>
#include <Particle.h>

namespace pso {

	class ParticleSwarmOptimizer {

	public:
		ParticleSwarmOptimizer();
		~ParticleSwarmOptimizer();

		// run a single iteration where each particle is updated
		void update() {

			std::vector<double> errors(particles_.size());

			// update each particle
			for (unsigned int i = 0; i < particles_.size(); ++i) {
				// update a single particle
				errors[i] = particles_[i].update(collectiveLowestErrorPosition_);
			}

			// update collective lowest error
			for (unsigned int i = 0; i < particles_.size(); ++i) {
				if (errors[i] < collectiveLowestError_) {
					collectiveLowestError_ = errors[i];
					collectiveLowestErrorPosition_ = particles_[i].getPosition();
				}
			}



		}

	private:
		unsigned int numParticles_ = 1;
		unsigned int dimension_ = 1;
		std::vector<pso::Particle> particles_(numParticles_);
		std::vector<double> collectiveLowestErrorPosition_(dimension_);
		double collectiveLowestError_ = update();
	};

}
