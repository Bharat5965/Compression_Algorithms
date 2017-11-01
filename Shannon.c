#include<stdio.h>
#include<conio.h>
#include<string.h>
#include<time.h>
struct node
{
	char sym;
	float pro;
	int arr[20];
	int top;
}s[95];
int tn=0;
typedef struct node node;
void shannon(int l,int h,node s[])
{
	float pack1=0,pack2=0,diff1=0,diff2=0;
	int i,d,k,j;
	if((l+1)==h || l==h || l>h)
	{
		if(l==h || l>h)
			return;
		s[h].arr[++(s[h].top)]=0;
		s[l].arr[++(s[l].top)]=1;
		return;
	}
	else
	{
		for(i=l;i<=h-1;i++)
			pack1=pack1+s[i].pro;
		pack2=pack2+s[h].pro;
		diff1=pack1-pack2;
		if(diff1< 0)
			diff1=diff1*-1;
		j=2;
		while(j!=h-l+1)
		{
			k=h-j;
			pack1=pack2=0;
			for(i=l;i<=k;i++)
				pack1=pack1+s[i].pro;
			for(i=h;i>k;i--)
				pack2=pack2+s[i].pro;
			diff2=pack1-pack2;
			if(diff2< 0)
				diff2=diff2*-1;
			if(diff2>=diff1)
				break;
			diff1=diff2;
			j++;
		}
		k++;
		for(i=l;i<=k;i++)
			s[i].arr[++(s[i].top)]=1;
		for(i=k+1;i<=h;i++)
			s[i].arr[++(s[i].top)]=0;
		shannon(l,k,s);
		shannon(k+1,h,s);
	}
}
int encode(char filename1[25],char filename2[25])
	{
		FILE *infile, *outfile;
		char ch;
		int i,j,orignal=0,after=0,compressed;
		infile = fopen(filename1, "r");
		outfile= fopen(filename2,"w");
		ch = fgetc(infile); 
    	while (ch != EOF)
    	{
        	orignal++;
			if (ch >=' ' && ch <= '~') 
			{			
				for(i=0;i<95;i++)
				{
					if(ch==s[i].sym)
					{
						for(j=0;j<=s[i].top;j++)
						{
							fprintf(outfile,"%d",s[i].arr[j]);
							after++;
						}
						fprintf(outfile," ");
						after++;
						break;		
					}
				}
			}
        	ch = fgetc(infile);
    	}
    	fclose(infile);
    	fclose(outfile);
    	orignal=orignal*8;
    	compressed=orignal-after;
    	printf("\nOrignal bits->%d\nBits after Compression->%d\nBits Saved->%d\n",orignal,after,compressed);
    	
    	return 0;
	}
int decode(char filename2[25])
{
	FILE *infile, *outfile;
	char ch;
	char filename1[25];
	int ar[20];
	int i,j,k,l,m=0;
    infile = fopen(filename2, "r");
    printf("Enter the filename for output \n");
    scanf("%s", filename1);
	outfile= fopen(filename1,"w");
	ch = fgetc(infile); 
    while(m==0)
		{
			i=0;
			while (ch !=' ')
    			{
    				ar[i]=ch-48;
					i++;
        			ch = fgetc(infile);
    			}
  			ch=fgetc(infile);
  			for(j=tn;j>0;j--)
			  {
			  	for(k=0;k<i;k++)
				  {
				  	if(ar[k]==s[j].arr[k]){
			  		  l=1;
				  	}
			  		else{
					  l=0;
					  break;
					  }	
				  }
				 if(l==1)
				 {
				 	fprintf(outfile,"%c",s[j].sym);
				 	break;
				 }
			  }
			 if(ch==EOF)
			 	m=1; 
   	
    	}
 	fclose(infile);
   	fclose(outfile);
    	


return 0;
}
int main()
{
	FILE *infile;
    int i,j,c = 0;
    int freq[95]={0};
	float x,total=0,p,uni=0;
	char ch;
	char filename1[25],filename2[25];
	node temp;
    clock_t start,end;
	double cpu_time_used;
    
    LOOP:
	printf("1.compress\t2.decompress\t3. exit\n");
    scanf("%d",&i);
    if(i==2){
    decode(filename2);
    goto LOOP;
    }
    if(i==3)
    exit(0);
    printf("Enter the filename to open \n");
    scanf("%s", filename1);
    infile = fopen(filename1, "r");
    printf("Enter the filename for output \n");
    scanf("%s", filename2);
    if (infile == NULL)
    {
        printf("Cannot open file \n");
        exit(0);
    }
    start=clock();
	ch = fgetc(infile); 
    while (ch != EOF)
    {
        if (ch >=' ' && ch <= '~') 
		{
			freq[ch-' ']++;
			uni++;
		}
        ch = fgetc(infile);
    }
    
   for (c = 0; c < 95; c++)
    {     
	  	if (freq[c] != 0)
		  	{
		  		p=(float)freq[c]/uni;
				s[tn].sym=c+' ';	
		  		s[tn].pro=p;
		  		total=total+s[tn].pro;
		  		tn++;
			  }	  
   }
   fclose(infile);
	
	for(j=1;j<=tn;j++)
	{
		for(i=0;i<tn;i++)
		{
			if((s[i].pro)>=(s[i+1].pro))
			{
				temp.pro=s[i].pro;
				temp.sym=s[i].sym;
				s[i].pro=s[i+1].pro;
				s[i].sym=s[i+1].sym;
				s[i+1].pro=temp.pro;
				s[i+1].sym=temp.sym;
			}
		}
	}
	for(i=0;i<tn+1;i++)
		s[i].top=-1;
	shannon(1,tn,s);
	printf("---------------------------------------------------------------");
	printf("\n\n\n\tSymbol\tProbability\tCode");
	for(i=tn;i>0;i--)
	{
		printf("\n\t%c\t%f\t",s[i].sym,s[i].pro);
		for(j=0;j<=s[i].top;j++)
			printf("%d",s[i].arr[j]);
	}
	printf("\n---------------------------------------------------------------\n");
	encode(filename1, filename2);
	end=clock();
	cpu_time_used=((double)(end-start))/CLOCKS_PER_SEC;
	printf("time taken is %f\n",cpu_time_used);
	goto LOOP;
	getch();
	return 0;
}
