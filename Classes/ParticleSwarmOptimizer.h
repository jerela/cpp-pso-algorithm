#pragma once

#include <vector>
#include <Particle.h>
#include <math.h>

namespace pso {

	class ParticleSwarmOptimizer {

	public:
		//ParticleSwarmOptimizer();
		//~ParticleSwarmOptimizer();

		// sets the dimension of particles
		void setDimension(size_t dim) { dimension_ = dim; }
		// sets the number of particles
		void setNumParticles(unsigned int n) { numParticles_ = n; }
		// sets the upper and lower bounds of the search space
		void setBounds(int lb, int ub) {
			lowerBound_ = lb;
			upperBound_ = ub;
		}

		// initializes all particles
		void initialize() {
			for (unsigned int i = 0; i < numParticles_; ++i) {
				particles_.push_back(pso::Particle(dimension_,lowerBound_,upperBound_));
			}
			collectiveLowestErrorPosition_ = std::vector<double>(dimension_);
		}

		// sets the input data
		void setInput(std::vector<double> input) { input_ = input; } // ALTERNATIVE: GIVE INPUT AS PARAMETER IN UPDATE()
		void setTargetValue(double target) { targetValue_ = target; } // ALTERNATIVE: GIVE TARGET VALUE AS PARAMETER IN UPDATE()

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

		// gets the position of the global lowest error
		std::vector<double> getLowestErrorPosition() {
			return collectiveLowestErrorPosition_;
		}

	private:
		int upperBound_ = 0;
		int lowerBound_ = 0;
		unsigned int numParticles_ = 1;
		size_t dimension_ = 1;
		std::vector<double> input_;
		double targetValue_ = 0;
		std::vector<pso::Particle> particles_;
		std::vector<double> collectiveLowestErrorPosition_;
		double collectiveLowestError_ = INFINITY;



	};

}
