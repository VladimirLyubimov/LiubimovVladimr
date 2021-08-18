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

	void check(int node, int symbol_index, int*& result, vector<std::pair<std::string, int>> const& patterns) {
		for (int state = node; state != 0; state = calcCompressedSuffixLink(state)) {
			if (m_trie[state].m_is_leaf) {
				for (int sub_index : m_trie[state].m_substrings_index) {
					int temp_index = 0;
					int j = symbol_index - patterns[sub_index - 1].first.length() + 1;
					int l_i = patterns[sub_index - 1].second;
					temp_index = j - l_i;
					if (temp_index > -1) {
						result[temp_index] += 1;
					}
				}
			}
		}
	}

	void findAll(std::string const& text, vector<std::pair<std::string, int>> const& patterns, int*& result) {
		int node = 0;
		for (int i = 0; i < text.length(); i++) {
			node = calcTransfer(node, text[i]);
			check(node, i+1, result, patterns);
		}
	}

	int NodeAmount() {
		return m_trie.size();
	}
};

void preparePattern(std::string const& pattern, vector<std::pair<std::string, int>>& substrings, char wild_card) {
	std::string temp_str = "";
	for (int i = 0; i < pattern.length(); i++) {
		if (pattern[i] != wild_card) {
			temp_str += pattern[i];
		}
		else {
			if (!temp_str.empty()) {
				substrings.emplace_back(temp_str, i-temp_str.length()+1);
				temp_str.clear();
			}
		}
	}
}

int main() {
	std::string text, pattern;
	char wild_card;
	cin >> text >> pattern >> wild_card;

	vector<std::pair<std::string, int>> patterns;
	pattern += wild_card;
	preparePattern(pattern, patterns, wild_card);
	int count = patterns.size();

	map<char, int> alphabet = { {'A', 0},{'C', 1},{'G', 2},{'T', 3},{'N', 4}};
	Automat AC(alphabet);
	for (int i = 0; i < count; i++) {
		AC.addString(i+1,patterns[i].first);
	}
	
	int* result = new int[text.length()];
	for (int i = 0; i < text.length(); i++) {
		result[i] = 0;
	}
	AC.findAll(text, patterns, result);

	int len = pattern.length()-1;
	int text_len = text.length();
	vector<int> abs_res;
	for (int i = 0; i < text_len; i++) {
		if (result[i] == count && i+len <= text_len) {
			//cout << i + 1 << '\n';
			abs_res.push_back(i);
		}
	}

	cout << AC.NodeAmount() << '\n';
	vector<int> inter_res;
	for (int i = 0; i < abs_res.size() - 1; i++) {
		if (abs_res[i] - abs_res[i + 1] + 1 <= len) {
			if (std::find(inter_res.begin(), inter_res.end(), abs_res[i]) == inter_res.end()) {
				inter_res.push_back(abs_res[i]);
			}
			if (std::find(inter_res.begin(), inter_res.end(), abs_res[i+1]) == inter_res.end()) {
				inter_res.push_back(abs_res[i+1]);
			}
		}
	}
	
	for (int index : inter_res) {
		for (int i = index; i < index + len; i++) {
			cout << text[i];
		}
		cout << '\n';
	}

	delete[] result;
	return 0;
}
