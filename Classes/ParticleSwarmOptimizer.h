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
		void setBounds(double lb, double ub) {
			lowerBound_ = lb;
			upperBound_ = ub;
		}

		// initializes all particles
		void initialize();

		// run a single iteration where each particle is updated
		void update(std::vector<double> input, double targetValue);
		void updateMultiple(std::vector<std::vector<double>> inputs, std::vector<double> targetValues);

		// gets the position of the global lowest error
		std::vector<double> getLowestErrorPosition();

	private:
		// upper bound of search space
		double upperBound_ = 0;
		// lower bound of search space
		double lowerBound_ = 0;
		// number of particles
		unsigned int numParticles_ = 1;
		// dimension of particles
		size_t dimension_ = 1;
		std::vector<pso::Particle> particles_;
		// position of lowest error particle per neighbourhood
		std::vector<std::vector<double>> neighbourhoodLowestErrorPosition_;
		// lowest error per neighbourhood
		std::vector<double> neighbourhoodLowestError_;

		int neighboursPerSide_ = 0;

	};

}
