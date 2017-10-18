class BlastNode {
	public:
		BlastNode(std::string k, unsigned int v) { key = k; value = v; next = NULL;}
		std::string key; //kmer
		unsigned int value; //position
		BlastNode* next;

};

typedef std::pair<std::string, std::vector<int> > bucket;
class BlastHash {
	public:
		BlastHash(unsigned int size, float occupancy, int k);
		unsigned int hash(const char* key);
		void fill(const std::string &genome);
		void query(std::string key);
		void print();
		void resize();
		void query(std::string sequence, int error);
		bool valid_loc(std::string &sequence, int error, int seed);
	private:
		unsigned int m_size;
		std::vector<bucket> m_table;
		float occupancy;
		int contains;
		int k;
		std::string gene;

};