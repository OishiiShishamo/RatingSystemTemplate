#pragma once
#ifndef RATING_SYSTEM_TEMPLATE_RATE_H
#define RATING_SYSTEM_TEMPLATE_RATE_H

#include <algorithm>
#include <array>
#include <fstream>
#include <utility>
#include <vector>

constexpr size_t kRateNum = 25;

class Rate {
public:
	void AddRate(long long id, double rate) {
		int min_index = INT_MAX;
		double min_rate = -1;
		auto itr = std::find(rates_.begin(), rates_.end(), std::pair(id, rate));
		if (itr != rates_.end()) {
			(*itr).second = std::max((*itr).second, rate);
			return;
		}
		for (int i = 0; i < kRateNum; i++) {
			if (min_rate == -1) {
				min_rate = rates_[i].second;
				min_index = i;
			}
			if (min_rate > rates_[i].second) {
				min_rate = rates_[i].second;
				min_index = i;
			}
		}
		if (rates_[min_index].second < rate) {
			rates_[min_index] = std::make_pair(id, rate);
		}
	}

	double GetRate() {
		std::vector<double> rate_tmp;
		for (const auto& x : rates_) {
			rate_tmp.emplace_back(x.second);
		}
		std::sort(rate_tmp.rbegin(), rate_tmp.rend());
		double tmp = 0;
		for (int i = 0; i < kRateNum; i++) {
			tmp += rate_tmp.at(i);
		}
		tmp /= kRateNum;
		return tmp;
	}

	void Save(std::ofstream& ofs) const {
		ofs.write(reinterpret_cast<const char*>(&rates_), sizeof(rates_));
	}

	void Load(std::ifstream& ifs) {
		ifs.read(reinterpret_cast<char*>(&rates_), sizeof(rates_));
	}
private:
	std::array<std::pair<long long, double>, 25> rates_;
};

#endif  // RATING_SYSTEM_TEMPLATE_RATE_H