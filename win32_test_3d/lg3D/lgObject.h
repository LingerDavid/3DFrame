//lgObject.h

#ifndef _FILE_LGOBJECT_H
#define _FILE_LGOBJECT_H

#include "lgLink.h"
#include "lgLight.h"
#include "lgTriangle.h"
#include "lgQuaternion.h"

#define STATE_VISIBLE 0
#define STATE_INVISIBLE 1

#ifndef AXIS_LENGTH
#define AXIS_LENGTH 3
#endif

class lgBoundingRectBox
{
public:
	double lgXL;
	double lgXR;
	double lgYT;
	double lgYB;
	double lgZY;
	double lgZH;

	virtual const lgPoint lgGetNearestPoint(const lgPoint&);
};

class lgBoundingSphereBox
{
public:
	double lgRadius;
};

class lgObject
{
	lgDisplay m_lgDisplay;
private:
	unsigned int m_lgID;
	lgPoint m_lgWorldPoint;
	char* m_lgObjectName;
	int m_lgState;
	int m_lgAttr;
	int m_lgCurFame;
	int m_lgFrameCount;
	lgEluer m_lgDirection;
	lgLink<lgLink<lgTriangle>> m_lgFaces;
	lgLink<lgTriangle> m_lgRenderFaces;
	lgBoundingRectBox m_lgBoundingRectBox;
	lgBoundingSphereBox m_lgBoundingSphereBox;
	lgControl m_lgControl;
	lgVector m_lgXVector;
	lgVector m_lgYVector;
	lgVector m_lgZVector;
public:
	lgObject();
	lgObject(const lgObject&);
	~lgObject();
	virtual void lgInit();
	virtual const lgBoundingRectBox& lgGetBoundingRectBox();
	virtual const lgBoundingSphereBox& lgGetBoundingSphereBox();
	virtual const lgPoint lgGetWorldPoint() const;
	virtual void lgSetWorldPoint(const lgPoint&);
	virtual bool lgIsVisible();
	virtual void lgInsertTriangle(int, double, double, double, double, double, double, double, double, double);
	virtual void lgCreateFrames(int);
	virtual void lgCalVertexNormals(lgLink<lgTriangle>&);
	virtual void lgCalPrimitiveVertexNormal();

	virtual void lgMove(const lgVector&);
	virtual void lgRotate(double, const lgVector&);
	virtual void lgZoom(const lgVector&);

	//!
	virtual void lgCreateStandardCube(double);
	//!
	virtual void lgInitAllFacesTexture(const lgTexture*);
	//!
	virtual void lgCreateTerrian(int, int, const lgTexture&, int, int);

	virtual void lgRenderPipeLine(const lgCamera&);
	virtual const lgLink<lgTriangle>& lgGetRenderList() const;

	virtual lgLink<lgTriangle>& lgGetFaceLink();

	virtual void lgDraw(void*, lgCamera&, int, int);
	virtual void lgDrawXAxis(void*, lgCamera&);
	virtual void lgDrawYAxis(void*, lgCamera&);
	virtual void lgDrawZAxis(void*, lgCamera&);
	virtual void lgDrawAxises(void*, lgCamera&);
	virtual void lgDrawVertexNormal(void*);
	virtual void lgDrawBoundingBox(void*, lgCamera&);
};

#endif