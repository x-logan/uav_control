#pragma once

#define _USE_MATH_DEFINES
#include <vector>
#include <algorithm>
#include <cmath>
#include "../Maps/PointLatLng.h"
#include "../Maps/PointLatLngAlt.h"

namespace Navigation
{

class Path4D
{
private:
	std::vector<PointLatLngAlt*> pointsList;
	std::vector<PointLatLng*> _pointsList;
	std::vector<double> theta_f;
	std::vector<double> psi_f;
	std::vector<double> Cc;
	std::vector<double> velocity;

public:
	Path4D();
	Path4D(std::vector<PointLatLngAlt*> &PointsList, std::vector<double> &Psi_f, std::vector<double> &Theta_f, std::vector<double> &Curvature, std::vector<double> &Velocity);
	void AddPath(std::vector<PointLatLngAlt*> &Points, std::vector<double> &Velocity, std::vector<double> &Curvature, std::vector<double> &Psi_f, std::vector<double> &Theta_f);

	void AddPoint(PointLatLngAlt *Point, double Velocity, double Curvature, double Psi_f, double Theta_f);

	void Reverse();
	void InsertRange(int Index, Path4D *Path);
	void InsertRange(int Index, std::vector<double> Velocity, std::vector<double> Curvature, std::vector<double> Psi_f, std::vector<double> Theta_f);

	std::vector<PointLatLngAlt*> getPointList() const;
	void setPointList(const std::vector<PointLatLngAlt*> &value);
	std::vector<PointLatLng*> get_PointList() const;
		//set { pointsList = value; updatePointList(); }

	const std::vector<double> &getTheta_f() const;
	void setTheta_f(const std::vector<double> &value);
	const std::vector<double> &getPsi_f() const;
	void setPsi_f(const std::vector<double> &value);
	const double &getLastPsi_f() const;
	const std::vector<double> &getCurvature() const;
	void setCurvature(const std::vector<double> &value);
	const std::vector<double> &getVelocity() const;
	void setVelocity(const std::vector<double> &value);
	PointLatLngAlt *getLastPoint() const;
	int getCount();

private:
	void updatePointList();

private:
	void InitializeInstanceFields();
};

}
