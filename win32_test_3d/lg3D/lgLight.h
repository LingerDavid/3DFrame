#ifndef _FILE_LGLIGHT_H
#define _FILE_LGLIGHT_H

#include "lgLink.h"
#include "lgColor.h"
#include "lgVector.h"

class lgLight
{
	//This class just detail the color int pixel level
	//given a primitive pixel color and return a lightend color
	//based on the soft ware,this process is very time spending
	//so now the first version just implements simplyfied light model
	// and the light source model.
	enum
	{
		PURPLE,
		BLUE,
		GREEN,
		YELLOW,
		ORANGE,
		RED
	};
	class lgLenda
	{
	public:
		//nm
		double m_lgMinLenda;
		double m_lgMaxLenda;

		lgLenda();
		~lgLenda();

		virtual const lgLenda operator =(const lgLenda&);
	};

private:
	typedef struct _lgAmbientLight
	{
		lgColor m_lgI;
	}lgAmbientLight, *plgAmbientLight;
	typedef struct _lgInfiniteLight
	{
		lgVector m_lgDirection;
		lgColor m_lgI;
	}lgInfiniteLight, *plgInfiniteLight;
	typedef struct _lgPointLight
	{
		lgPoint m_lgPos;
		lgVector m_lgDirection;
		lgColor m_lgI;
		double m_lgKc;
		double m_lgKd;
		double m_lgKq;
		double m_lgSpotPf;
	}lgPointLight, *plgPointLight;
	typedef struct _lgSpotLight
	{
		lgPoint m_lgPos;
		lgVector m_lgDirection;
		lgColor m_lgI;
		double m_lgKc;
		double m_lgKd;
		double m_lgKq;
		double m_lgSpotInnerAngle;
		double m_lgSpotOuterAngle;
		double m_lgSpotPf;
	}lgSpotLight, *plgSpotLight;
	//id
	int m_lgID;
	//nm
	lgLenda m_lgLenda[6];
	//m/s
	double m_lgLightSpeed;
	//state
	int m_lgState;
	/*light model*/
	//Ambient light
	//Csa*Ia
	//Scattered light
	//Rs * (Is *(n.*l)).*
	//Specular reflection light/Phong illumination model
	//Rs * Is * (r.*v)^sp,when angle is bigger than 90,the light cann't emit to the face
	//Emmitted light
	//Rse
	/*lgiht source model*/
	//fixed direction light source
	//1.infinite far
	//2.parallel
	//3.no decrease by dstance
	//4.intensity and color
	//IOd * Cld
	//point light source
	//direction
	//1.decrease by distance
	//IOp * Clp / (kc + kl * d + kq * d^2)
	//Projector lamp light source
	//Inner cone angle
	//External cone angle
	//Direction
	//Position
	//lgVector m_lgDirection;
	//lgColor m_lgIDiffuse;

	lgLink<lgAmbientLight> m_lgAmbientLights;
	lgLink<lgInfiniteLight> m_lgInfiniteLights;
	lgLink<lgPointLight> m_lgPointLights;
	lgLink<lgSpotLight> m_lgSpotLights;
public:
	lgLight();
	~lgLight();

	virtual void lgRenderAmbientLight(const lgColor&, lgColor&);
	virtual void lgRenderInfiniteLight(const lgColor&, const lgFace&, lgColor&);
	virtual void lgRenderPointLight(const lgColor&, const lgFace&, lgColor&);
	virtual void lgRenderSimpleSpotLight(const lgColor&, const lgFace&, lgColor&);
	virtual void lgRenderSpotLight(const lgColor&, const lgFace&, lgColor&);
	virtual void lgRenderAllLight(const lgColor&, const lgFace&, lgColor&);

	virtual void lgRenderInfiniteLightByGouraud(const lgColor&, const lgPoint&, lgColor&);
	virtual void lgRenderPointLightByGouraud(const lgColor&, const lgPoint&, lgColor&);
	virtual void lgRenderSimpleSpotLightByGouraud(const lgColor&, const lgPoint&, lgColor&);
	virtual void lgRenderSpotLightByGouraud(const lgColor&, const lgPoint&, lgColor&);
	virtual void lgRenderAllLightByGouraud(const lgColor&, const lgPoint&, lgColor&);

};
#endif