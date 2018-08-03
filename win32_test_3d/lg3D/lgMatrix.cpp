#include <math.h>
#include <iostream>

#include "lgCamera.h"
#include "lgVector.h"
#include "lgQuaternion.h"
#include "lgMatrix.h"

/*
* lgMatrix()
* 
* Sets Default 1X1 Matrix.
*
* This method is the default construct function of lgMatrix.
*/
lgMatrix::lgMatrix()
{
	lgInit();
}

/*
* lgMatrix(unsigned int tR, unsigned int tC)
* 
* call adjust functin to make tha matrix to target RXC
* finally reset all elements zero.
*
* Parameters:
*    tR is the row number.
*    tC is the column number
* Returns:
*    void
*
* this method is the construct function of lgMatrix
*/
lgMatrix::lgMatrix(unsigned int tR, unsigned int tC)
{
	lgInit();
	lgMakeZeroMatrix(tR, tC);
}

/*
* lgMatrix(const lgMatrix& tlgMatrix)
* 
* Copy the tlgMatrix which is the reference 
* of another matrix.

* this method is depp copy construct function of lgMatrix.
*/
lgMatrix::lgMatrix(const lgMatrix& tlgMatrix)
{
	lgInit();
	lgCopy(tlgMatrix);
}

/*
* ~lgMatrix()
* 
* clear resource
*
*/
lgMatrix::~lgMatrix()
{
	lgDeleteMatrix();
}

void lgMatrix::lgInit()
{
	m_lgR = 1;
	m_lgC = 1;
	m_lgMatrix = new double*[1];
	m_lgMatrix[0] = new double[1];
	m_lgMatrix[0][0] = 0;
}

void lgMatrix::lgCopy(const lgMatrix& tlgMatrix)
{
	if(m_lgMatrix)
	{
		lgDeleteMatrix();
		lgInit();
	}
	unsigned row = tlgMatrix.lgGetRow(), 
		column = tlgMatrix.lgGetColumn();
	lgMakeZeroMatrix(row, column);
	lgCopyFromMatrix(0, 0, tlgMatrix, 0, 0, row, column);
}

/*
* void lgMakeZeroMatrix(unsigned int tR, unsigned int tC)
*
* Reset all matrix elementes to zero.
*
* Parameter:
*	  tR-row number
*	  tC-column number
* Return:
*	  void
* 
* If the old row/column is as same as target row/column,
* just skip adjust.
*/
void lgMatrix::lgMakeZeroMatrix(unsigned int tR, unsigned int tC)
{
	lgReAlloc(tR, tC);
	lgEmptyMatrix(0);
}

/*
* void lgMakeDiagonalMatrix(unsigned int tWidth, double tK)
* 
* This method generate diagonal matrix of tWdithXtWidth.
*
* Parameter:
*	  tWdith is the target width
*     tK is the target giagonal value
* Return:
*	  void
*
*  This method is based the matrix which hte row 
*  is as same as column.
*/
void lgMatrix::lgMakeDiagonalMatrix(unsigned int tWidth, double tK)
{
	lgMakeZeroMatrix(tWidth, tWidth);
	unsigned int i = 0;
	for(i = 0; i < tWidth; i++)
	{
		m_lgMatrix[i][i] = tK;
	}
}

/*
* void lgMakeUnitMatrix(unsigned int tWidth)
* 
* This method generate diagonal matrix of tWdithXtWidth
* and the diagonal value must be one.
*
* Parameter:
*	  tWdith is the target width
* Return:
*	  void
*
*  This method is based the matrix which hte row 
*  is as same as column.
*/
void lgMatrix::lgMakeUnitMatrix(unsigned int tWidth)
{
	lgMakeDiagonalMatrix(tWidth, 1);
}

/*
* void lgDotMultiply(const lgMatrix& tlgMatrix)
* 
* This method generate diagonal matrix of tWdithXtWidth
* and the diagonal value must be one.
*
* Parameter:
*	  tlgMatrix is right Matrix
* Return:
*	  lgMatrix is the mirror of the result matrix
*
* This method is based the matrix dot multiply formula,
* and both matrixes must have same row and same column.
*/
const lgMatrix lgMatrix::lgDotMultiply(const lgMatrix& tlgMatrix)
{
	unsigned int i = 0, j = 0;
	if(m_lgC != tlgMatrix.lgGetColumn() 
		|| m_lgR != tlgMatrix.lgGetRow())
	{
		//?
	}
	for(i = 0; i < m_lgR; i++)
	{
		for(j = 0; j< m_lgC; j++)
		{
			m_lgMatrix[i][j] = m_lgMatrix[i][j] * tlgMatrix[i][j];
		}
	}
	return *this;
}

/*
* void lgEmptyMatrix(double tK)
* 
* This method reset all matrix elements to tK
*
* Parameter:
*	  tK is the the target value
* Return:
*	  void
*/
void lgMatrix::lgEmptyMatrix(double tK)
{
	unsigned int i = 0, j = 0;
	for(i = 0; i < m_lgR; i++)
	{
		for(j = 0; j < m_lgC; j++)
		{
			m_lgMatrix[i][j] = tK;
		}
	}
}

/*
* void lgDeleteMatrix()
* 
* This method delete entire matrix
*
* Parameter:
*	  none
* Return:
*	  void
*/
void lgMatrix::lgDeleteMatrix()
{
	unsigned i = 0;
	for(i = 0; i < m_lgR; i++)
	{
		delete m_lgMatrix[i];
	}
	if(m_lgMatrix)
	{
		delete m_lgMatrix;
		m_lgMatrix = nullptr;
	}
}

/*
* const lgMatrix lgTransposMatrix()
* 
* This method return a TransposMatrix based on
* m_lgMatrix.
*
* Parameter:
*	  none
* Return:
*	  const lgMatrix is the transpose result
*/
const lgMatrix lgMatrix::lgTransposMatrix()
{
	unsigned i = 0, j = 0;
	double temp = 0.0;
	for(i = 0; i < m_lgR; i++)
	{
		for(j = i + 1; j < m_lgC; j++)
		{
			temp = m_lgMatrix[i][j];
			m_lgMatrix[i][j] = m_lgMatrix[j][i];
			m_lgMatrix[j][i] = temp;
		}
	}
	return *this;
}

/*
* bool lgGetReversibleMatrix(lgMatrix& tlgMatrix)
* 
* This method get the reversible matrix based on
* m_lgMatrix;
*
* Parameter:
*	  tlgMatrix is the result matrix
* Return:
*	  true if matrix is reversible,else false
*
*/
bool lgMatrix::lgGetReversibleMatrix(lgMatrix& tlgMatrix)
{
	if(!lgIsReversible())
	{
		return false;
	}
	else
	{
		tlgMatrix = lgGetAdjMatrix() / lgGetDetMatrix();
		return true;
	}
}

/*
* const lgMatrix lgGetAdjMatrix()
* 
* This method get the reversible matrix based on
* m_lgMatrix;
*
* Parameter:
*	  tlgMatrix is the result matrix
* Return:
*	  true if matrix is reversible,else false
*
* This method require least 2X2 matrix
*/
const lgMatrix lgMatrix::lgGetAdjMatrix()
{
	lgMatrix tlgMatrix, tlgRestMatrix;
	tlgRestMatrix.lgMakeZeroMatrix(m_lgR, m_lgC);
	tlgMatrix.lgMakeZeroMatrix(m_lgR - 1, m_lgC - 1);
	unsigned int i = 0, j = 0, m = 0, n = 0;
	for(i = 0; i < m_lgR; i++)
	{
		for(j = 0; j < m_lgC; j++)
		{
			//i,j
			for(m = 0; m < m_lgR; m++)
			{
				for(n = 0; n < m_lgC; n++)
				{
					if(m != i && n != j)
					{
						tlgMatrix[m > i ? m - 1 : m][n > j ? n - 1 : n] = m_lgMatrix[m][n];
					}
				}
			}
			tlgRestMatrix[i][j] = pow(-1, i + j) * tlgMatrix.lgGetDetMatrix();
		}
	}
	tlgRestMatrix.lgTransposMatrix();
	return tlgRestMatrix;
}

/*
* double lgGetDetMatrix()
* 
* This method get the det value if m_lgMatrix
*
* Parameter:
*	  none
* Return:
*	  det value
*
* This method require square matrix.
*/
double lgMatrix::lgGetDetMatrix()
{
	if(m_lgR != m_lgC)
	{
		//?
	}
	double det = 0.0;
	lgMatrix tlgMat(m_lgC, 1), tlgOrderMatrix(m_lgC, 1), tlgFlagMatrix(m_lgC, 1);
	tlgFlagMatrix.lgEmptyMatrix(1.0);
	tlgOrderMatrix.lgEmptyMatrix(0.0);
	lgGetDetMatrix(*this, tlgOrderMatrix, tlgFlagMatrix, 0, 0, tlgMat, det);
	return det;
}

/*
* const lgMatrix lgGetOrthogonalMatrix()
* 
* This method get the orthogonal matrix
* m_lgMatrix;
*
* Parameter:
*	  count is the max iteration count
*	  k is the	tiny parameter to iterate
* Return:
*	  return orthogonal matrix
*
*/
const lgMatrix lgMatrix::lgGetOrthogonalMatrix(unsigned int count, double k)
{
	lgMatrix tlgMat = *this, lgTMatrix, r, g;
	r.lgMakeZeroMatrix(1, m_lgC);
	g.lgMakeZeroMatrix(1, m_lgC);
	unsigned int i = 0, j = 0, m = 0, n = 0;
	for(i = 0; i < count; i++)
	{
		if(tlgMat.lgIsOrthogonal())
		{
			break;
		}
		for(j = 0; j < m_lgR; j++)
		{
			for(m = 0; m < m_lgC; m++)
			{
				g[0][m] = tlgMat[j][m];
				lgTMatrix[0][m] = tlgMat[j][m];
			}
			for(m = 0; m < m_lgR; m++)
			{
				if(m == j)
				{
					continue;
				}
				for(n = 0; n < m_lgC; n++)
				{
					r[0][n] = tlgMat[m][n];
				}
				lgTMatrix = lgTMatrix - k * lgGetInnerProduct(g, r) / lgGetInnerProduct(r, r) * r;	
			}
			for(m = 0; m < m_lgC; m++)
			{
				tlgMat[j][m] = lgTMatrix[0][m];
			}
		}
	}
	return tlgMat;
}

/*
* bool lgIsOrthogonal()
* 
* This method judge if matrix is orthogonal
*
* Parameter:
*	  none
* Return:
*	  true if is orthogonal,else false
*/
bool lgMatrix::lgIsOrthogonal()
{
	lgMatrix tlgMat = *this;
	tlgMat.lgTransposMatrix();
	tlgMat = tlgMat * (*this);
	if(abs(tlgMat.lgGetDetMatrix() - 1.0) < 10E-10)
	{
		return true;
	}
	else
	{
		return false;
	}
}

/*
* bool lgIsReversible()
* 
* This method judge if matrix is reversible
*
* Parameter:
*	  none
* Return:
*	  true if is reversible,else false
*/
bool lgMatrix::lgIsReversible()
{
	double det = lgGetDetMatrix();
	if(abs(det) < 10E-10)
	{
		return false;
	}
	else
	{
		return true;
	}
}

/*
* unsigned int lgSgn(const lgMatrix& tlgMatrix)
* 
* This method is sgn(x) function
*
* Parameter:
*	  NX1 sequence
* Return:
*	  return sgn result
*/
unsigned int lgMatrix::lgSgn(const lgMatrix& tlgMatrix) const
{
	unsigned int sgn = 0, i = 0, j = 0, r = tlgMatrix.lgGetRow();
	if(tlgMatrix.lgGetColumn() != 1)
	{
		//?
	}
	for(i = 0; i < r; i++)
	{
		for(j = i + 1; j < r; j++)
		{
			if((int)tlgMatrix[j][0] < (int)tlgMatrix[i][0])
			{
				sgn++;
			}
		}
	}
	return sgn;
}

/*
* void lgReAlloc(unsigned int tR, unsigned int tC)
* 
* This method realloc the matrix
*
* Parameter:
*	  none
* Return:
*	  current row
*
*/
void lgMatrix::lgReAlloc(unsigned int tR, unsigned int tC)
{
	if(m_lgR == tR && m_lgC == tC)
	{
		return;
	}

	unsigned int i = 0, j = 0, fr = 0, fc = 0, oldR = m_lgR, oldC = m_lgC;
	double **tMatrix = new double*[oldR];

	//////////////////////////////////////////////////////
	for(i = 0; i < oldR; i++)
	{
		tMatrix[i] = new double[oldC];
	}
	for(i = 0; i < oldR; i++)
	{
		for(j = 0; j < oldC; j++)
		{
			tMatrix[i][j] = m_lgMatrix[i][j];
		}
	}

	/////////////////////////////////////////////////////
	lgDeleteMatrix();

	m_lgC = tC;
	m_lgR = tR;

	m_lgMatrix = new double*[tR];
	for(i = 0; i < tR; i++)
	{
		m_lgMatrix[i] = new double[tC];
	}

	lgEmptyMatrix(0.0);

	fr = tR < oldR ? tR : oldR;
	fc = tC < oldC ? tC : oldC;

	for(i = 0; i < fr; i++)
	{
		for(j = 0; j < fc; j++)
		{
			m_lgMatrix[i][j] = tMatrix[i][j];
		}
	}
	//////////////////////////////////////////////////////
	for (i = 0; i < oldR; i++)
	{
		delete tMatrix[i];
	}
	delete tMatrix;
}	

const lgQuaternion lgMatrix::lgMatrixCopyToQuaternion()
{
	lgQuaternion tlgQuaternion(m_lgMatrix[0][0], m_lgMatrix[0][1], m_lgMatrix[0][2], m_lgMatrix[0][3]);
	return tlgQuaternion;
}

/*
* void lgMatrixTolgEluerAngle(const lgEluer& tlgEluer)
* 
* This method transfer matrix to eluer angle
*
* Parameter:
*	  tlgEluer saves result
* Return:
*	  none
*
*/
void lgMatrix::lgMatrixTolgEluerAngle(lgEluer& tlgEluer)
{
	m_lgTransfer.lgMatrixTolgEluerAngle(*this, tlgEluer);
}

/*
* void lgMatrixTolgQuaternion(const lgQuaternion& tlgQuaternion)
* 
* This method transfer matrix to quaternion
*
* Parameter:
*	  tlgQuaternion saves result
* Return:
*	  none
*
*/
void lgMatrix::lgMatrixTolgQuaternion(lgQuaternion& tlgQuaternion)
{
	m_lgTransfer.lgMatrixTolgQuaternion(*this, tlgQuaternion);
}
/*
* unsigned int lgMatrix::lgGetRow() const
* 
* This method get current row number
*
* Parameter:
*	  none
* Return:
*	  current row
*
*/
unsigned int lgMatrix::lgGetRow() const
{
	return m_lgR;
}

/*
* unsigned int lgMatrix::lgGetColumn() const
* 
* This method get current column number
*
* Parameter:
*	  none
* Return:
*	  current column
*
*/
unsigned int lgMatrix::lgGetColumn() const
{
	return m_lgC;
}

/*
* bool lgCopyFromMatrix(unsigned int tSROrg, unsigned int tSCOrg,
							const lgMatrix& tlgMatrix, unsigned int tDROrg, 
		unsigned int tDCOrg, unsigned int tR, unsigned int tC)
* 
* This method overload operator -.
*
* Parameter:
*	  tSROrg is the row orgin of source matrix
*	  tSCOrg is the column orgin of source matrix
*	  tlgMatrix is the source matrix
*	  tDROrg is the target row origin of target matrix
*	  tDCOrg is the target column origin of target matrix
*	  tR is the row number of area
*	  tC is the column number of area
* Return:
*	  true if copy success,else false

* This method requires the target/src area is
* included in target/src matrix.
*/
bool lgMatrix::lgCopyFromMatrix(unsigned int tSROrg, unsigned int tSCOrg,
							const lgMatrix& tlgMatrix, unsigned int tDROrg, 
		unsigned int tDCOrg, unsigned int tR, unsigned int tC)
{
	unsigned int row = tlgMatrix.lgGetRow(), 
		column = tlgMatrix.lgGetColumn();
	////////////////////////////////////
	if(tDROrg < 0)
	{
		//?
	}
	else if(tDROrg > row - 1)
	{
		//?
	}
	else
	{
		if(tDROrg + tR > row - 1)
		{
			//?
		}
	}
	if(tDCOrg < 0)
	{
		//?
	}
	else if(tDCOrg > column - 1)
	{
		//?
	}
	else
	{
		if(tDCOrg + tC > column - 1)
		{
			//?
		}
	}
	////////////////////////////////////
	if(tSROrg < 0)
	{
		//?
	}
	else if(tSROrg > m_lgR - 1)
	{
		//?
	}
	else
	{
		if(tSROrg + tR > m_lgR - 1)
		{
			//?
		}
	}
	if(tSCOrg < 0)
	{
		//?
	}
	else if(tSCOrg > m_lgC - 1)
	{
		//?
	}
	else
	{
		if(tSCOrg + tC > m_lgC - 1)
		{
			//?
		}
	}

	unsigned int i = 0, j = 0;
	for(i = 0; i < tR; i++)
	{
		for(j = 0; j< tC; j++)
		{
			m_lgMatrix[tDROrg + i][tDCOrg + j] = tlgMatrix[tSROrg + i][tSCOrg + j];
		}
	}
	return true;
}

/*
* double lgGetInnerProduct(const lgMatrix& tlgMatrix1, const lgMatrix& tlgMatrix2)
* 
* This method calculate the inner product
* of tlgMatrix1 and the tlgMatrx2
*
* Parameter:
*	  tlgMatrix1 is the left matrix
*	  tlgMatrix2 is the right matrix
* Return:
*	  a inner product result

* This method require the tlgMatrix1 and 
* tlgMatrix2 have same column, and both are
* 1XN form matrix.
*/
double lgMatrix::lgGetInnerProduct(const lgMatrix& tlgMatrix1, const lgMatrix& tlgMatrix2)
{
	unsigned i = 0, c = tlgMatrix1.lgGetColumn();
	double result = 0.0;
	for(i = 0; i < c; i++)
	{
		result += tlgMatrix1[0][i] * tlgMatrix2[0][i];
	}
	return result;
}

/*
* const lgMatrix operator +(const lgMatrix& tlgMatrix)
* 
* This method overload operator +.
*
* Parameter:
*	  tlgMatrix is the right matrix
* Return:
*	  a copy of the result lgMatrix

* This method require the column of left matrix
* and the row of right matrix are equal.
*/
const lgMatrix lgMatrix::operator +(const lgMatrix& tlgMatrix)
{
	if(m_lgR != tlgMatrix.lgGetRow() 
		|| m_lgC != tlgMatrix.lgGetColumn())
	{
		//?
	}
	unsigned int i = 0, j = 0;
	lgMatrix tlgMat = *this;
	for(i = 0; i < m_lgR; i++)
	{
		for(j = 0; j < m_lgC; j++)
		{
			tlgMat[i][j] += tlgMatrix[i][j];
		}
	}
	return tlgMat;
}

/*
* const lgMatrix operator -(const lgMatrix& tlgMatrix)
* 
* This method overload operator -.
*
* Parameter:
*	  tlgMatrix is the right matrix
* Return:
*	  a copy of the result lgMatrix

* this method require the column of left matrix
* and the row of right matrix are equal.
*/
const lgMatrix lgMatrix::operator -(const lgMatrix& tlgMatrix)
{
	if(m_lgR != tlgMatrix.lgGetRow() 
		|| m_lgC != tlgMatrix.lgGetColumn())
	{
		//?
	}
	unsigned int i = 0, j = 0;
	lgMatrix tlgMat = *this;
	for(i = 0; i < m_lgR; i++)
	{
		for(j = 0; j < m_lgC; j++)
		{
			tlgMat[i][j] -= tlgMatrix[i][j];
		}
	}
	return tlgMat;
}

/*
* const lgMatrix operator *(const lgMatrix& tlgMatrix)
* 
* This method overload operator *.
*
* Parameter:
*	  tlgMatrix is the right matrix
* Return:
*	  a copy of the result lgMatrix

* this method require the column of left matrix
* and the row of right matrix are equal.
*/
const lgMatrix lgMatrix::operator *(const lgMatrix& tlgMatrix)
{
	unsigned int i = 0, j = 0, k = 0, 
		r = tlgMatrix.lgGetRow(), c = tlgMatrix.lgGetColumn();
	if(m_lgC != r)
	{
		//?
	}
	lgMatrix tlgMat;
	tlgMat.lgMakeZeroMatrix(m_lgR, c);
	for(i = 0; i < m_lgR; i++)
	{
		for(j = 0; j < c; j++)
		{
			for(k = 0; k < m_lgC; k++)
			{
				tlgMat[i][j] += m_lgMatrix[i][k] * tlgMatrix[k][j];
			}
		}
	}
	return tlgMat;
}

/*
* const lgMatrix operator *(double tK)
* 
* This method overload operator *.
*
* Parameter:
*	  tK is the constant number
* Return:
*	  a copy of the result lgMatrix
*
*/
const lgMatrix operator *(const lgMatrix& ltlgMatrix, const lgMatrix& rtlgMatrix)
{
	unsigned int i = 0, j = 0, k = 0, r = ltlgMatrix.lgGetRow(), c = ltlgMatrix.lgGetColumn();
	lgMatrix tlgMatrix = ltlgMatrix;
	if(r != rtlgMatrix.lgGetRow() || c != rtlgMatrix.lgGetColumn())
	{
		//?
	}
	lgMatrix tlgMat;
	tlgMat.lgMakeZeroMatrix(r, c);
	for (i = 0; i < r; i++)
	{
		for (j = 0; j < c; j++)
		{
			for (k = 0; k < c; k++)
			{
				tlgMat[i][j] += ltlgMatrix[i][k] * rtlgMatrix[k][j];
			}
		}
	}
	return tlgMat;
}

/*
* const lgMatrix operator *(double tK, const lgMatrix& tlgMatrix)
* 
* This method overload operator *.
*
* Parameter:
*	  tK is the left constant number
*	  tlgMatrix is the right matrix
* Return:
*	  a copy of the result lgMatrix
*
*/
const lgMatrix operator *(double tK, const lgMatrix& tlgMatrix)
{
	unsigned int i = 0, j = 0, r = tlgMatrix.lgGetRow(), c = tlgMatrix.lgGetColumn();
	lgMatrix tlgMat = tlgMatrix;
	for(i = 0; i < r; i++)
	{
		for(j = 0; j < c; j++)
		{
			tlgMat[i][j] = tlgMat[i][j] * tK;
		}
	}
	return tlgMat;
}

/*
* const lgMatrix operator *(double tK)
* 
* This method overload operator *.
*
* Parameter:
*	  tK is the constant number
* Return:
*	  a copy of the result lgMatrix
*
*/
const lgMatrix lgMatrix::operator *(double tK)
{
	unsigned int i = 0, j = 0, r = m_lgR, c = m_lgC;
	lgMatrix tlgMat = *this;
	for(i = 0; i < r; i++)
	{
		for(j = 0; j < c; j++)
		{
			tlgMat[i][j] = tlgMat[i][j] * tK;
		}
	}
	return tlgMat;
}

/*
* const lgMatrix operator /(double tK)
* 
* This method overload operator *.
*
* Parameter:
*	  tK is the constant number
* Return:
*	  a copy of the result lgMatrix
*
*/
const lgMatrix lgMatrix::operator /(double tK) const
{
	if(tK == 0)
	{
		//?
	}
	unsigned int i = 0, j = 0;
	for(i = 0; i < m_lgR; i++)
	{
		for(j = 0; j < m_lgC; j++)
		{
			m_lgMatrix[i][j] /= tK;
		}
	}
	return *this;
}

/*
* double* operator [](unsigned index) const
* 
* This method overload operator *.
*
* Parameter:
*	  index is the rowth of matrix
* Return:
*	  a address of the line of matrix
*
*/
double* lgMatrix::operator [](unsigned index) const
{
	return m_lgMatrix[index];
}

/*
* const lgMatrix operator =(const lgMatrix& tlgMatrix)
* 
* This method overload operator *.
*
* Parameter:
*	  tlgMatrix is the src matrix
* Return:
*	  a copy of the result matrix
*
*/
const lgMatrix lgMatrix::operator =(const lgMatrix& tlgMatrix)
{
	lgCopy(tlgMatrix);
	return *this;
}

const lgMatrix lgMatrix::operator =(const lgPoint& tlgPoint)
{
	lgDeleteMatrix();
	lgInit();
	lgMakeZeroMatrix(1, 4);
	lgEmptyMatrix(0.0);
	m_lgMatrix[0][0] = tlgPoint.lgGetX();
	m_lgMatrix[0][1] = tlgPoint.lgGetY();
	m_lgMatrix[0][2] = tlgPoint.lgGetZ();
	m_lgMatrix[0][3] = 1.0;
	return *this;
}

/*
* void lgGetDetMatrix(const lgMatrix& tlgSrcMatrix, unsigned int tC, 
							 unsigned int tR, lgMatrix& tTarSequence, double& det)
* 
* This method use recursion to calculate 
*  the det of matrix.
*
* Parameter:
*	  tlgSrcMatrix is the src matrix
*	  tC is current column
*	  tR is the new line that last 
*			selected row num adds one
*	  tTarSequence is 1XN matrix that record
*			the sequence
*	  det is the final det result
* Return:
*	  void
*
*/
void lgMatrix::lgGetDetMatrix(const lgMatrix& tlgSrcMatrix, lgMatrix& tlgOrderMatrix, 
							  lgMatrix& tlgFlagMatrix, unsigned int tR, 
							  unsigned int tC, lgMatrix& tTarSequence, double& det)
{
	if(tR == tlgSrcMatrix.lgGetRow())
	{
		unsigned int j = 0, sgn = 0;
		int sign = 1;
		double t = 1.0;
		sgn = lgSgn(tlgOrderMatrix);
		for(j = 0; j < tR; j++)
		{
			t *= tTarSequence[j][0];
		}
		if(sgn % 2)
		{
			sign = -1;
		}
		else
		{
			sign = 1;
		}
		det += sign * t;
		return;
	}
	unsigned int i = 0, c = tlgSrcMatrix.lgGetColumn();
	for(i = 0; i < c; i++)
	{
		if(((int)(tlgFlagMatrix[i][0])) == 0)
		{
			continue;
		}
		tTarSequence[tR][0] = tlgSrcMatrix[tR][i];
		tlgOrderMatrix[tR][0] = i;
		tlgFlagMatrix[i][0] = 0.0;
		lgGetDetMatrix(tlgSrcMatrix, tlgOrderMatrix, tlgFlagMatrix, tR + 1, i + 1, tTarSequence, det);
		tlgFlagMatrix[i][0] = 1.0;
	}
}

/*
* void lgMakeLocalToWorldMatrix(const lgPoint&, lgMatrix&)
* 
* This method makes a tranposition matrix used to
* transform local coords.
*
* Parameter:
*	  lgPoint is the world origin point
*	  of the object
*	  lgMatrix is used to save result
* Return:
*	  void
*
* This medthod return 4X4 matrix.
*/
void lgMatrix::lgMakeLocalToWorldMatrix(const lgPoint& tlgWorldPoint, lgMatrix& tlgMatrix)
{
	lgPoint tlgPoint = tlgWorldPoint;
	tlgMatrix.lgMakeDiagonalMatrix(4, 1);
	tlgMatrix[3][0] = tlgPoint.lgGetX();
	tlgMatrix[3][1] = tlgPoint.lgGetY();
	tlgMatrix[3][2] = tlgPoint.lgGetZ();
}

/*
* void lgMakeLocalToWorldMatrix(const lgPoint&, lgMatrix&)
* 
* This method makes a tranposition matrix used to
* transform world coords.
*
* Parameter:
*	  tlgPoint is the world origin point
*	  of the object
*	  tlgMatrix is used to save result
* Return:
*	  void
*
* This medthod return 4X4 matrix.
*/
void lgMatrix::lgMakeWorldToCameraMatrix(const lgCamera& tlgCamera, lgMatrix& tlgMatrix)
{
	lgMatrix tlgRotateMatrix, tlgMoveMatrix;
	//rorate
	lgEluer tlgEluer = tlgCamera.lgGetEluer();
	tlgEluer = -tlgEluer;
	tlgEluer.lgEluerAngleTolgMatrix(tlgRotateMatrix);
	//move
	tlgMoveMatrix.lgMakeDiagonalMatrix(4, 1.0);
	/*lgPoint tlgWorldPoint = tlgCamera.lgGetWorldPoint();
	tlgMoveMatrix.lgMakeDiagonalMatrix(4, 1.0);
	tlgMoveMatrix[3][0] = tlgWorldPoint.lgGetX();
	tlgMoveMatrix[3][1] = tlgWorldPoint.lgGetY();
	tlgMoveMatrix[3][2] = tlgWorldPoint.lgGetZ();*/
	//first rotate,then move
	tlgMatrix = tlgRotateMatrix * tlgMoveMatrix;
}

/*
* void lgMakeCameraToViewMatrix(const lgCamera& tlgCamera, lgMatrix& tlgMatrix)
* 
* This method makes a tranposition matrix used to
* transform camera matrix.
*
* Parameter:
*	  tlgCamera is the camera parameters
*	  tlgMatrix is used to save result
* Return:
*	  void
*
* This medthod bases on the formula:
* (zcp - z) / (zcp - zh) = x / x'
* and requires zcp = 0,so x'=x/(z/zh)
* namly w=1/zh,and if  zh also equals one
* x' will be in the range [-m_lgX / zh,m_lgX / zh],
* so the view,coords will be easy to resolve.
*/
void lgMatrix::lgMakeCameraToViewMatrix(const lgCamera& tlgCamera, lgMatrix& tlgMatrix)
{
	//poject to standard view
	lgCamera::lgFrustum tlgFrustum = tlgCamera.lgGetFrustum();
	//tlgFrustum.m_lgZCP=0
	double d = tlgFrustum.m_lgZH;
	tlgMatrix.lgMakeDiagonalMatrix(4, 1.0);
	tlgMatrix[0][0] = d;
	tlgMatrix[1][1] = d;
	tlgMatrix[3][3] = 0.0;
	tlgMatrix[2][3] = 1.0;
	//zoom to view panel
	lgCamera::lgView tlgView = tlgCamera.lgGetView();
	if(tlgView.m_ViewHeight < tlgView.m_ViewWidth)
	{
		tlgMatrix[0][0] *= ((double)tlgView.m_ViewHeight) / tlgView.m_ViewWidth;
	}
	else
	{
		tlgMatrix[1][1] *= ((double)tlgView.m_ViewWidth) / tlgView.m_ViewHeight;
	}
}

/*
* void lgMakeViewToWindowMatrix(const lgCamera& tlgCamera, lgMatrix& tlgMatrix)
* 
* This method makes a tranposition matrix used to
* transform camera matrix.
*
* Parameter:
*	  tlgCamera is the camera parameters
*	  tlgMatrix is used to save result
* Return:
*	  void
*
* This medthod require point is 1X4 and
* z=0,w=1, like [x,y,0,1], then bases on 
* the formula:(zcp - z) / (zcp - zh) = x / x',
* it requires zcp = 0,the range of x' is 
* [-m_lgX/zh, m_lgX/zh], use function:
* m_WindowX + (x'+m_lgX/zh)/(2*m_lgX/zh)*(m_WindowWidth)
* and m_WindowY + (1-(y'+m_lgY/zh)/(2*m_lgY/zh))*(m_WindowHeight),
* if zh=m_lgX=m_lgY=1,this formula will be more easy.
*/
void lgMatrix::lgMakeViewToWindowMatrix(const lgCamera& tlgCamera, 
										lgMatrix& tlgMatrix)
{
	lgMatrix tlgZoomMatrix;
	tlgZoomMatrix.lgMakeDiagonalMatrix(4, 1.0);
	lgCamera::lgWindow tlgWindow = tlgCamera.lgGetWindow();
	lgCamera::lgFrustum tlgFrustum = tlgCamera.lgGetFrustum();
	tlgZoomMatrix[0][0] = tlgWindow.m_WindowWidth / (2 * tlgFrustum.m_lgX);
	tlgZoomMatrix[1][1] = -tlgWindow.m_WindowHeight / (2 * tlgFrustum.m_lgY);
	tlgZoomMatrix[2][0] = tlgWindow.m_WindowWidth / 2 + tlgWindow.m_WindowX;
	tlgZoomMatrix[2][1] = tlgWindow.m_WindowHeight / 2 + tlgWindow.m_WindowY;

	tlgMatrix = tlgZoomMatrix;
}

void lgMatrix::lgMakeLocalToWindowMatrix(const lgPoint& tlgWorldPoint, const lgCamera& tlgCamera, lgMatrix& tlgMatrix)
{
	lgMatrix tlgMat, tlgTransferMatrix;
	lgMakeLocalToWorldMatrix(tlgWorldPoint, tlgTransferMatrix);
	tlgMat = tlgTransferMatrix;
	lgMatrix::lgMakeWorldToCameraMatrix(tlgCamera, tlgTransferMatrix);
	tlgMat = tlgMat * tlgTransferMatrix;
	lgMatrix::lgMakeCameraToViewMatrix(tlgCamera, tlgTransferMatrix);
	tlgMat = tlgMat * tlgTransferMatrix;
	lgMatrix::lgMakeViewToWindowMatrix(tlgCamera, tlgTransferMatrix);
	tlgMatrix = tlgMat * tlgTransferMatrix;
}

/*
* void lgMakeRotateMatrix(double tAngle, const lgVector& tlgVector, 
								  lgMatrix& tlgMatrix)
* 
* This method makes a rotate matrix
*
* Parameter:
*	  tAngle is the rotate radian angle
*	  tlgVector is a unit vector
*	  tlgMatrix saves the result
* Return:
*	  void
*
* This medthod require tAngle must be radian, 
* and tlgVector must be a unit vector.
*/
void lgMatrix::lgMakeRotateMatrix(double tAngle, const lgVector& tlgVector, 
								  lgMatrix& tlgMatrix)
{
	tlgMatrix.lgMakeDiagonalMatrix(4, 1.0);
	lgDirect tlgDirect = tlgVector.lgGetDirectVector();
	lgPoint tlgOrgPoint = tlgVector.lgGetOrgPoint();

	double cosTheta = cos(tAngle),
		sinTheta = sin(tAngle),
		x = tlgDirect.lgGetX(),
		y = tlgDirect.lgGetY(),
		z = tlgDirect.lgGetZ(),
		xy = x * y,
		yx = xy,
		xz = x * z,
		zx = xz,
		yz = y * z,
		zy = yz,
		xx = x * x,
		yy = y * y,
		zz = z * z,
		xyCosTheta = xy * cosTheta,
		xzCosTheta = xz * cosTheta,
		yzCosTheta = yz * cosTheta,
		zyCosTheta = yzCosTheta,
		xSinTheta = x * sinTheta,
		ySinTheta = y * sinTheta,
		zSinTheta = z * sinTheta;

	tlgMatrix[0][0] = xx * (1 - cosTheta) + cosTheta;
	tlgMatrix[0][1] = xy - xyCosTheta + zSinTheta;
	tlgMatrix[0][2] = xz - xzCosTheta - ySinTheta;
	tlgMatrix[1][0] = xy * (1 - cosTheta) - zSinTheta;
	tlgMatrix[1][1] = yy * (1 - cosTheta) + cosTheta;
	tlgMatrix[1][2] = yz - yzCosTheta + xSinTheta;
	tlgMatrix[2][0] = xz - xzCosTheta + ySinTheta;
	tlgMatrix[2][1] = yz - yzCosTheta - xSinTheta;
	tlgMatrix[2][2] = zz * (1 - cosTheta) + cosTheta;
	
}

/*
* void lgMakeZoomMatrix(const lgVector& tlgVector, 
								lgMatrix& tlgMatrix)
* 
* This method makes a zoom matrix
*
* Parameter:
*	  tZoom is the zoom ratate
*	  tlgVector is a unit vector
*	  tlgMatrix saves the result
* Return:
*	  void
*
* This medthod require tAngle must be radian
*/
void lgMatrix::lgMakeZoomMatrix(const lgVector& tlgVector, 
								lgMatrix& tlgMatrix)
{
	double zoom = tlgVector.lgGetAbsoluteValue();
	lgVector n = tlgVector;
	n.lgNormalize();
	tlgMatrix.lgMakeDiagonalMatrix(4, 1.0);
	lgDirect tlgDirect = n.lgGetDirectVector();
	double k = tlgVector.lgGetAbsoluteValue(), 
		x = tlgDirect.lgGetX(), 
		y = tlgDirect.lgGetY(), 
		z = tlgDirect.lgGetZ(), 
		xy = x * y, 
		xz = x * z, 
		zx = xz,
		yz = y * z, 
		zy = yz,
		xx = x * x, 
		yy = y * y, 
		zz = z * z, 
		kxy = k * xy, 
		kxz = k * xz, 
		kyz = k * yz, 
		kzy = kyz;
	
	tlgMatrix[0][0] = 1 + (k - 1) * xx;
	tlgMatrix[0][1] = kxy  - xy;
	tlgMatrix[0][2] = kxz - xz;
	tlgMatrix[1][0] = kxy - xy;
	tlgMatrix[1][1] = 1 + (k - 1) * yy;
	tlgMatrix[1][2] = kyz - yz;
	tlgMatrix[2][0] = kxz - xz;
	tlgMatrix[2][1] = kzy - zy;
	tlgMatrix[2][2] = 1 + (k - 1) * zz;
}

void lgMatrix::lgMakeMoveMatrix(const lgVector& tlgVector, lgMatrix& tlgMatrix)
{
	tlgMatrix.lgMakeDiagonalMatrix(4, 1);
	lgDirect tlgDirect = tlgVector.lgGetDirectVector();
	tlgMatrix[3][0] = tlgDirect.lgGetX();
	tlgMatrix[3][1] = tlgDirect.lgGetY();
	tlgMatrix[3][2] = tlgDirect.lgGetZ();
}

//!
void lgMatrix::lgPrintMatrix() const
{
	unsigned int i = 0, j = 0;
	std::cout << std::endl;
	for (i = 0; i < m_lgR; i++)
	{
		for (j = 0; j < m_lgC; j++)
		{
			std::cout << m_lgMatrix[i][j] << ' ';
		}
		std::cout << std::endl;
	}
}