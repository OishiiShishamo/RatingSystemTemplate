#include <algorithm>
#include <array>
#include <cmath>
#include <fstream>
#include <iostream>
#include <string>
#include <utility>
#include <vector>

#include "rate.h"

// example.
int main() {
	std::cout << "Hello." << std::endl << "This Program is Rating System Template v0.1" << std::endl << "Now Loading." << std::endl;
	Rate rate_;
	std::ifstream ifs("save.rate", std::ios::binary);
	rate_.Load(ifs);
	ifs.close();
	while (1) {
		std::cout << "What do you do?(1.Add Rate 2.Show Rate 3.Save Rate 4.Exit)> ";
		int input = 0;
		std::cin >> input;
		switch (input) {
		case 1:
		{
			long long id = 0;
			double rate = 0;
			std::cout << "ID> ";
			std::cin >> id;
			std::cout << "Rate> ";
			std::cin >> rate;
			rate_.AddRate(id, rate);
			break;
		}
		case 2:
		{
			std::cout << rate_.GetRate() << std::endl;;
			break;
		}
		case 3:
		{
			std::ofstream ofs("save.rate", std::ios::binary);
			rate_.Save(ofs);
			ofs.close();
			break;
		}
		case 4:
		{
			std::cout << "Good bye." << std::endl;
			return 0;
		}
		}
	}
	return 0;
}