#include <iostream>
#include <ParticleSwarmOptimizer.h>
#include <math.h>
#include <time.h>
#include <string>

#include <algorithm>
#include <random>

template <class anyType>
void printVector(std::vector<anyType> vec, std::string label) {
	std::cout << label << ": ";
	for (unsigned int i = 0; i < vec.size(); ++i) {
		std::cout << vec[i];
		if (i < vec.size() - 1) {
			std::cout << ", ";
		}
	}
	std::cout << std::endl;
}

std::vector<double> estimateParameters(std::vector<std::vector<double>> inputs, std::vector<double> targets, size_t dim, double lowerBound = -100, double upperBound = 100, unsigned int nParticles = 200, unsigned int maxEpochs = 1000, double threshold = 1e-5) {

	auto rng = std::default_random_engine{};

	std::vector<size_t> indices;
	for (unsigned int i = 0; i < inputs.size(); ++i) {
		indices.push_back(i);
	}

	size_t nSamples = targets.size();

	// construct a PSO object
	pso::ParticleSwarmOptimizer PSO;

	// dimension of particles is the number of parameters
	size_t inputSize = inputs[0].size();

	// set values for PSO
	PSO.setDimension(dim);
	PSO.setNumParticles(nParticles);
	PSO.setBounds(lowerBound, upperBound);
	PSO.initialize();

	unsigned int epoch = 1;

	std::vector<double> estimatedParams;

	double bestError = INFINITY;
	std::vector<double> bestParams;

	double err = 0;

	// for each epoch
	for (unsigned int currentEpoch = 0; currentEpoch < maxEpochs; ++currentEpoch) {

		// shuffle indices so that data samples are picked in a random order when updating particles
		std::shuffle(std::begin(indices), std::end(indices), rng);

		// initialize the error sum of all data samples to 0
		err = 0;
	
		// calculate error over all inputs and targets at once

		// iterate through all data samples to update parameters
		for (unsigned int i = 0; i < inputs.size(); ++i) {
			std::vector<double> currentInput = inputs[indices[i]];
			double currentTarget = targets[indices[i]];
			PSO.update(currentInput, currentTarget);
		}
		//PSO.updateMultiple(inputs, targets);

		// get estimated parameters as the position corresponding to global lowest error
		estimatedParams = PSO.getLowestErrorPosition();
			
		// iterate through all data samples to calculate error in target value
		for (unsigned int i = 0; i < inputs.size(); ++i) {
			std::vector<double> currentInput = inputs[indices[i]];
			double currentTarget = targets[indices[i]];
				

			// calculate an estimate of the output value to calculate error
			double estimatedTarget = 0;
			for (unsigned int j = 0; j < inputSize; ++j) {
				estimatedTarget += estimatedParams[j] * currentInput[j];
			}

			err += abs(currentTarget - estimatedTarget);

		}
		err = err / inputs.size();

		std::cout << "Epoch " << currentEpoch << ", mean error over all inputs: " << err << std::endl;

		if (err < bestError) {
			bestError = err;
			bestParams = estimatedParams;
		}

		epoch += 1;
		if (epoch > maxEpochs) {
			break;
		}

		if (err < threshold) {
			break;

		}

	} // end iteration through epochs

	std::cout << "Best mean error: " << bestError << std::endl;
	printVector(bestParams, "Best parameters considering mean error");

	std::cout << "Final error: " << err << std::endl;
	printVector(estimatedParams, "Final params: ");

	return bestParams;
}


int main()
{

	// Initialize RNG
	srand((unsigned int)time(NULL));

	// determine inputs and true parameters

	std::vector<std::vector<double>> inputs;
	std::vector<double> targets;

	// Generate some inputs
	inputs.push_back(std::vector<double>{5, 1});
	inputs.push_back(std::vector<double>{5, 5});
	inputs.push_back(std::vector<double>{7, 23});
	inputs.push_back(std::vector<double>{8, 5});
	for (unsigned int i = 0; i < 100; ++i) {
		inputs.push_back(std::vector<double>{((double)(rand() % (((5+5) * 1000 + 1))) / 1000 + 5), ((double)(rand() % (((5 + 5) * 1000 + 1))) / 1000 + 5)});
	}

	// Define the parameters we are trying to estimate
	std::vector<double> params_true = { 2, 3 };

	// calculate target values from input and ground truth params (TODO: read from file)
	// iterate through all data samples
	for (unsigned int i = 0; i < inputs.size(); ++i) {
		double currentTarget = 0;
		std::vector<double> currentInput = inputs[i];
		// iterate through all elements in the current sample
		for (unsigned int j = 0; j < currentInput.size(); ++j) {
			currentTarget += params_true[j] * currentInput[j];
		}
		targets.push_back(currentTarget);
		
	}

	std::vector<double> params = estimateParameters(inputs, targets, params_true.size());
	printVector(params, "Parameters");
	printVector(targets, "Targets");

}
