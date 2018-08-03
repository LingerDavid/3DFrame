#include <iostream>
#include <stdarg.h>
#include "lgParser.h"

/*
*void lgDeleteKeywordsSpaces(char* str, int len, char** newstr, int& newlen)
*This function delete spaces between keywords except between ' and ',
*like [ and ], [ and ' ,'and ] and etc.The order is also important.
*
*Parameter:
*	str:the source string
*	len:the length of the source string
*	newstr:the final string
*	newlen:the final string length
*Return:
*	None
*
*Note:
*	The function is very useful and standard the command string.
*/
void lgParser::lgDeleteKeywordsSpaces(char* str, int len, char** newstr, int& newlen)
{
	char *temp = nullptr;
	int i = 0, j = 0, state = 0;
	temp = new char[len + 1];
	for (i = 0; i < len; i++)
	{
		if (*(str + i) == '\'')
		{
			if (state == 0)
			{
				//out->in
				state = 1;
			}
			else
			{
				//in->out
				state = 0;
			}
		}
		if (state == 0)
		{
			if (*(str + i) == ' ')
			{
				continue;
			}
		}
		*(temp + j) = *(str + i);
		j++;
	}
	*(temp + j) = '\0';

	*newstr = new char[j + 1];
	newlen = j;
	memcpy(*newstr, temp, j);
	*(*newstr + j) = '\0';

	if (temp)
	{
		delete temp;
	}
}

/*
*void lgDeleteHeadEndSpace(char* str, int len, char** newstr, int& newlen)
*This function delete head and end continus spaces.
*
*Parameter:
*	str:the source string
*	len:the length of the source string
*	newstr:the final string
*	newlen:the final string length
*Return:
*	None
*
*Note:
*	The function is very useful and make it easier to analyse in later parse.
*/
void lgParser::lgDeleteHeadEndSpace(char* str, int len, char** newstr, int& newlen)
{
	int i = 0, j = 0;
	//the first no space char
	for (i = 0; i < len && (*(str + i) == ' '); i++);
	//the last no space char
	for (j = len - 1; j >= 0 && (*(str + j) == ' '); j--);
	if (j >= i && j < len)
	{
		newlen = j - i + 1;
		*newstr = new char[j - i + 2];
		memcpy(*newstr, str + i, j - i + 1);
		*(*newstr + j - i + 1) = '\0';
	}
}

/*
*void lgReplaceStringChar(char* str, int len, char sc, char tc)
*This function delete head and end continus spaces.
*
*Parameter:
*	str:the source string
*	len:the length of the source string
*	sc:the target character
*	tc:the replace character
*Return:
*	None
*
*Note:
*	The function is gobal area useful.
*/
void lgParser::lgReplaceStringChar(char* str, int len, char sc, char tc)
{
	int i = 0;
	for (i = 0; i < len; i++)
	{
		if (*(str + i) == sc)
		{
			*(str + i) = tc;
		}
	}
}

/*
*void lgDeleteAllSpaces(char* str, int len, char** newstr, int& newlen)
*This function delete all the soace in string.
*
*Parameter:
*	str:the source string
*	len:the length of the source string
*	newstr:the final string
*	newlen:the final string length
*Return:
*	None
*
*Note:
*	The function will delete all spaces even if the space is in the keywords '.
*	So it's just used by command string because the command string devides keywords
*	by [ and ].
*/
void lgParser::lgDeleteAllSpaces(char* str, int len, char** newstr, int& newlen)
{
	int i = 0, k = 0;
	char* temp = new char[len + 1];
	for (i = 0; i < len; i++)
	{
		if (*(str + i) != ' ')
		{
			*(temp + k) = *(str + i);
			k++;
		}
	}
	*newstr = new char[k + 1];
	newlen = k;
	*(*newstr + k) = '\0';
	memcpy(*newstr, temp, k);
	delete temp;
}

/*
*void lgCombineSpaces(char* str, int len, char** newstr, int& newlen)
*This function combine continus soaces to one space.
*
*Parameter:
*	str:the source string
*	len:the length of the source string
*	newstr:the final string
*	newlen:the final string length
*Return:
*	None
*
*Note:
*	The function will combine even if the space is in the keywords '.
*	So it's just used by source string because souorce string preprocess
*	replace the ' and " by space and the data during ' or " is just the real
*	string or data we want.
*/
void lgParser::lgCombineSpaces(char* str, int len, char** newstr, int& newlen)
{
	//combine more than one spaces to one space
	int i = 0, j = 0, k = 0;
	char* temp = new char[len];
	for (i = 0; i < len; i++)
	{
		for (j = i; i < len && *(str + i) == ' '; i++);
		if (i < len)
		{
			if (i > j)
			{
				*(temp + k) = ' ';
				k++;
			}
			*(temp + k) = *(str + i);
			k++;
		}
	}
	*newstr = new char[k + 1];
	newlen = k;
	memcpy(*newstr, temp, k);
	*(*newstr + k) = '\0';
	delete temp;
}

/*
*bool lgIsInt(char* str, int len, int& iresult)
*This function supports decimal/heximal/octal number transfer.
*Also,it supports long and signed/unsigned int transfer
*
*Parameter:
*	str:the source string
*	len:the length of the source string
*	iresult:the final transfer result
*Return:
*	bool:if return true, the result will be saved in iresult
*
*Support modes;
*	0([0-9].*)([L|l|U|u])?
*	[1-9]([0-9]*)([L|l|U|u])?
*	+0([L|l|U|u])?,-0([L|l|U|u])?
*	0x[0-9|a-f|A-F]([L|l|U|u])?
*/
bool lgParser::lgIsInt(char* str, int len, int& iresult)
{
	int i = 0, 
		sign = 1, 
		decimal = 10, 
		result = 0,
		newlen = 0;
	bool havesign = false, 
		longint = false, 
		unsignedint = false, 
		havedata = false;
	char *newstr = nullptr;

	lgReplaceStringChar(str, strlen(str), '\n', ' ');
	lgDeleteHeadEndSpace(str, strlen(str), &newstr, newlen);

	if (*(newstr + i) == '+')
	{
		if (havesign == false)
		{
			havesign = true;
			sign = 1;
			i++;
		}
		else
		{
			//sign just happen one time
			return false;
		}
	}//if
	else if (*(newstr + i) == '-')
	{
		if (havesign == false)
		{
			havesign = true;
			sign = -1;
			i++;
		}
		else
		{
			//sign just happen one time
			return false;
		}
	}//else if
	if (i < newlen)
	{
		if (*(newstr + i) == '0')
		{
			i++;
			if (i < newlen)
			{
				if (*(newstr + i) == 'x'
					|| *(newstr + i) == 'X')
				{
					decimal = 16;
				}
				else if (*(newstr + i) >= '0'
					&& *(newstr + i) <= '7')
				{
					decimal = 8;
					result = (*(newstr + i) - '0') + result* decimal;
					if (havedata == false)
					{
						havedata = true;
					}
				}
				else
				{
					//no legal char
					return false;
				}

			}
			else
			{
				result = 0;
				//just one zero
				return true;
			}
		}
		else if (*(newstr + i) >= '1'
			&& *(newstr + i) <= '9')
		{
			decimal = 10;
			result = (*(newstr + i) - '0') + result * decimal;
			if (havedata == false)
			{
				havedata = true;
			}
		}
		else
		{
			//no legal char
			return false;
		}
		i++;
	}//if(i<len)
	else
	{
		//just have one sign
		return false;
	}
	while (i < newlen)
	{
		if (*(newstr + i) == 'L'
			|| *(newstr + i) == 'l')
		{
			if (longint)
			{
				//L or l can just happen one time
				return false;
			}
			else
			{
				longint = true;
			}
		}//if
		else if (*(newstr + i) == 'U'
			|| *(newstr + i) == 'u')
		{
			if (sign == -1)
			{
				//U or u shows mustn't be signed
				return false;
			}
			else
			{
				if (unsignedint == false)
				{
					unsignedint = true;
				}
				else
				{
					//U oe u can just happen one time
					return false;
				}
			}
		}//else if
		else
		{
			if (longint || unsignedint)
			{
				//L or l or U or u is the last char
				return false;
			}
			else
			{
				if (decimal == 16)
				{
					if (*(newstr + i) >= '0'
						&& *(newstr + i) <= '9')
					{
						result = (*(newstr + i) - '0') + result * 16;
						if (havedata == false)
						{
							havedata = true;
						}
					}
					else if ((*(newstr + i) >= 'a'
						&& *(newstr + i) <= 'f')
						|| (*(newstr + i) >= 'A'
						&& *(newstr + i) <= 'F'))
					{
						result = (*(newstr + i) - 'a' + 10) + result * 16;
						if (havedata == false)
						{
							havedata = true;
						}
					}
					else
					{
						//no legal char
						return false;
					}
				}//if
				else if (decimal == 8)
				{
					if (*(newstr + i) >= '0'
						&& *(newstr + i) <= '7')
					{
						result = (*(newstr + i) - '0') + result * 8;
						if (havedata == false)
						{
							havedata = true;
						}
					}
					else
					{
						//can just be in the range [0,7]
						return false;
					}
				}
				else if (decimal == 10)
				{
					if (*(newstr + i) >= '0'
						&& *(newstr + i) <= '9')
					{
						result = (*(newstr + i) - '0') + result * 10;
						if (havedata == false)
						{
							havedata = true;
						}
					}
					else
					{
						//no legal char
						return false;
					}
				}//else
			}
		}//else
		i++;
	}//while
	if (havedata == false)
	{
		//no number
		return false;
	}
	if (newstr)
	{
		delete newstr;
	}
	iresult = sign * result;
	return true;
}

/*
*bool lgIsFloat(char* str, int len, int& result)
*This function supports general and exponent forms.
*
*Parameter:
*	str:the source string
*	len:the length of the source string
*	result:the final transfer result
*Return:
*	bool:if return true, the result will be saved in result
*
*Support modes:
*	[+,-]([0-9].*)([.]([0-9].*)([E][+,-][0-9].*))?
*Note:
*	0-int area
*	1-decimal area
*	2-exp area
*/
bool lgParser::lgIsFloat(char* str, int len, double& result)
{
	enum
	{
		intarea,
		decarea,
		exparea
	};
	int intresult = 0, 
		decresult = 0, 
		expresult = 0, 
		newlen = 0,
		area = intarea,
		i = 0, 
		intsign = 1, 
		expsign = 1;
	bool longdouble = false, 
		inthavesign = false, 
		exphavesign = false, 
		inthavedata = false, 
		dechavedata = false, 
		exphavedata = false;
	char *newstr = nullptr;

	lgReplaceStringChar(str, strlen(str), '\n', ' ');
	lgDeleteHeadEndSpace(str, strlen(str), &newstr, newlen);

	for (i = 0; i < newlen; i++)
	{
		if (*(newstr + i) == '.')
		{
			if (area == intarea)
			{
				area = decarea;
			}
			else
			{
				return false;
			}
		}
		else if (*(newstr + i) == 'E'
			|| *(newstr + i) == 'e')
		{
			if (area == exparea)
			{
				return false;
			}
			else
			{
				area = exparea;
			}
		}
		else if (*(newstr + i) == 'L'
			|| *(newstr + i) == 'l')
		{
			if (longdouble == false)
			{
				longdouble = true;
			}
			else
			{
				return false;
			}
		}
		else if (((area == intarea || area == exparea)
			&& (*(newstr + i) == '+'
			|| *(newstr + i) == '-'
			|| (*(newstr + i) >= '0'
			&& *(newstr + i) <= '9')))
			|| ((area == decarea)
			&& (*(newstr + i) >= '0'
			&& *(newstr + i) <= '9')))
		{
			if (area == intarea)
			{
				if (*(newstr + i) == '+')
				{
					if (inthavesign == false)
					{
						intsign = 1;
						i++;
					}
					else
					{
						return false;
					}
				}
				else if (*(newstr + i) == '-')
				{
					if (inthavesign == false)
					{
						intsign = -1;
						i++;
					}
					else
					{
						return false;
					}
				}
				while (i < newlen && *(newstr + i) >= '0'
					&& *(newstr + i) <= '9')
				{
					if (inthavedata == false)
					{
						inthavedata = true;
					}
					intresult = (*(newstr + i) - '0') + intresult * 10;
					i++;
				}
				i--;
			}
			else if (area == decarea)
			{
				while (i < newlen && *(newstr + i) >= '0'
					&& *(newstr + i) <= '9')
				{
					if (dechavedata == false)
					{
						dechavedata = true;
					}
					decresult = (*(newstr + i) - '0') + decresult * 10;
					i++;
				}
				i--;
			}
			else
			{
				if (*(newstr + i) == '+')
				{
					if (exphavesign == false)
					{
						expsign = 1;
						i++;
					}
					else
					{
						return false;
					}
				}
				else if (*(newstr + i) == '-')
				{
					if (exphavesign == false)
					{
						expsign = -1;
						i++;
					}
					else
					{
						return false;
					}
				}
				while (i < newlen && *(newstr + i) >= '0'
					&& *(newstr + i) <= '9')
				{
					if (exphavedata == false)
					{
						exphavedata = true;
					}
					expresult = (*(newstr + i) - '0') + expresult * 10;
					i++;
				}
				i--;
			}
		}
		else
		{
			return false;
		}
	}
	if (inthavedata || dechavedata)
	{
		//the final result
		//intsign*intresult.decresultEexpsign*expresult
		if (inthavedata)
		{
			result = intsign * intresult;
		}
		if (dechavedata)
		{
			double temp = decresult;
			while (temp - 1.0 > 10E-15)
			{
				temp /= 10;
			}
			result += intsign * temp;
		}
		if (exphavedata)
		{
			double temp = 1.0;
			for (i = 0; i < expresult; i++)
			{
				temp *= 10;
			}
			result *= temp;
		}
		return true;
	}
	return false;
}

/*
*bool lgParseProcess(char* str, int len1, char* pattern, int len2)
*This function supports commands:
*	[i]
*	[f]
*	[s=d]
*	[s>d]
*	[s<d]
*	['ss..ss']
*Also the integer can be hex,decimal or the octal,
*the float/double data type can be general or exponent form.
*
*Parameter:
*	str:the source string
*	len1:the length of the source string
*	pattern:the match pattern
*	len2:the length of the pattern length
*Return:
*	bool:if return true, the result will be saved in class memebers.
*
*Note:
*	0-int state
*	1-float state
*	2-string compare state
*	3-get equal length string
*	4-get longer length string
*	5-get shorter length string
*The function ignore space/,/:/=/'/" etc. characters, and regard them as spaces.
*/
bool lgParser::lgParseProcess(char* str, int len1, char* pattern, int len2, ...)
{
	enum
	{
		intstate,
		floatstate,
		stringcompstate,
		stringgetstateequal,
		stringgetstatebigger,
		stringgetstatesmaller,
	};
	char* newstr1 = nullptr, 
		* newstr2 = nullptr, 
		* newpattern1 = nullptr, 
		* newpattern2 = nullptr,
		* tempstr = nullptr,
		* compstr = nullptr,
		* vt = nullptr,
		** ptempstr = nullptr;
	int newlen1 = 0,
		newlen2 = 0,
		newpatternlen1 = 0,
		newpatternlen2 = 0,
		i = 0,
		j = 0,
		d = 0,
		temp = 0,
		state = 0,
		iresult = 0;
	double dresult = 0.0;
	va_list vl;

	//Preprocess for resource string
	lgDeleteHeadEndSpace(str, len1, &newstr1, newlen1);
	lgReplaceStringChar(newstr1, newlen1, ':', ' ');
	lgReplaceStringChar(newstr1, newlen1, ',', ' ');
	lgReplaceStringChar(newstr1, newlen1, '\"', ' ');
	lgReplaceStringChar(newstr1, newlen1, '=', ' ');
	lgCombineSpaces(newstr1, newlen1, &newstr2, newlen2);

	//preprocess for pattern string
	lgDeleteHeadEndSpace(pattern, len2, &newpattern1, newpatternlen1);
	lgDeleteKeywordsSpaces(newpattern1, newpatternlen1, &newpattern2, newpatternlen2);

	va_start(vl, len2);

	//now datas are ready for parse
	//newstr2
	//newlen1
	//newpattern2
	//newpattern2len
	for (i = 0; i < newpatternlen2; i++)
	{
		if (*(newpattern2 + i) == '[')
		{
			i++;
			if (i < newpatternlen2)
			{
				if (*(newpattern2 + i) == 'i')
				{
					state = intstate;
					i++;
					if (i < newpatternlen2)
					{
						if (*(newpattern2 + i) != ']')
						{
							//std::cout << "the " << i + 1 << "th pos char must be ]" << std::endl;
							va_end(vl);
							if (compstr)
							{
								delete compstr;
							}
							if (tempstr)
							{
								delete tempstr;
							}
							if (newpattern1)
							{
								delete newpattern1;
							}
							if (newstr1)
							{
								delete newstr1;
							}
							if (newstr2)
							{
								delete newstr2;
							}
							if (newpattern2)
							{
								delete newpattern2;
							}
							return false;
						}
					}
					else
					{
						//std::cout << "the " << i + 1 << "th pos char must be ]" << std::endl;
						va_end(vl);
						if (compstr)
						{
							delete compstr;
						}
						if (tempstr)
						{
							delete tempstr;
						}
						if (newpattern1)
						{
							delete newpattern1;
						}
						if (newstr1)
						{
							delete newstr1;
						}
						if (newstr2)
						{
							delete newstr2;
						}
						if (newpattern2)
						{
							delete newpattern2;
						}
						return false;
					}
				}//if (*(newpattern2 + i) == 'i')
				else if (*(newpattern2 + i) == 'f')
				{
					state = floatstate;
					i++;
					if (i < newpatternlen2)
					{
						if (*(newpattern2 + i) != ']')
						{
							//std::cout << "the " << i + 1 << "th pos char must be ]" << std::endl;
							va_end(vl);
							if (compstr)
							{
								delete compstr;
							}
							if (tempstr)
							{
								delete tempstr;
							}
							if (newpattern1)
							{
								delete newpattern1;
							}
							if (newstr1)
							{
								delete newstr1;
							}
							if (newstr2)
							{
								delete newstr2;
							}
							if (newpattern2)
							{
								delete newpattern2;
							}
							return false;
						}
					}
					else
					{
						//std::cout << "the " << i + 1 << "th pos char must be ]" << std::endl;
						va_end(vl);
						if (compstr)
						{
							delete compstr;
						}
						if (tempstr)
						{
							delete tempstr;
						}
						if (newpattern1)
						{
							delete newpattern1;
						}
						if (newstr1)
						{
							delete newstr1;
						}
						if (newstr2)
						{
							delete newstr2;
						}
						if (newpattern2)
						{
							delete newpattern2;
						}
						return false;
					}
				}
				else if (*(newpattern2 + i) == 's')
				{
					i++;
					if (i < newpatternlen2)
					{
						if (*(newpattern2 + i) == '=' 
							|| *(newpattern2 + i) == '<'
							|| *(newpattern2 + i) == '>')
						{
							if (*(newpattern2 + i) == '=')
							{
								state = stringgetstateequal;
							}
							else if (*(newpattern2 + i) == '<')
							{
								state = stringgetstatesmaller;
							}
							else if (*(newpattern2 + i) == '>')
							{
								state = stringgetstatebigger;
							}
							else
							{
								//std::cout << "the " << i + 1 << "th pos char must be =/>/<" << std::endl;
								va_end(vl);
								if (compstr)
								{
									delete compstr;
								}
								if (tempstr)
								{
									delete tempstr;
								}
								if (newpattern1)
								{
									delete newpattern1;
								}
								if (newstr1)
								{
									delete newstr1;
								}
								if (newstr2)
								{
									delete newstr2;
								}
								if (newpattern2)
								{
									delete newpattern2;
								}
								return false;
							}
							i++;
							if (i < newpatternlen2)
							{
								for (temp = i; i < newpatternlen2 && *(newpattern2 + i) != ']'; i++);

								if (i < newpatternlen2)
								{
									if (i > temp)
									{
										if (tempstr)
										{
											delete tempstr;
										}
										tempstr = new char[i - temp + 1];
										memcpy(tempstr, newpattern2 + temp, i - temp);
										*(tempstr + i - temp) = '\0';
										if (!lgIsInt(tempstr, i - temp, d) 
											|| (state == stringgetstateequal && d <= 0)
											|| (state == stringgetstatesmaller && d <= 1)
											|| ((state == stringgetstatebigger) && d < 0))
										{
											//std::cout << "the " << i + 1 << "th pos char must be an integer bigger than 0" << std::endl;
											va_end(vl);
											if (compstr)
											{
												delete compstr;
											}
											if (tempstr)
											{
												delete tempstr;
											}
											if (newpattern1)
											{
												delete newpattern1;
											}
											if (newstr1)
											{
												delete newstr1;
											}
											if (newstr2)
											{
												delete newstr2;
											}
											if (newpattern2)
											{
												delete newpattern2;
											}
											return false;
										}
									}
									else
									{
										//std::cout << "the " << i + 1 << "th pos requires an integer" << std::endl;
										va_end(vl);
										if (compstr)
										{
											delete compstr;
										}
										if (tempstr)
										{
											delete tempstr;
										}
										if (newpattern1)
										{
											delete newpattern1;
										}
										if (newstr1)
										{
											delete newstr1;
										}
										if (newstr2)
										{
											delete newstr2;
										}
										if (newpattern2)
										{
											delete newpattern2;
										}
										return false;
									}
								}
								else
								{
									//std::cout << "the " << i + 1 << "th pos isn't closed" << std::endl;
									va_end(vl);
									if (compstr)
									{
										delete compstr;
									}
									if (tempstr)
									{
										delete tempstr;
									}
									if (newpattern1)
									{
										delete newpattern1;
									}
									if (newstr1)
									{
										delete newstr1;
									}
									if (newstr2)
									{
										delete newstr2;
									}
									if (newpattern2)
									{
										delete newpattern2;
									}
									return false;
								}
							}
							else
							{
								//std::cout << "the " << i + 1 << "th pos isn't closed" << std::endl;
								va_end(vl);
								if (compstr)
								{
									delete compstr;
								}
								if (tempstr)
								{
									delete tempstr;
								}
								if (newpattern1)
								{
									delete newpattern1;
								}
								if (newstr1)
								{
									delete newstr1;
								}
								if (newstr2)
								{
									delete newstr2;
								}
								if (newpattern2)
								{
									delete newpattern2;
								}
								return false;
							}
						}
					}
					else
					{
						//std::cout << "the " << i + 1 << "th pos isn't closed" << std::endl;
						va_end(vl);
						if (compstr)
						{
							delete compstr;
						}
						if (tempstr)
						{
							delete tempstr;
						}
						if (newpattern1)
						{
							delete newpattern1;
						}
						if (newstr1)
						{
							delete newstr1;
						}
						if (newstr2)
						{
							delete newstr2;
						}
						if (newpattern2)
						{
							delete newpattern2;
						}
						return false;
					}
				}
				else if (*(newpattern2 + i) == '\'')
				{
					state = stringcompstate;
					i++;
					for (temp = i; i < newpatternlen2 && *(newpattern2 + i) != '\''; i++);
					if (i < newpatternlen2)
					{
						if (i > temp)
						{
							if (compstr)
							{
								delete compstr;
							}
							compstr = new char[i - temp + 1];
							memcpy(compstr, newpattern2 + temp, i - temp);
							*(compstr + i - temp) = '\0';
						}
						else
						{
							//std::cout << "the " << i + 1 << "th pos has continus spaces" << std::endl;
							va_end(vl);
							if (compstr)
							{
								delete compstr;
							}
							if (tempstr)
							{
								delete tempstr;
							}
							if (newpattern1)
							{
								delete newpattern1;
							}
							if (newstr1)
							{
								delete newstr1;
							}
							if (newstr2)
							{
								delete newstr2;
							}
							if (newpattern2)
							{
								delete newpattern2;
							}
							return false;
						}
						i++;
						if (i < newpatternlen2)
						{
							if (*(newpattern2 + i) != ']')
							{
								//std::cout << "the " << i + 1 << "th pos must be ]" << std::endl;
								va_end(vl);
								if (compstr)
								{
									delete compstr;
								}
								if (tempstr)
								{
									delete tempstr;
								}
								if (newpattern1)
								{
									delete newpattern1;
								}
								if (newstr1)
								{
									delete newstr1;
								}
								if (newstr2)
								{
									delete newstr2;
								}
								if (newpattern2)
								{
									delete newpattern2;
								}
								return false;
							}
						}
						else
						{
							//std::cout << "the " << i + 1 << "th pos isn't colsed" << std::endl;
							va_end(vl);
							if (compstr)
							{
								delete compstr;
							}
							if (tempstr)
							{
								delete tempstr;
							}
							if (newpattern1)
							{
								delete newpattern1;
							}
							if (newstr1)
							{
								delete newstr1;
							}
							if (newstr2)
							{
								delete newstr2;
							}
							if (newpattern2)
							{
								delete newpattern2;
							}
							return false;
						}
					}//if (i < newpatternlen2)
					else
					{
						//std::cout << "the " << i + 1 << "th pos isn't colsed" << std::endl;
						va_end(vl);
						if (compstr)
						{
							delete compstr;
						}
						if (tempstr)
						{
							delete tempstr;
						}
						if (newpattern1)
						{
							delete newpattern1;
						}
						if (newstr1)
						{
							delete newstr1;
						}
						if (newstr2)
						{
							delete newstr2;
						}
						if (newpattern2)
						{
							delete newpattern2;
						}
						return false;
					}
				}
				else
				{
					//std::cout << "the " << i + 1 << "th pos char must be i/f/s/'" << std::endl;
					va_end(vl);
					if (compstr)
					{
						delete compstr;
					}
					if (tempstr)
					{
						delete tempstr;
					}
					if (newpattern1)
					{
						delete newpattern1;
					}
					if (newstr1)
					{
						delete newstr1;
					}
					if (newstr2)
					{
						delete newstr2;
					}
					if (newpattern2)
					{
						delete newpattern2;
					}
					return false;
				}
				for (temp = j; j < newlen2 && *(newstr2 + j) != ' '; j++);
				if (j > temp)
				{
					if (tempstr)
					{
						delete tempstr;
					}
					tempstr = new char[j - temp + 1];
					memcpy(tempstr, newstr2 + temp, j - temp);
					*(tempstr + j - temp) = '\0';
					if (state == intstate)
					{
						if (lgIsInt(tempstr, j - temp, iresult))
						{
							//save iresult
							*va_arg(vl, int*) = iresult;
							//std::cout << iresult << std::endl;
						}
						else
						{
							//std::cout << "the " << i + 1 << "th pos data is not required data form" << std::endl;
						}
					}
					else if (state == floatstate)
					{
						if (lgIsFloat(tempstr, j - temp, dresult))
						{
							*va_arg(vl, double*) = dresult;
							//std::cout << dresult << std::endl;
						}
						else
						{
							//std::cout << "the " << i + 1 << "th pos data is not required data form" << std::endl;
						}
					}
					else if (state == stringgetstateequal
						|| state == stringgetstatebigger
						|| state == stringgetstatesmaller)
					{
						if (state == stringgetstateequal)
						{
							if (j - temp == d)
							{
								ptempstr = _crt_va_arg(vl, char**);
								vt = *ptempstr;
								if (vt)
								{
									delete vt;
								}
								vt = new char[j - temp + 1];
								memcpy(vt, tempstr, j - temp);
								*(vt + j - temp) = '\0';
								*ptempstr = vt;
								//std::cout << tempstr << std::endl;
							}
							else
							{
								//std::cout << "the " << i + 1 << "th pos string length is not equal to required length" << std::endl;
							}
						}
						else if (state == stringgetstatebigger)
						{
							if (j - temp > d)
							{
								ptempstr = _crt_va_arg(vl, char**);
								vt = *ptempstr;
								if (vt)
								{
									delete vt;
								}
								vt = new char[j - temp + 1];
								memcpy(vt, tempstr, j - temp);
								*(vt + j - temp) = '\0';
								*ptempstr = vt;
								//std::cout << tempstr << std::endl;
							}
							else
							{
								//std::cout << "the " << i + 1 << "th pos string length is not longer than required length" << std::endl;
							}
						}
						else if (state == stringgetstatesmaller)
						{
							if (j - temp < d)
							{
								ptempstr = _crt_va_arg(vl, char**);
								vt = *ptempstr;
								if (vt)
								{
									delete vt;
								}
								vt = new char[j - temp + 1];
								memcpy(vt, tempstr, j - temp);
								*(vt + j - temp) = '\0';
								*ptempstr = vt;
								//std::cout << tempstr << std::endl;
							}
							else
							{
								//std::cout << "the " << i + 1 << "th pos string length is not shoter to required length" << std::endl;
							}
						}
					}
					else if (state == stringcompstate)
					{
						if (strcmp(tempstr, compstr) == 0)
						{
							/*vt = *_crt_va_arg(vl, char**);
							if (vt)
							{
								delete vt;
							}
							j = strlen(tempstr);
							vt = new char[j + 1];
							memcpy(vt, tempstr, j);
							*(vt + j) = '\0';*/
							//std::cout << tempstr << std::endl;
						}
						else
						{
							//std::cout << "the " << i + 1 << "th pos data is not equal to required string" << std::endl;
							va_end(vl);
							if (compstr)
							{
								delete compstr;
							}
							if (tempstr)
							{
								delete tempstr;
							}
							if (newpattern1)
							{
								delete newpattern1;
							}
							if (newstr1)
							{
								delete newstr1;
							}
							if (newstr2)
							{
								delete newstr2;
							}
							if (newpattern2)
							{
								delete newpattern2;
							}
							return false;
						}
					}
					j++;
					if (j > newlen2)
					{
						//std::cout << "the " << i + 1 << "th pos is the end of source string" << std::endl;
						va_end(vl);
						if (compstr)
						{
							delete compstr;
						}
						if (tempstr)
						{
							delete tempstr;
						}
						if (newpattern1)
						{
							delete newpattern1;
						}
						if (newstr1)
						{
							delete newstr1;
						}
						if (newstr2)
						{
							delete newstr2;
						}
						if (newpattern2)
						{
							delete newpattern2;
						}
						return true;
					}
				}//if(j>temp)
				
			}//if (i < newpatternlen2)
			else
			{
				//std::cout << "the " << i + 1 << "th pos isn't colsed" << std::endl;
				va_end(vl);
				if (compstr)
				{
					delete compstr;
				}
				if (tempstr)
				{
					delete tempstr;
				}
				if (newpattern1)
				{
					delete newpattern1;
				}
				if (newstr1)
				{
					delete newstr1;
				}
				if (newstr2)
				{
					delete newstr2;
				}
				if (newpattern2)
				{
					delete newpattern2;
				}
				return false;
			}
		}//if (*(newpattern2 + i) == '[')
		else
		{
			//std::cout << "the " << i + 1 << "th pos must be [" << std::endl;
			va_end(vl);
			if (compstr)
			{
				delete compstr;
			}
			if (tempstr)
			{
				delete tempstr;
			}
			if (newpattern1)
			{
				delete newpattern1;
			}
			if (newstr1)
			{
				delete newstr1;
			}
			if (newstr2)
			{
				delete newstr2;
			}
			if (newpattern2)
			{
				delete newpattern2;
			}
			return false;
		}
	}
	va_end(vl);
	if (compstr)
	{
		delete compstr;
	}
	if (tempstr)
	{
		delete tempstr;
	}
	if (newpattern1)
	{
		delete newpattern1;
	}
	if (newstr1)
	{
		delete newstr1;
	}
	if (newstr2)
	{
		delete newstr2;
	}
	if (newpattern2)
	{
		delete newpattern2;
	}
	return true;
}
