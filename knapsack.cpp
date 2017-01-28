#include <iostream>
#include <new>
#include <cmath>
#include <iomanip>
#include <stdlib.h>
using namespace std;

int main()
{
	int n;
	cin >> n;
	int *V=new int[n];
	int *W=new int[n];
	for (int i = 0; i < n; ++i)
	{
		cin >> V[i];
		cin >> W[i];
	}
	int mW;
	cin >> mW;
	int D[n][mW+1];
	int **S = (int **)malloc((n)* sizeof(int *));
    for (int i=0; i<n; i++)
         S[i] = (int *)malloc((mW+1)* sizeof(int));
	for (int w = 0; w < mW+1; ++w)
	{
		for (int j = 0; j < n; ++j)
		{
			if(j==0)
			{
				if(W[j]>w)
					{
						D[j][w]=0;
						S[j][w]=-1;
					}
				else 
				{
					D[j][w]=V[j];
					S[j][w]=1;
				}
			}
			else
			{
				if(W[j]>w)
					{
						D[j][w]= D[j-1][w];
						S[j][w]=-1;
					}
				else
				{
					int x=max((D[j-1][w-W[j]]+V[j]),D[j-1][w]);
					if((D[j-1][w-W[j]]+V[j])==x)
						S[j][w]=1;
					else
						S[j][w]=-1;
					D[j][w]=x;
				}

			}
		}
	}
	cout << D[n-1][mW] << endl;
	for (int j = 0; j < n; ++j)
	{
		for (int w = 0; w < mW+1; ++w)
		{
			cout << left <<setw(4) << S[j][w] << " ";

		}
		cout << endl;
	}
	return 0;
}