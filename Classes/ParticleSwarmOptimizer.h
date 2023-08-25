#pragma once

#include <vector>
#include <Particle.h>
#include <math.h>

namespace pso {

	class ParticleSwarmOptimizer {

	public:
		//ParticleSwarmOptimizer();
		//~ParticleSwarmOptimizer();

		// launch the optimization algorithm
		void optimizeParameters(const std::vector<std::vector<double>>& inputs, const std::vector<double>& targets, size_t dim, double lowerBound = -100, double upperBound = 100, unsigned int nParticles = 200, unsigned int maxEpochs = 1000, double threshold = 1e-5);
		
	private:
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
		void update(const std::vector<double>& input, const double targetValue);

		// gets the position of the global lowest error
		std::vector<double> getLowestErrorPosition();

		// upper bound of search space
		double upperBound_ = 0;
		// lower bound of search space
		double lowerBound_ = 0;
		// number of particles
		unsigned int numParticles_ = 0;
		// dimension of particles
		size_t dimension_ = 1;
		// container for particles
		std::vector<pso::Particle> particles_;

		// how many neighbours a particle should have on each side (social ring neighbours configuration)
		int neighboursPerSide_ = 0;


	};

}
