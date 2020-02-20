#include <stdio.h> 
#include <string.h> 
#include <malloc.h>
struct library {
	int b;
	int lib_id;
	int day;
	int per;
	int *id;
	int *scores;
	int sum;
};
typedef struct library libr;
libr *item;

void swap(libr *a,libr *b)
{
	libr temp;
	temp=*a;
	*a=*b;
	*b=temp;
}

void swap_num(int *a,int *b)
{
	int temp;
	temp=*a;
	*a=*b;
	*b=temp;
}

void swap_lib(int lib)
{
	int i,j,max;
	for(i=0;i<lib;i++)
	{
		max=i;
		for(j=i+1;j<lib;j++)
		{	
			if(item[max].sum<item[j].sum)
			{
				max=j;				
			}
		}
		swap(&item[i],&item[max]);
	}
}

void assign_score(int books,int lib,int *score)
{
	int i,j,k,id;
	for(i=0;i<lib;i++)
	{
		item[i].sum=0;
		item[i].scores=(int*)malloc(sizeof(int)*(item[i].b));
		for(j=0;j<item[i].b;j++)
		{
			id=item[i].id[j];
			for(k=0;k<books;k++)	
			{
				if(id==k)
				{
					item[i].scores[j]=score[k];
					item[i].sum=item[i].sum+score[k];
					break;					
				}
			}		
		}		
	}
}

void book_priority(int lib)
{	
	int i,j,k,max;
	for(i=0;i<lib;i++)
	{
		for(j=0;j<item[i].b;j++)
		{
			max=j;
			for(k=j+1;k<item[i].b;k++)
			{	
				if(item[i].scores[max]<item[i].scores[k])
				{
					max=k;				
				}
			}
			swap_num(&item[i].scores[j],&item[i].scores[max]);
			swap_num(&item[i].id[j],&item[i].id[max]);
		}
	}
}

int main()
{
	FILE *fp,*ft;
	
	fp=fopen("f_libraries_of_the_world.txt","r");
	int i,j,k,count=0;
	int books,lib,days,rem_days;
	int *score,*temp;
	fscanf(fp,"%d ",&books);
	fscanf(fp,"%d ",&lib);
	fscanf(fp,"%d\n",&days);
	
	score=(int*)malloc(sizeof(int)*books);
	temp=(int*)malloc(sizeof(int)*lib);
	for(i=0;i<books;i++)
		fscanf(fp,"%d ",&score[i]);
	
	item=(libr*)malloc(sizeof(libr)*lib);
	for(i=0;i<lib;i++)
	{
		fscanf(fp,"%d ",&item[i].b);
		fscanf(fp,"%d ",&item[i].day);
		fscanf(fp,"%d\n",&item[i].per);
		item[i].lib_id=i;
		item[i].id=(int*)malloc(sizeof(int)*(item[i].b));
		for(j=0;j<item[i].b;j++)
			fscanf(fp,"%d ",&item[i].id[j]);
		
	}

	//score assigning to library book id
	assign_score(books,lib,score);

	//arrange in highest to lowest score sum
	swap_lib(lib);

	book_priority(lib);

	rem_days=days;
	for(i=0;i<lib;i++)
	{
		if(rem_days>item[i].day)
		{
			rem_days=rem_days-item[i].day;
			temp[count]=i;
			count++;
		}
	}
	fclose(fp);
	
	ft=fopen("o6.txt","w");	
	fprintf(ft,"%d\n",count);
	for(i=0;i<count;i++)
	{
		fprintf(ft,"%d %d\n",item[i].lib_id,item[i].b);
		for(j=0;j<item[i].b;j++)
		{
			fprintf(ft,"%d ",item[i].id[j]);
		}
		fprintf(ft,"\n");
	}
		
	fclose(ft);
	
	return 0;
}
