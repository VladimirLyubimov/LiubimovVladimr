#include <iostream>
#include <string>
#include <vector> 

using namespace std;

vector<int> KMP(string& text, string& pattern) {
	string substring = pattern + "#" + text;
	size_t len = substring.length();

	vector<int> indexes_of_entries;
	vector<int> prefixes(len);

	prefixes[0] = 0;//prefix function
	cout << "Calculating prefix function for substring.\n";
	cout << "Value of prefix function for symbol " << substring[0] << " with index 0 is 0\n\n";
	int k = 0;
	for (int i = 1; i < len; i++) {
		cout << "Calculating value of prefix function for symbol " << substring[i] << " with index " << i << "\n";
		k = prefixes[i - 1];
		while ((k > 0) && (substring[i] != substring[k])) {
			cout << "Current size of suffix is " << k << ". It can't be increased, so we decrease it.\n";
			k = prefixes[k - 1];
		}


		if (substring[i] == substring[k]) {
			cout << "Current size of suffix is " << k << ". It can be increased, so we increase it.\n";
			k++;
		}

		cout << "Final size of suffix is " << k << "\n\n";

		prefixes[i] = k;
	}

	cout << "Overall prefix function for sought substring:\n";
	for (int i = 0; i < len; i++) {
		cout << substring[i] << "  " << prefixes[i] << '\n';
	}
	cout << "-----------------------------------------------------------------------------------";
	cout << '\n';

	cout << "Starting findings of indexes of enties of pattern into text.\n";
	//searching patterns
	cout << "For each symbol in text compare value of prefix function for this symbol with length of pattern\n";
	for (int i = 0; i < text.length(); i++) {
		cout << "Value of prefix function for this symbol " << text[i] << " with index " << i << " is " << prefixes[pattern.length() + 1 + i] << ". Length of the pattern is " << pattern.length() << '\n';
		if (prefixes[pattern.length() + 1 + i] == pattern.length()) {
			cout << "Pattern entry found! Its index is " << (i - pattern.length() + 1) << "\n";
			indexes_of_entries.push_back(i - pattern.length() + 1);
		}
	}

	if (indexes_of_entries.empty()) {
		cout << "No match with pattern!\n";
		indexes_of_entries.push_back(-1);
	}

	cout << "-----------------------------------------------------------------------------------";

	return indexes_of_entries;
}

int main() {
	string text = "";
	string substring = "";
	cout << "Input pattern:\n";
	cin >> substring;
	cout << "Input text:\n";
	cin >> text;
	cout << "\n\n";
	int in_pos = 0;
	vector<int> positions = KMP(text, substring);
	cout << "\n\nResult:\n";
	int i = 0;
	for (i = 0; i < positions.size() - 1; i++) {
		cout << positions[i] << ',';
	}

	cout << positions[i] << '\n';
	return 0;
}
