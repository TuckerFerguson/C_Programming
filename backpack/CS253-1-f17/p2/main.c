#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
void printUsage();

int main(int argc, char **argv)
{
  char *mval = NULL;
  int index = 0;
  int match = 0;
  int words = 0;
  int lines = 0;
  int chars = 0;
  int d1 = 0;
  int d3 = 0;
  int d4 = 0;
  int d5 = 0;
  int d6 = 0;
  int d7 = 0;
  int d8 = 0;
  int d2 = 0;
  int d9 = 0;
  int d0 = 0;
  int c = 0;
  opterr = 0;


while ((c = getopt (argc, argv, "m:h")) != -1){
    switch (c)
      {
      case 'm':
	mval = optarg;
        break;
      case 'h':
        printUsage();
	break;
      case '?':
        if (optopt == 'm')
          fprintf (stderr, "Option -%c requires an argument.\n", optopt);
        else if (isprint (optopt))
          fprintf (stderr, "Unknown option `-%c'.\n", optopt);
        else
          fprintf (stderr, "Unknown option character `\\x%x'.\n", optopt);
        return 1;
      default:
        abort ();
      }
}

char ch;
char prevchar;
while ((ch = getchar()) != EOF){
++chars;

if( ch  == '\n'){++words;}
if( ch == ' ' && prevchar != ' '){++words;}
if(ch == '\n') {++lines;}
if(ch == '0') {++d0;}
if( ch == '1') {++d1;}
if( ch == '2') {++d2;}
if( ch == '3') {++d3;}
if( ch == '4') {++d4;}
if( ch == '5') {++d5;}
if( ch == '6') {++d6;}
if( ch == '7') {++d7;}
if( ch == '8') {++d8;}
if( ch == '9') {++d9;}
if(mval != NULL){
	if(ch == mval[index]){
		index ++;
		if(mval[index] == '\0'){
			++match;
		index = 0;
		}
	}
	else if( ch != mval[index]){
		index = 0;
	}
}


prevchar = ch;

}

printf("words: %d\n", words);
printf("chars: %d\n", chars);
printf("lines: %d\n", lines);
printf("digit 0: %d\n", d0);
printf("digit 1: %d\n", d1);
printf("digit 2: %d\n", d2);
printf("digit 3: %d\n", d3);
printf("digit 4: %d\n", d4);
printf("digit 5: %d\n", d5);
printf("digit 6: %d\n", d6);
printf("digit 7: %d\n", d7);
printf("digit 8: %d\n", d8);
printf("digit 9: %d\n", d9);
printf("Matched %s: %d\n", mval, match);

return 1;

}
void printUsage(){
	printf("Usage:\n -m <match>\n -h\n");
	exit(1);
}
