#include <iostream>
#include <string>
#include <vector> 

using namespace std;

vector<int> KMP(string& text, int begin, string& substring){
	size_t len = substring.length();

	vector<int> indexes_of_entries;
	vector<int> prefixes(len);

	prefixes[0] = 0;//prefix function
	for (int k = 0, i = 1; i < len; ++i)
	{
		while ((k > 0) && (substring[i] != substring[k]))
			k = prefixes[k - 1];

		if (substring[i] == substring[k])
			k++;

		prefixes[i] = k;
	}

	for (int k = 0, i = begin; i < text.length(); ++i)//searching substrings
	{
		while ((k > 0) && (substring[k] != text[i]))
			k = prefixes[k - 1];

		if (substring[k] == text[i])
			k++;

		if (k == len)
			indexes_of_entries.push_back(i - len + 1);

	}

	if (indexes_of_entries.empty()) {
		indexes_of_entries.push_back(-1);
	}

	return indexes_of_entries;
}

int main(){
	std::string text = "";
	std::string substring = "";
	cin >> substring;
	cin >> text;
	int in_pos = 0;
	int old_pos = 1;
	std::vector<int> positions = KMP(text, 0, substring);
	int i = 0;
	for (i = 0; i < positions.size() - 1; i++) {
		cout << positions[i] << ',';
	}

	cout << positions[i] << '\n';
	return 0;
}
