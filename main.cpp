#include <iostream>
#include <ParticleSwarmOptimizer.h>
#include <math.h>
#include <time.h>
#include <string>

int main(int argc, char *argv[])
{

	// parse cmd line arguments
	unsigned int nParticles = std::stoi(argv[1]); // number of particles to use
	int lowerBound = std::stoi(argv[2]); // lower bound of search space
	int upperBound = std::stoi(argv[3]); // upper bound of search space

	// Initialize RNG
	srand(time(NULL));

	// determine inputs and true parameters
	std::vector<double> input = { 1, 2, 3, 4, 20 }; // TODO: read from file
	std::vector<double> params_true = { 2, -3, 6, 22, -15 };
	// calculate target values from input and ground turth params (TODO: read from file)
	double target = 0;
	for (unsigned int i = 0; i < input.size(); ++i) {
		target += params_true[i] * input[i];
	}

	// construct a PSO object
	pso::ParticleSwarmOptimizer PSO;

	// dimension of particles is the number of parameters
	auto dim = params_true.size();
	
	// set values for PSO
	PSO.setDimension(dim);
	PSO.setNumParticles(nParticles);
	PSO.setBounds(lowerBound, upperBound);
	PSO.initialize();

	// initialize error to inf
	double err = INFINITY;

	// if error is below this threshold, iterations stop
	double threshold = 1e-5;

	// if this number of iterations have passed, iterations stop
	unsigned int maxEpochs = 100;
	unsigned int epoch = 1;

	// loop while error is above a threshold or maximum number of iterations have not passed
	while (err > threshold) {

		// update particle positions
		PSO.update(input, target);

		// get estimated parameters as the position corresponding to global lowest error
		std::vector<double> params_estimated = PSO.getLowestErrorPosition();
		std::cout << "Parameters:" << std::endl;
		for (unsigned int i = 0; i < params_estimated.size(); ++i) {
			std::cout << params_estimated[i] << std::endl;

		}

		// calculate an estimate of the output value to calculate error
		double estimate = 0;
		for (unsigned int i = 0; i < input.size(); ++i) {
			estimate += params_estimated[i] * input[i];
		}
		std::cout << "Target value: " << target << ", current value: " << estimate << std::endl;

		err = abs(target - estimate);

		std::cout << std::endl;

		epoch += 1;
		if (epoch > maxEpochs){
			break;
		}
	
	}

}
