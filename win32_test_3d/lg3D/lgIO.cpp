#include "lgObject.h"
#include "lgParser.h"
#include "lgIO.h"

lgIO::lgIO()
{}

lgIO::~lgIO()
{
}

char* lgIO::lgGetLineFromPLGFile(char* buffer, int maxlength, FILE* fp)
{
	//ignore '#'and space
	int index = 0, length = 0;
	while (1)
	{
		if (!fgets(buffer, maxlength, fp))
		{
			return nullptr;
		}

		//count space
		length = strlen(buffer);
		for (index = 0; isspace(buffer[index]); index++);

		if (index >= length || buffer[index] == '#')
		{
			continue;
		}
		return &buffer[index];
	}
}

char* lgIO::lgGetLineFromASCFile(char* buffer, int maxlength, FILE* fp)
{
	//ignore empty lines
	int index = 0, length = 0;
	while (1)
	{
		if (!fgets(buffer, maxlength, fp))
		{
			return nullptr;
		}

		//count space
		length = strlen(buffer);
		for (index = 0; isspace(buffer[index]); index++);

		if (index >= length)
		{
			continue;
		}
		return &buffer[index];
	}
}

bool lgIO::lgGetObjectFromPLGFile(char* fileName, lgObject& tlgObject)
{
	if (fileName == nullptr)
	{
		return false;
	}
	
	FILE *fp = nullptr;
	char buffer[256] = { '\n' }, tempstring[8] = { '\n' };

	char *token_string = nullptr;

	char name[256] = {'\n'};
	int i = 0, vertices = 0, polys = 0, index1 = 0, index2 = 0, index3 = 0, polynumverts = 0, framcount = 1;

	int* x = nullptr, * y = nullptr, * z = nullptr;

	tlgObject.lgCreateFrames(framcount);

	if (fopen_s(&fp, fileName, "r"))
	{
		return false;
	}

	if (!(token_string = lgGetLineFromPLGFile(buffer, 255, fp)))
	{
		return false;
	}

	//name vertices polys
	sscanf_s(token_string, "%s %d %d", name, _countof(name), &vertices, &polys);

	x = new int[vertices];
	y = new int[vertices];
	z = new int[vertices];

	for (i = 0; i < vertices; i++)
	{
		if (!(token_string = lgGetLineFromPLGFile(buffer, 255, fp)))
		{
			return false;
		}
		sscanf_s(token_string, "%d %d %d", &x[i], &y[i], &z[i]);
	}
	
	for (i = 0; i < polys; i++)
	{
		if (!(token_string = lgGetLineFromPLGFile(buffer, 255, fp)))
		{
			return false;
		}
		sscanf_s(token_string, "%s %d %d %d %d", tempstring, _countof(tempstring), &polynumverts, &index1, &index2, &index3);
		tlgObject.lgInsertTriangle(0, x[index1], y[index1], z[index1], 
			x[index2], y[index2], z[index2],
			x[index3], y[index3], z[index3]);

	}
	fclose(fp);
	delete x;
	delete y;
	delete z;
	return true;
}

bool lgIO::lgGetObjectFromASCFile(char* fileName, lgObject& tlgObject)
{
	//['Ambient']['light']['color']['Red'][f]['Green'][f]['Blue'][f]
	//['Named']['object'][s>0]
	//['Tri-mesh']['Vertices'][i]['Faces'][i]
	//['Vertex']['list']
	//['Page'][i]
	//['Vertex'][i]['X'][f]['Y'][f]['Z'][f]
	//['Face']['list']
	//['Face'][i]['A'][i]['B'][i]['C'][i]['AB'][i]['BC'][i]['CA'][i]
	//['Material'][s>0]
	//['Smoothing'][i]
	char command0[] = "['Ambient']['light']['color']['Red'][f]['Green'][f]['Blue'][f]",
		command1[] = "['Named']['object'][s>0]",
		command2[] = "['Tri-mesh']['Vertices'][i]['Faces'][i]",
		command3[] = "['Vertex']['list']",
		command4[] = "['Page'][i]",
		command5[] = "['Vertex'][i]['X'][f]['Y'][f]['Z'][f]",
		command6[] = "['Face']['list']",
		command7[] = "['Face'][i]['A'][i]['B'][i]['C'][i]['AB'][i]['BC'][i]['CA'][i]",
		command8[] = "['Material'][s>0]",
		command9[] = "['Smoothing'][i]";
	int i = 0, 
		index = 0,
		vertices = 0, 
		polys = 0, 
		index1 = 0, 
		index2 = 0, 
		index3 = 0, 
		polynumverts = 0, 
		framcount = 1,
		v1 = 0,
		v2 = 0,
		v3 = 0,
		v12 = 0,
		v23 = 0, 
		v31 = 0;
	FILE *fp = nullptr;
	double *xyz[3] = {nullptr};
	char *token_string = nullptr, 
		buffer[256] = { '\n' }, 
		* tempstring[256] = {nullptr};
	double aclr[] = {0.0, 0.0, 0.0};

	tlgObject.lgCreateFrames(framcount);

	if (fopen_s(&fp, fileName, "r"))
	{
		return false;
	}


	if (!(token_string = lgGetLineFromASCFile(buffer, 255, fp)))
	{
		fclose(fp);
		return false;
	}
	//ambient light
	lgParser::lgParseProcess(token_string, strlen(token_string), command0, strlen(command0), &aclr[0], &aclr[1], &aclr[2]);

	//obejct name
	if (!(token_string = lgGetLineFromASCFile(buffer, 255, fp)))
	{
		fclose(fp);
		return false;
	}
	lgParser::lgParseProcess(token_string, strlen(token_string), command1, strlen(command1), &tempstring[0]);

	//verties faces
	if (!(token_string = lgGetLineFromASCFile(buffer, 255, fp)))
	{
		fclose(fp);
		return false;
	}
	lgParser::lgParseProcess(token_string, strlen(token_string), command2, strlen(command2), &vertices, &polys);

	//get vertices
	xyz[0] = new double[vertices];
	xyz[1] = new double[vertices];
	xyz[2] = new double[vertices];

	for (i = 0; i < vertices;)
	{
		if (!(token_string = lgGetLineFromASCFile(buffer, 255, fp)))
		{
			delete xyz[0];
			delete xyz[1];
			delete xyz[2];
			fclose(fp);
			return false;
		}
		else
		{
			if (lgParser::lgParseProcess(token_string, strlen(token_string), command5, strlen(command5), &index, &xyz[0][i], &xyz[1][i], &xyz[2][i]))
			{
				i++;
			}
		}
	}

	//get faces
	for (i = 0; i < polys;)
	{
		if (!(token_string = lgGetLineFromASCFile(buffer, 255, fp)))
		{
			delete xyz[0];
			delete xyz[1];
			delete xyz[2];
			fclose(fp);
			return false;
		}
		else
		{
			if (lgParser::lgParseProcess(token_string, strlen(token_string), command7, strlen(command7), &index, &v1, &v2, &v3, &v12, &v23, &v31))
			{
				//save in object
				tlgObject.lgInsertTriangle(0, xyz[0][v1], xyz[1][v1], xyz[2][v1],
					xyz[0][v2], xyz[1][v2], xyz[2][v2],
					xyz[0][v3], xyz[1][v3], xyz[2][v3]);
			}
			else if (lgParser::lgParseProcess(token_string, strlen(token_string), command8, strlen(command8), &tempstring[0]))
			{
				//save in object
				//need rgb string parese
				i++;
			}
		}
	}

	for (i = 0; tempstring[i] && i < 256; i++)
	{
		delete tempstring[i];
		tempstring[i] = nullptr;
	}

	delete xyz[0];
	delete xyz[1];
	delete xyz[2];

	fclose(fp);
	return true;
}

bool lgIO::lgGetBitmapFromFile(char* file, lgBmp& tlgBmp)
{
	char* temp = nullptr;
	HFILE hfile;
	OFSTRUCT fileData;
	int count = 0, itemp = 0;
	if ((hfile = OpenFile(file, &fileData, OF_READ)) == -1)
	{
		return false;
	}

	_lread(hfile, &tlgBmp.m_lgBmpFileHeader, sizeof(tagBITMAPFILEHEADER));

	if (tlgBmp.m_lgBmpFileHeader.bfType != 0X4D42)
	{
		_lclose(hfile);
		return false;
	}
	_lread(hfile, &tlgBmp.m_lgBmpInfo.bmiHeader, sizeof(tagBITMAPINFOHEADER));

	if (tlgBmp.m_lgBmpInfo.bmiHeader.biBitCount == 8)
	{
		_lread(hfile, &tlgBmp.m_lgBmpInfo.bmiColors, sizeof(RGBQUAD));
		itemp = tlgBmp.m_lgBmpInfo.bmiColors[0].rgbRed;
		tlgBmp.m_lgBmpInfo.bmiColors[0].rgbRed = tlgBmp.m_lgBmpInfo.bmiColors[0].rgbBlue;
		tlgBmp.m_lgBmpInfo.bmiColors[0].rgbBlue = itemp;
	}
	_llseek(hfile, -(int)(tlgBmp.m_lgBmpInfo.bmiHeader.biSizeImage), SEEK_END);

	if (tlgBmp.m_lgBmpInfo.bmiHeader.biBitCount == 8
		|| tlgBmp.m_lgBmpInfo.bmiHeader.biBitCount == 16
		|| tlgBmp.m_lgBmpInfo.bmiHeader.biBitCount == 24)
	{
		if (tlgBmp.m_lgBuffer)
		{
			delete tlgBmp.m_lgBuffer;
		}
		if (!(tlgBmp.m_lgBuffer = new unsigned char[tlgBmp.m_lgBmpInfo.bmiHeader.biSizeImage]))
		{
			_lclose(hfile);
			return false;
		}
		_lread(hfile, tlgBmp.m_lgBuffer, tlgBmp.m_lgBmpInfo.bmiHeader.biSizeImage);

	}
	else
	{
		_lclose(hfile);
		return false;
	}

	_lclose(hfile);

	tlgBmp.lgFlipBitmap();
	return true;
}