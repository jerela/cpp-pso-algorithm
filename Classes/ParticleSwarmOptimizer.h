#pragma once

#include <vector>
#include <Particle.h>
#include <math.h>

namespace pso {

	class ParticleSwarmOptimizer {

	public:
		//ParticleSwarmOptimizer();
		//~ParticleSwarmOptimizer();

		void optimizeParameters(const std::vector<std::vector<double>>& inputs, const std::vector<double>& targets, size_t dim, double lowerBound = -100, double upperBound = 100, unsigned int nParticles = 200, unsigned int maxEpochs = 1000, double threshold = 1e-5);


		void setInputs(std::vector<std::vector<double>> inputs) { inputs_ = inputs; }
		void setTargets(std::vector<double> targets) { targets_ = targets; }
		

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
		void updateMultiple(std::vector<std::vector<double>> inputs, std::vector<double> targetValues);

		// gets the position of the global lowest error
		const std::vector<double> getLowestErrorPosition();


		// upper bound of search space
		double upperBound_ = 0;
		// lower bound of search space
		double lowerBound_ = 0;
		// number of particles
		unsigned int numParticles_ = 0;
		// dimension of particles
		size_t dimension_ = 1;
		std::vector<pso::Particle> particles_;

		int neighboursPerSide_ = 0;

		std::vector<std::vector<double>> inputs_;
		std::vector<double> targets_;
		size_t nParameters_ = 0;

	};

}
