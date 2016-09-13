
/* MapTools.h
 *
 *  Created on: Nov 18, 2014
 *      Author: Logan
 */
#ifndef MAPTOOLS_H_
#define MAPTOOLS_H_

#define _USE_MATH_DEFINES
#include "PointLatLng.h"
#include "PointLatLngAlt.h"
#include <vector>
#include <cmath>
using namespace std;

class MapTools
{
public:

	static const double mPI  =3.141592653589793238463;
	MapTools();
	virtual ~MapTools();

	PointLatLng* OffsetInMeters(PointLatLng *InitialPosition, double OffsetE, double OffsetN);
	PointLatLngAlt* OffsetInMeters(PointLatLngAlt *InitialPosition, double OffsetE, double OffsetN, double OffsetZ);

	double GetDistance(PointLatLng *InitialPosition, PointLatLng *FinalPosition);
	double GetDistance(PointLatLngAlt *InitialPosition, PointLatLngAlt *FinalPosition);

	double GetDistanceMeters(PointLatLng *InitialPosition, PointLatLng *FinalPosition);
	double GetDistanceMeters(PointLatLngAlt *InitialPosition, PointLatLngAlt *FinalPosition);

	double GetSlopeFromNord(PointLatLng *InitialPosition, PointLatLng *FinalPosition);

	double GetAngleMeassuredFromNord(PointLatLng *InitialPosition, PointLatLng *FinalPosition);
	double GetAngleMeassuredFromNord(PointLatLngAlt *InitialPosition, PointLatLngAlt *FinalPosition);
	double GetSlope(PointLatLng *InitialPosition, PointLatLng *FinalPosition);

	//double angleBetweenVectors(PointLatLng initialPointV1, PointLatLng finalPointV1, PointLatLng initialPointV2, PointLatLng finalPointV2, GMapControl *gmapControl);


	bool IsInside(PointLatLng Point, std::vector<PointLatLng> &PontosPolig);

	bool IsInsideCircle(PointLatLng *Point, PointLatLng *Center, double Radius);
	bool IsInsideCircle(PointLatLngAlt *Point, PointLatLngAlt *Center, double Radius);

	vector<float> Geodetic2ENU(PointLatLng *Point, PointLatLng *InitialPoint);
	vector<float> Geodetic2ENU(PointLatLngAlt *Point, PointLatLngAlt *InitialPoint);

private:
	vector<float> Geodetic2ECEF(PointLatLng Point);

};

#endif /* MAPTOOLS_H_ */


