//============================================================================
// Name        : Trie.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <bits/stdc++.h> 
using namespace std; 

struct trie {
	std::map<char,trie*> child;
};

trie *createNode(){
	trie *NewNode = new trie;

	return NewNode;
}

void insertString(trie*& node, string str) {
	char val = 0;
	if(str.length() != 0) {
		val = str.at(0);
		if(node == nullptr) {
			node = createNode();
		}
		std::map<char,trie*>::iterator it = node->child.find(val);
		if(it == node->child.end()) {
			node->child[val] = createNode();
		}
		insertString(node->child[val], str.substr(1));
	}
}

void printTrie(trie*& node) {
	std::map<char,trie*>::iterator it;
	for(it=node->child.begin();it!= node->child.end();it++) {
		cout << it->first << " " << it->second << endl;
		printTrie(it->second);
	}
}

bool searchStringRecursive(trie*& node, string str, int strlength, int itr) {
	bool retval = false;
	std::map<char,trie*>::iterator it = node->child.find(str.at(0));
	if(it != node->child.end()) {
		cout << "Search: " << str.at(0) << " Length: " << str.length() << strlength << " " << itr << endl;
		if(itr == (strlength-1)) {
			return true;
		}
		retval = searchStringRecursive(node->child[str.at(0)], str.substr(1), strlength, itr+1);
	}
	return retval;
}

void searchString(trie*& node, string str) {
	if(searchStringRecursive(node, str, str.length(), 0)) {
		cout << "Found\n";
	} else {
		cout << "Not Found\n";
	}
}

int main() {
	trie *root = createNode();

	insertString(root, "custom");
	searchString(root, "custom");
	searchString(root, "custum");
	insertString(root, "hello");
	searchString(root, "hello");
	insertString(root, "world");
	searchString(root, "world");

	printTrie(root);

	return 0;
}

