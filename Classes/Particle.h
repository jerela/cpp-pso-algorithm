#pragma once

#include <vector>
#include <time.h>
#include <math.h>

namespace pso {

	class Particle {

	public:

		// constructor
		Particle(size_t dim, int lb, int ub) {
			
			// set dimension of particle
			dimension_ = dim;

			currentPosition_ = std::vector<double>(dimension_);
			velocity_ = std::vector<double>(dimension_);
			lowestErrorPosition_ = std::vector<double>(dimension_);


			// generate random starting position in the given search space and initialize other vectors to 0
			int range = ub - lb;
			if (verbose_)
				std::cout << "Initialized particle at ";
			for (unsigned int i = 0; i < dim; ++i) {
				currentPosition_[i] = ((double)(rand() % (range+1)) + lb);
				if (verbose_)
					std::cout << currentPosition_[i] << " ";
				velocity_[i] = 0;
				lowestErrorPosition_[i] = 0;

			}
			if (verbose_)
				std::cout << std::endl;

		};
		//~Particle();

		// gets the position of lowest error so far for this particle
		std::vector<double> getLowestErrorPosition() { return lowestErrorPosition_; }

		// gets the current position for this particle
		std::vector<double> getPosition() { return currentPosition_; }

		// updates the particle's velocity and current position
		double update(std::vector<double> collectiveLowestErrorPosition, double targetValue, std::vector<double> input) {

			// generate random factors for velocity changes
			double randomFactorIndividual = ((double)(rand() % 101) / 100);
			double randomFactorCollective = ((double)(rand() % 101) / 100);


			// update each dimension of direction
			for (unsigned int i = 0; i < velocity_.size(); ++i) {
				// update velocity
				velocity_[i] = a_ * velocity_[i] + b_ * randomFactorIndividual * (lowestErrorPosition_[i] - currentPosition_[i]) + c_ * randomFactorCollective * (collectiveLowestErrorPosition[i] - currentPosition_[i]);

				// update position
				currentPosition_[i] = currentPosition_[i] + velocity_[i];
				
			}

			// evaluate error in new position
			double error = evaluate(targetValue, input);
			if (error < lowestError_) {
				lowestError_ = error;
				lowestErrorPosition_ = currentPosition_;
			}

			return lowestError_;
			
		}

	private:
		bool verbose_ = false; // whether to print information to console
		double a_ = 0.4;
		double b_ = 0.3;
		double c_ = 0.3;
		size_t dimension_ = 1;
		std::vector<double> lowestErrorPosition_;
		double lowestError_ = INFINITY;
		std::vector<double> velocity_;;
		std::vector<double> currentPosition_;;
		
		// calculate error
		double evaluate(double targetValue, std::vector<double> input) {
			double result = 0;
			for (unsigned int i = 0; i < input.size(); ++i) {
				result += currentPosition_[i] * input[i];
			}

			double error = abs(result - targetValue);
			
			if (verbose_) {
				std::cout << "POSITION: ";
				for (unsigned int i = 0; i < input.size(); ++i) {
					std::cout << currentPosition_[i] << " ";
				}
				std::cout << "ERROR: " << error << std::endl;
			}
			
			return error;
		}
	};

}
