#include <math.h>
#include "lgEluer.h"
#include "lgMatrix.h"
#include "lgQuaternion.h"
#include "lgTransfer.h"

#ifndef PI
#define PI 3.1415926
#endif

void lgTransfer::lgEluerAngleTolgMatrix(const lgEluer& tlgEluer, lgMatrix& tlgMatrix)
{
	double h = tlgEluer.lgGetHeading(),
		p = tlgEluer.lgGetPitch(),
		b = tlgEluer.lgGetBank();
	tlgMatrix.lgMakeDiagonalMatrix(4, 1.0);

	double cosh = cos(h),
		cosp = cos(p),
		cosb = cos(b),
		sinh = sin(h),
		sinp = sin(p),
		sinb = sin(b);
	tlgMatrix[0][0] = cosh * cosb + sinh * sinp * sinb;
	tlgMatrix[0][1] = sinb * cosp;
	tlgMatrix[0][2] = -sinh * cosb + cosh * sinp * sinp;
	tlgMatrix[1][0] = -cosh * sinb + sinh * sinp * cosb;
	tlgMatrix[1][1] = cosb * cosp;
	tlgMatrix[1][2] = sinb * sinh + cosh * sinp * cosb;
	tlgMatrix[2][0] = sinh * cosp;
	tlgMatrix[2][1] = -sinp;
	tlgMatrix[2][2] = cosh * cosp;
}

void lgTransfer::lgMatrixTolgEluerAngle(const lgMatrix& tlgMatrix, lgEluer& tlgEluer)
{
	tlgEluer.lgSetPitch(asin(-tlgMatrix[1][2]));
	tlgEluer.lgSetHeading(atan2(tlgMatrix[0][2], tlgMatrix[2][2]));
	tlgEluer.lgSetBank(atan2(tlgMatrix[1][0], tlgMatrix[1][1]));
}

void lgTransfer::lgQuaternionTolgMatrix(const lgQuaternion& tlgQuaternion, lgMatrix& tlgMatrix)
{
	lgDirect tlgDirect = tlgQuaternion.lgGetVector().lgGetDirectVector();
	double w = tlgQuaternion.lgGetW(), 
		x = tlgDirect.lgGetX(), 
		y = tlgDirect.lgGetY(), 
		z = tlgDirect.lgGetZ();
	tlgMatrix[0][0] = 1 - 2 * y * y - 2 * z * z;
	tlgMatrix[0][1] = 2 * x * y + 2 * w * z;
	tlgMatrix[0][2] = 2 * x * z - 2 * w * y;
	tlgMatrix[1][0] = 2 * x * y - 2 * w * z;
	tlgMatrix[1][1] = 1 - 2 * x * x - 2 * z * z;
	tlgMatrix[1][2] = 2 * y * z + 2 * w * x;
	tlgMatrix[2][0] = 2 * x * z + 2 * w *  y;
	tlgMatrix[2][1] = 2 * y * z - 2 * w * x;
	tlgMatrix[2][2] = 1 - 2 * x * x - 2 * y * y;
}

void lgTransfer::lgMatrixTolgQuaternion(const lgMatrix& tlgMatrix, lgQuaternion& tlgQuaternion)
{
	lgQuaternion tlgQuater(pow(tlgMatrix[0][0] - tlgMatrix[1][1] - tlgMatrix[2][2] + 1, 0.5) / 2,
		pow(-tlgMatrix[0][0] + tlgMatrix[1][1] - tlgMatrix[2][2] + 1, 0.5) / 2,
		pow(-tlgMatrix[0][0] - tlgMatrix[1][1] + tlgMatrix[2][2] + 1, 0.5) / 2,
		pow(tlgMatrix[0][0] + tlgMatrix[1][1] + tlgMatrix[2][2] + 1, 0.5) / 2);
}

void lgTransfer::lgEluerAngleTolgQuaternion(const lgEluer& tlgEluer, lgQuaternion& tlgQuaternion)
{
	double h = tlgEluer.lgGetHeading(),
		p = tlgEluer.lgGetPitch(),
		b = tlgEluer.lgGetBank(),
		cosh2 = cos(h / 2), 
		cosp2 = cos(p / 2), 
		cosb2 = cos(b / 2), 
		sinh2 = sin(h / 2), 
		sinp2 = sin(p / 2), 
		sinb2 = sin(b / 2);
	lgQuaternion tlgQuater(-cosh2 * sinp2 * cosb2 - sinh2 * cosp2 * sinb2, 
		cosh2 * sinp2 * sinb2 - sinh2 * cosp2 * cosb2, 
		sinh2 * sinp2 * cosb2 - cosh2 * cosp2 * sinb2, 
		cosh2 * cosp2 * cosb2 + sinh2 + sinp2 * sinb2);
	tlgQuaternion = tlgQuater;
}

void lgTransfer::lgQuaternionTolgEluerAngle(const lgQuaternion& tlgQuaternion, lgEluer& tlgEluer)
{
	lgDirect tlgDirect = tlgQuaternion.lgGetVector().lgGetDirectVector();
	double w = tlgQuaternion.lgGetW(), 
		x = tlgDirect.lgGetX(), 
		y = tlgDirect.lgGetY(), 
		z = tlgDirect.lgGetZ();
	tlgEluer.lgSetPitch(asin(-2 * (y * z + w * x)));
	if (abs(cos(tlgEluer.lgGetPitch())) > 10E-10)
	{
		tlgEluer.lgSetHeading(atan2(x * z - w * y, 0.5 - x * x - y * y));
		tlgEluer.lgSetBank(atan2(x * y - w * z, 0.5 - x * x - z * z));
	}
	else
	{
		tlgEluer.lgSetHeading(atan2(-x * z - w * y, 0.5 - y * y - z * z));
		tlgEluer.lgSetBank(0.0);
	}
}


void lgTransfer::lgPointTolgQuaternion(const lgPoint& tlgPoint, lgQuaternion& tlgQuaternion)
{
	lgQuaternion tlgQuater(tlgPoint.lgGetX(), tlgPoint.lgGetY(), tlgPoint.lgGetZ(), 1.0);
	tlgQuaternion = tlgQuater;
}

void lgTransfer::lgQuaternionTolgPoint(const lgQuaternion& tlgQuaternion, lgPoint& tlgPoint)
{
	lgDirect tlgDirect = tlgQuaternion.lgGetVector().lgGetDirectVector();
	double tlgW = tlgQuaternion.lgGetW();
	if (tlgW)
	{
		tlgPoint = tlgDirect / tlgW;
	}
	else
	{
		//z=0
	}
}