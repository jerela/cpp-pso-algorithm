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

double generateRandom(int lb, int ub) {
	int range = ub - lb;
	return ((double)(rand() % ((range * 1000 + 1))) / 1000 + lb);
}



void polynomialExample() {
	// determine inputs and true parameters

	std::vector<std::vector<double>> inputs;
	std::vector<double> targets;

	// Generate some inputs
	inputs.push_back(std::vector<double>{5, 1});
	inputs.push_back(std::vector<double>{5, 5});
	inputs.push_back(std::vector<double>{7, 23});
	inputs.push_back(std::vector<double>{8, 5});
	for (unsigned int i = 0; i < 100; ++i) {
		inputs.push_back({ generateRandom(-100.0,100.0) });
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

	// construct a PSO object
	pso::ParticleSwarmOptimizer PSO;
	PSO.optimizeParameters(inputs, targets, params_true.size());
	printVector(targets, "Targets");
}


void linearExample() {
	// determine inputs and true parameters

	std::vector<std::vector<double>> inputs;
	std::vector<double> targets;

	// Generate some inputs
	inputs.push_back(std::vector<double>{5});
	inputs.push_back(std::vector<double>{23});
	inputs.push_back(std::vector<double>{8});
	for (unsigned int i = 0; i < 100; ++i) {
		inputs.push_back({ generateRandom(-100.0,100.0) });
	}

	// Define the parameters we are trying to estimate
	std::vector<double> params_true = {2, -3};

	// calculate target values from input and ground truth params
	// iterate through all data samples
	for (unsigned int i = 0; i < inputs.size(); ++i) {
		double currentTarget = params_true[0]*inputs[i][0] + params_true[1];
		targets.push_back(currentTarget);

	}

	// construct a PSO object
	pso::ParticleSwarmOptimizer PSO;
	PSO.optimizeParameters(inputs, targets, params_true.size());
	printVector(targets, "Targets");
}


int main()
{

	// Initialize RNG
	srand((unsigned int)time(NULL));

	std::cout << "### LINEAR EXAMPLE ### " << std::endl;
	linearExample();

	std::cout << "### POLYNOMIAL EXAMPLE ### " << std::endl;
	polynomialExample();

}
