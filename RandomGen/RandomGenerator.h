#pragma once

#include <cstdint>

namespace RG {
	class RandomGenerator {
		public:
			RandomGenerator();
			RandomGenerator(uint32_t seed_);
			uint32_t Generate();

		private:
			uint32_t F = 1, prevF = 1, seed = 1000000000;
	};
}