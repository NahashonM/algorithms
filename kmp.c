#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//
// KMP(Knuth-Morris-Pratt) Patten matching algorithm
//
//---------------------------------------------------



//
// Compute the prefix Table
// @param pattern: the pattern string
// @param szPattern: Length of the pattern string
// @param prefTable: The prefix table; length should be  = to szPattern
void genPrefixTable(const char* pattern, int szPattern, int* prefixTable) {
	
	int length = 0;			// length of current longest prefix
	prefixTable[0] = 0;		// first entry is always 0 as first character has no perfect prefix
	
	for( int i = 1; i < szPattern ; i++) {
		
		if(pattern[i] == pattern[length]) {
			
			length++;
			prefixTable[i] = length;

		}else {

			if(length != 0) {		// check if there is a previous prefix that has mismatch character
				length = prefixTable[length - 1];
				i--;     			//decrease i to avoid effect of increasing after iteration while we check previous prefixes
			}else
				prefixTable[i] = 0;
		}
	}

}

// Find pattern in text
int kmpPatternSearch(const char* pattern, const int* prefixTable, int szPattern, const char* text, int szText) {
	
	if (!pattern || !text || !prefixTable ) return 0;			// check empty text, pattern and prefixTable arrays
	
	int j = 0, count = 0;
	for(int i = 0; i < szText; i++){
		printf("%d,%d ",i,j);
		if ( text[i] == pattern[j]) {
			j++;
			if(j==szPattern) { 
					count++; 
					j=0;						// if skipping matched characters
					//j=prefixTable[j-1];		// if matched chars can be part of next match
			}
			continue;
		}else if (j) {
			j = prefixTable[j-1];
			i--;								// readjust the text so that mismatch alligns with first character of pattern after adjustments
		}
	}

	return count;
}

//
//
//
int main(int argc, char**argv) {
	
	char* text =  "browbrobrobrobrownck brOwn fox jumped over the lazy dog";
	char* pattern="brobrobrow";
	int	szPattern= strlen(pattern);
	int szText= strlen(text);

	int* prefixTable = (int*)malloc(sizeof(int) * szPattern );					// allocate memory for the prefix table
	if (!prefixTable) return 0;														// cod-> mem allocation failed

	genPrefixTable(pattern, szPattern, prefixTable);							// populate the prefix table
	
	int count = 0;
	count = kmpPatternSearch(pattern, prefixTable, szPattern, text, szText);	// search for pattern in text
	
	printf("num occurences = %d", count);

	
	free(prefixTable);
	
	//int* bht = gen_bht_table(pattern, 5, 256 );
	 
	//if (bht) {

	//	for(int i = 0; i < 256; i++)
	//			printf("%d", bht[i]);

	//	free(bht);
	//}
	
}



// Creates BHT table for Bad Character Heuristics
// @Param pattern: The pattern P being looked up in text T
// @Param szPattern: Length of the pattern P
// @Param szAlphabet: Length of the alphabet
//----------------------------------------------------------------------------
int* gen_bht_table(const char* pattern, int szPattern, int szAlphabet) {
	
	// check 0 length pattern & alphabet and empty pattern
	if (!szAlphabet || !szPattern || !pattern) return (int*)0;

	// allocate memory for the bht table
	int* bht = (int*)( malloc( sizeof(int) * szAlphabet ));
	if (!bht) return (void*)bht;

	// set the alignment values for each alphabet character in the bht
	for(int i=0; i < szAlphabet; i++) bht[i] = szPattern;

	for(int i=0; i < szPattern - 1; i++) if ( (int)pattern[i] < szAlphabet ) bht[ pattern[i] ] = szPattern - 1 - i;

	return bht;
}
