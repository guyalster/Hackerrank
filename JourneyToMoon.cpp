#include <iostream>
#include <vector>
#include <map>
#include <numeric>

using namespace std;


struct UF
{
	UF *Parent;
	int Astro;
	int size;
};


UF *Root(UF *first)
{
	if (first->Parent == NULL ||
		first->Parent == first)
	{
		return (first);
	}

	first->Parent = Root(first->Parent);
	return (first->Parent);
}

void Union(UF *first, UF *second)
{
	UF *r1 = Root(first);
	UF *r2 = Root(second);

	if (first->size < second->size)
	{
		r1->Parent = r2;
		r1->Parent->size += r2->size;
	}
	else
	{
		r2->Parent = r1;
		r2->Parent->size += r1->size;
	}
}

vector<int> GetAllUnions(const vector<vector<int> >& Pairs)
{
	vector<UF> Unions(Pairs.size(), { 0 });

	for (auto i = 0; i < Unions.size(); ++i)
	{
		Unions[i].Parent = &(Unions[i]);
		Unions[i].Astro = i;
		Unions[i].size = 1;
	}

	for (auto iter = Pairs.begin(); iter != Pairs.end(); ++iter)
	{
		for (auto iter2 = iter->begin(); iter2 != iter->end(); ++iter2)
		{
			Union(&(Unions[iter - Pairs.begin()]), &(Unions[*iter2]));
		}
	}

	map<int, int> M;

	for (auto U : Unions)
	{
		UF *It = Root(&U);

		if (M.find(It->Astro) == M.end())
		{
			M[It->Astro] = 1;
		}
		else
		{
			M[It->Astro]++;
		}
	}

	vector<int> Res;

	for (auto P : M)
	{
		Res.push_back(P.second);
	}

	return (Res);
}


long long Binomial2(int i)
{
	long long res = 1;

	if (i == 0 || i == 1)
	{
		return (0);
	}

	if (i <= 2)
	{
		return (1);
	}

	for (int j = i - 2 + 1; j <= i; ++j)
	{
		res *= j;
	}

	return (res / 2);
}


int main()
{
	int N, I;
	cin >> N >> I;
	vector<vector<int> > pairs(N);
	for (int i = 0; i < I; ++i) {
		int a, b;
		cin >> a >> b;
		pairs[a].push_back(b);
		pairs[b].push_back(a);
	}

	long long result = 0;

	/** Write code to compute the result using N,I,pairs **/

	vector<int> Res = GetAllUnions(pairs);

	result = (Binomial2(accumulate(Res.begin(), Res.end(), 0)));

	for (auto i : Res)
	{
		result -= Binomial2(i);
	}

	cout << result << endl;
	return 0;
}
