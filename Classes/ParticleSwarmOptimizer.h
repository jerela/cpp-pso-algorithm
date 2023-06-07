#pragma once

#include <vector>
#include <Particle.h>
#include <math.h>

namespace pso {

	class ParticleSwarmOptimizer {

	public:
		//ParticleSwarmOptimizer();
		//~ParticleSwarmOptimizer();

		void setDimension(size_t dim) { dimension_ = dim; }
		void setNumParticles(unsigned int n) { numParticles_ = n; }
		void initialize() {
			for (unsigned int i = 0; i < numParticles_; ++i) {
				particles_.push_back(pso::Particle(dimension_));
			}
			collectiveLowestErrorPosition_ = std::vector<double>(dimension_);
		}

		void setInput(std::vector<double> input) { input_ = input; }
		void setTargetValue(double target) { targetValue_ = target; }

		// run a single iteration where each particle is updated
		void update() {

			// prepare a vector of errors for each particle
			std::vector<double> errors(particles_.size());

			// update each particle
			for (unsigned int i = 0; i < particles_.size(); ++i) {
				// update a single particle
				errors[i] = particles_[i].update(collectiveLowestErrorPosition_, targetValue_, input_);
			}

			// update collective lowest error
			for (unsigned int i = 0; i < particles_.size(); ++i) {
				if (errors[i] < collectiveLowestError_) {
					collectiveLowestError_ = errors[i];
					collectiveLowestErrorPosition_ = particles_[i].getPosition();
				}
			}



		}

		std::vector<double> getLowestErrorPosition() {
			return collectiveLowestErrorPosition_;
		}

	private:
		unsigned int numParticles_ = 1;
		unsigned int dimension_ = 1;
		std::vector<double> input_;
		double targetValue_ = 0;
		std::vector<pso::Particle> particles_;
		std::vector<double> collectiveLowestErrorPosition_;
		double collectiveLowestError_ = INFINITY;// = update();



	};

}
