#include "SpaceShip.h"
#include <stdlib.h>
#include <time.h>
#include <cmath>
#include <iostream>
#include <string>
#include <vector>
#include <utility>

#define EPS 10e-6

#define LOG(msg) std::cerr << msg << std::endl

namespace SpaceS {
	
	Gold::Gold(long double x_, long double y_, long double z_):
		x(x_) , y(y_) , z(z_)
	{
		srand(time(NULL));
		long double eps = pow((-1), rand() % 2) * (rand() % 5) + 1;
		ro = 19.3 + (eps / 100) * 19.3;
		L = 66.2 + (eps / 100) * 66.2;
		c = 0.130 + (eps / 100) * 0.130;
		LOG("------------------------------------------------------------");
		LOG("New ingot's parametrs:");
		LOG("Width: " + std::to_string((int)x));
		LOG("Height: " + std::to_string((int)y));
		LOG("Length: " + std::to_string((int)z));
		LOG("Other params: C = " + std::to_string(c) + ", L = " + std::to_string(L) + " ro: " + std::to_string(ro));
		LOG("------------------------------------------------------------");
	}

	Gold::Gold(long double x_, long double y_, long double z_, bool fl)
		:x(x_), y(y_), z(z_)
	{
		srand(time(NULL));
		long double eps = pow((-1), rand() % 2) * (rand() % 5) + 1;
		ro = 19.3 + (eps / 100) * 19.3;
		L = 66.2 + (eps / 100) * 66.2;
		c = 0.130 + (eps / 100) * 0.130;
	}

	long double Gold::volume() {
		return x * y * z;
	}

	long double Gold::weight() {
		return volume() * ro;
	}

	SpaceShip::SpaceShip(long double cur_en, long double min_en, long double bbl_volume, int w_w, int w_h):
		current_energy(cur_en) , min_energy(min_en) , bubble_volume(bbl_volume) , window_height(w_h) , window_width(w_w)
	{
		LOG(""); // new line
		LOG("New ship created with next params");
		LOG("ooooooooooooooooooooooooooooooooooooooooooooooooo");

		LOG("Current energy: " + std::to_string(current_energy));
		LOG("Energy for go home: " + std::to_string(min_energy));
		LOG("Max volume of gold in bubble: " + std::to_string(bubble_volume));
		LOG("Window size W/H : " + std::to_string(window_width) + "/" + std::to_string(window_height));

		LOG("ooooooooooooooooooooooooooooooooooooooooooooooooo");

	}
	


	bool SpaceShip::PutGold(Gold& ingot) {
		if (!Ability_to_take_gold) {
			LOG("We can't tale gold");
			return false;
		}

		if (!RotateIngot(ingot))
			return false;
		
		long double scale = GetCutScale(ingot);

		LOG("We will melt " + std::to_string((scale * 100)) + " % of this ingot");

		ingot.z *= scale;
		if (Melt(ingot)) {
			if (current_energy - min_energy <= EPS) {
				LOG("We can't take gold anymore , no enough energy");
			}
			else {
				LOG("We can't take gold anymore , no enough space in bubble");
			}
			Ability_to_take_gold = false;
		}
		
		ShowShipStatus();
		return true;
	}

	bool SpaceShip::RotateIngot(Gold& ingot) {
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
		
		// turn + spin
		std::swap(ingot.x , ingot.y);
		if (CheckIngotSize(ingot)) {
			LOG("Turn + Spin ingot, and put to bubble");
			return true;
		}
		
		LOG("Ingot is invalid. Drop out");
		return false;
	}

	// get scale for melt ingot: ingot.z = ingot.z * (result of func)
	long double SpaceShip::GetCutScale(Gold& ingot) {

		// do we need to cut ingot because not enough volume
		long double  volume_scale;

		DataForMelt energy(*this , ingot);
		
		// do we need to cut ingot because not enough energy
		long double energy_scale;

		//if we can melt and after recuperation go home , melt
		if ((current_energy - min_energy) - (energy.energy_for_melt + energy.need_en_before_melt) >= 0 &&
			(current_energy - min_energy) - (energy.energy_for_melt + energy.need_en_before_melt) + energy.recuperation_en >= min_energy) {
			energy_scale = 1;
		}

		// if we need to cut ingot , waste energy for it 
		if (std::min(volume_scale, energy_scale) != 1) {
			if (current_energy - energy.energy_for_cut >= 0)
				current_energy -= energy.energy_for_cut;
		}
		
		energy_scale = std::min((current_energy - min_energy) / (energy.need_en_before_melt + energy.energy_for_melt), (long double)1);

		volume_scale = std::min((bubble_volume - summary_volume) / (ingot.volume()), (long double)1);

		return std::min(volume_scale , energy_scale);
	}

	bool SpaceShip::Melt(Gold& ingot){
		// returning ability to take more ingots
		DataForMelt energy(*this , ingot);
		summary_volume += ingot.volume();
		current_energy -= (energy.energy_for_melt + energy.need_en_before_melt);
		current_energy += energy.recuperation_en;
		LOG("Energy wasted for melt: " + std::to_string(energy.energy_for_melt + energy.need_en_before_melt));
		LOG("Recuperated energy: " + std::to_string(energy.recuperation_en));
		return (current_energy - min_energy <= EPS || std::abs(bubble_volume - summary_volume) <=EPS);
	}

	double SpaceShip::MeltInfo(Gold& ingot){
		DataForMelt energy(*this, ingot);
		return (energy.energy_for_melt + energy.need_en_before_melt) + energy.recuperation_en;
	}

	void SpaceShip::ShowShipStatus(){
		//just ship status
		LOG(""); // new line
		LOG("/////////////////////////////////////////////////");
		
		LOG("Current ship status");

		LOG("Current energy: " + std::to_string(current_energy));
		LOG("Energy for go home: " + std::to_string(min_energy));
		LOG("Current gold on ship: " + std::to_string(summary_volume));
		LOG("Max volume of gold in bubble: " + std::to_string(bubble_volume));

		LOG("/////////////////////////////////////////////////");
	}

	bool SpaceShip::CheckIngotSize(Gold& ingot) {
		// ingot.x <= window.width , ingot.y <= window.height
		return ingot.x <= window_width && ingot.y <= window_height;
	}

	SpaceShip::DataForMelt::DataForMelt(SpaceShip& ship, Gold& ingot) {
		recuperation_en      = ingot.c * ingot.weight() * (ingot.meltT - 4) * ship.recuperation;
		need_en_before_melt  = ingot.c * ingot.weight() * (ingot.meltT - ingot.curT);
		energy_for_melt      = ingot.L * ingot.weight();
		energy_for_cut		 = ship.cut_coef * (ingot.x * ingot.y);
	}

}