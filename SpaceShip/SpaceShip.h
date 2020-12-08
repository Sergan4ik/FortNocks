#pragma once
#include <fstream>
#include "Constats.h"

namespace SpaceS {
	class Gold {
	public:
		Gold(long double x_, long double y_, long double z_);
		Gold(long double x_, long double y_, long double z_ , bool fl);
		long double volume();
		long double weight();
		~Gold();
	public:
		long double x, y, z;
		long double L, ro;
		long double c , meltT = 1064 , curT = 300;
		std::ofstream out;
	};
	class SpaceShip {
		public:
			SpaceShip(long double cur_en, long double min_en, long double bbl_volume , int w_w , int w_h);
			
			bool PutGold(Gold& ingot , std::string DemoType);

			bool RotateIngot(Gold& ingot);

			long double GetCutScale(Gold& ingot);

			bool Melt(Gold& ingot);

			double MeltInfo(Gold& ingot) ;

			void ShowShipStatus();

			~SpaceShip();
		private:
			struct DataForMelt {
				DataForMelt(SpaceShip& ship, Gold& ingot);
				long double recuperation_en;
				long double need_en_before_melt;
				long double energy_for_melt;
				long double energy_for_cut;
			};

			bool CheckIngotSize(Gold& ingot);

			long double current_energy, min_energy;
			long double bubble_volume;
			int window_height, window_width;
			long double summary_volume = 0;
			long double recuperation = RECUPERATION_COOF; // coof of recuperation
			long double cut_coef = CUT_COEF; // coof for cut , energy_for_cut = cut_coef * (ingot.x * ingot.y)
		public:
			bool Ability_to_take_gold = true;
			std::ofstream out;
	};
}