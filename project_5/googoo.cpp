#include <iostream>
#include <cctype>
#include <cassert>
#include <cstring>

using namespace std;

const int MAX_WORD_LENGTH = 20;

void adjustArray(int distance[],
	             char word1[][MAX_WORD_LENGTH+1],
                 char word2[][MAX_WORD_LENGTH+1],
                 int nCriteria,
				 int startingpos)
{
	//adjusts the arrays distance, word1, word2
	for(int p=startingpos; p<nCriteria-1; p++){
				distance[p]=distance[p+1];
				}
	distance[nCriteria-1]=0;
	for(int p=startingpos; p<nCriteria-1;p++){
		for(int col=0; col<MAX_WORD_LENGTH;col++){
			word1[p][col]=word1[p+1][col];
		}
	}
	word1[nCriteria-1][0] = '\0';

	for(int p=startingpos; p<nCriteria-1;p++){
		for(int col=0; col<MAX_WORD_LENGTH;col++){
			word2[p][col]=word2[p+1][col];
		}
	}
	word2[nCriteria-1][0] = '\0';
}
int normalizeCriteria(int distance[],
                      char word1[][MAX_WORD_LENGTH+1],
                      char word2[][MAX_WORD_LENGTH+1],
                      int nCriteria)
{
	if (nCriteria<=0)
		return 0;
	//if word1 or word2 is empty
	for(int k=0; k < nCriteria-1;k++){
	for(int row=0;row<nCriteria;row++)
		if(word1[row][0]=='\0'){
			adjustArray(distance, word1, word2, nCriteria, row);
		}
	for(int row=0;row<nCriteria;row++)
		if(word2[row][0]=='\0'){
			adjustArray(distance, word1, word2, nCriteria, row);
		}
	}
	//checks if the distance is nonpositive
	for(int k=0; k < nCriteria-1;k++)
		for(int d=0; d<nCriteria;d++)
			if(distance[d]<=0)
				adjustArray(distance, word1, word2, nCriteria, d);
	//checks if the word has a noncharacter
	for(int k = 0; k <nCriteria-1;k++){
	for(int row = 0; row<nCriteria;row++)
		for(int col = 0; word1[row][col]!='\0';col++)
			if(!isalpha(word1[row][col]))
				adjustArray(distance, word1, word2, nCriteria, row);
	for(int row = 0; row<nCriteria;row++)
		for(int col = 0; word2[row][col]!='\0';col++)
			if(!isalpha(word2[row][col]))
				adjustArray(distance, word1, word2, nCriteria, row);
	}
	//changes letters to lowercase
	for(int k = 0; k< nCriteria; k++)
		for(int j =0; word1[k][j]!='\0'; j++)
			word1[k][j]=tolower(word1[k][j]);
	for(int k =0; k<nCriteria;k++)
		for(int j=0; word2[k][j]!='\0'; j++)
			word2[k][j]=tolower(word2[k][j]);
	//if same w1 and w2 word in two different criteria, removes smaller distance
	for(int k = 0; k <nCriteria-1;k++){
	for(int initialrow=0; initialrow< nCriteria-1; initialrow++){
		for(int row = initialrow+1; row<nCriteria;row++){
			if(strcmp(word1[initialrow], word1[row])==0){
				if(strcmp(word2[initialrow], word2[row])==0){
					if (distance[initialrow]<distance[row]){
						adjustArray(distance, word1, word2, nCriteria, initialrow);
					}
					else if (distance[initialrow]>distance[row]){
						adjustArray(distance, word1, word2, nCriteria, row);

					}
					else if (distance[initialrow]==distance[row]){	//if same w1 and w2 word, and distance
						adjustArray(distance, word1, word2, nCriteria, row);
						
					}
				}
			}
		}
	}
	}
	//counts the normalized criteria
	int index=0;
	for(int k=0;k<nCriteria;k++)
		if(distance[k]>0&& word1[k][0]!='\0' && word2[k][0]!='\0')
			index++;
	return index;
}
int computeScore(const int distance[],
                 const char word1[][MAX_WORD_LENGTH+1],
                 const char word2[][MAX_WORD_LENGTH+1],
                 int nCriteria,
                 const char document[])
{
	char storage[200][201];
	int row=0; //for the position of the storage array
	int col=0; //for the position of the storage array
	bool firstspace=true; //in case there are multiple spaces
	// k stands for the row of the array storage
	
	for(int k=0; k<201 && document[k]!='\0';k++){
		//if not alpha, and not space then pos++
		if(document[k]==' ' && firstspace==true){
			storage[row][col]='\0';
			row++; //move to next row when its a nonconsecutive space
			col=0;
			firstspace=false;
		}
		if(isalpha(document[k])){
			storage[row][col]=document[k]; //put into string storage[k]
			storage[row][col]=tolower(storage[row][col]);
			col++;
			firstspace=true;
		}
		if(document[k+1]=='\0')
			storage[row][col]='\0';
	}
	
	int criteriaMet=0;
	for(int k=0;k<nCriteria;k++){ //outer loop for testing one criteria at a time
		for(int j=0;j<201;j++){  //inner loop for storage array to check the contents against criteria
			if(strcmp(word1[k], storage[j])==0){
				for(int d=1; d<=distance[k];d++)
					if(strcmp(word2[k], storage[j+d])==0){//if it is the same word, check for second word within distance
						criteriaMet++; //increase count
						j=0;
						k++;
						break;
					}
			}
		}
	}
	return criteriaMet;
}

int main()
{const int TEST1_NCRITERIA = 4;
            int test1dist[TEST1_NCRITERIA] = {
                2,           4,          1,           13
            };
            char test1w1[TEST1_NCRITERIA][MAX_WORD_LENGTH+1] = {
                "fat",       "deranged", "pretty", "feeling"
            };
            char test1w2[TEST1_NCRITERIA][MAX_WORD_LENGTH+1] = {
                "cat", "monster",    "pot",      "lazy"
            };

int distance[7]={2, 0, 6, -1, 3, 2, 1};
char testing1[7][21]={"Hello", "Goodbye", "Hello", "Goodbye", "Chicken", "Hello","Have"};
char testing2[7][21]={"She", "Unemp-loyment", "She", "Glasses", "","She","Bad"};
assert(normalizeCriteria(distance, testing1, testing2, 7)==2);//Tests the function as a whole


int distance1[3]={2, 0, 6};
char testing3[3][21]={"Hello", "Goodbye", "Hello"};
char testing4[3][21]={"She", "Unemployment", "Boy"};
assert(normalizeCriteria(distance1, testing3, testing4, 3)==2);//if the distance is zero

int otherdistance[3]={0, 0, 6};
char othertest1[3][21]={"Hello", "Goodbye", "Hello"};
char othertest2[3][21]={"She", "Unemployment", "Boy"};
assert(normalizeCriteria(otherdistance, othertest1, othertest2, 3)==1);//if multiple distances are zero


int distance2[3]={2, -1, 6};
char testing5[3][21]={"Hello", "Goodbye", "Hello"};
char testing6[3][21]={"She", "Unemployment", "Boy"};
assert(normalizeCriteria(distance2, testing5, testing6, 3)==2);//if the distance is less than zero

int otherdistance1[3]={-1, -1, 6};
char othertest3[3][21]={"Hello", "Goodbye", "Hello"};
char othertest4[3][21]={"She", "Unemployment", "Boy"};
assert(normalizeCriteria(otherdistance1, othertest3, othertest4, 3)==1);//if multiple distances are less than zero

int distance3[3]={2, 1, 6};
char testing7[3][21]={"Hello", "Goodbye", "Hello"};
char testing8[3][21]={"She", "Unemployment", "Boy"};
assert(normalizeCriteria(distance3, testing7, testing8, 3)==3);//if the distance is positive

int distance4[3]={2, 3, 6};
char testing9[3][21]={"Hello", "Goodbye", "Hello"};
char testing10[3][21]={"", "Unemployment", "Boy"};
assert(normalizeCriteria(distance4, testing9, testing10, 3)==2);//word has no characters

int otherdistance2[3]={2, 3, 6};
char othertest5[3][21]={"", "s", "s"};
char othertest6[3][21]={"s", "t", ""};
assert(normalizeCriteria(otherdistance2, othertest5, othertest6, 3)==1);//if multiple words have no characters

int distance5[3]={2, 3, 6};
char testing11[3][21]={"Hello", "Good-bye", "Hello"};
char testing12[3][21]={"She", "Unemployment", "Boy"};
assert(normalizeCriteria(distance5, testing11, testing12, 3)==2);//word1 has a character that isnt a letter

int otherdistance5[3]={2, 3, 6};
char othertesting11[3][21]={"Hel9lo", "Good-bye", "Hello"};
char othertesting12[3][21]={"She", "Unemployment", "Boy"};
assert(normalizeCriteria(otherdistance5, othertesting11, othertesting12, 3)==1);// multiple words in word1 have characters that aren't letters

int distance11[3]={2, 3, 6};
char testing23[3][21]={"Hello", "Goodbye", "Hello"};
char testing24[3][21]={"She", "Unempl-oyment", "Boy"};
assert(normalizeCriteria(distance11, testing23, testing24, 3)==2);//word2 has a character that isnt a letter


int odistance11[3]={2, 3, 6};
char otesting23[3][21]={"Hello", "Goodbye", "Hello"};
char otesting24[3][21]={"Sh9e", "Unemployment", "B3oy"};
assert(normalizeCriteria(odistance11, otesting23, otesting24, 3)==1);//multiple words in word2 have characters that arent letters

int distance6[3]={1, 2, 2};
char testing13[3][21]={"Hello", "Goodbye", "Hello"};
char testing14[3][21]={"She", "Unemployment", "She"};
assert(normalizeCriteria(distance6, testing13, testing14, 3)==2);//two criteria have the same w1 and w2 values, removes the lesser distance

int distance7[3]={2, 3, 2};
char testing15[3][21]={"Hello", "Goodbye", "Hello"};
char testing16[3][21]={"She", "Unemployment", "She"};
assert(normalizeCriteria(distance7, testing15, testing16, 3)==2);//criteria have the same w1 and w2 and distance values
int distance8[3]={2, 7, 6};
char testing17[3][21]={"Hello", "Hello", "Hello"};
char testing18[3][21]={"She", "She", "She"};
assert(normalizeCriteria(distance8, testing17, testing18, 3)==1);//more than two criteria have the same w1 and w2 values
int distance9[3]={2, 2, 6};
char testing19[3][21]={"Hello", "Goodbye", "Hello"};
char testing20[3][21]={"She", "Unemployment", "Boy"};

assert(normalizeCriteria(distance9, testing19, testing20, 3)==3);//returns proper value for normal input
int distance10[3]={2, 2, 6};
char testing21[3][21]={"Hello", "Goodbye", "Hello"};
char testing22[3][21]={"She", "Unemployment", "Boy"};
assert(normalizeCriteria(distance10, testing21, testing22, 3)==3);//the remaining criteria occupy positions 0- r-1, where r is the return value, will need to output the resulting array

assert(normalizeCriteria(distance, testing1, testing2, 0)==0);//nCriteria is 0 
assert(normalizeCriteria(distance, testing1, testing2, -2)==0);//nCriteria is less than 0
           
}