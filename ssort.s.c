#include <xmtc.h>
void sort(int[],int,int);
int main(){
sort(A,0,N-1);

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

