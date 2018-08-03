#include "lgPoint.h"
#include "lgLine.h"
#include "lgVector.h"
#include "lgMatrix.h"
#include "lgTriangle.h"
#include "lgControl.h"

//////////////////////////////////Point Control//////////////////////////////
void lgControl::lgRotate(double tlgAngle, const lgVector& tlgVector, 
						 const lgPoint& tSrclgPoint, lgPoint& tTarlgPoint)
{
	tTarlgPoint = tSrclgPoint;
	lgMatrix lgRotateMatrix, lgSrcMatrix;
	lgMatrix::lgMakeRotateMatrix(tlgAngle, tlgVector, lgRotateMatrix);
	//[x,y,z]->[x,y,z,1]
	lgSrcMatrix = tSrclgPoint;
	lgSrcMatrix = lgSrcMatrix * lgRotateMatrix;
	//[x,y,z,w]->[x/w,y/w,z/w]
	tTarlgPoint = lgSrcMatrix;
}

void lgControl::lgRotate(const lgMatrix& lgRotateMatrix, const lgPoint& tSrclgPoint, lgPoint& tTarlgPoint)
{
	tTarlgPoint = tSrclgPoint;
	lgMatrix lgSrcMatrix;
	lgSrcMatrix = tSrclgPoint;
	lgSrcMatrix = lgSrcMatrix * lgRotateMatrix;
	//[x,y,z,w]->[x/w,y/w,z/w]
	tTarlgPoint = lgSrcMatrix;
}

void lgControl::lgRotateByX(double tlgAngle, const lgPoint& tSrclgPoint, 
							lgPoint& tTarlgPoint)
{
	lgDirect tlgDirect(1, 0, 0);
	lgPoint tlgOrgPoint(0, 0, 0);
	lgVector tlgVector(tlgOrgPoint, tlgDirect + tlgOrgPoint);
	lgRotate(tlgAngle, tlgVector, tSrclgPoint, tTarlgPoint);
}

void lgControl::lgRotateByY(double tlgAngle, const lgPoint& tSrclgPoint, 
							lgPoint& tTarlgPoint)
{
	lgDirect tlgDirect(0, 1, 0);
	lgPoint tlgOrgPoint(0, 0, 0);
	lgVector tlgVector(tlgOrgPoint, tlgDirect + tlgOrgPoint);
	lgRotate(tlgAngle, tlgVector, tSrclgPoint, tTarlgPoint);
}
void lgControl::lgRotateByZ(double tlgAngle, const lgPoint& tSrclgPoint, 
							lgPoint& tTarlgPoint)
{
	lgDirect tlgDirect(0, 0, 1);
	lgPoint tlgOrgPoint(0, 0, 0);
	lgVector tlgVector(tlgOrgPoint, tlgDirect + tlgOrgPoint);
	lgRotate(tlgAngle, tlgVector, tSrclgPoint, tTarlgPoint);
}

void lgControl::lgMove(const lgVector& tlgVector, const lgPoint& tSrclgPoint, 
					   lgPoint& tTarlgPoint)
{
	tTarlgPoint = tSrclgPoint;
	lgMatrix lgMoveMatrix, lgSrcMatrix;
	lgMatrix::lgMakeMoveMatrix(tlgVector, lgMoveMatrix);
	//[x,y,z]->[x,y,z,1]
	lgSrcMatrix = tSrclgPoint;
	lgSrcMatrix = lgSrcMatrix * lgMoveMatrix;
	//[x,y,z,w]->[x/w,y/w,z/w]
	tTarlgPoint = lgSrcMatrix;
}

void lgControl::lgMove(const lgMatrix& lgMoveMatrix, const lgPoint& tSrclgPoint, lgPoint& tTarlgPoint)
{
	tTarlgPoint = tSrclgPoint;
	lgMatrix lgSrcMatrix;
	//[x,y,z]->[x,y,z,1]
	lgSrcMatrix = tSrclgPoint;
	lgSrcMatrix = lgSrcMatrix * lgMoveMatrix;
	//[x,y,z,w]->[x/w,y/w,z/w]
	tTarlgPoint = lgSrcMatrix;

}

void lgControl::lgMoveByX(double tOffSet, const lgPoint& tSrclgPoint, 
					   lgPoint& tTarlgPoint)
{
	lgDirect tlgDirect(tOffSet, 0, 0);
	lgPoint tlgOrgPoint(0, 0, 0);
	lgVector tlgVector(tlgOrgPoint, tlgDirect + tlgOrgPoint);
	lgMove(tlgVector, tSrclgPoint, tTarlgPoint);
}

void lgControl::lgMoveByY(double tOffSet, const lgPoint& tSrclgPoint, 
					   lgPoint& tTarlgPoint)
{
	lgDirect tlgDirect(0, tOffSet, 0);
	lgPoint tlgOrgPoint(0, 0, 0);
	lgVector tlgVector(tlgOrgPoint, tlgDirect + tlgOrgPoint);
	lgMove(tlgVector, tSrclgPoint, tTarlgPoint);
}

void lgControl::lgMoveByZ(double tOffSet, const lgPoint& tSrclgPoint, 
					   lgPoint& tTarlgPoint)
{
	lgDirect tlgDirect(0, 0, tOffSet);
	lgPoint tlgOrgPoint(0, 0, 0);
	lgVector tlgVector(tlgOrgPoint, tlgDirect + tlgOrgPoint);
	lgMove(tlgVector, tSrclgPoint, tTarlgPoint);
}

void lgControl::lgZoom(const lgVector& tlgVector, const lgPoint& tSrclgPoint, 
					   lgPoint& tTarlgPoint)
{
	tTarlgPoint = tSrclgPoint;
	lgMatrix lgZoomMatrix, lgSrcMatrix;
	lgMatrix::lgMakeZoomMatrix(tlgVector, lgZoomMatrix);
	//[x,y,z]->[x,y,z,1]
	lgSrcMatrix = tSrclgPoint;
	lgSrcMatrix = lgSrcMatrix * lgZoomMatrix;
	//[x,y,z,w]->[x/w,y/w,z/w]
	tTarlgPoint = lgSrcMatrix;
}

void lgControl::lgZoom(const lgMatrix& lgZoomMatrix, const lgPoint& tSrclgPoint, lgPoint& tTarlgPoint)
{
	tTarlgPoint = tSrclgPoint;
	lgMatrix lgSrcMatrix;
	lgSrcMatrix = tSrclgPoint;
	lgSrcMatrix = lgSrcMatrix * lgZoomMatrix;
	//[x,y,z,w]->[x/w,y/w,z/w]
	tTarlgPoint = lgSrcMatrix;
}

void lgControl::lgZoomByX(double tOffSet, const lgPoint& tSrclgPoint, 
					   lgPoint& tTarlgPoint)
{
	lgDirect tlgDirect(tOffSet, 0, 0);
	lgPoint tlgOrgPoint(0, 0, 0);
	lgVector tlgVector(tlgOrgPoint, tlgDirect + tlgOrgPoint);
	lgZoom(tlgVector, tSrclgPoint, tTarlgPoint);
}

void lgControl::lgZoomByY(double tOffSet, const lgPoint& tSrclgPoint, 
					   lgPoint& tTarlgPoint)
{
	lgDirect tlgDirect(0, tOffSet, 0);
	lgPoint tlgOrgPoint(0, 0, 0);
	lgVector tlgVector(tlgOrgPoint, tlgDirect + tlgOrgPoint);
	lgZoom(tlgVector, tSrclgPoint, tTarlgPoint);
}

void lgControl::lgZoomByZ(double tOffSet, const lgPoint& tSrclgPoint, 
					   lgPoint& tTarlgPoint)
{
	lgDirect tlgDirect(0, 0, tOffSet);
	lgPoint tlgOrgPoint(0, 0, 0);
	lgVector tlgVector(tlgOrgPoint, tlgDirect + tlgOrgPoint);
	lgZoom(tlgVector, tSrclgPoint, tTarlgPoint);
}

///////////////////////Vector Control/////////////////////////////////
void lgControl::lgRotate(double tlgAngle, const lgVector& tlgVector, 
						 const lgVector& tSrclgVector, lgVector& tTarlgVector)
{
	tTarlgVector = tSrclgVector;
	lgPoint srcPt, desPt;
	////////////////////////////////////
	srcPt = tTarlgVector.lgGetOrgPoint();
	desPt = srcPt;
	lgRotate(tlgAngle, tlgVector, srcPt, desPt);
	tTarlgVector.lgSetOrgPoint(srcPt);

	////////////////////////////////////
	srcPt = tTarlgVector.lgGetDesPoint();
	desPt = srcPt;
	lgRotate(tlgAngle, tlgVector, srcPt, desPt);
	tTarlgVector.lgSetDesPoint(srcPt);
}

void lgControl::lgRotate(const lgMatrix& lgRotateMatrix, const lgVector& tSrclgVector, lgVector& tTarlgVector)
{
	tTarlgVector = tSrclgVector;
	lgPoint srcPt, desPt;
	////////////////////////////////////
	srcPt = tTarlgVector.lgGetOrgPoint();
	desPt = srcPt;
	lgRotate(lgRotateMatrix, srcPt, desPt);
	tTarlgVector.lgSetOrgPoint(desPt);

	////////////////////////////////////
	srcPt = tTarlgVector.lgGetDesPoint();
	desPt = srcPt;
	lgRotate(lgRotateMatrix, srcPt, desPt);
	tTarlgVector.lgSetDesPoint(desPt);
}

void lgControl::lgRotateByX(double tlgAngle, const lgVector& tSrclgVector, 
							lgVector& tTarlgVector)
{
	lgDirect tlgDirect(1, 0, 0);
	lgPoint tlgOrgPoint(0, 0, 0);
	lgVector tlgVector(tlgOrgPoint, tlgDirect + tlgOrgPoint);
	lgRotate(tlgAngle, tlgVector, tSrclgVector, tTarlgVector);
}

void lgControl::lgRotateByY(double tlgAngle, const lgVector& tSrclgVector, 
							lgVector& tTarlgVector)
{
	lgDirect tlgDirect(0, 1, 0);
	lgPoint tlgOrgPoint(0, 0, 0);
	lgVector tlgVector(tlgOrgPoint, tlgDirect + tlgOrgPoint);
	lgRotate(tlgAngle, tlgVector, tSrclgVector, tTarlgVector);
}
void lgControl::lgRotateByZ(double tlgAngle, const lgVector& tSrclgVector, 
							lgVector& tTarlgVector)
{
	lgDirect tlgDirect(0, 0, 1);
	lgPoint tlgOrgPoint(0, 0, 0);
	lgVector tlgVector(tlgOrgPoint, tlgDirect + tlgOrgPoint);
	lgRotate(tlgAngle, tlgVector, tSrclgVector, tTarlgVector);
}

void lgControl::lgMove(const lgVector& tlgVector, const lgVector& tSrclgVector, 
					   lgVector& tTarlgVector)
{
	tTarlgVector = tSrclgVector;
	lgPoint srcPt, desPt;
	////////////////////////////////////
	srcPt = tTarlgVector.lgGetOrgPoint();
	desPt = srcPt;
	lgMove(tlgVector, srcPt, desPt);
	tTarlgVector.lgSetOrgPoint(srcPt);

	////////////////////////////////////
	srcPt = tTarlgVector.lgGetDesPoint();
	desPt = srcPt;
	lgMove(tlgVector, srcPt, desPt);
	tTarlgVector.lgSetDesPoint(srcPt);
}

void lgControl::lgMove(const lgMatrix& tlgMoveMatrix, const lgVector& tSrclgVector,
	lgVector& tTarlgVector)
{
	tTarlgVector = tSrclgVector;
	lgPoint srcPt, desPt;
	////////////////////////////////////
	srcPt = tTarlgVector.lgGetOrgPoint();
	desPt = srcPt;
	lgMove(tlgMoveMatrix, srcPt, desPt);
	tTarlgVector.lgSetOrgPoint(srcPt);

	////////////////////////////////////
	srcPt = tTarlgVector.lgGetDesPoint();
	desPt = srcPt;
	lgMove(tlgMoveMatrix, srcPt, desPt);
	tTarlgVector.lgSetDesPoint(srcPt);
}

void lgControl::lgMoveByX(double tOffSet, const lgVector& tSrclgVector, 
					   lgVector& tTarlgVector)
{
	lgDirect tlgDirect(1, 0, 0);
	lgPoint tlgOrgPoint(0, 0, 0);
	lgVector tlgVector(tlgOrgPoint, tlgDirect + tlgOrgPoint);
	lgMove(tlgVector, tSrclgVector, tTarlgVector);
}

void lgControl::lgMoveByY(double tOffSet, const lgVector& tSrclgVector, 
					   lgVector& tTarlgVector)
{
	lgDirect tlgDirect(0, 1, 0);
	lgPoint tlgOrgPoint(0, 0, 0);
	lgVector tlgVector(tlgOrgPoint, tlgDirect + tlgOrgPoint);
	lgMove(tlgVector, tSrclgVector, tTarlgVector);
}

void lgControl::lgMoveByZ(double tOffSet, const lgVector& tSrclgVector, 
					   lgVector& tTarlgVector)
{
	lgDirect tlgDirect(0, 0, 1);
	lgPoint tlgOrgPoint(0, 0, 0);
	lgVector tlgVector(tlgOrgPoint, tlgDirect + tlgOrgPoint);
	lgMove(tlgVector, tSrclgVector, tTarlgVector);
}

void lgControl::lgZoom(const lgVector& tlgVector, const lgVector& tSrclgVector, 
					   lgVector& tTarlgVector)
{
	tTarlgVector = tSrclgVector;
	lgPoint srcPt, desPt;
	////////////////////////////////////
	srcPt = tTarlgVector.lgGetOrgPoint();
	desPt = srcPt;
	lgZoom(tlgVector, srcPt, desPt);
	tTarlgVector.lgSetOrgPoint(srcPt);

	////////////////////////////////////
	srcPt = tTarlgVector.lgGetDesPoint();
	desPt = srcPt;
	lgZoom(tlgVector, srcPt, desPt);
	tTarlgVector.lgSetDesPoint(srcPt);
}

void lgControl::lgZoom(const lgMatrix& lgZoomMatrix, const lgVector& tSrclgVector,
	lgVector& tTarlgVector)
{
	tTarlgVector = tSrclgVector;
	lgPoint srcPt, desPt;
	////////////////////////////////////
	srcPt = tTarlgVector.lgGetOrgPoint();
	desPt = srcPt;
	lgZoom(lgZoomMatrix, srcPt, desPt);
	tTarlgVector.lgSetOrgPoint(srcPt);

	////////////////////////////////////
	srcPt = tTarlgVector.lgGetDesPoint();
	desPt = srcPt;
	lgZoom(lgZoomMatrix, srcPt, desPt);
	tTarlgVector.lgSetDesPoint(srcPt);
}


void lgControl::lgZoomByX(double tOffSet, const lgVector& tSrclgVector, 
					   lgVector& tTarlgVector)
{
	lgDirect tlgDirect(1, 0, 0);
	lgPoint tlgOrgPoint(0, 0, 0);
	lgVector tlgVector(tlgOrgPoint, tlgDirect + tlgOrgPoint);
	lgZoom(tlgVector, tSrclgVector, tTarlgVector);
}

void lgControl::lgZoomByY(double tOffSet, const lgVector& tSrclgVector, 
					   lgVector& tTarlgVector)
{
	lgDirect tlgDirect(0, 1, 0);
	lgPoint tlgOrgPoint(0, 0, 0);
	lgVector tlgVector(tlgOrgPoint, tlgDirect + tlgOrgPoint);
	lgZoom(tlgVector, tSrclgVector, tTarlgVector);
}

void lgControl::lgZoomByZ(double tOffSet, const lgVector& tSrclgVector, 
					   lgVector& tTarlgVector)
{
	lgDirect tlgDirect(0, 0, 1);
	lgPoint tlgOrgPoint(0, 0, 0);
	lgVector tlgVector(tlgOrgPoint, tlgDirect + tlgOrgPoint);
	lgZoom(tlgVector, tSrclgVector, tTarlgVector);
}

///////////////////////Face Control///////////////////////////////////
void lgControl::lgRotate(double tlgAngle, const lgVector& tlgVector, 
						 const lgTriangle& tSrclgTriangle, lgTriangle& tTarlgTriangle)
{
	int i = 1;
	lgPoint srcPt, desPt;
	for(i = 0; i < 3; i++)
	{
		srcPt = tSrclgTriangle[i];
		lgRotate(tlgAngle, tlgVector, srcPt, desPt);
		tTarlgTriangle[i] = desPt;
	}
	lgVector normal = tSrclgTriangle.lgGetNormal();
	normal.lgRotate(tlgAngle, tlgVector);
	tTarlgTriangle.lgSetNormal(normal);
}

void lgControl::lgRotate(const lgMatrix& lgRotateMatrix, const lgTriangle& tSrclgTriangle, lgTriangle& tTarlgTriangle)
{
	int i = 1;
	lgPoint srcPt, desPt;
	for (i = 0; i < 3; i++)
	{
		srcPt = tSrclgTriangle[i];
		lgRotate(lgRotateMatrix, srcPt, desPt);
		tTarlgTriangle[i] = desPt;
	}
	lgVector normal = tSrclgTriangle.lgGetNormal();
	normal.lgRotate(lgRotateMatrix);
	tTarlgTriangle.lgSetNormal(normal);
}


void lgControl::lgRotateByX(double tlgAngle, const lgTriangle& tSrclgTriangle,
							lgTriangle& tTarlgTriangle)
{
	lgDirect tlgDirect(1, 0, 0);
	lgPoint tlgOrgPoint(0, 0, 0);
	lgVector tlgVector(tlgOrgPoint, tlgDirect + tlgOrgPoint);
	lgRotate(tlgAngle, tlgVector, tSrclgTriangle, tTarlgTriangle);
}

void lgControl::lgRotateByY(double tlgAngle, const lgTriangle& tSrclgTriangle,
							lgTriangle& tTarlgTriangle)
{
	lgDirect tlgDirect(0, 1, 0);
	lgPoint tlgOrgPoint(0, 0, 0);
	lgVector tlgVector(tlgOrgPoint, tlgDirect + tlgOrgPoint);
	lgRotate(tlgAngle, tlgVector, tSrclgTriangle, tTarlgTriangle);
}

void lgControl::lgRotateByZ(double tlgAngle, const lgTriangle& tSrclgTriangle,
							lgTriangle& tTarlgTriangle)
{
	lgDirect tlgDirect(0, 0, 1);
	lgPoint tlgOrgPoint(0, 0, 0);
	lgVector tlgVector(tlgOrgPoint, tlgDirect + tlgOrgPoint);
	lgRotate(tlgAngle, tlgVector, tSrclgTriangle, tTarlgTriangle);
}

void lgControl::lgMove(const lgVector& tlgVector, const lgTriangle& tSrclgTriangle, 
					   lgTriangle& tTarlgTriangle)
{
	int i = 1;
	lgPoint srcPt, desPt;
	for (i = 0; i < 3; i++)
	{
		srcPt = tSrclgTriangle[i];
		lgMove(tlgVector, srcPt, desPt);
		tTarlgTriangle[i] = desPt;
	}
}

void lgControl::lgMove(const lgMatrix& tlgMoveMatrix, const lgTriangle& tSrclgTriangle,
	lgTriangle& tTarlgTriangle)
{
	int i = 1;
	lgPoint srcPt, desPt;
	for (i = 0; i < 3; i++)
	{
		srcPt = tSrclgTriangle[i];
		lgMove(tlgMoveMatrix, srcPt, desPt);
		tTarlgTriangle[i] = desPt;
	}
}

void lgControl::lgMoveByX(double tOffSet, const lgTriangle& tSrclgTriangle,
					   lgTriangle& tTarlgTriangle)
{
	lgDirect tlgDirect(1, 0, 0);
	lgPoint tlgOrgPoint(0, 0, 0);
	lgVector tlgVector(tlgOrgPoint, tlgDirect + tlgOrgPoint);
	lgMove(tlgVector, tSrclgTriangle, tTarlgTriangle);
}

void lgControl::lgMoveByY(double tOffSet, const lgTriangle& tSrclgTriangle,
					   lgTriangle& tTarlgTriangle)
{
	lgDirect tlgDirect(0, 1, 0);
	lgPoint tlgOrgPoint(0, 0, 0);
	lgVector tlgVector(tlgOrgPoint, tlgDirect + tlgOrgPoint);
	lgMove(tlgVector, tSrclgTriangle, tTarlgTriangle);
}

void lgControl::lgMoveByZ(double tOffSet, const lgTriangle& tSrclgTriangle,
					   lgTriangle& tTarlgTriangle)
{
	lgDirect tlgDirect(0, 0, 1);
	lgPoint tlgOrgPoint(0, 0, 0);
	lgVector tlgVector(tlgOrgPoint, tlgDirect + tlgOrgPoint);
	lgMove(tlgVector, tSrclgTriangle, tTarlgTriangle);
}

void lgControl::lgZoom(const lgVector& tlgVector, const lgTriangle& tSrclgTriangle,
					   lgTriangle& tTarlgTriangle)
{
	int i = 1;
	lgPoint srcPt, desPt;
	for (i = 0; i < 3; i++)
	{
		srcPt = tSrclgTriangle[i];
		lgZoom(tlgVector, srcPt, desPt);
		tTarlgTriangle[i] = desPt;
	}
}

void lgControl::lgZoom(const lgMatrix& lgZoomMatrix, const lgTriangle& tSrclgTriangle,
	lgTriangle& tTarlgTriangle)
{
	int i = 1;
	lgPoint srcPt, desPt;
	for (i = 0; i < 3; i++)
	{
		srcPt = tSrclgTriangle[i];
		lgZoom(lgZoomMatrix, srcPt, desPt);
		tTarlgTriangle[i] = desPt;
	}
}

void lgControl::lgZoomByX(double tOffSet, const lgTriangle& tSrclgTriangle,
					   lgTriangle& tTarlgTriangle)
{
	lgDirect tlgDirect(1, 0, 0);
	lgPoint tlgOrgPoint(0, 0, 0);
	lgVector tlgVector(tlgOrgPoint, tlgDirect + tlgOrgPoint);
	lgZoom(tlgVector, tSrclgTriangle, tTarlgTriangle);
}

void lgControl::lgZoomByY(double tOffSet, const lgTriangle& tSrclgTriangle,
					   lgTriangle& tTarlgTriangle)
{
	lgDirect tlgDirect(0, 1, 0);
	lgPoint tlgOrgPoint(0, 0, 0);
	lgVector tlgVector(tlgOrgPoint, tlgDirect + tlgOrgPoint);
	lgZoom(tlgVector, tSrclgTriangle, tTarlgTriangle);
}

void lgControl::lgZoomByZ(double tOffSet, const lgTriangle& tSrclgTriangle,
					   lgTriangle& tTarlgTriangle)
{
	lgDirect tlgDirect(0, 0, 1);
	lgPoint tlgOrgPoint(0, 0, 0);
	lgVector tlgVector(tlgOrgPoint, tlgDirect + tlgOrgPoint);
	lgZoom(tlgVector, tSrclgTriangle, tTarlgTriangle);
}

void lgControl::lgTransfer(const lgMatrix& tlgMatrix, const lgPoint& tSrclgPoint, lgPoint& tTarlgPoint)
{
	lgMatrix lgSrcMatrix;
	//[x,y,z]->[x,y,z,1]
	lgSrcMatrix = tSrclgPoint;
	lgSrcMatrix = lgSrcMatrix * tlgMatrix;
	//[x,y,z,w]->[x/w,y/w,z/w]
	tTarlgPoint = lgSrcMatrix;
}

void lgControl::lgTransfer(const lgMatrix& tlgMatrix, const lgVector& tSrclgVector, lgVector& tTarlgVector)
{
	tTarlgVector = tSrclgVector;
	lgPoint srcPt, desPt;
	////////////////////////////////////
	srcPt = tSrclgVector.lgGetOrgPoint();
	desPt = srcPt;
	lgTransfer(tlgMatrix, srcPt, desPt);
	tTarlgVector.lgSetOrgPoint(srcPt);

	////////////////////////////////////
	srcPt = tSrclgVector.lgGetDesPoint();
	desPt = srcPt;
	lgTransfer(tlgMatrix, srcPt, desPt);
	tTarlgVector.lgSetDesPoint(srcPt);
}

void lgControl::lgTransfer(const lgMatrix& tlgMatrix, const lgTriangle& tSrclgTriangle, lgTriangle& tTarlgTriangle)
{
	int i = 1;
	lgPoint srcPt, desPt;
	for (i = 0; i < 3; i++)
	{
		desPt = srcPt = tSrclgTriangle[i];
		lgTransfer(tlgMatrix, srcPt, desPt);
		tTarlgTriangle[i] = desPt;
	}
}