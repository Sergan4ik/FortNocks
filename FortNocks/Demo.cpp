#include <iostream>
#include "RandomGenerator.h"	
#include "SpaceShip.h"
#include <array>
#include <fstream>

using namespace std;
using namespace RG;
using namespace SpaceS;

ofstream out;

void RandomDemonstate(RandomGenerator& Generator) {
	long double en = 10000LL + Generator.Generate() , min_en = Generator.Generate() , bbl = Generator.Generate() % 1'000;
	int w_w = 5 + (Generator.Generate() % 10), w_h = 5 + (Generator.Generate() % 30);
	if (en < min_en)
		swap(en, min_en);
	SpaceShip ship(en, min_en, bbl, w_w, w_h);
	double x = 1LL + (double)(Generator.Generate() % 20), y = 1LL + (double)(Generator.Generate() % 20), z = 1LL + (double)(Generator.Generate() % 20);
	do{
		Gold ingot(x, y, z);
		ship.PutGold(ingot , "Random");
		x = 1LL + (double)(Generator.Generate() % 20);
		y = 1LL + (double)(Generator.Generate() % 20);
		z = 1LL + (double)(Generator.Generate() % 20);
	} while (ship.Ability_to_take_gold);
	cout << "Random Demo is end" << endl;
}

void CustomDemonstate() {
	cout << "Units see at GitHub repository's description , link -> https://github.com/Sergan4ik/FortNocks" << endl << endl;
	cout << "Input ship params (Energy | Energy for return home | Max bubble volume | Window width/height)" << endl;
	array <double, 5> Ship_params;
	for (auto& i : Ship_params)
		cin >> i;

	SpaceShip ship(Ship_params[0], Ship_params[1], Ship_params[2], (int)Ship_params[3], (int)Ship_params[4]);

	do {
		cout << "Input ingot parametrs (Width , Height , Lenght)" << endl;
		long double x, y, z;
		cin >> x >> y >> z;
		Gold ingot(x, y, z);
		ship.PutGold(ingot , "Custom");
	} while (ship.Ability_to_take_gold);

	cout << "Custom demo is end" << endl;
}

enum class DemonstrationTokens {
	RANDOM, CUSTOM , INVALID , EXIT
};

DemonstrationTokens GetToken(string s) {
	if (s == "Random")
		return DemonstrationTokens::RANDOM;
	if (s == "Custom")
		return DemonstrationTokens::CUSTOM;
	if (s == "Exit")
		return DemonstrationTokens::EXIT;
	return DemonstrationTokens::INVALID;
}

int main() {

	RandomGenerator Generator(100'000'000);
	string demo_type;
	cout << "For select how to demo Lab with Random data/Custom data , input Random/Custom" << endl;
	
	while (cin >> demo_type) {
		system("cls");
		DemonstrationTokens demo_token = GetToken(demo_type);
		switch (demo_token)
		{
		case DemonstrationTokens::RANDOM:
			RandomDemonstate(Generator);
			break;
		case DemonstrationTokens::CUSTOM:
			CustomDemonstate();
			break;
		case DemonstrationTokens::INVALID:
			cout << "Type of demo is invalid, input again " << endl;
			break;
		case DemonstrationTokens::EXIT:
			cout << "Program end";
			return 0;
		default:
			break;
		}
	}

	
}