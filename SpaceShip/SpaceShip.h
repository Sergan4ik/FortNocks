#pragma once

namespace SpaceS {
	class Gold {
	public:
		Gold(double x_, double y_, double z_);
		double volume();
		double weight();
	public:
		double x, y, z;
		double L, ro;
		double c;
	};
	class SpaceShip {
		public:
			SpaceShip(double cur_en, double min_en, double bbl_volume , int w_w , int w_h);
			
			bool PutGold(Gold ingot);



			void ChangeBubble();
			         
		private:
			bool CheckIngotSize(Gold ingot);

			double current_energy, min_energy;
			int bubbles_cnt = 0;
			double bubble_volume;
			int window_height, window_width;
			double summary_volume = 0;
	};
}