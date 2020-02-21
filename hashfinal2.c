#include <stdio.h> 
#include <string.h> 
#include <malloc.h>
struct library {
	int b;
	int day;
	int per;
	int lid;
	int *id;
	int *scanned;
	int scan;
	int sumscore;
	float ratio;
};
typedef struct library libr;
int main()
{
	FILE *fp;
	libr *item;
	fp=fopen("f_libraries_of_the_world.txt","r");
	int i,j,n,max;
	int books,lib,days;
	int *score;
	fscanf(fp,"%d ",&books);
	fscanf(fp,"%d ",&lib);
	fscanf(fp,"%d\n",&days);
	
	score=(int*)malloc(sizeof(int)*books);
	for(i=0;i<books;i++)
	{
		fscanf(fp,"%d ",&score[i]);
	}

	item=(libr*)malloc(sizeof(libr)*lib);
	for(i=0;i<lib;i++)
	{
		fscanf(fp,"%d ",&item[i].b);
		fscanf(fp,"%d ",&item[i].day);
		fscanf(fp,"%d\n",&item[i].per);
		item[i].id=(int*)malloc(sizeof(int)*(item[i].b));
		item[i].scanned=(int*)malloc(sizeof(int)*(item[i].b));
		for(j=0;j<item[i].b;j++)
			fscanf(fp,"%d ",&item[i].id[j]);
		item[i].lid=i;
	}
	int x,y;
    libr temp;
    for(i=0;i<lib;i++)
    {
    	item[i].sumscore=0; 	
    	for(x=0;x<item[i].b;x++)
	  		item[i].sumscore=item[i].sumscore+score[item[i].id[x]]; 	
	   	item[i].ratio=(float)item[i].sumscore/item[i].day;
	}

    //sort
    for (x = 0; x<lib-1; x++)
    {
        for (y = 0; y < (lib-1-x); y++)
        {
            if (item[y].ratio < item[y + 1].ratio)
            {
                temp = item[y];
                item[y] = item[y+1];
                item[y+1] = temp;
            } 
        }
    }
	int a,b,c=0,d;     
    int m=0;
	float maxi=0;
    int k=0,t;
    int sum=0;j=0;
//    while((sum+item[j].day)<days && j<lib)
//    {
//    	sum=sum+item[j].day;
//    	j++;
//	}
	int sign=lib;
	t=0;

	for(i=0;i<lib;i++)
	{	
//	    for(a=i;a<lib;a++)
//    	{
//    		item[a].sumscore=0;
//    		for(b=0;b<item[a].b;b++)
//	    		item[a].sumscore=item[a].sumscore+score[item[a].id[b]]; 	
//	    	item[a].ratio=(float)item[a].sumscore/item[a].day;
//	    	
//	    	if(item[a].ratio>maxi)
//	    	{
//	    		maxi=item[a].ratio;
//				c=a;
//				temp = item[i];
//        		item[i] = item[c];
//        		item[c] = temp;
//	    		
//			}
//		}
		//printf("%d",item[i].lid);
				
		//printf("%d",item[i].lid);
		//sort	
		for(x=0;x<item[i].b;x++)
		{
			for(j=0;j<item[i].b-x-1;j++)
			{
				if(score[item[i].id[j]]<score[item[i].id[j+1]])
				{
					t=item[i].id[j];
					item[i].id[j]=item[i].id[j+1];
					item[i].id[j+1]=t;
				}
			}
		}
		for(k=0;k<item[i].b;k++)
		{
			item[i].scanned[k]=item[i].id[k];
			score[item[i].scanned[k]]=m--;
		}
		item[i].scan=k;
	}
	int len;
	fclose(fp);
	fp=fopen("o6.txt","w");
	fprintf(fp,"%d",sign);
	for(i=0;i<sign;i++)
	{
		len=item[i].scan;
		fprintf(fp,"\n%d ",item[i].lid);
		fprintf(fp,"%d\n",len);
		for(j=0;j<len;j++)
			fprintf(fp,"%d ",item[i].scanned[j]);
	}
	fclose(fp);
	return 0;
}

