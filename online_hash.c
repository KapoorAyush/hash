#include <stdio.h> 
#include <string.h> 
#include <malloc.h>
struct library {
	int b;
	int day;
	int per;
	int *id;
};
typedef struct library libr;
int main()
{
	FILE *fp;
	libr *item;
	fp=fopen("a_example.txt","r");
	int i,j,temp,n,max;
	int books,lib,days;
	int *score;
	fscanf(fp,"%d ",&books);
	fscanf(fp,"%d ",&lib);
	fscanf(fp,"%d\n",&days);
	
	score=(int*)malloc(sizeof(int)*books);
	for(i=0;i<books;i++)
		fscanf(fp,"%d ",&score[i]);
	
	item=(libr*)malloc(sizeof(libr)*lib);
	for(i=0;i<lib;i++)
	{
		fscanf(fp,"%d ",&item[i].b);
		fscanf(fp,"%d ",&item[i].day);
		fscanf(fp,"%d\n",&item[i].per);
		item[i].id=(int*)malloc(sizeof(int)*(item[i].b));
		for(j=0;j<item[i].b;j++)
			fscanf(fp,"%d ",&item[i].id[j]);
		
	}

	printf("%d ",books);
	printf("%d ",lib);
	printf("%d\n",days);

	for(i=0;i<books;i++)
		printf("%d ",score[i]);
	printf("\n");

	for(i=0;i<lib;i++)
	{
		printf("%d ",item[i].b);
		printf("%d ",item[i].day);
		printf("%d\n",item[i].per);
		for(j=0;j<item[i].b;j++)
			printf("%d ",item[i].id[j]);
		printf("\n");
	}
	
	fclose(fp);
	
	return 0;
}
