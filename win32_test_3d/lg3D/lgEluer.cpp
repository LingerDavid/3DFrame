#include "lgEluer.h"


lgEluer::lgEluer()
{
	m_lgHeading = 0;
	m_lgPitch = 0;
	m_lgBank = 0;
}

lgEluer::lgEluer(double tlgHeading, double tlgPitch, double tlgBank)
{
	m_lgHeading = tlgHeading;
	m_lgPitch = tlgPitch;
	m_lgBank = tlgBank;
}

lgEluer::lgEluer(const lgEluer& tlgEluer)
{
	m_lgHeading = tlgEluer.lgGetHeading();
	m_lgPitch = tlgEluer.lgGetPitch();
	m_lgBank = tlgEluer.lgGetBank();
}

double lgEluer::lgGetHeading() const
{
	return m_lgHeading;
}

double lgEluer::lgGetPitch() const
{
	return m_lgPitch;
}

double lgEluer::lgGetBank() const
{
	return m_lgBank;
}

void lgEluer::lgSetHeading(double tlgHeading)
{
	m_lgHeading = tlgHeading;
}

void lgEluer::lgSetPitch(double tlgPitch)
{
	m_lgPitch = tlgPitch;
}

void lgEluer::lgSetBank(double tlgBank)
{
	m_lgBank = tlgBank;
}


void lgEluer::lgEluerAngleTolgMatrix(lgMatrix& tlgMatrix)
{
	m_lgTransfer.lgEluerAngleTolgMatrix(*this, tlgMatrix);
}

void lgEluer::lgEluerAngleTolgQuaternion(lgQuaternion& tlgQuaternion)
{
	m_lgTransfer.lgEluerAngleTolgQuaternion(*this, tlgQuaternion);
}

const lgEluer& lgEluer::operator =(const lgEluer& tlgEluer)
{
	m_lgHeading = tlgEluer.lgGetHeading();
	m_lgPitch = tlgEluer.lgGetPitch();
	m_lgBank = tlgEluer.lgGetBank();
	return *this;
}

const lgEluer lgEluer::operator +(const lgEluer& tlgEluer)
{
	lgEluer tlgElr = *this;
	tlgElr.m_lgHeading += tlgEluer.lgGetHeading();
	tlgElr.m_lgPitch += tlgEluer.lgGetPitch();
	tlgElr.m_lgBank += tlgEluer.lgGetBank();

	if (tlgElr.m_lgHeading - 2 * PI > 10E-10)
	{
		tlgElr.m_lgHeading -= 2 * PI;
	}
	else if (tlgElr.m_lgHeading + 2 * PI < 10E-10)
	{
		tlgElr.m_lgHeading += 2 * PI;
	}

	if (tlgElr.m_lgPitch - 2 * PI > 10E-10)
	{
		tlgElr.m_lgPitch -= 2 * PI;
	}
	else if (tlgElr.m_lgPitch + 2 * PI < 10E-10)
	{
		tlgElr.m_lgPitch += 2 * PI;
	}

	if (tlgElr.m_lgBank - 2 * PI > 10E-10)
	{
		tlgElr.m_lgBank -= 2 * PI;
	}
	else if (tlgElr.m_lgBank + 2 * PI < 10E-10)
	{
		tlgElr.m_lgBank += 2 * PI;
	}
	return tlgElr;
}

const lgEluer& operator -(lgEluer& tlgEluer)
{
	tlgEluer.m_lgHeading = -tlgEluer.m_lgHeading;
	tlgEluer.m_lgPitch = -tlgEluer.m_lgPitch;
	tlgEluer.m_lgBank = -tlgEluer.m_lgBank;
	return tlgEluer;
}