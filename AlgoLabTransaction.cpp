#include<iostream>
#include<new>
#include<iomanip>
#include<cmath>
using namespace std;

typedef struct a{
	int x;
	int i;
	int j;
}dates;


typedef struct b{
	int x;
	int i;
	int j;
	int min;
	int max;
}data;

dates conq(int* B,int* S,int i,int j,int C)
{
	int mid=(i+j)/2;
	int k,l;
	int mini=i;
	int maxj=j;
	for(k=i;k<=mid;k++)
	{
		if(B[k]<B[mini])
			mini=k;
	}
	for(l=mid+1;l<=j;l++)
	{
		if(S[l]>S[maxj])
			maxj=l;
	}
	int x=(C/B[mini])*(S[maxj]-B[mini]);
	dates A;
	A.x=x;
	A.i=mini;
	A.j=maxj;
	return A;
}




dates st1(int *B, int* S,int i,int j, int C)
{
	if(i==j)
	{
		dates A;
		A.x=floor(C/B[i])*(S[j]-B[i]);
		A.i=i;
		A.j=j;
		return A;
	}
	else
	{
		dates m1=st1(B,S,i,(i+j)/2,C);
		dates m2=st1(B,S,(i+j)/2+1,j,C);
		dates m3=conq(B,S,i,j,C);
		dates l;
		if(m1.x>m2.x)
			l=m1;
		else
			l=m2;
		if(l.x>m3.x)
			return l;
		else
			return m3;
	}
}

void singletrans1(int *B, int* S,int n, int C)
{
	dates A=st1(B,S,0,n-1,C);
	cout << "#Single Transaction (O(nlogn)) :" << endl << endl; 
	cout << "Buying Date: " << A.i <<", Buying Rate: "<< B[A.i]<< endl;
	cout << "Selling Date: " << A.j <<", Selling Rate: "<< S[A.j]<< endl;
	cout << "Maximum profit: " << A.x << endl << endl;
}



data st2(int *B, int* S,int i,int j, int C)
{
	if(i==j)
	{
		data A;
		A.x=(C/B[i])*(S[j]-B[i]);
		A.i=i;
		A.j=j;
		A.min=i;
		A.max=j;
		return A;
	}
	else
	{
		data m1=st2(B,S,i,(i+j)/2,C);
		data m2=st2(B,S,(i+j)/2+1,j,C);
		int mini=m1.min;
		int maxj=m2.max;
		int x=(C/B[mini])*(S[maxj]-B[mini]);
		data m3;
		m3.x=x;
		m3.i=mini;
		m3.j=maxj;
		/*dates m3=conq(B,S,i,j,C);*/
		data l;
		if(m1.x>m2.x)
			l=m1;
		else
			l=m2;

		if(l.x<m3.x)
			l=m3;

		if(B[m1.min]<=B[m2.min])
			l.min=m1.min;
		else
			l.min=m2.min;
		if(S[m1.max]>=S[m2.max])
			l.max=m1.max;
		else
			l.max=m2.max;
		return l;
	}
}

void singletrans2(int *B, int* S,int n, int C)
{
	data A=st2(B,S,0,n-1,C);
	cout << "#Single Transaction (O(n)) :" << endl << endl; 
	cout << "Buying Date: " << A.i <<", Buying Rate: "<< B[A.i]<< endl;
	cout << "Selling Date: " << A.j <<", Selling Rate: "<< S[A.j]<< endl;
	cout << "Maximum profit: " << A.x << endl << endl;
}


void solution(int* SH,int* D, int i, int* B, int* S)
{
	if(i<1)
		{
			cout << "Initial Capital = " << D[0] << endl << endl;
			return;
		}
	else
	{
		if(SH[i]==-1)
			{
				solution(SH,D,i-1,B,S);
				cout << "Buying Date = " <<i-1 << "," << "Buying Rate = " << B[i-1]<< endl;
				cout << "Selling Date = " <<i-1 << "," << "Selling Rate = " << S[i-1]<< endl;
				cout << "Current Capital = " <<D[i] << endl << endl; 
			}
		else if(SH[i]>0)
		{
			solution(SH,D,SH[i]-1,B,S);
			cout << "Buying Date = " <<SH[i]-1 << "," << "Buying Rate = " << B[SH[i]-1]<< endl;
			cout << "Selling Date = " <<i-1 << "," << "Selling Rate = " << S[i-1]<< endl;
			cout << "Current Capital = " <<D[i] << endl << endl; 

		}
		else
			solution(SH,D,i-1,B,S);
	}
}

void multitrans(int* B,int* S,int n,int C)
{
	int k;
	int* D=new int[n+1];
	D[0]=C;
	int* SH=new int[n+1];
	SH[0]=-1000;
	int l=0;
	for(k=1;k<=n;k++)
	{
		if(k==1)
		{
			if(B[k-1]<S[k-1])
			{
			int x=(C/B[k-1])*(S[k-1]-B[k-1]);
			D[k]=C+x;
			SH[k]=-1;
			}
			else
			{
			D[k]=C+0;
			SH[k]=-2;
			}
		}
		else
		{
			int q1,q2;
			if(B[k-1]<S[k-1])
			{
			int x=(D[k-1]/B[k-1])*(S[k-1]-B[k-1]);
			q1=D[k-1]+x;
			}
			else
				q1=D[k-1]+0;
			int max=0;
			int maxf=k;
			int f;
			int x;
			for(f=k;f>=1;f--)
			{
				if(B[f-1]<S[k-1])
					x=(D[f-1]/B[f-1])*(S[k-1]-B[f-1]);
				else
					x=0;
				if(x>=max)
					{
					max=x;
					maxf=f;
					}
			}
			q2=D[maxf-1]+max;
			if(q1>=q2)
				{
					D[k]=q1;
					if(q1!=D[k-1])
					{
					SH[k]=-1;
					}
					else
					{
						SH[k]=-2;
					}
				}
			else
				{	
					D[k]=q2;
					SH[k]=maxf;
				}
			
		}
	}
	cout << "#Multiple Transactions :" << endl << endl;
	solution(SH,D,n,B,S);
	cout << "Maximum Profit = " << D[n]-C << endl;
}




int main()
{
	int n,i;
	cin >> n;
	int* B=new int[n];
	int* S=new int[n];
	for(i=0;i<n;i++)
		cin >> B[i];
	for(i=0;i<n;i++)
		cin >> S[i];
	int C;
	cin >> C;
	singletrans1(B,S,n,C);
	singletrans2(B,S,n,C);
	multitrans(B,S,n,C);
	return 0;
	
}