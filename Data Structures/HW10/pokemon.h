#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <cassert>

////////////////POKEMON CLASSES/////////////
class Pokemon {
	public:
	Pokemon(std::map<std::string, std::vector<std::string> > f) {facts = f;}
	virtual ~Pokemon() {}
	//Accessors
	std::string getLabel();
	std::vector<std::string> getGroup() { return facts["eggGroups"]; }
	//Checking functions
	bool correctEgg(std::string egg);
	bool correctPoke(double h, double w);
	bool SharesEggGroup(Pokemon* p);
	
	protected:
	std::map<std::string, std::vector<std::string> > facts;


};

class Amorphous : virtual public Pokemon {
public:
Amorphous(std::map<std::string, std::vector<std::string> > f) : Pokemon(f) {
facts = f;
std::string egg = "Amorphous";
if (!correctEgg(egg)) {
	throw 0; }
}
};


class Bug : virtual public Pokemon {
public:
Bug(std::map<std::string, std::vector<std::string> > f) : Pokemon(f){
facts = f;
std::string egg = "Bug";
if (!correctEgg(egg)) {
	throw 0; }
}

};

class Dragon : virtual public Pokemon {
public:
Dragon(std::map<std::string, std::vector<std::string> > f) : Pokemon(f){
facts = f;
std::string egg = "Dragon";
if (!correctEgg(egg)) {
	throw 0; }
}
};


class Fairy : virtual public Pokemon {
public:
Fairy(std::map<std::string, std::vector<std::string> > f) : Pokemon(f) {
facts = f;
std::string egg = "Fairy";
if (!correctEgg(egg)) {
	throw 0; }
}
};

class Field : virtual public Pokemon {
public:
Field(std::map<std::string, std::vector<std::string> > f) : Pokemon(f) {
facts = f;
std::string egg = "Field";
if (!correctEgg(egg)) {
	throw 0; }
}
};
class Flying : virtual public Pokemon {
public:
Flying(std::map<std::string, std::vector<std::string> > f) : Pokemon(f) {
facts = f;
std::string egg = "Flying";
if (!correctEgg(egg)) {
	throw 0; }
}
};
class Grass : virtual public Pokemon {
public:
Grass(std::map<std::string, std::vector<std::string> > f) : Pokemon(f) {
facts = f;
std::string egg = "Grass";
if (!correctEgg(egg)) {
	throw 0; }
}
};
class HumanLike : virtual public Pokemon {
public:
HumanLike(std::map<std::string, std::vector<std::string> > f) : Pokemon(f) {
facts = f;
std::string egg = "HumanLike";
if (!correctEgg(egg)) {
	throw 0; }
}
};
class Mineral : virtual public Pokemon {
public:
Mineral(std::map<std::string, std::vector<std::string> > f) : Pokemon(f) {
facts = f;
std::string egg = "Mineral";
if (!correctEgg(egg)) {
	throw 0; }
}
};
class Monster : virtual public Pokemon {
public:
Monster(std::map<std::string, std::vector<std::string> > f) : Pokemon(f) {
facts = f;
std::string egg = "Monster";
if (!correctEgg(egg)) {
	throw 0; }
}
};
class Water1 : virtual public Pokemon {
public:
Water1(std::map<std::string, std::vector<std::string> > f) : Pokemon(f) {
facts = f;
std::string egg = "Water1";
if (!correctEgg(egg)) {
	throw 0; }
}
};


class Water2 : virtual public Pokemon {
public:
Water2(std::map<std::string, std::vector<std::string> > f) : Pokemon(f) {
facts = f;
std::string egg = "Water2";
if (!correctEgg(egg)) {
	throw 0; }
}
};
class Water3 : virtual public Pokemon {
public:
Water3(std::map<std::string, std::vector<std::string> > f) : Pokemon(f) {
facts = f;
std::string egg = "Water3";
if (!correctEgg(egg)) {
	throw 0; }
}
};

class Ditto : virtual public Pokemon {
public:
Ditto(std::map<std::string, std::vector<std::string> > f) : Pokemon(f) {
facts = f;
std::string egg = "Ditto";
if (!correctEgg(egg)) {
	throw 0; }
}
};

class Undiscovered : virtual public Pokemon{
public:
Undiscovered(std::map<std::string, std::vector<std::string> > f) : Pokemon(f) {
facts = f;
std::string egg = "Undiscovered";
if (!correctEgg(egg)) {
	throw 0; }
}
};

class NidoranMale : public Field , public Monster {
public:
NidoranMale(std::map<std::string, std::vector<std::string> > f) : Pokemon(f), Field(f), Monster(f){
	facts = f;
	if (!correctPoke(0.5, 9.0) && !correctPoke(0.9, 19.5) && !correctPoke(1.4, 62))
		throw 0;
}
};

class Nidorino : public NidoranMale {
public:
Nidorino(std::map<std::string, std::vector<std::string> > f) : Pokemon(f), NidoranMale(f) {
	facts = f;
	if (!correctPoke(0.9, 19.5) && !correctPoke(1.4, 62))
		throw 0;
}
};

class Nidoking : public Nidorino{
public:
Nidoking(std::map<std::string, std::vector<std::string> > f) : Pokemon(f), Nidorino(f) {
	facts = f;
	if (!correctPoke(1.4, 62))
		throw 0;
}
};

class Seel : public Field , public Water1 {
public:
Seel(std::map<std::string, std::vector<std::string> > f) : Pokemon(f), Field(f), Water1(f){
	facts = f;
	if (!correctPoke(1.1, 90) && !correctPoke(1.7, 120))
		throw 0;
}
};

class Dewgong : public Seel {
public:
Dewgong(std::map<std::string, std::vector<std::string> > f) : Pokemon(f), Seel(f) {
	facts = f;
	if (!correctPoke(1.7, 120))
		throw 0;
}
};

class Shellos : public Water1 , public Amorphous {
public:
Shellos(std::map<std::string, std::vector<std::string> > f) : Pokemon(f), Water1(f), Amorphous(f){
	facts = f;
	if (!correctPoke(0.3,6.3) && !correctPoke(0.9, 29.9))
		throw 0;
}
};

class Gastrodon : public Shellos {
public:
Gastrodon(std::map<std::string, std::vector<std::string> > f) : Pokemon(f), Shellos(f){
	facts = f;
	if (!correctPoke(0.9, 29.9))
		throw 0;
}
};

class Finneon : public Water2 {
public:
Finneon(std::map<std::string, std::vector<std::string> > f) : Pokemon(f), Water2(f) {
	facts = f;
	if (!correctPoke(0.4, 7.0) && !correctPoke(1.2, 24.0))
		throw 0;
}
};

class Lumineon : public Finneon {
public:
Lumineon(std::map<std::string, std::vector<std::string> > f) : Pokemon(f), Finneon(f){
	facts = f;
	if (!correctPoke(1.2, 24.0))
		throw 0;
}
};

class Basculin : public Water2 {
public:
Basculin(std::map<std::string, std::vector<std::string> > f) : Pokemon(f), Water2(f){
	facts = f;
	if (!correctPoke(1, 18.0))
		throw 0;
}
};
