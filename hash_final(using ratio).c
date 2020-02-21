#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include<math.h>
struct library {
	int b;
	int day;
	int per;
	int *id;
	float value;
    int lib_id;
    int sum_score;
    int dayr;
    int days_book;

    int howmb;
    int *whichb;
};
typedef struct library libr;

int check_is_book_scanned(int *a,int key,int n);
int *scannedbooks;
int scan_index=0;
int main()
{
	FILE *fp;
	libr *item;


	fp=fopen("f_libraries_of_the_world.txt","r");
	int i,j,temp,n,max;
	int books,lib,days;
	int *score;
	fscanf(fp,"%d ",&books);
	fscanf(fp,"%d ",&lib);
	fscanf(fp,"%d\n",&days);

	score=(int*)malloc(sizeof(int)*(books));

    scannedbooks=(int*)malloc(sizeof(int)*(books));

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
        {
            fscanf(fp,"%d ",&item[i].id[j]);
            item[i].whichb=(int*)malloc(sizeof(int)*(item[i].b));
        }


	}

	printf("%d ",books);
	printf("%d ",lib);
	printf("%d\n",days);

	/*for(i=0;i<books;i++)
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
	}*/
	for(i=0;i<books;i++)
        {
            scannedbooks[i]=-1;

        }

	for(int z=0;z<lib ;z++)
    {
        item[z].sum_score=0;
        item[z].lib_id=z;
        item[z].dayr=0;
        item[z].days_book=0;

        item[z].dayr+= item[z].day;

        item[z].days_book= (int)(ceil((float)(item[z].b)/(item[z].per)));

        item[z].dayr+=item[z].days_book;

        for(int p=0;p<item[z].b;p++)
        {
            item[z].sum_score+= score[item[z].id[p]];
        }
       // printf("%d\n",sum_score);
        item[z].value=(float)item[z].sum_score/item[z].dayr;
    }

    // sort with increasing order of ratio
    libr tempratio;

   for (int p = 0; p < lib-1; p++)
    {

        int max_idx = p;
        for (int t = p+1; t < lib; t++)
            if (item[t].value > item[max_idx].value)
                max_idx = t;

        tempratio = item[max_idx];
        item[max_idx] = item[p];
        item[p] = tempratio;

    }

    // sort books_id w.r.t score
    int tp;
   for (int p = 0; p<lib; p++)
    {

        for (int d = 0; d < (item[p].b)-1; d++)
            {
                int max_idx = d;
                for (int t = d+1; t < item[p].b; t++)
                    if (score[item[p].id[t]]>score[item[p].id[max_idx]])
                        max_idx = t;

               tp=item[p].id[max_idx];
               item[p].id[max_idx]=item[p].id[d];
               item[p].id[d]=tp;

            }

    }


    int avail_days=days;
    int total_lib_scanned=0;
    int rs;
    for(int c=0;c<lib;c++)
        {
            item[c].howmb=0;
            int pick_max=0;
            int add_in_whichb=0;
            if((avail_days-item[c].day)>0)
                {
                    total_lib_scanned++;
                    avail_days-=item[c].day;
                    for(int l=0;l<item[c].b;l++)
                    {
                        rs=check_is_book_scanned(scannedbooks,item[c].id[pick_max],books);
                        //printf("%d",rs);

                        if(rs==1)
                        {
                        item[c].whichb[add_in_whichb++]=item[c].id[pick_max];

                        item[c].howmb+=1;
                        //printf("\n%d ",item[c].howmb);

                        scannedbooks[scan_index++]=item[c].id[pick_max++];
                        }
                        else
                        {
                            if(pick_max<=item[c].b)
                                pick_max++;
                        }




                    }

                }
            else break;
        }



/*	for(i=0;i<lib;i++)
    {
        printf("\n\nvalue %f \n",item[i].value);
        printf("lib_id  %d\n",item[i].lib_id);
        printf("days required  %d \n",item[i].dayr);
        printf("id in inc score order:");
        for(int g=0;g<item[i].b;g++)
            {printf("%d  ",item[i].id[g]);

            }

    }
*/
printf("\ntotal lib scanned %d",total_lib_scanned);

double hello=0;

for(int g=0;g<total_lib_scanned;g++)
{
   // printf("\n library with books %d %d\n\n",item[g].lib_id,item[g].howmb);
    for(int h=0;h<item[g].howmb;h++)
    {
         //printf("%d ",item[g].whichb[h]);
         hello+=score[item[g].whichb[h]];
    }

}

printf("score is %lf",hello);
	fclose(fp);


    fp=fopen("output6.txt","w");
    if(fp==NULL)
    {
        printf("\n\nno file");
    }
	fprintf(fp,"\n%d",total_lib_scanned);
	for(i=0;i<total_lib_scanned;i++)
	{   if(item[i].howmb!=0)
            {
                fprintf(fp,"\n%d ",item[i].lib_id);
                fprintf(fp,"%d\n",item[i].howmb);
                for(int j=0;j<item[i].howmb;j++)
                        fprintf(fp,"%d ",item[i].whichb[j]);
            }

	}
	fclose(fp);

	return 0;
}

int check_is_book_scanned(int *a, int key, int n)
    {
        for(int i=0;i<n;i++)
            if(a[i]==key)
                return 0;
        return 1;
    }
