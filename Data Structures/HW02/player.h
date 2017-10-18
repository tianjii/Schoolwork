class Player {

	public:
	Player();
	Player(std::string name, std::string champion);
	//Accessors
		int getKills() const;
		int getDeaths() const;
		float getKDR() const;
		std::string getName() const;
		std::string lastchamp() const;
		void addKill();
		void addDeath();
		void addChampion(std::string champion);

		void playedchamp(std::string champion);
		void printchamp(std::ostream &out_file);

	private:
		std::string name;
		int kill;
		int death;
		std::vector<std::string> champion_list;

};

bool ComparePlayer(const Player &Player1, const Player &Player2);