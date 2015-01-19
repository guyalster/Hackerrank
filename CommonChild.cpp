#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;


size_t LongestChild(const string &S1, const string &S2)
{
	vector<vector<size_t> >D(S1.size(), vector<size_t>(S2.size(), 0));

	for (int i = 0; i < S2.size(); ++i)
	{
		D[S1.size() - 1][i] = (int)(S2.substr(i, S2.size() - i).find(S1[S1.size() - 1]) != string::npos);
	}

	for (int i = 0; i < S1.size(); ++i)
	{
		D[i][S2.size() - 1] = (int)(S1.substr(i, S1.size() - i).find(S2[S2.size() - 1]) != string::npos);
	}

	for (int i = S1.size() - 2; i >= 0; i--)
	{
		for (int j = S2.size() - 2; j >= 0; j--)
		{
			D[i][j] = std::max(((S1[i] == S2[j] ? 1 : 0) + D[i + 1][j + 1]), std::max(D[i + 1][j], D[i][j + 1]));
		}
	}

	return (D[0][0]);
}




int main() {
	string S1;
	string S2;

	cin >> S1;
	cin >> S2;

	cout << LongestChild(S1, S2) << endl;
	return 0;
}
