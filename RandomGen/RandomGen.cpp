#include "RandomGenerator.h"
//#include "pch.h"

namespace RG{
	RandomGenerator::RandomGenerator() {}
	RandomGenerator::RandomGenerator(uint32_t seed_): 
		seed(seed_) {}

	uint32_t RandomGenerator::Generate() {
		F += prevF;
		prevF = F - prevF;
		return F % seed;
	}
}