/* ASSUMPTIONS:
1. When a node must be split and has an odd number of keys, the extra key will go to the new right-hand node.
2. There will never be a duplicate key passed to insert.
*/

#include <vector>
#include <string>
#include <iostream>
#include <fstream>

#ifndef DS_BPLUSTREE
#define DS_BPLUSTREE

///////////////////////////////////////////////////////////////////////////////
//DO NOT CHANGE THIS CODE
///////////////////////////////////////////////////////////////////////////////
template <class T> class BPlusTree;

template <class T>
class BPlusTreeNode{
public:
	BPlusTreeNode() : parent(NULL) {};
	bool is_leaf();
	bool contains(const T& key);
	void printkeys();

	//For grading only, this is actually bad to have because
	//it exposes a private member variable.
	BPlusTreeNode* get_parent() { return parent; } 

	//We need this to let BPlusTree access private members
	friend class BPlusTree<T>; 
private:
	bool contains(const T& key,std::size_t low,std::size_t high);
	std::vector<T> keys;
	std::vector<BPlusTreeNode*> children;
	BPlusTreeNode* parent;
};
//tmp
template <class T>
void BPlusTreeNode<T>::printkeys(){
	for (unsigned int i = 0; i < keys.size(); i++) {
		std::cout<<keys[i]<<" ";
	}
	std::cout<<std::endl;
}

template <class T>
bool BPlusTreeNode<T>::is_leaf(){
	for(unsigned int i=0; i<children.size(); i++){
		if(children[i]){
			return false;
		}
	}
	return true;
}

template <class T>
bool BPlusTreeNode<T>::contains(const T& key){
	return contains(key,0,keys.size()-1);
}

//Private method takes advantage of the fact keys are sorted
template <class T>
bool BPlusTreeNode<T>::contains(const T& key,std::size_t low,std::size_t high){
	if(low>high){
		return false;
	}
	if(low==high){
		return key == keys[low];
	}
	std::size_t mid = (low+high)/2;
	if(key<=keys[mid]) {
		return contains(key,0,mid);
	}
	else{
		return contains(key,mid+1,high);
	}
}

///////////////////////////////////////////////////////////////////////////////////////
//Your BPlusTree implementation goes below this point.
///////////////////////////////////////////////////////////////////////////////////////
//Build from bottom up
template <class T>
class BPlusTree {
	public:
		BPlusTree(int b) { root_ = new BPlusTreeNode<T>; size = b; }
		~BPlusTree() {
			deletetree(root_);
		}
		BPlusTree<T>(BPlusTree<T> &b) { size = b.size; root_ = copy_tree(b.root_);}
		void insert(const T &tofind) { return insert(tofind, root_);}
		BPlusTreeNode<T>* find(const T &tofind) { return find(tofind, root_);}
		void print_sideways(std::ofstream &ostr) { 
			if (root_->keys.size() == 0) {
				ostr<<"Tree is empty."<<std::endl;
				return;
			}
			print_sideways(ostr,root_, 0); }
		void print_BFS(std::ofstream &ostr) {
			if (root_->keys.size() == 0) {
				ostr<<"Tree is empty."<<std::endl;
				return;
			}
			std::vector<std::vector<std::vector<T> > > v;
			print_BFS(ostr, root_, 0, v);
			print_vec(ostr, v);
		}

		void operator=(const BPlusTree &b) {
			if(root_) {
				delete root_; }
			size = b.size; 
			root_ = copy_tree(b.root_);}
	private:
		unsigned int size;
		BPlusTreeNode<T>* root_;


//While original tree has children, recursively push back pointers to copied children into copied parent
BPlusTreeNode<T>* copy_tree(BPlusTreeNode<T>* old_root) {
    if (!old_root) {
      return NULL;
    }
    
    BPlusTreeNode<T>* new_root = new BPlusTreeNode<T>;
    new_root->keys = old_root->keys;

    for (unsigned int i = 0; i < old_root->children.size(); i++) {
    	 BPlusTreeNode<T>* branch = copy_tree(old_root->children[i]);
    	 if (branch) {
    	 	branch->parent = new_root;
    	 	new_root->children.push_back(branch); }
    }

    return new_root;
  }

//recursively call function for children then delete parent
void deletetree(BPlusTreeNode<T>* p) {
	for (unsigned int i = 0; i < p->children.size(); i++) {
		deletetree(p->children[i]);
	}

	delete p;
}

BPlusTreeNode<T>* find(const T &tofind, BPlusTreeNode<T>* t) {
	BPlusTreeNode<T>* found;
	bool isfound = false;
	if (root_->keys.size() == 0) {
		return NULL;
	}

	if (t->is_leaf()) {
		return t;
	}

	for (unsigned int i = 0; i < t->keys.size(); i++) {
			if (tofind < t->keys[i]) {
				found = find(tofind, t->children[i]);
				isfound = true;
				break;
			}
	}
	if (!isfound) {
		found = find(tofind, t->children[t->children.size()-1]);
	}
	return found;
}

//If node is not a leaf, call insert on appropriate child
//If child, insert value into keys, call splitting function
void insert(const T &tofind, BPlusTreeNode<T>* t) {
	typename std::vector<T>::iterator key_itr;
	typename std::vector<BPlusTreeNode<T>* >::iterator child_itr;
	if (t->is_leaf()) {
		bool placed = false;
		for (key_itr = t->keys.begin(); key_itr != t->keys.end(); key_itr++) {
			if (*key_itr > tofind) {
				t->keys.insert(key_itr, tofind);
				placed = true;
				break;
			}
		}
		if (!placed)
			t->keys.push_back(tofind);
	checksplit(t);
	
	}

	else {
		for (unsigned int i = 0; i < t->keys.size(); i++) {
			if (tofind < t->keys[i]) {
				insert(tofind, t->children[i]);
				break;
			}

			else if (tofind > t->keys[t->keys.size()-1]) {
				insert(tofind, t->children[t->keys.size()]);
				break;
			}

		}
	}

}

void checksplit(BPlusTreeNode<T>* left) {
	unsigned int split = size/2;
	unsigned int child_split = (size+1)/2;
	if (size%2 == 0) {
		child_split+=1;
	}
	bool placed = false;
	//If the node has just reached the max number of elements, split
	if (left->keys.size() == size) {
		BPlusTreeNode<T>* right = new BPlusTreeNode<T>;
		//split the keys, give right side the middle key if odd
		right->keys = std::vector<T>(left->keys.begin()+split, left->keys.end());
		left->keys = std::vector<T>(left->keys.begin(), left->keys.begin()+split);
		//If there are children, divide the children between the 2 nodes
		if (left->children.size() > 0) {
			right->children = std::vector<BPlusTreeNode<T>*>(left->children.begin()+child_split, left->children.end());
			left->children = std::vector<BPlusTreeNode<T>*>(left->children.begin(), left->children.begin()+child_split); 
			for (unsigned int i = 0; i < right->children.size(); i++) {
				right->children[i]->parent = right;
			}
		}

		//test the first value of new node to find place in parent
		T test_value = right->keys[0];
		right->parent = left->parent;
		BPlusTreeNode<T>* parent = left->parent;
		typename std::vector<T>::iterator key_itr;
		typename std::vector<BPlusTreeNode<T>* >::iterator child_itr;

//			0 1 2 3
//		   0 1 2 3 4

		//if there is a parent, test the test value
		if (parent) {
			for (key_itr = parent->keys.begin(), child_itr = parent->children.begin(); key_itr != parent->keys.end(); key_itr++, child_itr++) {
				if (*key_itr > test_value) {
					(parent->keys).insert(key_itr, test_value);
					//Important! Using the above method would insert the new node before the old node, 
					//if the newly added value was the lowest key, trade locations
					if (left->keys[0] < right->keys[0]) {
						child_itr++;
					}
					(parent->children).insert(child_itr, right);
					placed = true;
					break;
				}
			}
			if (!placed) {
				parent->keys.push_back(test_value);
				parent->children.push_back(right);
			}

			if (!right->is_leaf()) {
				right->keys.erase(right->keys.begin());
			}
			checksplit(parent);
		}
		//create a new parent that will become the root_
		else if (!parent) {
			parent = new BPlusTreeNode<T>;
			parent->children.push_back(left);
			parent->children.push_back(right);
			parent->keys.push_back(test_value);
			if (!left->is_leaf()) {
			right->keys.erase(right->keys.begin()); }

			right->parent = parent;
			left->parent = parent;
			root_ = parent;
		}
	}
}
//Recurseively print te first half of children, print current node, then print last half of children
void print_sideways(std::ofstream &ostr, const BPlusTreeNode<T>* p, int depth) {
	unsigned int mid = p->children.size()/2;

	if (p) {
		for (unsigned int i= 0; i< mid; i++) {
			print_sideways(ostr, p->children[i], depth+1);
		}
		for (int i=0; i<depth; ++i) ostr<< "\t";
		for (unsigned int i = 0; i < p->keys.size(); i++) {
			ostr<<p->keys[i];
			if (i != p->keys.size()-1) { ostr<<","; }
		}
		ostr<<"\n";
		for (unsigned int i= mid; i< p->children.size(); i++) {
			print_sideways(ostr, p->children[i], depth+1);
		}

	}
}

//Used 3D vector to organize information without printing, then used helper function to print it.
void print_BFS(std::ofstream &ostr, const BPlusTreeNode<T>* p, int depth, std::vector<std::vector<std::vector<T> > > &v) {
	unsigned int s = depth;
	if (p) {
		std::vector<T> tmp;
		for (unsigned int i = 0; i < p->keys.size(); i++) {
			tmp.push_back(p->keys[i]);
		}
		if (v.size() <= s) {
			std::vector<std::vector<T> > tmp2;
			tmp2.push_back(tmp);
			v.push_back(tmp2);
		}

		else {
			v[depth].push_back(tmp);}

		for (unsigned int i = 0; i < p->children.size(); i++) {
			print_BFS(ostr, p->children[i], depth+1, v);
		}

	}
}
//Helper function to print 3D vector correctly
void print_vec(std::ofstream &ostr, std::vector<std::vector<std::vector<T> > > &v) {
	for (unsigned int i = 0; i < v.size(); i++) {
		for (unsigned int j = 0; j < v[i].size(); j++) {
			for (unsigned int k = 0; k < v[i][j].size(); k++) {
				ostr<<v[i][j][k];
				if (k != v[i][j].size()-1) {
					ostr<<",";
				}
			}

			if (j != v[i].size()-1) {
				ostr<<"\t";}
			else { ostr<<"\n";}
		}
	}
}

};

#endif