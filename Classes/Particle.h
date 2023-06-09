#pragma once

#include <vector>
#include <time.h>
#include <math.h>

namespace pso {

	class Particle {

	public:

		// constructor
		Particle(size_t dim, int lb, int ub, unsigned int neighbourhood) {
			
			// set dimension of particle
			dimension_ = dim;

			upperBound_ = ub;
			lowerBound_ = lb;

			currentPosition_ = std::vector<double>(dimension_);
			velocity_ = std::vector<double>(dimension_);
			lowestErrorPosition_ = std::vector<double>(dimension_);

			neighbourhood_ = neighbourhood;

			// generate random starting position in the given search space and initialize other vectors to 0
			randomizePosition();

		};
		//~Particle();

		// (re)initialize particle position randomly; TODO: RANDOMISE ENTIRE NEIGHBOURHOOD IF IT HAS A HIGH ERROR
		void randomizePosition() {
			if (verbose_)
				std::cout << "Initialized particle at ";
			for (unsigned int i = 0; i < dimension_; ++i) {
				//currentPosition_[i] = ((double)(rand() % (range+1)) + lb);
				currentPosition_[i] = generateRandomNumber(lowerBound_, upperBound_);
				if (verbose_)
					std::cout << currentPosition_[i] << " ";
				velocity_[i] = 0;
				lowestErrorPosition_[i] = 0;

			}

			if (verbose_)
				std::cout << std::endl;
		}

		unsigned int getNeighbourhood() { return neighbourhood_; }

		// gets the position of lowest error so far for this particle
		std::vector<double> getLowestErrorPosition() { return lowestErrorPosition_; }

		// gets the current position for this particle
		std::vector<double> getPosition() { return currentPosition_; }

		// updates the particle's velocity and current position
		double update(std::vector<double> collectiveLowestErrorPosition, double targetValue, std::vector<double> input) {

			// generate random factors for velocity changes
			double randomFactorIndividual = generateRandomNumber(0, 1); //((double)(rand() % 101) / 100);
			double randomFactorCollective = generateRandomNumber(0, 1); //((double)(rand() % 101) / 100);
			//std::cout << "random number: " << randomFactorIndividual << std::endl;

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
				updatesSinceMinimum = 0;
			}
			else {
				updatesSinceMinimum += 1;
			}

			// give the particle a slight chance to be reinitialized each run; it is more likely when the particle hasn't reduced its error in a while
			if (generateRandomNumber(0, 1) < 0.001*updatesSinceMinimum) {
				randomizePosition();
			}

			return lowestError_;
			
		}

	private:
		// whether to print information to console
		bool verbose_ = false;
		// factors for weighting the importance of momentum, particle-specific lowest error position, and neighbourhood-specific lowest error position
		double a_ = 0.4;
		double b_ = 0.3;
		double c_ = 0.3;
		// dimension of this particle
		size_t dimension_ = 1;
		// position of lowest error so far
		std::vector<double> lowestErrorPosition_;
		// amount of lowest error so far
		double lowestError_ = INFINITY;
		// velocity of particle
		std::vector<double> velocity_;
		// position of particle
		std::vector<double> currentPosition_;
		// the neighbourhood this particle belongs to
		unsigned int neighbourhood_ = 0;
		// upper bound of search space when initializing particle position
		int upperBound_ = 0;
		// lower bound of search space when initializing particle position
		int lowerBound_ = 0;
		// how many updates have passed since the last lowest error for this particle
		unsigned int updatesSinceMinimum = 0;
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

		// generate random numbers between lb and ub
		double generateRandomNumber(int lb, int ub) {
			int range = ub - lb;
			return ( (double)(rand() % ((range*1000 + 1)))/1000 + lb );
		}



	};

}
