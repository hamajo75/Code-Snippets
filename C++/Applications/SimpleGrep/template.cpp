#include <stdio.h>
#include <iostream>
#include <string.h>

int match(char *regexp, char *text);

//-------------------------------------------------------------------------------
int main(int argc, const char* argv[])
{
	char text[100];
	char regexp[100];
	char chr;

	while(1)
	{
		std::cout << "Enter text and regexp:\n";
		std::cin.getline(text, sizeof(text));
		std::cin >> regexp;

		if (match(regexp, text))
			std::cout << "found\n";
		else
			std::cout << "not found\n";
	}
}




/****************************************************************************
* Mimics grep for the simple class of regular expressions:
*
* c - any literal character
* . - any single character
* ^ - bginning of input string
* $ - end of input string
* * - zero or more occurences of the previous character
*
*****************************************************************************/
int matchstar(int c, char *regexp, char *text);

/****************************************************************************
* Test match of first char of regexp with the current position (first char
* of text).
* If the first symbol of regexp doesn't match, there can be no match at
* this text position.
*****************************************************************************/
int matchhere(char *regexp, char *text)
{
    if (regexp[0] == '\0')
        return 1;																														// last symbol -> successfully mathced regexp
    if (regexp[0] == '$' && regexp[1] == '\0')
        return *text == '\0';
    if (regexp[1] == '*')
        return matchstar(regexp[0], regexp+2, text);
    if (*text!='\0' && (regexp[0]=='.' || regexp[0]==*text))
        return matchhere(regexp+1, text+1);																					// recursive call
    return 0;
}

/****************************************************************************
* search for c*regexp at beginning of text
*****************************************************************************/
int matchstar(int c, char *regexp, char *text)
{
    do {    /* a * matches zero or more instances */
        if (matchhere(regexp, text))
            return 1;
    } while (*text != '\0' && (*text++ == c || c == '.'));
    return 0;
}   

/****************************************************************************
* match: search for regexp anywhere in text 
* Notes:
* - for multiple matches it finds the leftmost
*****************************************************************************/
int match(char *regexp, char *text)
{
	if (regexp[0] == '^')
		return matchhere(regexp + 1, text);		// e.g. ^abc
	do 
	{		
		if (matchhere(regexp, text))		// must look even if string is empty
			return 1;

	} while (*text++ != '\0');

	return 0;
}

     
