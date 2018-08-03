#ifndef _FILE_LGPARSER_H
#define _FILE_LGPARSER_H

class lgParser
{
private:
	static void lgDeleteKeywordsSpaces(char*, int, char**, int&);
public:
	lgParser();
	~lgParser();

	static void lgDeleteHeadEndSpace(char*, int, char**, int&);
	static void lgReplaceStringChar(char*, int, char, char);
	static void lgDeleteAllSpaces(char*, int, char**, int&);
	static void lgCombineSpaces(char*, int, char**, int&);

	static bool lgIsInt(char*, int, int&);
	static bool lgIsFloat(char*, int, double&);

	static bool lgParseProcess(char*, int, char*, int, ...);
};

#endif