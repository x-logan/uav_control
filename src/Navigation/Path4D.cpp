#include "Path4D.h"

namespace Navigation
{
Path4D::Path4D()
{
	pointsList = std::vector<PointLatLngAlt*>();
	_pointsList = std::vector<PointLatLng*>();
	theta_f = std::vector<double>();
	psi_f = std::vector<double>();
	Cc = std::vector<double>();
	velocity = std::vector<double>();
}

Path4D::Path4D(std::vector<PointLatLngAlt*> &PointsList, std::vector<double> &Psi_f, std::vector<double> &Theta_f, std::vector<double> &Curvature, std::vector<double> &Velocity)
{
	InitializeInstanceFields();
	pointsList = PointsList;
	updatePointList();
	theta_f = std::vector<double>();
	psi_f = std::vector<double>();
	Cc = std::vector<double>();
	velocity = std::vector<double>();
}

void Path4D::AddPath(std::vector<PointLatLngAlt*> &Points, std::vector<double> &Velocity, std::vector<double> &Curvature, std::vector<double> &Psi_f, std::vector<double> &Theta_f)
{
	pointsList.insert(pointsList.end(),Points.begin(),Points.end());
	for (int i = 0;i < Points.size();i++)
	{
		_pointsList.push_back(Points[i]->GetPointLatLng());
	}
	velocity.insert(velocity.end(),Velocity.begin(),Velocity.end());
	Cc.insert(Cc.end(),Curvature.begin(),Curvature.end());
	psi_f.insert(psi_f.end(),Psi_f.begin(),Psi_f.end());
	theta_f.insert(theta_f.end(),Theta_f.begin(),Theta_f.end());

	//initialPosition = pointsList[pointsList.Count - 1];
}

void Path4D::AddPoint(PointLatLngAlt *Point, double Velocity, double Curvature, double Psi_f, double Theta_f)
{
	pointsList.push_back(Point);
	_pointsList.push_back(Point->GetPointLatLng());
	velocity.push_back(Velocity);
	Cc.push_back(Curvature);
	psi_f.push_back(Psi_f);
	theta_f.push_back(Theta_f);

	//initialPosition = pointsList[pointsList.Count - 1];
}

void Path4D::Reverse()
{
	std::reverse(pointsList.begin(), pointsList.end());
	std::reverse(_pointsList.begin(), _pointsList.end());
	std::reverse(velocity.begin(), velocity.end());
	std::reverse(Cc.begin(), Cc.end());
	std::reverse(psi_f.begin(), psi_f.end());
	std::reverse(theta_f.begin(), theta_f.end());
	for (int i = 0; i < psi_f.size(); i++)
	{
		if (psi_f[i] <= 0)
		{
			psi_f[i] += M_PI;
		}
		else
		{
			psi_f[i] -= M_PI;
		}
	}

	for (int i = 0; i < theta_f.size(); i++)
	{
		theta_f[i] = -theta_f[i];
	}

}

void Path4D::InsertRange(int Index, Path4D *Path)
{
	InsertRange(Index, Path->getVelocity(), Path->getCurvature(), Path->getPsi_f(), Path->getTheta_f());
}

void Path4D::InsertRange(int Index,  std::vector<double> Velocity, std::vector<double> Curvature, std::vector<double> Psi_f, std::vector<double> Theta_f)
{
	//pointsList.insert(pointsList.begin()+Index, Points.begin(),Points.end());
	//_pointsList = new List<PointLatLng>();
	theta_f.insert(theta_f.begin()+Index, Theta_f.begin(),Theta_f.end());
	psi_f.insert(psi_f.begin()+Index,Psi_f.begin(),Psi_f.end());
	Cc.insert(Cc.begin()+Index,Curvature.begin(),Curvature.end());
	velocity.insert(velocity.begin()+Index,Velocity.begin(),Velocity.end());
}

std::vector<PointLatLngAlt*> Path4D::getPointList() const
{
	return pointsList;
}

void Path4D::setPointList(const std::vector<PointLatLngAlt*> &value)
{
	pointsList = value;
	updatePointList();
}

std::vector<PointLatLng*> Path4D::get_PointList() const
{
	return _pointsList;
}

const std::vector<double> &Path4D::getTheta_f() const
{
	return theta_f;
}

void Path4D::setTheta_f(const std::vector<double> &value)
{
	theta_f = value;
}

const std::vector<double> &Path4D::getPsi_f() const
{
	return psi_f;
}

void Path4D::setPsi_f(const std::vector<double> &value)
{
	psi_f = value;
}

const double &Path4D::getLastPsi_f() const
{
	return psi_f[psi_f.size() - 1];
}

const std::vector<double> &Path4D::getCurvature() const
{
	return Cc;
}

void Path4D::setCurvature(const std::vector<double> &value)
{
	Cc = value;
}

const std::vector<double> &Path4D::getVelocity() const
{
	return velocity;
}

void Path4D::setVelocity(const std::vector<double> &value)
{
	velocity = value;
}

PointLatLngAlt *Path4D::getLastPoint() const
{
	return pointsList[pointsList.size() - 1];
}

int Path4D::getCount()
{
	return pointsList.size();
}

void Path4D::updatePointList()
{
	_pointsList = std::vector<PointLatLng*>();
	for (int i = 0; i < pointsList.size();i++)
	{
		_pointsList.push_back(pointsList[i]->GetPointLatLng());
	}
}

void Path4D::InitializeInstanceFields()
{
	pointsList = std::vector<PointLatLngAlt*>();
	_pointsList = std::vector<PointLatLng*>();
	theta_f = std::vector<double>();
	psi_f = std::vector<double>();
	Cc = std::vector<double>();
	velocity = std::vector<double>();
}

}
