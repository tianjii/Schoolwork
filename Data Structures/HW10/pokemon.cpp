#include <string>
#include <iostream>
#include <stdlib.h>
#include <map>
#include "pokemon.h"
//Check eggGroups vector to see if it matches
bool Pokemon::correctEgg(std::string egg) {
	bool hasegg = false;
	for (unsigned int i = 0; i < facts["eggGroups"].size(); i++) {
	if (facts["eggGroups"][i] == egg) {
		hasegg = true; }
	}

	return hasegg;

}

//Compare height and weight to verify the specific pokemon constructor
bool Pokemon::correctPoke(double h, double w) {

	if (atof(facts["weight"][0].c_str()) != w) {
		return false;} 
	else if (atof(facts["height"][0].c_str()) != h) {
		return false; }

	return true;
}

//accessor for label in facts map
std::string Pokemon::getLabel() {
	return facts["label"][0];
}

//Check if another pokemon shares an eggGroup as this one
bool Pokemon::SharesEggGroup(Pokemon* p) {
	for (unsigned int i = 0; i < p->getGroup().size(); i++) {
		for (unsigned int j = 0; j < facts["eggGroups"].size(); j++) {
			std::cout<<p->getGroup()[i]<<" "<<facts["eggGroups"][j]<<std::endl;
			if (p->getGroup()[i] == facts["eggGroups"][j]) {
				return true;
			}
		}
	}

	return false;
}

