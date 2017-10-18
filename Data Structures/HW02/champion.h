class Champion {

public:
	Champion();
	Champion(std::string n, int team);

	std::string getName() const;
	int getWin() const;
	int getLose() const;
	float getWinrate() const;
	int getMinion() const;
	std::string lastchamp() const;

	void addWin();
	void addLose();
	void addMinion();

	void killtime(int t);
	void deathtime(int t);
	void dividematch(int t, std::ofstream &out_file);

private:
	int win;
	int lose;
	int miniondeath;
	std::string name;
	std::vector<int> killtimes;
	std::vector<int> deathtimes;

};

bool CompareChampion(const Champion &Champ1, const Champion &Champ2);