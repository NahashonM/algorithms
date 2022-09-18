// 
// Boyer Moore Pattern Matching algorithm
//
// This implementaion uses only the bad character heuristics
//
//
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int genBhtTable(const char* pattern, int* bht, int szPattern, int szAlphabet);
int bmpPatternMatch(const char* pattern, const int* bhtTable, int szPattern, const char* text, int szText);

int main(int argc, char**argv) {

	char* text = "The Quick Brown fox mpedxjumped over the lazy dog";	
	char* pattern="jumped";
	int szText = strlen(text), szPattern = strlen(pattern), szAlphabet = 256; 
	int* bht = (int*)( malloc( sizeof(int) * szAlphabet ));

	genBhtTable(pattern, bht, szPattern, szAlphabet );
	
	int count=0;
	count = bmpPatternMatch(pattern, bht, szPattern, text, szText);
	
	printf("count=%d\n", count);

	for(int i = 0; i < szPattern; i++){
		printf("%d", bht[ pattern[i] ] );
	}

	free(bht);
	
}



// Creates BHT table for Bad Character Heuristics
// @Param pattern: The pattern P being looked up in text T
// @Param bht:		The bad character heuristics table
// @Param szPattern: Length of the pattern P
// @Param szAlphabet: Length of the alphabet
//----------------------------------------------------------------------------
int genBhtTable(const char* pattern, int* bhtTable, int szPattern, int szAlphabet) {
	
	// check 0 length pattern & alphabet and empty pattern
	if (!pattern || !bhtTable) return 0;

	// set the alignment values for each alphabet character in the bht
	for(int i=0; i < szAlphabet; i++) 
		bhtTable[i] = szPattern;

	// set bad character table for pattern; ignore last character
	for(int i=0; i < szPattern - 1; i++)
		bhtTable[ pattern[i] ] = szPattern - 1 - i;

	return 1;
}



int  bmpPatternMatch(const char* pattern, const int* bhtTable, int szPattern, const char* text, int szText){
	
	if (!pattern || !bhtTable || !text) return -1;

	int j = szPattern - 1, count = 0;

	for (int i=0; (i + szPattern)< szText;){
		
		printf("%d,%d ", i,j);

		if ( pattern[j] == text[i + j] ) {		// if text and pattern characters allign

			j--;

			if (j <= 0) {								// if its a complete match j < 0
				i = i + szPattern;							// move i past the matched charactes [if matched caanot be part of next match]
				j = szPattern - 1;							// reset j to last character of pattern
				count++;									// just to say we found you
			}

			continue;										// search for more
															//
															//
		}else{									// current index does not allign with bht table
			i += bhtTable[ text[i+j] ];				// check in bht table how much to move to align char with equal in pattern
			j = szPattern - 1;						// reset j to last char in pattern just in case we had partial match
		}

	}
	return count;
}
