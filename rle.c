#include<stdio.h>
#include<time.h>
char Rle[1000000];
int main ( )
{
	int i=0;
	FILE *fptr;
    char filename[25], c;
    time_t t;
	printf("Enter the filename to open \n");
    scanf("%s", filename);
    fptr = fopen(filename, "r");
    c = fgetc(fptr);
    while (c != EOF)
    {
    	Rle[i]=c;
        c = fgetc(fptr);
        i++;
    }
    fclose(fptr);
	printf("\n\n1 =>: Run - Length Encoding.\n\n2 =>: Run - Length Decoding.\n\n3 =>: Exit the Program.\n\nEnter your Choice =>:");
	scanf("%d",&i);
	switch(i)
	{
		case 1: RLEcompression();break;
		case 2: RLEdecompression();break;
		case 3: exit(0);break;
		default: printf("Please select the correct option");
	}
}
int RLEcompression()
{
	 
	FILE *outfile;
	clock_t start,end;
	int count=0,setcount=1,len,orignal_bits=0,compressed_bits=0,bits_saved=0;
	double timetaken;
	outfile=fopen("out.txt","w");
	start=clock();
	len=strlen(Rle);
	orignal_bits=8*len;
	while(count<len)
	{
    	if(Rle[count]==Rle[count+1])
    	{
    		setcount++;
    		count++;
    	}
    	else
    	{
   			printf("%c%d ",Rle[count],setcount);
    		fprintf(outfile, "%c%d ", Rle[count],setcount);
    		compressed_bits=compressed_bits+(8*2);
    		setcount=1;
    		count++;
    	}
	}
	bits_saved=orignal_bits-compressed_bits;
	printf("\norignal bits= %d\n",orignal_bits);
	printf("Compressed bits= %d\n",compressed_bits);
	printf("bits saved = %d\n\n",bits_saved);
	end=clock();
	timetaken=((double)(end-start))/CLOCKS_PER_SEC;
	printf("%f\n",timetaken);
}
int RLEdecompression()
{
FILE *outfile;
char filename1[25];
int count,i,len,j;
printf("Enter file for output");
scanf("%s", filename1);
outfile=fopen(filename1,"w");
len=strlen(Rle);
for(i=1;i<len;i=i+3)
{
	count=Rle[i]-'0';
	for(j=1;j<=count;j++)
	{
		printf("%c",Rle[i-1]);
		fprintf(outfile, "%c", Rle[i-1]);
	}
}
}
