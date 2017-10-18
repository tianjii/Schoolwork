#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <fstream>
#include <string>
#include "player.h"
#include "champion.h"

//if Input is players
//When Match starts, take in all player names and record champion used
//When Events, record killer and dyer LOL

//Prints the output for the players chart
void outputPlayer(std::vector<Player> &players, std::ostream &out_file) {
	sort(players.begin(), players.end(), ComparePlayer);
	out_file<< "PLAYER NAME            KILLS  DEATHS     KDR   PLAYED WITH CHAMPION(S)"
	<<std::endl;
	for (unsigned int i=0; i < players.size(); i++) {
		out_file<<std::setw(23)<<std::left<<players[i].getName();
		out_file<<std::setw(5)<<std::right<<players[i].getKills();
		out_file<<std::setw(8)<<std::right<<players[i].getDeaths();
		out_file<<std::setw(8)<<std::right<<std::fixed<<std::setprecision(2)<<players[i].getKDR();
		players[i].printchamp(out_file);
		out_file<<std::endl;}
	}
//Prints output for champions chart
void outputChampion(std::vector<Champion> &champions, std::ofstream &out_file) {
	sort(champions.begin(), champions.end(), CompareChampion);
	out_file<<"CHAMPION NAME           WINS  LOSSES    WIN%   MINION DEATHS"<<std::endl;
	for (unsigned int i=0; i < champions.size(); i++) {
		out_file<<std::setw(23)<<std::left<<champions[i].getName();
		out_file<<std::setw(5)<<std::right<<champions[i].getWin();
		out_file<<std::setw(8)<<std::right<<champions[i].getLose();
		out_file<<std::setw(8)<<std::right<<std::fixed<<std::setprecision(2)<<champions[i].getWinrate();
		out_file<<std::setw(16)<<std::right<<champions[i].getMinion();
		out_file<<std::endl;
}}

//Accesses each champion object and prints the custom table from within the class
void outputCustom(int lasttime, std::vector<Champion> &champions, std::ofstream &out_file) {
	sort(champions.begin(), champions.end(), CompareChampion);
	out_file<<"CHAMPION NAME       EARLY   MID  LATE   SCALING"<<std::endl;
	for (unsigned int i=0; i < champions.size(); i++) {
			champions[i].dividematch(lasttime, out_file);}
}

//Finds the champion of the player killed by the minion in order to increment the death
void minionKill(std::vector<Player> &players, std::vector<Champion> &champions, std::string name) {
	std::string champion_name;
	for (unsigned int i = 0; i<players.size(); i++) {
			if (players[i].getName() == name) {
			champion_name = players[i].lastchamp();}}
	for (unsigned int i = 0; i<champions.size(); i++) {
			if (champions[i].getName() == champion_name) {
				champions[i].addMinion();
			}
	}}

//If player does not exist, creates a new one
void playerInit(std::string name, std::string champion, std::vector<Player> &players) {
	for (unsigned int i = 0; i < players.size(); i++) {
		if (players[i].getName() == name) {
			players[i].playedchamp(champion);
			return;}}
		Player newplayer(name,champion);
		players.push_back(newplayer);}
//If champion does not exist, creates a new one
void championInit(std::string name, int team, std::vector<Champion> &champions){
	for (unsigned int i = 0; i<champions.size(); i++) {
		if (champions[i].getName() == name) {
			if (team == 1) {champions[i].addWin();}
			else if (team==0) {champions[i].addLose();}
			return;}}
	Champion newchampion(name,team);
	champions.push_back(newchampion);
		}
//For custom table, adds the time of the kill to champion object
void championKill(int time, std::string champion, std::vector<Champion> &champions){
	for (unsigned int i = 0; i < champions.size(); i++) {
		if (champions[i].getName() == champion) {
			champions[i].killtime(time);
		}
	}
}

//For custom table, adds the time of the death to champion object
void championDeath(int time, std::string champion, std::vector<Champion> &champions){
	for (unsigned int i = 0; i < champions.size(); i++) {
		if (champions[i].getName() == champion) {
			champions[i].deathtime(time);
		}
	}
}

//Adds kills or deaths to respective players
void playerKill(std::string playerK,std::string playerD, std::vector<Player> &players, 
	int time, std::vector<Champion> &champions) {

	for (unsigned int i = 0; i < players.size(); i++) {
		if (players[i].getName() == playerK) {
			players[i].addKill();
			championKill(time, players[i].lastchamp(), champions);}
		else if (players[i].getName() == playerD) {
			players[i].addDeath();
			championDeath(time, players[i].lastchamp(), champions);}}

}


int main( int argc, char* argv[]) {
	std::ifstream in_file(argv[1]);
	std::ofstream out_file(argv[2]);
	std::string chart = argv[3];
	std::vector<std::string> temp_vec;
	std::vector<Player> players;
	std::vector<Champion> champions;
	std::string tmp;
	std::string event;
	int team;
	std::string currenttime;
	int lasttime;

	for (unsigned int i = 0; i<players.size(); i++) {
		std::cout<<players[i].getName()<<std::endl;
	}

	//Check which team (winning/losing)
	while (in_file >> tmp) {
		if (tmp == "MATCH") {																															
			for (int i = 0; i < 4; i++) {
				in_file >> tmp;
				if (tmp == "WINNING") { team = 1;}
				else if (tmp == "LOSING") { team = 0; }}}

	//Read in players for 1st team, initialize player and champions
		for (int i = 0; i < 5; i++) {
			temp_vec.clear();
		for (int j = 0; j < 4; j++) {
			in_file >> tmp;
			temp_vec.push_back(tmp);} //
		playerInit(temp_vec[0], temp_vec[3], players);
		championInit(temp_vec[3], team, champions);}
	
	//Read in players for 2nd team, initialize player and champions	
		for (int i = 0; i < 2; i++) {
				in_file >> tmp;
				if (tmp == "WINNING") { team = 1;}
				else if (tmp == "LOSING") { team = 0; }}
		
		for (int i = 0; i < 5; i++) {
			temp_vec.clear();
		for (int j = 0; j < 4; j++) {
			in_file >> tmp;
			temp_vec.push_back(tmp);}
		playerInit(temp_vec[0], temp_vec[3], players);
		championInit(temp_vec[3], team, champions);}

		temp_vec.clear();

	//Pack events into vector, execute event and clear vector
	//when @ or END is reached
		for (int i = 0; i < 1; i++) {
				in_file >> tmp;}		
		
		while (tmp != "END") {
			in_file >> tmp;
			if (tmp == "@" || tmp == "END") {
				if (temp_vec.size() > 0){
					if (temp_vec[1] == "minion") {
					minionKill(players, champions, temp_vec[temp_vec.size()-1]);}
				currenttime = temp_vec[0];
				lasttime = atoi(currenttime.c_str());
				playerKill(temp_vec[1],temp_vec[temp_vec.size()-1], players, lasttime, champions);}
				temp_vec.clear();}
			else {
			temp_vec.push_back(tmp);}
				
			}
		}
	//Call output based on command line input
		if (chart == "players")	{
		outputPlayer(players, out_file);}
		else if (chart == "champions") {
		outputChampion(champions, out_file);}
		else if (chart == "custom") {

		outputCustom(lasttime, champions, out_file);

		}
	}