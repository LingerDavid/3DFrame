#ifndef _FILE_LGCONTROL_H
#define _FILE_LGCONTROL_H

class lgPoint;
class lgLine;
class lgVector;
class lgFace;
class lgTriangle;
class lgMatrix;


class lgControl
{
public:
	virtual void lgRotate(double, const lgVector&, const lgPoint&, lgPoint&);
	virtual void lgRotate(const lgMatrix&, const lgPoint&, lgPoint&);
	virtual void lgRotateByX(double, const lgPoint&, lgPoint&);
	virtual void lgRotateByY(double, const lgPoint&, lgPoint&);
	virtual void lgRotateByZ(double, const lgPoint&, lgPoint&);
	virtual void lgMove(const lgVector&, const lgPoint&, lgPoint&);
	virtual void lgMove(const lgMatrix&, const lgPoint&, lgPoint&);
	virtual void lgMoveByX(double, const lgPoint&, lgPoint&);
	virtual void lgMoveByY(double, const lgPoint&, lgPoint&);
	virtual void lgMoveByZ(double, const lgPoint&, lgPoint&);
	virtual void lgZoom(const lgVector&, const lgPoint&, lgPoint&);
	virtual void lgZoom(const lgMatrix&, const lgPoint&, lgPoint&);
	virtual void lgZoomByX(double, const lgPoint&, lgPoint&);
	virtual void lgZoomByY(double, const lgPoint&, lgPoint&);
	virtual void lgZoomByZ(double, const lgPoint&, lgPoint&);
	
	virtual void lgRotate(double, const lgVector&, const lgVector&, lgVector&);
	virtual void lgRotate(const lgMatrix&, const lgVector&, lgVector&);
	virtual void lgRotateByX(double, const lgVector&, lgVector&);
	virtual void lgRotateByY(double, const lgVector&, lgVector&);
	virtual void lgRotateByZ(double, const lgVector&, lgVector&);
	virtual void lgMove(const lgVector&, const lgVector&, lgVector&);
	virtual void lgMove(const lgMatrix&, const lgVector&, lgVector&);
	virtual void lgMoveByX(double, const lgVector&, lgVector&);
	virtual void lgMoveByY(double, const lgVector&, lgVector&);
	virtual void lgMoveByZ(double, const lgVector&, lgVector&);
	virtual void lgZoom(const lgVector&, const lgVector&, lgVector&);
	virtual void lgZoom(const lgMatrix&, const lgVector&, lgVector&);
	virtual void lgZoomByX(double, const lgVector&, lgVector&);
	virtual void lgZoomByY(double, const lgVector&, lgVector&);
	virtual void lgZoomByZ(double, const lgVector&, lgVector&);
	
	virtual void lgRotate(double, const lgVector&, const lgTriangle&, lgTriangle&);
	virtual void lgRotate(const lgMatrix&, const lgTriangle&, lgTriangle&);
	virtual void lgRotateByX(double, const lgTriangle&, lgTriangle&);
	virtual void lgRotateByY(double, const lgTriangle&, lgTriangle&);
	virtual void lgRotateByZ(double, const lgTriangle&, lgTriangle&);
	virtual void lgMove(const lgVector&, const lgTriangle&, lgTriangle&);
	virtual void lgMove(const lgMatrix&, const lgTriangle&, lgTriangle&);
	virtual void lgMoveByX(double, const lgTriangle&, lgTriangle&);
	virtual void lgMoveByY(double, const lgTriangle&, lgTriangle&);
	virtual void lgMoveByZ(double, const lgTriangle&, lgTriangle&);
	virtual void lgZoom(const lgVector&, const lgTriangle&, lgTriangle&);
	virtual void lgZoom(const lgMatrix&, const lgTriangle&, lgTriangle&);
	virtual void lgZoomByX(double, const lgTriangle&, lgTriangle&);
	virtual void lgZoomByY(double, const lgTriangle&, lgTriangle&);
	virtual void lgZoomByZ(double, const lgTriangle&, lgTriangle&);

	virtual void lgTransfer(const lgMatrix&, const lgPoint&, lgPoint&);
	virtual void lgTransfer(const lgMatrix&, const lgVector&, lgVector&);
	virtual void lgTransfer(const lgMatrix&, const lgTriangle&, lgTriangle&);
};
#endif