#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include "player.h"

	Player::Player() {
		kill = 0;
		death = 0;
	}

	Player::Player(std::string n, std::string champion) {
		name = n;
		champion_list.push_back(champion);
		kill = 0;
		death = 0; }

	//Accessors
		int Player::getKills() const {
			return kill;
		}
		int Player::getDeaths() const {
			return death;
		}

		float Player::getKDR() const {
			float KDR;
			if (death == 0) {
				KDR = kill;
			}
			else {
				KDR = (float)kill/(float)death;}
			return KDR;
		}


		std::string Player::getName() const {
			return name;
		}

		std::string Player::lastchamp() const {
			return champion_list[champion_list.size()-1];
		}


		void Player::addKill() {
			kill +=1;
		}
		void Player::addDeath() {
			death += 1;
		}

		//Checks to see if champion has already been played
		void Player::playedchamp(std::string champion) {
			for (unsigned int i=0; i < champion_list.size(); i++) {
				if (champion_list[i] == champion) {
					return;}
				}
			champion_list.push_back(champion);}
		//Prints out sorted list of champions
		void Player::printchamp(std::ostream &out_file) {
			sort(champion_list.begin(), champion_list.end());
			out_file<<"   ";
			for (unsigned int i=0; i < champion_list.size(); i++) {
				if (i == 0) {
					out_file<<champion_list[0];}
				else {
					out_file<<", "<<champion_list[i];
				}
			}
		}

		//Sort list of players by KDR, if KDR is the same then by name

		bool ComparePlayer(const Player &Player1, const Player &Player2) {
	if (Player1.getKDR() > Player2.getKDR()) {
		return true;
	}

	else if (Player1.getKDR() == Player2.getKDR()) {
		if (Player1.getKills()>Player2.getKills()) {
			return true;}
		else if (Player1.getKills()==Player2.getKills()) {
			if (Player1.getDeaths() < Player2.getDeaths()) {
				return true;}
			else if (Player1.getDeaths() == Player2.getDeaths()) {
				if (Player1.getName() < Player2.getName()) {
					return true;}
		}}}

	return false;
}