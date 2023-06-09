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
		// sets the number of neighbourhoods
		void setNeighbourhoods(unsigned int n) {
			neighbourhoods_ = n;
		}

		// initializes all particles
		void initialize() {
			for (unsigned int i = 0; i < numParticles_; ++i) {
				particles_.push_back(pso::Particle(dimension_,lowerBound_,upperBound_,i%neighbourhoods_));
			}
			//collectiveLowestErrorPosition_ = std::vector<double>(dimension_);

			for (unsigned int i = 0; i < neighbourhoods_; ++i) {
				neighbourhoodLowestErrorPosition_.push_back(std::vector<double>(dimension_));
				neighbourhoodLowestError_.push_back(INFINITY);
			}

		}


		// run a single iteration where each particle is updated
		void update(std::vector<double> input, double targetValue) {

			// prepare a vector of errors for each particle
			std::vector<double> errors(particles_.size());

			// update each particle
			for (unsigned int i = 0; i < particles_.size(); ++i) {
				// update a single particle
				//errors[i] = particles_[i].update(collectiveLowestErrorPosition_, targetValue, input);
				errors[i] = particles_[i].update(neighbourhoodLowestErrorPosition_[particles_[i].getNeighbourhood()], targetValue, input);
			}

			// update neighbourhood lowest error
			for (unsigned int i = 0; i < particles_.size(); ++i) {
				//if (errors[i] < collectiveLowestError_) {
				unsigned int currentNeighbourhood = particles_[i].getNeighbourhood();
				//std::cout << "Current neighbourhood: " << currentNeighbourhood << std::endl;
				if (errors[i] < neighbourhoodLowestError_[currentNeighbourhood]) {
					//collectiveLowestError_ = errors[i];
					neighbourhoodLowestError_[currentNeighbourhood] = errors[i];
					//collectiveLowestErrorPosition_ = particles_[i].getPosition();
					neighbourhoodLowestErrorPosition_[currentNeighbourhood] = particles_[i].getPosition();
				}
			}

		}

		// gets the position of the global lowest error
		std::vector<double> getLowestErrorPosition() {
			std::vector<double> lowestErrorPosition;
			double error = INFINITY;
			for (unsigned int i = 0; i < neighbourhoods_; ++i) {
				if (neighbourhoodLowestError_[i] < error) {
					error = neighbourhoodLowestError_[i];
					lowestErrorPosition = neighbourhoodLowestErrorPosition_[i];
					//std::cout << "Neighbourhood " << i << ", error: " << error << std::endl;

				}
			}
			return lowestErrorPosition;
		}

	private:
		// upper bound of search space
		int upperBound_ = 0;
		// lower bound of search space
		int lowerBound_ = 0;
		// number of particles
		unsigned int numParticles_ = 1;
		// dimension of particles
		size_t dimension_ = 1;
		std::vector<pso::Particle> particles_;
		//std::vector<double> collectiveLowestErrorPosition_;
		// position of lowest error particle per neighbourhood
		std::vector<std::vector<double>> neighbourhoodLowestErrorPosition_;
		//double collectiveLowestError_ = INFINITY;
		// lowest error per neighbourhood
		std::vector<double> neighbourhoodLowestError_;
		// number of neighbourhoods (social neighbourhoods with an even number of particles each, if possible)
		unsigned int neighbourhoods_ = 10; // NOW NEIGHBOURHOODS DO NOT OVERLAP; FIX THIS LATER



	};

}
