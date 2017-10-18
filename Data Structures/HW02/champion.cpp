#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <fstream>
#include "champion.h"

	Champion::Champion() {
		win = 0;
		lose = 0;
		miniondeath = 0;
	}

	Champion::Champion(std::string n, int team) {
		name = n;
		win = 0;
		lose = 0;
		if (team == 1) {
			win = 1;
		}

		if (team == 0) {
			lose = 1;
		}

		miniondeath = 0;
		std::vector<int> killtimes;
	std::vector<int> deathtimes;
	}

	std::string Champion::getName() const {
		return name;
	}

	int Champion::getWin() const {
		return win;
	}
	int Champion::getLose() const {
		return lose;
	}
	float Champion::getWinrate() const {
		float rate = ((float)win/((float)win+(float)lose));
		return rate;
	}
	int Champion::getMinion() const {
		return miniondeath;
	}

	void Champion::addWin() {
		win +=1;
	}

	void Champion::addLose() {
		lose +=1;
	}
	void Champion::addMinion() {
		miniondeath +=1;
	}

	//Adds event time to list of kills for this champion
	void Champion::killtime(int t) {
		killtimes.push_back(t);
	}

	//Adds event time to list of deaths
	void Champion::deathtime(int t) {
		deathtimes.push_back(t);
	}
	//For custom table:
	//Takes time of last event, divides match into 3 parts
	//Calculates KDR for individual parts by using time stamps
	//Prints appropriate output
	void Champion::dividematch(int t, std::ofstream &out_file) {
		int third = t;
		int second = t*2/3;
		int first = t/3;
		int firstKill = 0;
		int firstDeath = 0;
		int secondKill = 0;
		int secondDeath = 0;
		int thirdKill = 0;
		int thirdDeath = 0;
		float firstKDR;
		float secondKDR;
		float thirdKDR;
		std::string scaling;

		for (unsigned int i =0; i < killtimes.size(); i++) {
			if (killtimes[i] <= first) {firstKill+=1;}
			else if (killtimes[i] > first && killtimes[i] <= second) {secondKill+=1;}
			else if (killtimes[i] > second && killtimes[i] <= third) {thirdKill+=1;}
			
		}

		for (unsigned int i =0; i < deathtimes.size(); i++) {
			if (deathtimes[i] <= first) {firstDeath+=1;}
			else if (deathtimes[i] > first && deathtimes[i] <= second) {secondDeath+=1;}
			else if (deathtimes[i] > second && deathtimes[i] <= third) {thirdDeath+=1;}
		}

		if (firstDeath == 0) { firstKDR = firstKill;}
		else {firstKDR = (float)firstKill/(float)firstDeath;}

		
		if (secondDeath == 0) { secondKDR = secondKill;}
		else {secondKDR = (float)secondKill/(float)secondDeath;}

		if (thirdDeath == 0) { thirdKDR = thirdKill;}
		else {thirdKDR = (float)thirdKill/(float)thirdDeath;}

		if (firstKDR > secondKDR && firstKDR > thirdKDR) {
			scaling = "EARLY GAME";}
		else if (secondKDR > firstKDR && secondKDR > thirdKDR) {
			scaling = "MID GAME";}
		else if (thirdKDR > secondKDR && thirdKDR > firstKDR) {
			scaling = "LATE GAME";}
		else {
			scaling = "MID GAME";}


		out_file<<std::setw(20)<<std::left<<name;
		out_file<<std::setw(5)<<std::right<<std::fixed<<std::setprecision(2)<<firstKDR;
		out_file<<std::setw(6)<<std::right<<std::fixed<<std::setprecision(2)<<secondKDR;
		out_file<<std::setw(6)<<std::right<<std::fixed<<std::setprecision(2)<<thirdKDR;
		out_file<<"   "<<std::setw(12)<<std::left<<scaling;
		out_file<<std::endl;
	}



	//Sorts champions by Win Rate (for both Champions and Custom Table)
	bool CompareChampion(const Champion &Champ1, const Champion &Champ2) {
	if (Champ1.getWinrate() > Champ2.getWinrate()) {
		return true;
	}

	else if (Champ1.getWinrate() == Champ2.getWinrate()) {
		if (Champ1.getWin() > Champ2.getWin()) {
			return true;}

		else if (Champ1.getWin() == Champ2.getWin()) {
			if (Champ1.getLose() < Champ2.getLose()) {
				return true;}
			else if (Champ1.getLose()==Champ2.getLose()) {
			if (Champ1.getName() < Champ2.getName()) {
				return true; }}}
	}

	return false;
}