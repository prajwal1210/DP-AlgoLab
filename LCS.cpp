#include <iostream>
#include <string>
#include <new>
#include <iomanip>
using namespace std;

void solution(int** S, string X, int i, int j)
{
	if(i==0 || j==0)
		return;
	else
	{
		if(S[i][j]==0)
			{
				solution(S,X,i-1,j-1);
				cout << X[i-1];
			}
		else if(S[i][j]==1)
			solution(S,X,i,j-1);
		else
			solution(S,X,i-1,j);
	}

	/*int i=m;
	int j=n;
	while(i>0 && j>0)
	{
		if(S[i][j]==0)
			{
				cout << X[i-1];
				i--;
				j--;
			}
		else if(S[i][j]==1)
		{
			j--;
		}
		else if(S[i][j]==-1)
		{
			i--;
		}
	}*/
}


int main(int argc, char const *argv[])
{
	string X;
	string Y;
	cin >> X;
	cin >> Y;
	int m=X.length();
	int n=Y.length();
	int** D=new int*[m+1];
	for (int i = 0; i < m+1; ++i)
	{
		D[i]=new int[n+1];
	}
	int** S=new int*[m+1];
	for (int i = 0; i < m+1; ++i)
	{
		S[i]=new int[n+1];
	}
	for (int i = 0; i < m+1; ++i)
	{
		D[i][0]=0;
	}
	for (int i = 0; i < n+1; ++i)
	{
		D[0][i]=0;
	}
	for (int i = 1; i < m+1;++i)
	{
		for (int j = 1; j < n+1; ++j)
		{
			int q;
			if(X[i-1]==Y[j-1])
			{
				q=D[i-1][j-1]+1;
				S[i][j]=0;
			}
			else
			{
				int x=D[i-1][j];
				int y=D[i][j-1];
				if(x>=y)
				{
					q=x;
					S[i][j]=-1;
				}
				else
				{
					q=y;
					S[i][j]=1;
				}
			}
			D[i][j]=q;

		}
	}
	cout << D[m][n] << endl;
	solution(S,X,m,n);
	/*for (int i = 0; i < m+1; ++i)
	{
		for (int j = 0; j < n+1; ++j)
		{
			cout << S[i][j] << setw(4);
		}
		cout << endl;
	}*/

	return 0;
}