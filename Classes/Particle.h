#pragma once

#include <vector>

namespace pso {

	class Particle {

	public:
		PSOParticle() {
			// Initialize RNG
			srand(time(NULL));
		};
		~PSOParticle();

		std::vector<double> getLowestErrorPosition() { return lowestErrorPosition_; }

		std::vector<double> getPosition() { return currentPosition_; }

		double update(std::vector<double> collectiveLowestErrorPosition) {

			double randomFactorIndividual = ((double)(rand() % 101) / 100);
			double randomFactorCollective = ((double)(rand() % 101) / 100);


			// update each dimension of direction
			for (unsigned int i = 0; i < velocity_.size(); ++i) {
				// update velocity
				velocity_[i] = a * velocity_[i] + b * randomFactorIndividual * (lowestErrorPosition_[i] - currentPosition_[i]) + c * randomFactorCollective * (collectiveLowestErrorPosition[i] - currentPosition_[i]);

				// update position
				currentPosition_[i] = currentPosition_[i] + velocity_[i]
				
			}

			// evaluate error in new position
			double error = evaluate(currentPosition_);
			if (error < lowestError_) {
				lowestError_ = error;
			}

			return lowestError_;
			
		}

	private:
		double a = 0.4;
		double b = 0.3;
		double c = 0.3;
		unsigned int dimension_ = 1;
		std::vector<double> lowestErrorPosition_(dimension_);
		double lowestError_ = evaluate(lowestErrorPosition_);
		std::vector<double> velocity_(dimension_);
		std::vector<double> currentPosition_(dimension_);


		double evaluate(std::vector<double> position);
	};

}
