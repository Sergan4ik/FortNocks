#include "SpaceShip.h"
#include <stdlib.h>
#include <time.h>
#include <cmath>
#include <iostream>
#include <string>

#define LOG(msg) std::cout << msg << std::endl

namespace SpaceS {
	
	Gold::Gold(double x_, double y_, double z_):
		x(x_) , y(y_) , z(z_)
	{
		srand(time(NULL));
		double eps = pow((-1), rand() % 2) * (rand() % 5) + 1;
		ro = 19.3 + (eps / 100) * 19.3;
		L = 66.2 + (eps / 100) * 66.2;
		c = 0.130 + (eps / 100) * 0.130;
		LOG("New ingot's parametrs:");
		LOG("Width: " + std::to_string((int)x));
		LOG("Height: " + std::to_string((int)y));
		LOG("Length: " + std::to_string((int)z));
		LOG("Other params: C = " + std::to_string(c) + ", L = " + std::to_string(L) + " ro: " + std::to_string(ro));
		LOG("------------------------------------------------------------");
	}

	double Gold::volume() {
		return x * y * z;
	}

	double Gold::weight() {
		return volume() * ro;
	}

	SpaceShip::SpaceShip(double cur_en, double min_en, double bbl_volume, int w_w, int w_h):
		current_energy(cur_en) , min_energy(min_en) , bubble_volume(bbl_volume) , window_height(w_h) , window_width(w_w)
	{}

	bool SpaceShip::PutGold(Gold ingot) {
		if (CheckIngotSize(ingot)) {
			LOG("Ingot wasn't turned/spinned , put to bubble");
			return true;
		}

		//spin ingot

		std::swap(ingot.x, ingot.y);
		if (CheckIngotSize(ingot)) {
			LOG("Spin ingot, and put to bubble");
			return true;
		}

		// return size
		std::swap(ingot.x, ingot.y);
		//

		//turn ingot
		std::swap(ingot.x, ingot.z);
		if (CheckIngotSize(ingot)) {
			LOG("Turn ingot, and put to bubble");
			return true;
		}
		//
		
		// turn + rotate
		std::swap(ingot.x , ingot.y);
		if (CheckIngotSize(ingot)) {
			LOG("Turn + Rotate ingot, and put to bubble");
			return true;
		}
		
		LOG("Ingot is invalid. Drop out");
		return false;
	}

	bool SpaceShip::CheckIngotSize(Gold ingot) {
		// ingot.x <= window.width , ingot.y <= window.height
		return ingot.x <= window_width && ingot.y <= window_height;
	}
}