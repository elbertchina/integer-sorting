#include <xmtc.h>


void sort(int[], int,int);
int binarySearch(int[], int, int, int);
int main(){
	
        const int p = NTCU;
	
	const int Slen= s*p;
	const int SSlen=p-1;
	int S[Slen];

	spawn(0,s*p-1)
	{
	  S[$] = RANDOM[($*s*p)%NRAND];
	}
	sort(S,0,s*p-1);
	int SS[SSlen];//S prime array
	spawn(0,p-2)
	{
	  SS[$] = S[s*($+1)];
	}
	int c[NTCU][NTCU]={{0}};
	int partition[N];
	int serial[N];
		
	spawn(0,p-1)//binary search,c, partition,serial
	{
	  int i;
	  int out;
	  
	  for (int i=0;i<=N/p-1;i++)
	  {
	    out = binarySearch(SS,0,SSlen-1,A[i+$*N/p]);
	    c[$][out] = c[$][out]+1;
	    partition[i+$*N/p] = out;
	    serial[i+$*N/p] = c[$][out]-1;
	  }	  
	}
	int prefixSum[NTCU][NTCU]={{0}};//prefix-sums
	int sum[NTCU]={0};
	int global_ps[NTCU+1]={0};
	int j=0;
	while(j<NTCU)//prefixsum and sum
	{  
	  int i;
	  for (i=0; i<p;i++)
	  {
	    sum[j]=sum[j]+c[i][j];
	    if(i<p-1)
	    {
		 prefixSum[i+1][j]=sum[j];
	    }
	  }
	  
	  j++;
	}
	//global_ps[0]=sum[0];
	for (j=0;j<NTCU-1;j++)//global_ps
	{
	  global_ps[j+1] = global_ps[j]+ sum[j];
	}	
	global_ps[NTCU]=global_ps[NTCU-1]+sum[NTCU-1];
	spawn(0,p-1)// step4
	{
	  int j;
	  int pos;
	  for(j=$*N/p;j<($+1)*N/p;j++)
	  {
	    pos = global_ps[partition[j]] + prefixSum[$][partition[j]]+ serial[j];
	    result[pos]=A[j];
	  }
	}
	spawn(0,p-1)//step5
	{
	  sort(result,global_ps[$],global_ps[$+1]-1);
	}	
	/*int ii=0;
	for(ii=0;ii<N;ii++)
	{
	  printf(" %d)",result[ii]);
	}*/
	return 0;
}

void sort(int x[],int first,int last){
	int pivot,j,temp,i;
	if (first<last){
		pivot = first;
		i = first;
		j = last;
		while(i<j){
			while (x[i]<=x[pivot]&&i<last)
				i++;
			while (x[j]>x[pivot])
				j--;
			if (i<j){
				temp=x[i];
				x[i]=x[j];
				x[j]=temp;
			}
		}
	temp = x[pivot];
	x[pivot]=x[j];
	x[j]=temp;
	sort(x,first,j-1);
	sort(x,j+1,last);
	}	
}

int binarySearch(int array[], int first, int last,int search){
	int middle =( first+last)/2;
	while(first <= last){
	  if(array[middle] < search)
	  {  first = middle + 1;}
	  else if (array[middle]==search)
	  {  return middle; }
	  else
	  {  last = middle - 1; }
	  middle = (first + last) / 2;
	}
	
	
	return first;
	
}
