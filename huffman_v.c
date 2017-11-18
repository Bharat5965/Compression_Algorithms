#include <stdio.h>
#include <string.h>
#include<time.h> 
typedef struct node_t {
	struct node_t *left, *right;
	int freq;
	char c;
} *node;

struct node_t pool[256] = {{0}};
node qqq[255], *q = qqq - 1;
int n_nodes = 0, qend = 1;
char *code[128] = {0}, buf[10000000];
char Str[10000000]; 
node new_node(int freq, char c, node a, node b)
{
	node n = pool + n_nodes++;
	if (freq) n->c = c, n->freq = freq;
	else {
		n->left = a, n->right = b;
		n->freq = a->freq + b->freq;
	}
	return n;
}
void qinsert(node n)
{
	int j, i = qend++;
	while ((j = i / 2)) {
		if (q[j]->freq <= n->freq) break;
		q[i] = q[j], i = j;
	}
	q[i] = n;
}
 
node qremove()
{
	int i, l;
	node n = q[i = 1];
 
	if (qend < 2) return 0;
	qend--;
	while ((l = i * 2) < qend) {
		if (l + 1 < qend && q[l + 1]->freq < q[l]->freq) l++;
		q[i] = q[l], i = l;
	}
	q[i] = q[qend];
	return n;
}
 
void build_code(node n, char *s, int len)
{
	static char *out = buf;
	if (n->c) {
		s[len] = 0;
		strcpy(out, s);
		code[n->c] = out;
		out += len + 1;
		return;
	}
 
	s[len] = '0'; build_code(n->left,  s, len + 1);
	s[len] = '1'; build_code(n->right, s, len + 1);
}
 
void init()
{
	int i,j=0, freq[128] = {0};
	char c[16];
 
	while (Str[j]){ 
		freq[Str[j++]]++;
	}
 
	for (i = 0; i < 128; i++)
		if (freq[i]) qinsert(new_node(freq[i], i, 0, 0));
 
	while (qend > 2) 
		qinsert(new_node(0, 0, qremove(), qremove()));
 
	build_code(q[1], c, 0);
}
 
void encode(char *out)
{
	int i=0;
	int orignal_bits=0,after=0,saved=0;
	while (Str[i]) {
		strcpy(out, code[Str[i]]);
		orignal_bits++;
		after=after+strlen(code[Str[i]]);
		out += strlen(code[Str[i++]]);
	}
	orignal_bits=8*orignal_bits;
	saved=orignal_bits-after;
	printf("Bits before compression= %d\n",orignal_bits);
	printf("Bits after compression= %d\n",after);
	printf("Bits saved = %d\n",saved);
}
void decode(const char *s, node t)
{
	node n = t;
	while (*s) {
		if (*s++ == '0') n = n->left;
		else n = n->right;
 
		if (n->c) putchar(n->c), n = t;
	}
 
	putchar('\n');
	if (t != n) printf("garbage input\n");
}
 
int main(void)
{
	int i=0;
	FILE *infile;
	char c;
 	char buf[10000000],filename1[25];
 	clock_t start,end;
	double cpu_time_used;
    
 	printf("Enter the filename to open \n");
    scanf("%s", filename1);
    infile = fopen(filename1, "r");
    c = fgetc(infile);
    while (c != EOF)
    {
    	Str[i]=c;
        c = fgetc(infile);
        i++;
    }
    fclose(infile);
    start=clock();
	init();
	
	for (i = 0; i < 128; i++)
		if (code[i]) printf("'%c': %s\n", i, code[i]);
	encode(buf);
	printf("encoded: %s\n", buf);
 	
	printf("decoded: ");
	decode(buf, q[1]);
 	end=clock();
	cpu_time_used=((double)(end-start))/CLOCKS_PER_SEC;
	printf("\ntime taken is %f",cpu_time_used);
	return 0;
}
