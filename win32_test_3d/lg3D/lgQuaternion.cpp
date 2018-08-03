#include <math.h>
#include "lgQuaternion.h"

lgQuaternion::lgQuaternion()
{
	m_lgVector.lgSetOrgPoint(lgPoint(0.0, 0.0, 0.0));
	m_lgVector.lgSetDesPoint(lgPoint(0.0, 0.0, 0.0));
	m_lgTheta = 0.0;
}

lgQuaternion::lgQuaternion(const lgVector& tlgVector, double tTheta)
{
	lgVector tlgVect = tlgVector;
	tlgVect.lgNormalize();
	m_lgVector = tlgVect;
	m_lgTheta = tTheta;
}

lgQuaternion::lgQuaternion(double tX, double tY, double tZ, double tW)
{
	double theta = acos(tW) * 2;
	m_lgVector.lgSetOrgPoint(lgPoint(0.0, 0.0, 0.0));
	m_lgVector.lgSetDesPoint(lgPoint(tX, tY, tZ));
	if (fabs(sin(theta / 2)) > 10E-10)
	{
		m_lgVector = m_lgVector / sin(theta / 2);
	}
	m_lgVector.lgNormalize();
	m_lgTheta = theta;
}

lgQuaternion::lgQuaternion(const lgQuaternion& tlgQuaternion)
{
	m_lgVector = tlgQuaternion.lgGetVector();
	m_lgTheta = tlgQuaternion.lgGetW();
}

const lgQuaternion lgQuaternion::operator +(const lgQuaternion& tlgQuaternion)
{
	double x1 = lgGetX(),
		y1 = lgGetY(),
		z1 = lgGetZ(),
		w1 = lgGetW(),
		x2 = tlgQuaternion.lgGetX(),
		y2 = tlgQuaternion.lgGetY(),
		z2 = tlgQuaternion.lgGetZ(),
		w2 = tlgQuaternion.lgGetW();

	lgQuaternion tlgQuatern(x1 + x2, y1 + y2, z1 + z2, w1 + w2);
	return tlgQuatern;
}

const lgQuaternion lgQuaternion::operator -(const lgQuaternion& tlgQuaternion)
{
	double x1 = lgGetX(),
		y1 = lgGetY(),
		z1 = lgGetZ(),
		w1 = lgGetW(),
		x2 = tlgQuaternion.lgGetX(),
		y2 = tlgQuaternion.lgGetY(),
		z2 = tlgQuaternion.lgGetZ(),
		w2 = tlgQuaternion.lgGetW();

	lgQuaternion tlgQuatern(x1 - x2, y1 - y2, z1 - z2, w1 - w2);
	return tlgQuatern;
}

const lgQuaternion  operator -(lgQuaternion& tlgQuaternion)
{
	double x = tlgQuaternion.lgGetX(),
		y = tlgQuaternion.lgGetY(),
		z = tlgQuaternion.lgGetZ(),
		w = tlgQuaternion.lgGetW();

	lgQuaternion tlgQuatern(-x, -y, -z, -w);
	tlgQuaternion = tlgQuatern;
	return tlgQuatern;
}

const lgQuaternion lgQuaternion::operator *(const lgQuaternion& tlgQuaternion) const
{
	lgVector v1(0.0, 0.0, 0.0, lgGetX(), lgGetY(), lgGetZ()), 
		v2(0.0, 0.0, 0.0, tlgQuaternion.lgGetX(), 
		tlgQuaternion.lgGetY(), tlgQuaternion.lgGetZ());
	double w1, w2;
	w1 = cos(m_lgTheta / 2);
	w2 = tlgQuaternion.lgGetW();

	double w3;
	lgVector v3;
	w3 = w1 * w2 - v1.lgDotMultiply(v2);
	v3 = w1 * v2 + w2 * v1 + v2 * v1;
	lgDirect lgDirect = v3.lgGetDirectVector();
	lgQuaternion tlgQuatern(lgDirect.lgGetX(), lgDirect.lgGetY(), 
		lgDirect.lgGetZ(), w3);
	return tlgQuatern;
}

const lgQuaternion lgQuaternion::operator /(double tK)
{
	lgQuaternion tlgQuaternion(lgGetX() / tK, lgGetY() / tK, lgGetZ() / tK, lgGetW() / tK);
	return tlgQuaternion;
}

const lgQuaternion operator*(double tK, const lgQuaternion& tlgQuaternion)
{
	double x = tlgQuaternion.lgGetX(),
		y = tlgQuaternion.lgGetY(),
		z = tlgQuaternion.lgGetZ(),
		w = tlgQuaternion.lgGetW();
	lgQuaternion tlgQuater(x * tK, y * tK, z * tK, w * tK);
	return tlgQuater;
}

bool lgQuaternion::operator ==(const lgQuaternion& tlgQuaternion)
{
	lgVector tlgVector = tlgQuaternion.lgGetVector();
	double tlgW = tlgQuaternion.lgGetW();
	if (tlgVector != lgGetVector()
		|| tlgW != lgGetW())
	{
		return false;
	}
	return true;
}

bool lgQuaternion::operator !=(const lgQuaternion& tlgQuaternion)
{
	return !(*this == tlgQuaternion);
}

const lgQuaternion lgQuaternion::operator =(const lgQuaternion& tlgQuaternion)
{
	m_lgVector = tlgQuaternion.lgGetVector();
	m_lgTheta = tlgQuaternion.lgGetTheta();
	return *this;
}

const lgQuaternion lgQuaternion::operator*(const lgMatrix& tlgMatrix)
{
	lgMatrix tMat = lgQuaternionCopyToMatrx();
	lgQuaternion tlgQuaternion;
	tMat = tMat * tlgMatrix;
	tlgQuaternion = tMat.lgMatrixCopyToQuaternion();
	return tlgQuaternion;
}

void lgQuaternion::lgQuaternionTolgEluerAngle(lgEluer& tlgEluer)
{
	m_lgTransfer.lgQuaternionTolgEluerAngle(*this, tlgEluer);
}

void lgQuaternion::lgQuaternionTolgMatrix(lgMatrix& tlgMatrix)
{
}
void lgQuaternion::lgQuaternionTolgPoint(lgPoint& tlgPoint)
{
	m_lgTransfer.lgQuaternionTolgPoint(*this, tlgPoint);
}

const lgQuaternion lgQuaternion::lgGetConjugateQuaternion() const
{
	lgQuaternion tlgQuaternion(-lgGetX(), -lgGetY(), -lgGetZ(), lgGetW());
	return tlgQuaternion;
}

const lgQuaternion lgQuaternion::lgGetNormalQuaternion() const
{
	lgQuaternion tlgQuaternion(0.0, 0.0, 0.0, 1.0);
	return tlgQuaternion;
}

double lgQuaternion::lgGetAbsoluteValue() const
{
	double abs = 0.0;
	double x = lgGetX(),
		y = lgGetY(),
		z = lgGetZ(), 
		w = lgGetW();
	abs = x * x + y * y + z * z + w * w;
	abs = pow(abs, 0.5);
	return abs;
}

const lgVector& lgQuaternion::lgGetVector() const
{
	return m_lgVector;
}

double lgQuaternion::lgGetW() const
{
	return cos(m_lgTheta / 2);
}

double lgQuaternion::lgGetX() const
{
	lgDirect tlgDirect = m_lgVector.lgGetDirectVector();
	return tlgDirect.lgGetX() * sin(m_lgTheta / 2);
}

double lgQuaternion::lgGetY() const
{
	lgDirect tlgDirect = m_lgVector.lgGetDirectVector();
	return tlgDirect.lgGetY() * sin(m_lgTheta / 2);
}

double lgQuaternion::lgGetZ() const
{
	lgDirect tlgDirect = m_lgVector.lgGetDirectVector();
	return tlgDirect.lgGetZ() * sin(m_lgTheta / 2);
}

double lgQuaternion::lgGetTheta() const
{
	return m_lgTheta;
}

void lgQuaternion::lgSetVector(const lgVector& tlgVector)
{
	m_lgVector = tlgVector;
	m_lgVector.lgNormalize();
}

void lgQuaternion::lgSetTheta(double tTheta)
{
	m_lgTheta = tTheta;
}

const lgMatrix lgQuaternion::lgQuaternionCopyToMatrx()
{
	lgMatrix tMat;
	tMat.lgMakeZeroMatrix(1, 4);
	tMat[0][0] = lgGetX();
	tMat[0][1] = lgGetY();
	tMat[0][2] = lgGetZ();
	tMat[0][3] = lgGetW();
	return tMat;
}

const lgQuaternion lgQuaternion::lgGetReversibleQuaternion() const
{
	lgQuaternion tlgQuaternion;
	tlgQuaternion = lgGetConjugateQuaternion();
	tlgQuaternion = tlgQuaternion / lgGetAbsoluteValue();
	return tlgQuaternion;
}

void lgQuaternion::lgLog(const lgQuaternion& tSrclgQuaternion, lgQuaternion& tTarlgQuaternion)
{
	double x = tSrclgQuaternion.lgGetX(), 
		y = tSrclgQuaternion.lgGetY(), 
		z = tSrclgQuaternion.lgGetZ(), 
		theta = tSrclgQuaternion.lgGetTheta();
	if (fabs(sin(theta / 2.0)) > 10E-10)
	{
		lgQuaternion tlgQuater(x * (theta / 2) / sin(theta / 2),
			y * (theta / 2) / sin(theta / 2),
			z * (theta / 2) / sin(theta), 0.0);
		tTarlgQuaternion = tlgQuater;
	}
}

void lgQuaternion::lgExp(const lgQuaternion& tSrclgQuaternion, lgQuaternion& tTarlgQuaternion)
{
	double w = tSrclgQuaternion.lgGetW();
	if (abs(w) > 10E-10)
	{
		return;
	}
	double x = tSrclgQuaternion.lgGetX(),
		y = tSrclgQuaternion.lgGetY(),
		z = tSrclgQuaternion.lgGetZ();
	double theta = pow(x * x + y * y + z * z, 0.5);
	lgQuaternion tlQuater(x * sin(theta / 2) / (theta / 2), y * sin(theta / 2) / (theta / 2), 
		z * sin(theta / 2) / (theta / 2), cos(theta / 2));

	tTarlgQuaternion = tlQuater;
}

void lgQuaternion::lgPower(const lgQuaternion& tSrclgQuaternion, double tT, lgQuaternion& tTarlgQuaternion)
{
	lgQuaternion tlgQuaternion, tlgQuater;
	lgLog(tSrclgQuaternion, tlgQuaternion);
	lgExp(tT * tlgQuaternion, tlgQuater);
	tTarlgQuaternion = tlgQuater;
}

void lgQuaternion::lgSlerp(const lgQuaternion& tSrclgQuaternion, 
	const lgQuaternion& tTarlgQuaternion, double tT, lgQuaternion& tInsertedlgQuaternion)
{
	lgQuaternion tlgQuaternion;
	tlgQuaternion = tSrclgQuaternion.lgGetReversibleQuaternion();
	tlgQuaternion = tlgQuaternion * tTarlgQuaternion;
	lgPower(tlgQuaternion, tT, tInsertedlgQuaternion);
	tInsertedlgQuaternion = tSrclgQuaternion * tInsertedlgQuaternion;
}

void lgQuaternion::lgSquad(const lgQuaternion&, const lgQuaternion&, double tT, lgQuaternion& tlgQuaternion)
{
}