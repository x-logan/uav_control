 /* 
 * File: MapTools.cpp
 * Autor: Logan
 * Date: 18/11/2014
 *
 */


#include "../Utils/Matrix.h"
#include "MapTools.h"
#include <cmath>

MapTools::MapTools()
{

}

MapTools::~MapTools() {
	// TODO Auto-generated destructor stub
}

PointLatLng* MapTools::OffsetInMeters(PointLatLng *InitialPosition, double OffsetE, double OffsetN)
{
	//offsets in meters

	//Earth’s radius, sphere
	double R = 6378137;
	//Coordinate offsets in radians
	double dLat = OffsetN / R;
	double dLon = OffsetE / (R * cos(M_PI * InitialPosition->getLat() / 180));
	//OffsetPosition, decimal degrees
	double latO = InitialPosition->getLat() + dLat * 180 / M_PI;
	double lonO = InitialPosition->getLng() + dLon * 180 / M_PI;

	return new PointLatLng(latO, lonO);

}

PointLatLngAlt* MapTools::OffsetInMeters(PointLatLngAlt *InitialPosition, double OffsetE, double OffsetN, double OffsetZ )
{
	//offsets in meters

	//Earth’s radius, sphere
	double R = 6378137;
	//Coordinate offsets in radians
	double dLat = OffsetN / R;
	double dLon = OffsetE / (R * cos(M_PI * InitialPosition->Lat() / 180));
	//OffsetPosition, decimal degrees
	double latO = InitialPosition->Lat() + dLat * 180 / M_PI;
	double lonO = InitialPosition->Lng() + dLon * 180 / M_PI;

	double z = InitialPosition->Alt() + OffsetZ;
	return new PointLatLngAlt(latO, lonO, z);

}

double MapTools::GetDistance(PointLatLng *InitialPosition, PointLatLng *FinalPosition)
{
	double R = 6371; // km
	double sphi_1 = InitialPosition->getLat() * mPI / 180;// lat1.toRadians();
	double phi_2 = FinalPosition->getLat() * mPI /180; // lat2.toRadians();
	double delta_phi = (FinalPosition->getLat() - InitialPosition->getLat()) * mPI / 180;
	double delta_lambda = (FinalPosition->getLng() - InitialPosition->getLng())* mPI /180;

	double a = sin(delta_phi / 2) * sin(delta_phi/ 2) + cos(sphi_1) * cos(phi_2) * sin(delta_lambda / 2) * sin(delta_lambda / 2);
	double c = 2 * atan2(sqrt(a), sqrt(1 - a));

	double d = R * c;
	return d;
}

double MapTools::GetDistance(PointLatLngAlt *InitialPosition, PointLatLngAlt *FinalPosition)
{
	return GetDistance(InitialPosition->GetPointLatLng(), FinalPosition->GetPointLatLng());
}

double MapTools::GetDistanceMeters(PointLatLng *InitialPosition, PointLatLng *FinalPosition)
{
	return GetDistance(InitialPosition,FinalPosition)*1000;
}

double MapTools::GetDistanceMeters(PointLatLngAlt *InitialPosition, PointLatLngAlt *FinalPosition)
{
	return GetDistance(InitialPosition,FinalPosition)*1000;
}

double MapTools::GetSlopeFromNord(PointLatLng *InitialPosition, PointLatLng *FinalPosition)
{
	double slope = GetSlope(InitialPosition, FinalPosition);
	slope = M_PI / 2 - slope;
	if (slope > M_PI)
	{
		slope -= 2 * M_PI;
	}
	else if (slope < -M_PI)
	{
		slope += 2 * M_PI;
	}
	return slope;
}

double MapTools::GetAngleMeassuredFromNord(PointLatLngAlt *InitialPosition, PointLatLngAlt *FinalPosition)
{
    return GetAngleMeassuredFromNord(InitialPosition->GetPointLatLng(), FinalPosition->GetPointLatLng());
}

double MapTools::GetAngleMeassuredFromNord(PointLatLng *InitialPosition, PointLatLng *FinalPosition)
{

	size_t size = 2;
	vector<float> point(size);
	point = Geodetic2ENU(FinalPosition, InitialPosition);

	double slope = atan2((point[1]), (point[0]));
	double angle = M_PI / 2 - atan2((point[1]), (point[0]));

	//double slope3 =  Math.Atan2(p2.Y - p1.Y, p2.X - p1.X) + Math.PI/2;

	if (angle > M_PI)
	{
		angle -= 2 * M_PI;
	}
	else if (angle < -M_PI)
	{
		angle += 2 * M_PI;
	}
	return angle;


}

double MapTools::GetSlope(PointLatLng *InitialPosition, PointLatLng *FinalPosition)
{
	// GMapControl control = new GMapControl();
	//GPoint p1 = control.FromLatLngToLocal(InitialPosition);
	//GPoint p2 = control.FromLatLngToLocal(FinalPosition);

	size_t size = 2;
	vector<float> point(size);
	point = Geodetic2ENU(FinalPosition, InitialPosition);
	double slope1 = M_PI / 2 - atan2((point[1]), (point[0]));
	double slope2 = -M_PI / 2 - atan2((InitialPosition->getLat() - FinalPosition->getLat()), (InitialPosition->getLng() - FinalPosition->getLng()));
	//double slope3 =  Math.Atan2(p2.Y - p1.Y, p2.X - p1.X) + Math.PI/2;

	if (slope1 > M_PI)
	{
		slope1 -= 2 * M_PI;
	}
	else if (slope1 < -M_PI)
	{
		slope1 += 2 * M_PI;
	}
	return slope1; // -Math.PI / 2 - Math.Atan2((InitialPosition.Lat - FinalPosition.Lat), (InitialPosition.Lng - FinalPosition.Lng));

	//return Math.PI / 2 - Math.Atan2((point.Y) ,(point.X));
}

/*double MapTools::angleBetweenVectors(PointLatLng initialPointV1, PointLatLng finalPointV1, PointLatLng initialPointV2, PointLatLng finalPointV2, GMapControl *gmapControl)
{
	double angle = 0;


	return angle;
}*/

bool MapTools::IsInside(PointLatLng Point, std::vector<PointLatLng> &PontosPolig)
{ //                             X               y
	int sides = PontosPolig.size();
	int j = sides - 1;
	bool pointStatus = false;

	for (int i = 0; i < sides; i++)
	{
		if ((PontosPolig[i].getLng() < Point.getLng() && PontosPolig[j].getLng() >= Point.getLng()) || (PontosPolig[j].getLng() < Point.getLng() && PontosPolig[i].getLng() >= Point.getLng()))
		{
			if (PontosPolig[i].getLat() + (Point.getLng() - PontosPolig[i].getLng()) / (PontosPolig[j].getLng() - PontosPolig[i].getLng()) * (PontosPolig[j].getLat() - PontosPolig[i].getLat()) < Point.getLat())
			{
				pointStatus = !pointStatus;
			}
		}
		j = i;
	}
	return pointStatus;
}

bool MapTools::IsInsideCircle(PointLatLng *Point, PointLatLng *Center, double Radius)
{

	double distance = GetDistanceMeters(Center, Point);
	distance *= distance;
	double radiusSquared = Radius * Radius;
	return distance <= radiusSquared;
}

bool MapTools::IsInsideCircle(PointLatLngAlt *Point, PointLatLngAlt *Center, double Radius)
{
	return IsInsideCircle(Point->GetPointLatLng(), Center->GetPointLatLng(), Radius);
}

vector<float> MapTools::Geodetic2ENU(PointLatLng *Point, PointLatLng *InitialPoint)
{
	size_t size = 2;
	double a = 6378137; // Semi-major axis
	double ex = 0.08181919; // Excentricity
	double h = 2241; // Height of Mexico City
	double N_phi = 0;
	double x_ecef = 0;
	double y_ecef = 0;
	double z_ecef = 0;

	double a_h = 48.032537299811120;
	double a_v = 57.210092131377180;

	double phi_r = InitialPoint->getLat(); //Convert.ToDouble(txtInitX.Text);
	double lambda_r = InitialPoint->getLng(); //Convert.ToDouble(txtInitY.Text);

	double N_phi_r = a / sqrt(1 - pow(ex, 2) * pow(sin(phi_r), 2));

	double x_ecef_r = (N_phi_r / a_v + h) * cos(phi_r) * cos(lambda_r);
	double y_ecef_r = (N_phi_r / a_v + h) * cos(phi_r) * sin(lambda_r);
	double z_ecef_r = ((N_phi_r / a_v) * (1 - pow(ex, 2)) + h) * sin(phi_r);

	/*double e2 = Math.Pow(ex, 2);
	double sinx = Math.Sin(lat);
	double sinx2 = Math.Pow(sinx, 2);
	double e2sinx = e2 * sinx2;
	double sqrte2sinx = Math.Sqrt(1 - e2sinx);
	double N_phi1 = a / (sqrte2sinx);
	*/
	N_phi = a / (sqrt(1 - pow(ex, 2) * pow(sin(Point->getLat()), 2)));

	double cosx = cos(Point->getLat());
	double cosy = cos(Point->getLng());

	x_ecef = (N_phi / a_v + h) * cos(Point->getLat()) * cos(Point->getLng());
	y_ecef = (N_phi / a_v + h) * cos(Point->getLat()) * sin(Point->getLng());
	z_ecef = (N_phi / a_v * (1 - pow(ex, 2)) + h) * sin(Point->getLat());

	Matrix *R = new Matrix(3, 3);
	(*R)(0,0) = -sin(lambda_r);
	(*R)(0,1) = cos(lambda_r);
	(*R)(0,2) = 0;

	(*R)(1,0) = -sin(phi_r) * cos(lambda_r);
	(*R)(1,1) = -sin(phi_r) * sin(lambda_r);
	(*R)(1,2) = cos(phi_r);

	(*R)(2,0) = cos(phi_r) * cos(lambda_r);
	(*R)(2,1) = cos(phi_r) * sin(lambda_r);
	(*R)(2,2) = sin(phi_r);

	Matrix *P = new Matrix(3, 1);
	(*P)(0,0) = x_ecef - x_ecef_r;
	(*P)(1,0) = y_ecef - y_ecef_r;
	(*P)(2,0) = z_ecef - z_ecef_r;

	Matrix *enu = new Matrix(3, 1);

	enu = R->Multiply(P);

	//PointF _p = PointF(static_cast<float>(enu[0][0]), static_cast<float>(enu[1][0]));
	vector<float> _p(size);
	_p[0]=(*enu)(0,0);
	_p[1]=(*enu)(1,0);


	double InitialPointLat = InitialPoint->getLat() * M_PI / 180;
	double InitialPointLng = InitialPoint->getLng() * M_PI / 180;
	double PointLat = Point->getLat() * M_PI / 180;
	double PointLng = Point->getLng() * M_PI / 180;

	// Matab code
	double e2 = pow(ex,2); //self.Eccentricity^2;

	double s1 = sin(InitialPointLat); //sinfun(phi1); phi1 lat0
	double c1 = cos(InitialPointLat); // cosfun(phi1);

	double s2 = sin(PointLat); // sinfun(phi2);
	double c2 = cos(PointLat); //cosfun(phi2);

	double p1 = c1 * cos(InitialPointLng); //c1 .* cosfun(lambda1);
	double p2 = c2 * cos(PointLng); //c2 .* cosfun(lambda2);

	double q1 = c1 * sin(InitialPointLng); // c1 .* sinfun(lambda1);
	double q2 = c2 * sin(PointLng); //c2 .* sinfun(lambda2);

	double w1 = 1 / sqrt(1 - e2 * pow(s1,2)); // 1 ./ sqrt(1 - e2 * s1.^2);
	double w2 = 1 / sqrt(1 - e2 * pow(s2,2)); // 1 / sqrt(1 - e2 * s2.^2);

	double deltaX = a * (p2 * w2 - p1 * w1) + (h * p2 - h * p1); //self.a * (p2 .* w2 - p1 .* w1) + (h2 .* p2 - h1 .* p1);
	double deltaY = a * (q2 * w2 - q1 * w1) + (h * q2 - h * q1); //self.a * (q2 .* w2 - q1 .* w1) + (h2 .* q2 - h1 .* q1);
	double deltaZ = (1 - e2) * a * (s2 * w2 - s1 * w1) + (h * s2 - h * s1); //(1 - e2) * self.a * (s2 .* w2 - s1 .* w1) + (h2 .* s2 - h1 .* s1);

	double cosPhi = cos(InitialPointLat); // cosfun(lat0); lat0 initialpoint.lat
	double sinPhi = sin(InitialPointLat); //sinfun(lat0);
	double cosLambda = cos(InitialPointLng); //cosfun(lon0);
	double sinLambda = sin(InitialPointLng); //sinfun(lon0);

	double t = cosLambda * deltaX + sinLambda * deltaY; // cosLambda .* u + sinLambda .* v; u = deltaX
	double uEast = -sinLambda * deltaX + cosLambda * deltaY; //-sinLambda .* u + cosLambda .* v;

	double wUp = cosPhi * t + sinPhi * deltaZ; //cosPhi .* t + sinPhi .* w;
	double vNorth = -sinPhi * t + cosPhi * deltaZ; // -sinPhi .* t + cosPhi .* w;

	//PointF _p = PointF(static_cast<float>(enu[0][0]), static_cast<float>(enu[1][0]));

	vector<float> p(size);
	p[0] = uEast;
	p[1] = vNorth;

	return p;
}

vector<float> MapTools::Geodetic2ENU(PointLatLngAlt *Point, PointLatLngAlt *InitialPoint)
{
	size_t size = 3;
	double a = 6378137;     // Semi-major axis
	double ex = 0.08181919; // Excentricity
	double h = 2241;        // Height of Mexico City
	double N_phi = 0;
	double x_ecef = 0;
	double y_ecef = 0;
	double z_ecef = 0;

	double a_h = 48.032537299811120;
	double a_v = 57.210092131377180;

	double phi_r = InitialPoint->Lat();//Convert.ToDouble(txtInitX.Text);
	double lambda_r = InitialPoint->Lng();//Convert.ToDouble(txtInitY.Text);

	double N_phi_r = a / sqrt(1 - pow(ex, 2) * pow(sin(phi_r), 2));

	double x_ecef_r = (N_phi_r / a_v + h) * cos(phi_r) * cos(lambda_r);
	double y_ecef_r = (N_phi_r / a_v + h) * cos(phi_r) * sin(lambda_r);
	double z_ecef_r = ((N_phi_r / a_v) * (1 - pow(ex, 2)) + h) * sin(phi_r);

	/*double e2 = Math.Pow(ex, 2);
	double sinx = Math.Sin(lat);
	double sinx2 = Math.Pow(sinx, 2);
	double e2sinx = e2 * sinx2;
	double sqrte2sinx = Math.Sqrt(1 - e2sinx);
	double N_phi1 = a / (sqrte2sinx);
	*/
	N_phi = a / (sqrt(1 - pow(ex, 2) * pow(sin(Point->Lat()), 2)));

	double cosx = cos(Point->Lat());
	double cosy = cos(Point->Lng());

	x_ecef = (N_phi / a_v + h) * cos(Point->Lat()) * cos(Point->Lng());
	y_ecef = (N_phi / a_v + h) * cos(Point->Lat()) * sin(Point->Lng());
	z_ecef = (N_phi / a_v * (1 - pow(ex, 2)) + h) * sin(Point->Lat());

	Matrix *R = new Matrix(3, 3);
	(*R)(0, 1) = cos(lambda_r);
	(*R)(0, 2) = 0;

	(*R)(1, 0) = -sin(phi_r) * cos(lambda_r);
	(*R)(1, 1) = -sin(phi_r) * sin(lambda_r);
	(*R)(1, 2) = cos(phi_r);

	(*R)(2, 0) = cos(phi_r) * cos(lambda_r);
	(*R)(2, 1) = cos(phi_r) * sin(lambda_r);
	(*R)(2, 2) = sin(phi_r);

	Matrix *P = new Matrix(3, 1);
	(*P)(0, 0) = x_ecef - x_ecef_r;
	(*P)(1, 0) = y_ecef - y_ecef_r;
	(*P)(2, 0) = z_ecef - z_ecef_r;

	Matrix *enu = new Matrix(3, 1);

	enu = R->Multiply(P);

	//PointF _p = new PointF((float)enu[0, 0], (float)enu[1, 0]);
	vector<float> _p(size);
	_p[0]=(*enu)(0,0);
	_p[1]=(*enu)(1,0);


	double InitialPointLat = InitialPoint->Lat() * mPI / 180;
	double InitialPointLng = InitialPoint->Lng() * mPI / 180;
	double PointLat = Point->Lat() * mPI / 180;
	double PointLng = Point->Lng() * mPI / 180;

	// Matab code
	double e2 = pow(ex, 2); //self.Eccentricity^2;

	double s1 = sin(InitialPointLat); //sinfun(phi1); phi1 lat0
	double c1 = cos(InitialPointLat); // cosfun(phi1);

	double s2 = sin(PointLat); // sinfun(phi2);
	double c2 = cos(PointLat); //cosfun(phi2);

	double p1 = c1 * cos(InitialPointLng); //c1 .* cosfun(lambda1);
	double p2 = c2 * cos(PointLng); //c2 .* cosfun(lambda2);

	double q1 = c1 * sin(InitialPointLng); // c1 .* sinfun(lambda1);
	double q2 = c2 * sin(PointLng); //c2 .* sinfun(lambda2);

	double w1 = 1 / sqrt(1 - e2 * pow(s1, 2)); // 1 ./ sqrt(1 - e2 * s1.^2);
	double w2 = 1 / sqrt(1 - e2 * pow(s2, 2)); // 1 / sqrt(1 - e2 * s2.^2);

	double deltaX = a * (p2 * w2 - p1 * w1) + (h * p2 - h * p1); //self.a * (p2 .* w2 - p1 .* w1) + (h2 .* p2 - h1 .* p1);
	double deltaY = a * (q2 * w2 - q1 * w1) + (h * q2 - h * q1); //self.a * (q2 .* w2 - q1 .* w1) + (h2 .* q2 - h1 .* q1);
	double deltaZ = (1 - e2) * a * (s2 * w2 - s1 * w1) + (h * s2 - h * s1); //(1 - e2) * self.a * (s2 .* w2 - s1 .* w1) + (h2 .* s2 - h1 .* s1);

	double cosPhi = cos(InitialPointLat); // cosfun(lat0); lat0 initialpoint.lat
	double sinPhi = sin(InitialPointLat); //sinfun(lat0);
	double cosLambda = cos(InitialPointLng); //cosfun(lon0);
	double sinLambda = sin(InitialPointLng); //sinfun(lon0);

	double t = cosLambda * deltaX + sinLambda * deltaY; // cosLambda .* u + sinLambda .* v; u = deltaX
	double uEast = -sinLambda * deltaX + cosLambda * deltaY; //-sinLambda .* u + cosLambda .* v;

	double wUp = cosPhi * t + sinPhi * deltaZ; //cosPhi .* t + sinPhi .* w;
	double vNorth = -sinPhi * t + cosPhi * deltaZ; // -sinPhi .* t + cosPhi .* w;

	//Point3D p = new Point3D((float)uEast, (float)vNorth, (float)wUp);
	vector<float> p(size);
	p[0] = uEast;
	p[1] = vNorth;
	p[2] = wUp;




	return p;
}

vector<float> MapTools::Geodetic2ECEF(PointLatLng Point)
{
	double a = 6378137; // Semi-major axis
	double ex = 0.08181919; // Excentricity
	double h = 2241; // Height of Mexico City
	double N_phi = 0;
	double x_ecef = 0;
	double y_ecef = 0;
	double z_ecef = 0;

	double a_h = 48.032537299811120;
	double a_v = 57.210092131377180;

	/*double e2 = Math.Pow(ex, 2);
	double sinx = Math.Sin(lat);
	double sinx2 = Math.Pow(sinx, 2);
	double e2sinx = e2 * sinx2;
	double sqrte2sinx = Math.Sqrt(1 - e2sinx);
	double N_phi1 = a / (sqrte2sinx);
	*/
	N_phi = a / (sqrt(1 - pow(ex, 2) * pow(sin(Point.getLat()), 2)));

	double cosx = cos(Point.getLat());
	double cosy = cos(Point.getLng());

	x_ecef = (N_phi / a_v + h) * cos(Point.getLat()) * cos(Point.getLng());
	y_ecef = (N_phi / a_v + h) * cos(Point.getLat()) * sin(Point.getLng());
	z_ecef = (N_phi / a_v * (1 - pow(ex, 2)) + h) * sin(Point.getLat());

	//PointF p = PointF(static_cast<float>(x_ecef), static_cast<float>(y_ecef));
	size_t size = 2;
	vector<float> p(size);
	p[0] = x_ecef;
	p[1] = y_ecef;
	return p;
}


