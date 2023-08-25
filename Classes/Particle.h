#pragma once

#include <vector>
#include <time.h>
#include <math.h>
#include <iostream>
#include <random>

namespace pso {

	class Particle {

	public:

		// constructor
		Particle(size_t dim, double lb, double ub);
		//~Particle();

		// (re)initialize particle position randomly
		void randomizePosition();

		// gets the position of lowest error so far for this particle
		std::vector<double> getLowestErrorPosition() { return lowestErrorPosition_; }

		std::vector<double> getNeighbourhoodLowestErrorPosition() { return neighbourhoodLowestErrorPosition_; }

		double getNeighbourhoodLowestError() { return neighbourhoodLowestError_; }
		void setNeighbourhoodLowestErrorPosition(std::vector<double> position) { neighbourhoodLowestErrorPosition_ = position; }
		void setNeighbourhoodLowestError(double error) { neighbourhoodLowestError_ = error; }

		// gets the current position for this particle
		std::vector<double> getPosition() { return currentPosition_; }

		// updates the particle's velocity and current position
		double update(const double targetValue, const std::vector<double>& input);

		double updateMultiple(std::vector<double> collectiveLowestErrorPosition, std::vector<double> targetValues, std::vector<std::vector<double>> inputs);


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
		// upper bound of search space when initializing particle position
		double upperBound_ = 0;
		// lower bound of search space when initializing particle position
		double lowerBound_ = 0;
		// how many updates have passed since the last lowest error for this particle
		unsigned int updatesSinceMinimum_ = 0;
		// calculate error
		double evaluate(const double targetValue, const std::vector<double>& input);
		double evaluateMultiple(std::vector<double> targetValues, std::vector<std::vector<double>> inputs);

		// generate random numbers between lb and ub
		double generateRandomNumber(int lb, int ub);

		std::vector<double> neighbourhoodLowestErrorPosition_;
		double neighbourhoodLowestError_ = INFINITY;

	};

}
