#include <iostream>
#include <vector>
#include <map>
#include <algorithm>

using std::cin;
using std::cout;
using std::map;
using std::vector;

class Node {
public:
	vector<int> m_childrens = {-1, -1, -1, -1, -1};
	vector<int> m_transfers = {-1, -1, -1, -1, -1};
	vector<int> m_substrings_index;
	std::pair<char, int> m_parent;
	int m_suffix_link = -1;
	int m_compressed_suffix_link = -1;
	bool m_is_leaf = false;

public:
	Node(char symbol = 0, int parent = -1){
		m_parent = std::make_pair(symbol, parent);
	}
};

class Automat {
private:
	vector<Node> m_trie;
	map<char, int> m_alphabet;
public:
	Automat(map<char, int> alphabet) {
		m_trie.push_back(Node());
		m_alphabet = alphabet;
	}
	void addString(int string_index, std::string const& str) {
		int cur_ver = 0;
		for (char ch : str) {
			int ch_index = m_alphabet[ch];
			if (m_trie[cur_ver].m_childrens[ch_index] == -1) {
				m_trie.emplace_back(ch, cur_ver);
				m_trie[cur_ver].m_childrens[ch_index] = m_trie.size() - 1;
			}
			cur_ver = m_trie[cur_ver].m_childrens[ch_index];
		}

		m_trie[cur_ver].m_is_leaf = true;
		m_trie[cur_ver].m_substrings_index.push_back(string_index);
	}

	int calcSuffixLink(int node) {
		if (m_trie[node].m_suffix_link == -1) {
			if(node == 0 || m_trie[node].m_parent.second == 0){
				m_trie[node].m_suffix_link = 0;
			}
			else {
				m_trie[node].m_suffix_link = calcTransfer(calcSuffixLink(m_trie[node].m_parent.second), m_trie[node].m_parent.first);
			}
		}

		return m_trie[node].m_suffix_link;
	}

	int calcTransfer(int node, char symbol) {
		int ch_index = m_alphabet[symbol];
		
		if (m_trie[node].m_transfers[ch_index] == -1) {
			if (m_trie[node].m_childrens[ch_index] != -1) {
				m_trie[node].m_transfers[ch_index] = m_trie[node].m_childrens[ch_index];
			}
			else {
				if (node == 0) {
					m_trie[node].m_transfers[ch_index] = 0;
				}
				else {
					m_trie[node].m_transfers[ch_index] = calcTransfer(calcSuffixLink(node), symbol);
				}
			}
		}

		return m_trie[node].m_transfers[ch_index];
	}

	int calcCompressedSuffixLink(int node) {
		if (m_trie[node].m_compressed_suffix_link == -1) {
			int suf_link = calcSuffixLink(node);
			if (m_trie[suf_link].m_is_leaf) {
				m_trie[node].m_compressed_suffix_link = suf_link;
			}
			else {
				if (suf_link == 0) {
					m_trie[node].m_compressed_suffix_link = 0;
				}
				else {
					m_trie[node].m_compressed_suffix_link = calcCompressedSuffixLink(suf_link);
				}
			}
		}

		return m_trie[node].m_compressed_suffix_link;
	}

	void check(int node, int symbol_index, vector<std::pair<int, int>>& result, vector<std::string> const& patterns) {
		for (int state = node; state != 0; state = calcCompressedSuffixLink(state)) {
			if (m_trie[state].m_is_leaf) {
				result.emplace_back(symbol_index - patterns[m_trie[state].m_substrings_index[0]-1].length() + 1, m_trie[state].m_substrings_index[0]);
			}
		}
	}

	vector<std::pair<int, int>> findAll(std::string const& text, vector<std::string> const& patterns) {
		vector<std::pair<int, int>> result;
		int node = 0;
		for (int i = 0; i < text.length(); i++) {
			node = calcTransfer(node, text[i]);
			check(node, i+1, result, patterns);
		}
		return result;
	}
};

bool cmp(std::pair<int, int> el1, std::pair<int, int> el2) {
	if (el1.first == el2.first) {
		return el1.second < el2.second;
	}

	return el1.first < el2.first;
}

int main() {
	std::string text, pattern;
	int count;
	vector<std::string> patterns;
	cin >> text >> count;
	for (int i = 0; i < count; i++) {
		cin >> pattern;
		patterns.push_back(pattern);
	}

	map<char, int> alphabet = { {'A', 0},{'C', 1},{'G', 2},{'T', 3},{'N', 4}};
	Automat AC(alphabet);
	for (int i = 0; i < count; i++) {
		AC.addString(i+1,patterns[i]);
	}
	
	vector<std::pair<int, int>> result = AC.findAll(text, patterns);
	std::sort(result.begin(), result.end(), cmp);
	for (std::pair<int, int> elem : result) {
		cout << elem.first << ' ' << elem.second << '\n';
	}
	return 0;
}
