#include <iostream>
#include <new>
#include <cmath>
#include <iomanip>
#include <stdlib.h>
using namespace std;




void solution(int **s, int i, int j)
{
	if(i==j)
		cout <<  "A" << i+1;
	else
	{
		cout << "(";
		solution(s,i,s[i][j]);
		solution(s,s[i][j]+1,j);
		cout << ")";
	}
}

void marrix(int pi[], int pj[],int  n)
{
	int r[n][n];
	int **s = (int **)malloc(n * sizeof(int *));
    for (int i=0; i<n; i++)
         s[i] = (int *)malloc(n* sizeof(int));
	for (int k = 0; k < n; ++k)
	{
		for (int m = 0; m+k < n; ++m)
		{
			if(k==0)
				{
					r[m][m]=0;
					s[m][m]=m;
				}
			/*else if(k==1)
				r[m][m+k]=pi[m]*pi[m+k]*pj[m+k];*/
			else
			{
				int q=99999999;
				for (int i = m; i < m+k; ++i)
				{
				  int x=r[m][i]+r[i+1][m+k]+pi[m]*pj[i]*pj[m+k];
				  if (x<q)
				  {
				  	 q=x;
				  	 s[m][m+k]=i;
				  }
				}
				r[m][m+k]=q;
			}
		}
	}
	cout << r[0][n-1] << endl;
	for (int i = 0; i < n; ++i)
	{
	     for (int j = 0; j < n; ++j)
	     {
	     	cout << left << setw(12) << s[i][j] ;
	     }
	     cout << endl;
	}
	solution(s,0,n-1);
	cout << endl;

}

int main()
{
	int n;
	cin >> n;
	int pi[n];
	int pj[n];
	for (int i = 0; i < n; ++i)
	{
		cin >> pi[i];
		cin >> pj[i]; 
	}
	marrix(pi,pj,n);
}