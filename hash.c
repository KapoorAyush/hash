#include <stdio.h> 
#include <string.h> 
#include <malloc.h>
int main()
{
	FILE *fp;
	fp=fopen("d_quite_big.in","r");
	int i,j=0,temp,n,max;
	int *arr;
	fscanf(fp,"%d ",&max);
	fscanf(fp,"%d\n",&n);
	arr=malloc(sizeof(int)*n);
	for(i=0;i<n;i++)
	{
		fscanf(fp,"%d ",&arr[i]);
	}
	for(i=n-1;i>=n/2;i--)
	{
		temp=arr[i];
		arr[i]=arr[j];
		arr[j]=temp;
		j++;
	}
	i=0;
	int sum=0;
	int sel[n];
	for(j=0;j<n;j++)
	{
		if((sum+arr[j])<=max)
		{
			sum=sum+arr[j];
			sel[i]=n-j-1;
			i++;
		}
	}
	fclose(fp);
	fp=fopen("o4.txt","w");
	fprintf(fp,"%d\n",i);
	for(j=i-1;j>=0;j--)
		fprintf(fp,"%d ",sel[j]);
	fclose(fp);
	printf(" %d",sum);
}
