#pragma once

#include <vector>
#include <time.h>
#include <math.h>

namespace pso {

	class Particle {

	public:
		Particle(unsigned int dim) {
			

			dimension_ = dim;

			currentPosition_ = std::vector<double>(dimension_);
			velocity_ = std::vector<double>(dimension_);
			lowestErrorPosition_ = std::vector<double>(dimension_);


			int range = 100;
			std::cout << "Initialized particle at ";
			for (unsigned int i = 0; i < dim; ++i) {
				currentPosition_[i] = ((double)(rand() % (range+1)) - ((double)range/2));
				std::cout << currentPosition_[i] << " ";
				velocity_[i] = 0;
				lowestErrorPosition_[i] = 0;

			}
			std::cout << std::endl;

		};
		//~Particle();

		std::vector<double> getLowestErrorPosition() { return lowestErrorPosition_; }

		std::vector<double> getPosition() { return currentPosition_; }

		double update(std::vector<double> collectiveLowestErrorPosition, double targetValue, std::vector<double> input) {

			double randomFactorIndividual = ((double)(rand() % 101) / 100);
			double randomFactorCollective = ((double)(rand() % 101) / 100);


			// update each dimension of direction
			for (unsigned int i = 0; i < velocity_.size(); ++i) {
				// update velocity
				velocity_[i] = a * velocity_[i] + b * randomFactorIndividual * (lowestErrorPosition_[i] - currentPosition_[i]) + c * randomFactorCollective * (collectiveLowestErrorPosition[i] - currentPosition_[i]);

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
		double a = 0.4;
		double b = 0.3;
		double c = 0.3;
		unsigned int dimension_ = 1;
		std::vector<double> lowestErrorPosition_;
		double lowestError_ = INFINITY;
		std::vector<double> velocity_;;
		std::vector<double> currentPosition_;;


		double evaluate(double targetValue, std::vector<double> input) {
			double result = 0;
			for (unsigned int i = 0; i < input.size(); ++i) {
				result += currentPosition_[i] * input[i];
			}

			double error = abs(result - targetValue);
			std::cout << "POS: ";
			for (unsigned int i = 0; i < input.size(); ++i) {
				std::cout << currentPosition_[i] << " ";
			}
			std::cout << "ERROR: " << error << std::endl;

			return error;
		}
	};

}
