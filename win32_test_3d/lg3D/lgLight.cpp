#include <math.h>
#include "lgLink.cpp"
#include "lgLight.h"

lgLight::lgLenda::lgLenda()
{
	m_lgMinLenda = m_lgMaxLenda = 0.0;
}

lgLight::lgLenda::~lgLenda()
{
}

const lgLight::lgLenda  lgLight::lgLenda::operator =(const lgLenda& tlgLenda)
{
	m_lgMinLenda = tlgLenda.m_lgMinLenda;
	m_lgMaxLenda = tlgLenda.m_lgMaxLenda;
	return *this;
}

lgLight::lgLight()
{
	m_lgLenda[PURPLE].m_lgMinLenda = 400;
	m_lgLenda[PURPLE].m_lgMaxLenda = 450;
	m_lgLenda[BLUE].m_lgMinLenda = 450;
	m_lgLenda[BLUE].m_lgMaxLenda = 500;
	m_lgLenda[GREEN].m_lgMinLenda = 500;
	m_lgLenda[GREEN].m_lgMinLenda = 550;
	m_lgLenda[YELLOW].m_lgMinLenda = 550;
	m_lgLenda[YELLOW].m_lgMinLenda = 600;
	m_lgLenda[ORANGE].m_lgMinLenda = 600;
	m_lgLenda[ORANGE].m_lgMinLenda = 650;
	m_lgLenda[RED].m_lgMinLenda = 650;
	m_lgLenda[RED].m_lgMinLenda = 700;

	m_lgLightSpeed = 3 * 10E8;

	lgAmbientLight tlgAmbientLight;
	lgInfiniteLight tlgInfiniteLight;
	lgPointLight tlgPointLight;
	lgSpotLight tlgSpotLight;

	tlgAmbientLight.m_lgI.lgSetRGB(0.0, 0.0, 0.0);

	tlgInfiniteLight.m_lgI.lgSetRGB(255.0, 255.0, 255.0);
	tlgInfiniteLight.m_lgDirection.lgSetOrgPoint(lgPoint(0.0, 0.0, -1.0));
	tlgInfiniteLight.m_lgDirection.lgSetDesPoint(lgPoint(0.0, 0.0, 0.0));

	tlgPointLight.m_lgI.lgSetRGB(255.0, 255.0, 255.0);
	tlgPointLight.m_lgDirection.lgSetOrgPoint(lgPoint(0.0, 0.0, -1.0));
	tlgPointLight.m_lgDirection.lgSetDesPoint(lgPoint(0.0, 0.0, 0.0));
	tlgPointLight.m_lgKc = 0.3;
	tlgPointLight.m_lgKd = 0.02;
	tlgPointLight.m_lgKq = 0.01;
	tlgPointLight.m_lgPos.lgSetX(0.0);
	tlgPointLight.m_lgPos.lgSetY(0.0);
	tlgPointLight.m_lgPos.lgSetZ(-4.0);
	tlgPointLight.m_lgSpotPf = 5.0;

	tlgSpotLight.m_lgI.lgSetRGB(0.0, 0.0, 0.0);
	tlgSpotLight.m_lgDirection.lgSetOrgPoint(lgPoint(0.0, 0.0, -1.0));
	tlgSpotLight.m_lgDirection.lgSetDesPoint(lgPoint(0.0, 0.0, 0.0));
	tlgSpotLight.m_lgKc = 0.3;
	tlgSpotLight.m_lgKd = 0.05;
	tlgSpotLight.m_lgKq = 0.01;
	tlgSpotLight.m_lgPos.lgSetX(-10.0);
	tlgSpotLight.m_lgPos.lgSetY(10.0);
	tlgSpotLight.m_lgPos.lgSetZ(-30.0);
	tlgSpotLight.m_lgSpotInnerAngle = 30.0;
	tlgSpotLight.m_lgSpotOuterAngle = 60.0;
	tlgSpotLight.m_lgSpotPf = 3.0;

	m_lgAmbientLights.lgInsert(tlgAmbientLight);
	m_lgInfiniteLights.lgInsert(tlgInfiniteLight);
	m_lgPointLights.lgInsert(tlgPointLight);
	m_lgSpotLights.lgInsert(tlgSpotLight);
}

lgLight::~lgLight()
{
	m_lgAmbientLights.lgDeleteAll();
	m_lgInfiniteLights.lgDeleteAll();
	m_lgPointLights.lgDeleteAll();
	m_lgSpotLights.lgDeleteAll();
}

void lgLight::lgRenderAmbientLight(const lgColor& tlgSrcRGB, lgColor& tlgTarRGB)
{
	lgLinkPoint<lgAmbientLight>* x = m_lgAmbientLights.lgGetLinkHead();
	lgColor tRGB;
	while (x)
	{
		tRGB = tRGB + tlgSrcRGB * x->m_lgData.m_lgI;
		x = x->m_NextlgLink;
	}
	tlgTarRGB = tRGB;
}

void lgLight::lgRenderInfiniteLight(const lgColor& tlgSrcRGB, const lgFace& tlgFace, lgColor& tlgTarRGB)
{
	lgLinkPoint<lgInfiniteLight>* x = m_lgInfiniteLights.lgGetLinkHead();
	lgColor tRGB;
	lgVector tNormal;
	while (x)
	{
		tNormal = tlgFace.lgGetNormal();
		tNormal.lgNormalize();
		double dp = tNormal.lgDotMultiply(x->m_lgData.m_lgDirection);
		if (dp > 0)
		{
			x = x->m_NextlgLink;
			continue;
		}
		tRGB = tRGB + tlgSrcRGB * x->m_lgData.m_lgI * (-dp);
		x = x->m_NextlgLink;
	}

	tlgTarRGB = tRGB;
}

void lgLight::lgRenderPointLight(const lgColor& tlgSrcRGB, const lgFace& tlgFace, lgColor& tlgTarRGB)
{
	lgLinkPoint<lgPointLight>* x = m_lgPointLights.lgGetLinkHead();
	lgColor tRGB;
	lgVector faceNormal, l;
	lgPoint facePoint;
	double dist = 0.0, dp = 0.0, attern = 0.0;
	while (x)
	{
		facePoint = tlgFace.lgGetPoint();
		faceNormal = tlgFace.lgGetNormal();
		faceNormal.lgNormalize();
		l.lgSetOrgPoint(facePoint);
		l.lgSetDesPoint(x->m_lgData.m_lgPos);
		dist = l.lgGetAbsoluteValue();
		l.lgNormalize();
		dp = faceNormal.lgDotMultiply(l);
		if (dp > 0)
		{
			x = x->m_NextlgLink;
			continue;
		}
		attern = x->m_lgData.m_lgKc + x->m_lgData.m_lgKd * dist + x->m_lgData.m_lgKq * dist * dist;
		tRGB = tRGB + tlgSrcRGB * x->m_lgData.m_lgI * dp * -1 / (attern);
		x = x->m_NextlgLink;
	}
	tlgTarRGB = tRGB;
}

void lgLight::lgRenderSimpleSpotLight(const lgColor& tlgSrcRGB, const lgFace& tlgFace, lgColor& tlgTarRGB)
	{
		lgLinkPoint<lgSpotLight>* x = m_lgSpotLights.lgGetLinkHead();
		lgColor tRGB;
		lgVector faceNormal, l;
		lgPoint facePoint;
		double dist = 0.0, dp = 0.0, attern = 0.0;
		while (x)
		{
			lgPoint facePoint = tlgFace.lgGetPoint();
			lgVector faceNormal = tlgFace.lgGetNormal();
			faceNormal.lgNormalize();
			dp = faceNormal.lgDotMultiply(x->m_lgData.m_lgDirection);
			l.lgSetOrgPoint(facePoint);
			l.lgSetDesPoint(x->m_lgData.m_lgPos);
			dist = l.lgGetAbsoluteValue();
			if (dp > 0)
			{
				x = x->m_NextlgLink;
				continue;
			}
			attern = x->m_lgData.m_lgKc + x->m_lgData.m_lgKd * dist + x->m_lgData.m_lgKq * dist * dist;
			tRGB = tRGB + tlgSrcRGB * x->m_lgData.m_lgI * dp / attern;
			x = x->m_NextlgLink;
		}
		tlgTarRGB = tRGB;
}

void lgLight::lgRenderSpotLight(const lgColor& tlgSrcRGB, const lgFace& tlgFace, lgColor& tlgTarRGB)
{
	lgLinkPoint<lgSpotLight>* x = m_lgSpotLights.lgGetLinkHead();
	lgColor tRGB;
	lgVector faceNormal, s;
	lgPoint facePoint;
	double dist = 0.0, dp = 0.0, attern = 0.0, dpsl = 0.0;
	while (x)
	{
		facePoint = tlgFace.lgGetPoint();
		faceNormal = tlgFace.lgGetNormal();
		faceNormal.lgNormalize();
		dp = faceNormal.lgDotMultiply(x->m_lgData.m_lgDirection);
		if (dp > 0)
		{
			x = x->m_NextlgLink;
			continue;
		}
		dp = -dp;
		s.lgSetOrgPoint(facePoint);
		s.lgSetDesPoint(x->m_lgData.m_lgPos);
		dist = s.lgGetAbsoluteValue();
		s.lgNormalize();
		dpsl = s.lgDotMultiply(x->m_lgData.m_lgDirection);
		if (dpsl > 0)
		{
			x = x->m_NextlgLink;
			continue;
		}
		dpsl = -dpsl;
		attern = x->m_lgData.m_lgKc + x->m_lgData.m_lgKd * dist + x->m_lgData.m_lgKq * dist * dist;
		tRGB = tRGB + tlgSrcRGB * x->m_lgData.m_lgI * dp * pow(dpsl, x->m_lgData.m_lgSpotPf) / attern;
		x = x->m_NextlgLink;
	}
	tlgTarRGB = tRGB;
}
void lgLight::lgRenderAllLight(const lgColor& tlgBaseColor, const lgFace& tlgFace, lgColor& tlgFinalColor)
{
	lgColor color[4];
	lgRenderAmbientLight(tlgBaseColor / 256.0, color[0]);
	lgRenderInfiniteLight(tlgBaseColor / 256.0, tlgFace, color[1]);
	lgRenderPointLight(tlgBaseColor / 256.0, tlgFace, color[2]);
	lgRenderSpotLight(tlgBaseColor / 256.0, tlgFace, color[3]);
	tlgFinalColor = color[0] + color[1] + color[2] + color[3];
}

void lgLight::lgRenderInfiniteLightByGouraud(const lgColor& tlgSrcRGB, const lgPoint& tlgPoint, lgColor& tlgTarRGB)
{
	lgLinkPoint<lgInfiniteLight>* x = m_lgInfiniteLights.lgGetLinkHead();
	lgColor tRGB;
	lgVector tNormal;
	while (x)
	{
		tNormal = tlgPoint.lgGetNormal();
		tNormal.lgNormalize();
		double dp = tNormal.lgDotMultiply(x->m_lgData.m_lgDirection);
		if (dp > 0)
		{
			x = x->m_NextlgLink;
			continue;
		}
		tRGB = tRGB + tlgSrcRGB * x->m_lgData.m_lgI * (-dp);
		x = x->m_NextlgLink;
	}

	tlgTarRGB = tRGB;
}

void lgLight::lgRenderPointLightByGouraud(const lgColor& tlgSrcRGB, const lgPoint& tlgPoint, lgColor& tlgTarRGB)
{
	lgLinkPoint<lgPointLight>* x = m_lgPointLights.lgGetLinkHead();
	lgColor tRGB;
	lgVector Normal, l;
	lgPoint Point;
	double dist = 0.0, dp = 0.0, attern = 0.0;
	while (x)
	{
		Point = tlgPoint;
		Normal = tlgPoint.lgGetNormal();
		Normal.lgNormalize();
		l.lgSetOrgPoint(Point);
		l.lgSetDesPoint(x->m_lgData.m_lgPos);
		dist = l.lgGetAbsoluteValue();
		l.lgNormalize();
		dp = Normal.lgDotMultiply(l);
		if (dp < 0)
		{
			x = x->m_NextlgLink;
			continue;
		}
		attern = x->m_lgData.m_lgKc + x->m_lgData.m_lgKd * dist + x->m_lgData.m_lgKq * dist * dist;
		tRGB = tRGB + tlgSrcRGB * x->m_lgData.m_lgI * dp / (attern);
		x = x->m_NextlgLink;
	}
	tlgTarRGB = tRGB;
}

void lgLight::lgRenderSimpleSpotLightByGouraud(const lgColor& tlgSrcRGB, const lgPoint& tlgPoint, lgColor& tlgTarRGB)
{
	lgLinkPoint<lgSpotLight>* x = m_lgSpotLights.lgGetLinkHead();
	lgColor tRGB;
	lgVector Normal, l;
	lgPoint Point;
	double dist = 0.0, dp = 0.0, attern = 0.0;
	while (x)
	{
		Point = tlgPoint;
		Normal = tlgPoint.lgGetNormal();
		Normal.lgNormalize();
		dp = Normal.lgDotMultiply(x->m_lgData.m_lgDirection);
		l.lgSetOrgPoint(Point);
		l.lgSetDesPoint(x->m_lgData.m_lgPos);
		dist = l.lgGetAbsoluteValue();
		if (dp > 0)
		{
			x = x->m_NextlgLink;
			continue;
		}
		attern = x->m_lgData.m_lgKc + x->m_lgData.m_lgKd * dist + x->m_lgData.m_lgKq * dist * dist;
		tRGB = tRGB + tlgSrcRGB * x->m_lgData.m_lgI * dp / attern;
		x = x->m_NextlgLink;
	}
	tlgTarRGB = tRGB;
}

void lgLight::lgRenderSpotLightByGouraud(const lgColor& tlgSrcRGB, const lgPoint& tlgPoint, lgColor& tlgTarRGB)
{
	lgLinkPoint<lgSpotLight>* x = m_lgSpotLights.lgGetLinkHead();
	lgColor tRGB;
	lgVector Normal, s;
	lgPoint Point;
	double dist = 0.0, dp = 0.0, attern = 0.0, dpsl = 0.0;
	while (x)
	{
		Point = tlgPoint;
		Normal = tlgPoint.lgGetNormal();
		Normal.lgNormalize();
		dp = Normal.lgDotMultiply(x->m_lgData.m_lgDirection);
		if (dp > 0)
		{
			x = x->m_NextlgLink;
			continue;
		}
		dp = -dp;
		s.lgSetOrgPoint(Point);
		s.lgSetDesPoint(x->m_lgData.m_lgPos);
		dist = s.lgGetAbsoluteValue();
		s.lgNormalize();
		dpsl = s.lgDotMultiply(x->m_lgData.m_lgDirection);
		if (dpsl > 0)
		{
			x = x->m_NextlgLink;
			continue;
		}
		dpsl = -dpsl;
		attern = x->m_lgData.m_lgKc + x->m_lgData.m_lgKd * dist + x->m_lgData.m_lgKq * dist * dist;
		tRGB = tRGB + tlgSrcRGB * x->m_lgData.m_lgI * dp * pow(dpsl, x->m_lgData.m_lgSpotPf) / attern;
		x = x->m_NextlgLink;
	}
	tlgTarRGB = tRGB;
}

void lgLight::lgRenderAllLightByGouraud(const lgColor& tlgBaseColor, const lgPoint& tlgPoint, lgColor& tlgFinalColor)
{
	lgColor color[4];
	lgRenderAmbientLight(tlgBaseColor / 256, color[0]);
	lgRenderInfiniteLightByGouraud(tlgBaseColor / 256, tlgPoint, color[1]);
	lgRenderPointLightByGouraud(tlgBaseColor / 256, tlgPoint, color[2]);
	lgRenderSpotLightByGouraud(tlgBaseColor / 256, tlgPoint, color[3]);
	tlgFinalColor = color[0] + color[1] + color[2] + color[3];
}