#include <iostream>
#include <new>
#include <vector>
#include <iomanip>
#include <stdlib.h>
using namespace std;



typedef struct 
{
	int s;
	int f;	
}interval;


void merge(interval A[], int start, int end)
{
	int n=end-start+1;
	interval *B=new interval[n];
	int k=0;
	int mid=(start+end)/2;
	int i=start;
	int j=mid+1;
	while(i<=mid && j<=end)
	{
		if(A[i].f<=A[j].f)
		{
			B[k]=A[i];
			i++;
			k++;
		}
		else
		{
			B[k]=A[j];
			j++;
			k++;
		}

	}
	while(i<=mid)
	{
		B[k]=A[i];
		i++;
		k++;
	}
	while(j<=end)
	{
		B[k]=A[j];
		k++;
		j++;
	}
	i=0;
	for (i = 0; i < n; ++i)
	{
		A[i+start]=B[i];
	}

}


void mergesort(interval A[], int start, int end)
{
	if(start>=end)
		return;
	else
	{
		mergesort(A,start,(start+end)/2);
		mergesort(A,(start+end)/2+1,end);
		merge(A,start,end);
	}

}


void solution(int **S, int i, int j)
{
	if(S[i][j]==-1 || i==j)
		return;
	else
	{
		cout << S[i][j] << " ";
		solution(S,i,S[i][j]);
		solution(S,S[i][j],j);
	}
}



int main()
{
	int n;
	cin >> n;
	interval *A=new interval[n];
	int D[n+2][n+2];
	int **S = (int **)malloc((n+2)* sizeof(int *));
    for (int i=0; i<n+2; i++)
         S[i] = (int *)malloc((n+2)* sizeof(int));
	for (int i = 0; i < n; ++i)
	{
		cin >> A[i].s;
		cin >> A[i].f;
	}
	mergesort(A,0,n-1);
	/*for (int i = 0; i < n; ++i)
	{
		cout <<  A[i].s << " ";
		cout << A[i].f << endl;
	}*/
	interval *B=new interval[n+2];
	B[0].s=0;   // Dummy Task
	B[0].f=0;
	for (int i = 0; i < n; ++i)
	{
		B[i+1]=A[i];
	}
	B[n+1].s=B[n].f;
	B[n+1].f=B[n].f;
	int k=0;
	for (k = 0; k < n+2; k++)
	{
		for (int r = 0; r+k < n+2; r++)
		{
			if(k==0)
				D[r][r+k]=0;
			else if(k==1)
				{
					D[r][r+k]=0;
					S[r][r+k]=-1;
				}
			else
			{
				S[r][r+k]=-1;
				int m;
				int ans;
				int max=0;
				for (m = r+1; m < r+k; m++)
				{
					if(B[m].s>=B[r].f && B[m].f<=B[r+k].s)
						ans=D[r][m]+D[m][r+k]+1;
					else
						ans=0;
					if(ans>max)
					{
						max=ans;
						S[r][r+k]=m;
					}

				}
				D[r][r+k]=max;
			}
		}
	}
	cout << D[0][n+1] << endl;
	/*for (int i = 0; i < n+2; ++i)
	{
	     for (int j = 0; j < n+2; ++j)
	     {
	     	cout << S[i][j] << " " ;
	     }
	     cout << endl;
	}*/
	
	solution(S,0,n+1);
	cout << endl;
	return 0;
}
