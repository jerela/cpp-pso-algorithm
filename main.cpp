#include <iostream>
#include <ParticleSwarmOptimizer.h>
#include <math.h>
#include <time.h>

int main()
{

	// Initialize RNG
	srand(time(NULL));

	std::vector<double> input = { 1, 2, 3, 4 };
	// a*x + b*y^2 + c*z

	std::vector<double>params_true = { 2, -3, 6, 22 };

	double target = 0;
	for (unsigned int i = 0; i < input.size(); ++i) {
		target += params_true[i] * input[i];
	}

	// determine parameters (weights) a,b,c

	pso::ParticleSwarmOptimizer PSO;


	auto dim = params_true.size();
	unsigned int nParticles = 20;
	PSO.setDimension(dim);
	PSO.setNumParticles(nParticles);
	PSO.initialize();

	PSO.setInput(input);
	PSO.setTargetValue(target);
	
	double diff = INFINITY;

	double threshold = 1.0;

	unsigned int maxEpochs = 100;
	unsigned int epoch = 1;

	while (diff > threshold) {
		PSO.update();

		std::vector<double> params_estimated = PSO.getLowestErrorPosition();
		std::cout << "Parameters:" << std::endl;
		for (unsigned int i = 0; i < params_estimated.size(); ++i) {
			std::cout << params_estimated[i] << std::endl;

		}


		double estimate = 0;
		for (unsigned int i = 0; i < input.size(); ++i) {
			estimate += params_estimated[i] * input[i];
		}
		std::cout << "Target value: " << target << ", current value: " << estimate << std::endl;

		diff = abs(target - estimate);

		std::cout << std::endl;

		epoch += 1;
		if (epoch > maxEpochs){
			break;
		}
	
	}

}
