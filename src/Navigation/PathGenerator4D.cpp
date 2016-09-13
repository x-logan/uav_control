#include "PathGenerator4D.h"


namespace Navigation
{

	PathGenerator4D::PathGenerator4D()
	{
		InitializeInstanceFields();
		path = new Path4D();
	}

	void PathGenerator4D::newPath()
	{
		path = new Path4D();

		//pointsList = new List<PointLatLngAlt>();
		//_pointsList = new List<PointLatLng>();
		//pointsList.Add(initialPosition);
		//x_enu = new List<double>();
		//x_enu.Add(0);
		//y_enu = new List<double>();
		//y_enu.Add(0);
		//psi_f = new List<double>();
		//theta_f = new List<double>();
		//psi_f.Add(0);
		//Cc = new List<double>();
		//Cc.Add(0);
		//arcLength = new List<double>();

		//loglog->ResetLog();

		//velocity = new List<double>();


	}

	void PathGenerator4D::AddPath(std::vector<PointLatLngAlt*> &Points, std::vector<double> &Velocity, std::vector<double> &Curvature, std::vector<double> &Psi_f, std::vector<double> &Theta_f)
	{
		/*
		pointsList.AddRange(Points);
		for(int i=0;i<Points.Count;i++)
			_pointsList.Add(Points[i].GetPointLatLng());
		velocity.AddRange(Velocity);
		Cc.AddRange(Curvature);
		psi_f.AddRange(Psi_f);
		theta_f.AddRange(Theta_f);
		 * */
		path->AddPath(Points, Velocity, Curvature, Psi_f, Theta_f);
		initialPosition = path->getPointList()[path->getPointList().size() - 1];



	}

	void PathGenerator4D::StraightLine(double meters)
	{

		double x = 0;
		double y = 0;
		double z = 0;
		double deltaDistance = 1;
		double totalDistance = 0;
		y = deltaDistance * cos(initialYaw); // Lat
		x = deltaDistance * sin(initialYaw); // Lon
		z = deltaDistance * sin(initialPitch);
		//pointsList.Add(initialPosition);
		if (meters == 0)
		{
			return;
		}
		while (totalDistance < meters)
		{
			totalDistance += sqrt(pow(x, 2) + pow(y, 2));

			PointLatLngAlt *addPoint;

			if (path->getCount() == 0)
			{
				addPoint = initialPosition;
				//pointsList.Add(initialPosition);
				//_pointsList.Add(pointsList[pointsList.Count - 1].GetPointLatLng());
				//velocity.Add(currentVelocity);



			}
			else
			{
				addPoint = mapTools->OffsetInMeters(path->getLastPoint(), x, y, z);
				//pointsList.Add(mapTools.OffsetInMeters(pointsList[pointsList.Count - 1], x, y, z));
				//_pointsList.Add(pointsList[pointsList.Count - 1].GetPointLatLng());
				//velocity.Add(currentVelocity);
			}




			// Data necesary for lyapunov tracking

			double x_dot = x;
			double y_dot = y;

		   /* p = mapTools.Geodetic2ENU(new PointLatLng(y_dot, x_dot), new PointLatLng( 0, 0));

			double x_dot_enu = p.X;
			double y_dot_enu = p.Y;

			double x_ddot = 0;
			double y_ddot = 0;

			p = mapTools.Geodetic2ENU(new PointLatLng(y_ddot, x_ddot), new PointLatLng(0, 0));

			double x_ddot_enu = p.X;
			double y_ddot_enu = p.Y;
			 * */

			double psi_f;
			psi_f = M_PI / 2 - atan2(y_dot, x_dot);
			if (psi_f > M_PI)
			{
				psi_f -= 2 * M_PI;
			}
			if (psi_f < -M_PI)
			{
				psi_f += 2 * M_PI;
			}

			//theta_f.Add(initialPitch);

			//Cc.Add(0);

			//arcLength.Add(route.Distance * 1000);

			// Constant curvature Cc=0
			path->AddPoint(addPoint, currentVelocity, 0, psi_f, initialPitch);
			//log->Append(path->getLastPoint()->ToStringCSV());


		}
		//double d = route.Distance;
		initialPosition = path->getLastPoint();


	}

	void PathGenerator4D::StraightLine(double Meters, double InitialVelocity, double FinalVelocity)
	{

		double x = 0;
		double y = 0;
		double z = 0;
		double deltaDistance = 1;
		double totalDistance = 0;
		y = deltaDistance * cos(initialYaw); // Lat
		x = deltaDistance * sin(initialYaw); // Lon
		z = deltaDistance * sin(initialPitch);
		//pointsList.Add(initialPosition);
		if (Meters == 0)
		{
			return;
		}
		PointLatLngAlt *addPoint;
		double addVelocity;
		while (totalDistance < Meters)
		{
			totalDistance += sqrt(pow(x, 2) + pow(y, 2));

			if (path->getCount() == 0)
			{
				addPoint = initialPosition;
				addVelocity = InitialVelocity;
				//pointsList.Add(initialPosition);
				//velocity.Add(InitialVelocity);
				//_pointsList.Add(pointsList[pointsList.Count - 1].GetPointLatLng());
			}
			else
			{
				addPoint = mapTools->OffsetInMeters(path->getLastPoint(), x, y, z);
				addVelocity = InitialVelocity + (totalDistance / Meters) * (FinalVelocity - InitialVelocity);
				//pointsList.Add(mapTools.OffsetInMeters(pointsList[pointsList.Count - 1], x, y, z));
				//velocity.Add(InitialVelocity + (totalDistance / Meters) * (FinalVelocity - InitialVelocity));
				//_pointsList.Add(pointsList[pointsList.Count - 1].GetPointLatLng());
			}





			// Data necesary for lyapunov tracking

			double x_dot = x;
			double y_dot = y;

			/*p = mapTools.Geodetic2ENU(new PointLatLng(y_dot, x_dot), new PointLatLng(0, 0));

			double x_dot_enu = p.X;
			double y_dot_enu = p.Y;

			double x_ddot = 0;
			double y_ddot = 0;

			p = mapTools.Geodetic2ENU(new PointLatLng(y_ddot, x_ddot), new PointLatLng(0, 0));

			double x_ddot_enu = p.X;
			double y_ddot_enu = p.Y;
			 *
			 * */

			double psi_f = M_PI / 2 - atan2(y_dot, x_dot);
			//psi_f.Add(Math.PI / 2 - Math.Atan2(y_dot, x_dot));
			if (psi_f > M_PI)
			{
				psi_f -= 2 * M_PI;
			}
			if (psi_f < -M_PI)
			{
				psi_f += 2 * M_PI;
			}
			//theta_f.Add(initialPitch);

			//Cc.Add(0);

			//arcLength.Add(route.Distance * 1000);
			path->AddPoint(addPoint, addVelocity, 0, psi_f, initialPitch);
			//log->Append(path->getLastPoint()->ToStringCSV());
		}
		//double d = route.Distance;
		currentVelocity = FinalVelocity;
		initialPosition = path->getLastPoint();


	}

	void PathGenerator4D::Turn(Direction direction, double angle)
	{
		PointLatLngAlt *addPoint;
		if (direction == Right)
		{

			// Calculate offsets
			double offsetX = -sin(initialYaw) * turnRadius;
			double offsetY = cos(initialYaw) * turnRadius;
			double offsetZ = 0;

			PointLatLngAlt *center = mapTools->OffsetInMeters(initialPosition, offsetY, offsetX, offsetZ);
			double s1 = 0;
			double s = initialYaw + 3*M_PI / 2;

			while (s < angle + initialYaw + 3*M_PI / 2)
			{
				s += deltaS;
				s1 += deltaS;

				addPoint = mapTools->OffsetInMeters(center, turnRadius * sin(s), turnRadius * cos(s), 2 * turnRadius * s1 * sin(initialPitch));
				//pointsList.Add(mapTools.OffsetInMeters(center, turnRadius * Math.Sin(s), turnRadius * Math.Cos(s), 2*turnRadius*s1 * Math.Sin(initialPitch)));
				//_pointsList.Add(pointsList[pointsList.Count - 1].GetPointLatLng());
				//velocity.Add(currentVelocity);

				// Data necesary for lyapunov tracking

				double x_dot = turnRadius * cos(s);
				double y_dot = -turnRadius * sin(s);

				double psi_f;
				psi_f = M_PI / 2 - atan2(y_dot, x_dot);
				if (psi_f > M_PI)
				{
					psi_f -= 2 * M_PI;
				}
				if (psi_f < -M_PI)
				{
					psi_f += 2 * M_PI;
				}
				//theta_f.Add(initialPitch);

				//Cc.Add(1/turnRadius);

				//
				//arcLength.Add(route.Distance * 1000);

				path->AddPoint(addPoint, currentVelocity, 1 / turnRadius, psi_f, initialPitch);
				//log->Append(path->getLastPoint()->ToStringCSV());
			}
			initialPosition = path->getLastPoint();
			initialYaw = initialYaw + angle;
			if (initialYaw > M_PI)
			{
				initialYaw -= 2 * M_PI;
			}
		}
		else
		{

			// Calculate offsets
			double offsetX = sin(initialYaw) * turnRadius;
			double offsetY = -cos(initialYaw) * turnRadius;
			double offsetZ = 0;

			PointLatLngAlt *center = mapTools->OffsetInMeters(initialPosition, offsetY, offsetX,offsetZ);
			double s1 = 0;
			double s = -initialYaw;
			while (s < angle - initialYaw)
			{
				s += deltaS;
				s1 += deltaS;

				addPoint = mapTools->OffsetInMeters(center, turnRadius * cos(s), turnRadius * sin(s), 2 * turnRadius * s1 * sin(initialPitch));
				//pointsList.Add(mapTools.OffsetInMeters(center, turnRadius * Math.Cos(s), turnRadius * Math.Sin(s), 2 * turnRadius * s1 * Math.Sin(initialPitch)));
				//_pointsList.Add(pointsList[pointsList.Count - 1].GetPointLatLng());
				//velocity.Add(currentVelocity);

				// Data necesary for lyapunov tracking

				double x_dot = -turnRadius * sin(s);
				double y_dot = turnRadius * cos(s);

				double psi_f = M_PI / 2 - atan2(y_dot, x_dot);
				//psi_f.Add(Math.PI / 2 - Math.Atan2(y_dot, x_dot));
				if (psi_f > M_PI)
				{
					psi_f -= 2 * M_PI;
				}
				if (psi_f < -M_PI)
				{
					psi_f += 2 * M_PI;
				}
				//theta_f.Add(initialPitch);

				//Cc.Add(1 / turnRadius);

				//UpdateRoute();
				//arcLength.Add(route.Distance * 1000);

				path->AddPoint(addPoint, currentVelocity, 1 / turnRadius, psi_f, initialPitch);
				//log->Append(path->getLastPoint()->ToStringCSV());
			}

			initialPosition = path->getLastPoint();
			initialYaw = initialYaw - angle;
			if (initialYaw < -M_PI)
			{
				initialYaw += 2 * M_PI;
			}


		}

	}

	void PathGenerator4D::TurnUntil(Direction direction, double angle)
	{
		PointLatLngAlt *addPoint;
		if (direction == Right)
		{

			// Calculate offsets
			double offsetX = sin(initialYaw) * turnRadius;
			double offsetY = cos(initialYaw) * turnRadius;
			double offsetZ = 0;

			PointLatLngAlt *center = mapTools->OffsetInMeters(initialPosition, offsetY, -offsetX, offsetZ);
			double s1 = 0;
			double s = initialYaw + 3 * M_PI / 2;
			if (!(s < angle + 3 * M_PI / 2) && abs(s - angle + 3 * M_PI / 2) > 0.1745) // y mayor que 10 grados
			{
				angle += 2 * M_PI;
			}
			while (s < angle + 3 * M_PI / 2)
			{
				s += deltaS;
				s1 += deltaS;
				addPoint = mapTools->OffsetInMeters(center, turnRadius * sin(s), turnRadius * cos(s), 2 * turnRadius * s1 * sin(initialPitch));
				//pointsList.Add(mapTools.OffsetInMeters(center, turnRadius * Math.Sin(s), turnRadius * Math.Cos(s), 2 * turnRadius * s1 * Math.Sin(initialPitch)));
				//_pointsList.Add(pointsList[pointsList.Count - 1].GetPointLatLng());
				//velocity.Add(currentVelocity);

				// Data necesary for lyapunov tracking


				double x_dot = turnRadius * cos(s);
				double y_dot = -turnRadius * sin(s);

				double psi_f = M_PI / 2 - atan2(y_dot, x_dot);
				//psi_f.Add(Math.PI / 2 - Math.Atan2(y_dot, x_dot));
				if (psi_f > M_PI)
				{
					psi_f -= 2 * M_PI;
				}
				if (psi_f < -M_PI)
				{
					psi_f += 2 * M_PI;
				}
				//theta_f.Add(initialPitch);

				//Cc.Add(1 / turnRadius);

				//UpdateRoute();
				//arcLength.Add(route.Distance * 1000);
				path->AddPoint(addPoint, currentVelocity, 1 / turnRadius, psi_f, initialPitch);
				//log->Append(path->getLastPoint()->ToStringCSV());
			}
			initialPosition = path->getLastPoint();
			initialYaw = angle;
			if (initialYaw > M_PI)
			{
				initialYaw -= 2 * M_PI;
			}
		}
		else
		{

			// Calculate offsets
			double offsetX = sin(initialYaw) * turnRadius;
			double offsetY = cos(initialYaw) * turnRadius;
			double offsetZ = 0;

			PointLatLngAlt *center = mapTools->OffsetInMeters(initialPosition, -offsetY, offsetX, offsetZ);
			double s1 = 0;
			double s = initialYaw + M_PI / 2;
			if (!(s > angle + M_PI / 2)) // y mayor que 10 grados
			{
				angle -= 2 * M_PI;
			}
			while (s > angle + M_PI / 2)
			{
				s -= deltaS;
				s1 += deltaS;

				addPoint = mapTools->OffsetInMeters(center, turnRadius * sin(s), turnRadius * cos(s), 2 * turnRadius * s1 * sin(initialPitch));
				//pointsList.Add(mapTools.OffsetInMeters(center, turnRadius * Math.Sin(s), turnRadius * Math.Cos(s), 2 * turnRadius * s1 * Math.Sin(initialPitch)));
				//_pointsList.Add(pointsList[pointsList.Count - 1].GetPointLatLng());
				//velocity.Add(currentVelocity);

				//x_enu.Add(p.X);
				//y_enu.Add(p.Y);

				double x_dot = turnRadius * cos(s);
				double y_dot = -turnRadius * sin(s);

				double psi_f = M_PI / 2 - atan2(y_dot, x_dot) + M_PI;
				//psi_f.Add(Math.PI / 2 - Math.Atan2(y_dot, x_dot) +Math.PI);
				if (psi_f > M_PI)
				{
					psi_f -= 2 * M_PI;
				}
				if (psi_f < -M_PI)
				{
					psi_f += 2 * M_PI;
				}
				//theta_f.Add(initialPitch);

				//Cc.Add(1 / turnRadius);

				//UpdateRoute();
				//arcLength.Add(route.Distance * 1000);

				path->AddPoint(addPoint, currentVelocity, 1 / turnRadius, psi_f, initialPitch);
				//log->Append(path->getLastPoint()->ToStringCSV());


			}
			initialYaw = angle;



			initialPosition = path->getLastPoint();

			if (initialYaw < -M_PI)
			{
				initialYaw += 2 * M_PI;
			}


		}

	}

	std::vector<PointLatLngAlt*> PathGenerator4D::GeneratePath(PointLatLngAlt *FinalPosition, double FinalYaw)
	{
		return GeneratePath(this->initialPosition, this->initialYaw, FinalPosition, FinalYaw);
	}

	std::vector<PointLatLngAlt*> PathGenerator4D::GeneratePath(PointLatLngAlt *InitialPosition, double InitialYaw, PointLatLngAlt *FinalPosition, double FinalYaw)
	{
		//Seleccionar la distancia menor de entre las circunferencias generadas
		DubinsPath dubinsPath = None;
		std::vector<PointLatLngAlt*> PathPoints = std::vector<PointLatLngAlt*>();

		if (FinalYaw > M_PI)
		{
			FinalYaw -= 2 * M_PI;
		}
		else if (FinalYaw < -M_PI)
		{
			FinalYaw += 2 * M_PI;
		}

		PointLatLngAlt *Ci1 = mapTools->OffsetInMeters(InitialPosition, cos(InitialYaw) * turnRadius, -sin(InitialYaw) * turnRadius,0); // Right
		PointLatLngAlt *Ci2 = mapTools->OffsetInMeters(InitialPosition, -cos(InitialYaw) * turnRadius, sin(InitialYaw) * turnRadius,0); // Left

		PointLatLngAlt *Cf1 = mapTools->OffsetInMeters(FinalPosition, cos(FinalYaw) * turnRadius, -sin(FinalYaw) * turnRadius,0); // Right
		PointLatLngAlt *Cf2 = mapTools->OffsetInMeters(FinalPosition, -cos(FinalYaw) * turnRadius, sin(FinalYaw) * turnRadius,0); // Left

		PathPoints.push_back(Ci1);
		PathPoints.push_back(Ci2);
		PathPoints.push_back(Cf1);
		PathPoints.push_back(Cf2);

		std::vector<double> listD = std::vector<double>();
		listD.push_back(mapTools->GetDistanceMeters(Ci1, Cf1));
		listD.push_back(mapTools->GetDistanceMeters(Ci2, Cf1));
		listD.push_back(mapTools->GetDistanceMeters(Ci1, Cf2));
		listD.push_back(mapTools->GetDistanceMeters(Ci2, Cf2));
		int index = -1;
		double minDistance = 10000000;
		int index2 = 0;
		double minDistance2 = 10000000;


		for (std::vector<double>::iterator distance=listD.begin(); distance!=listD.end(); ++distance)
		{

			if (*distance < minDistance)
			{
				index = index2;
				minDistance = *distance;
			}
			index2++;

		}





		switch (index)
		{
			case 0:
				PathPoints.push_back(Ci1);
				PathPoints.push_back(Cf1);
				dubinsPath = RSR;
				break;

			case 1:
				PathPoints.push_back(Ci2);
				PathPoints.push_back(Cf1);
				dubinsPath = LSR;
				break;

			case 2:
				PathPoints.push_back(Ci1);
				PathPoints.push_back(Cf2);
				dubinsPath = RSL;
				break;

			case 3:
				PathPoints.push_back(Ci2);
				PathPoints.push_back(Cf2);
				dubinsPath = LSL;
				break;

		}
		if (dubinsPath == LSL)
		{
			this->initialPosition = InitialPosition;
			this->initialYaw = InitialYaw;
			double slope = mapTools->GetAngleMeassuredFromNord(PathPoints[4], PathPoints[5]);
			double angle = acos(turnRadius * 2 / minDistance);
			double finalHeading = slope;

			this->initialPitch = FindPitch(InitialPosition, FinalPosition, InitialYaw, finalHeading, FinalYaw, mapTools->GetDistanceMeters(PathPoints[4], PathPoints[5]));

			TurnUntil(Left, finalHeading);

			StraightLine(mapTools->GetDistanceMeters(PathPoints[4], PathPoints[5]));

			if (finalHeading < FinalYaw)
			{
				TurnUntil(Right, FinalYaw);
			}
			else
			{
				TurnUntil(Left, FinalYaw);
			}

		}
		else if (dubinsPath == LSR)
		{
			this->initialPosition = InitialPosition;
			this->initialYaw = InitialYaw;

			double slope = mapTools->GetAngleMeassuredFromNord(PathPoints[4], PathPoints[5]);
			double angle = acos(turnRadius * 2 / minDistance);
			double finalHeading = slope + angle - M_PI / 2;

			this->initialPitch = FindPitch(InitialPosition, FinalPosition, InitialYaw, finalHeading, FinalYaw, sqrt(pow(minDistance, 2) - pow(turnRadius * 2, 2)));

			TurnUntil(Left, finalHeading);
			StraightLine(sqrt(pow(minDistance, 2) - pow(turnRadius * 2, 2)));
			TurnUntil(Right, FinalYaw);

		}
		else if (dubinsPath == RSR)
		{
			this->initialPosition = InitialPosition;
			this->initialYaw = InitialYaw;

			double slope = mapTools->GetAngleMeassuredFromNord(PathPoints[4], PathPoints[5]);
			double angle = acos(turnRadius * 2 / minDistance);
			double finalHeading = slope;

			this->initialPitch = FindPitch(InitialPosition, FinalPosition, InitialYaw, finalHeading, FinalYaw, mapTools->GetDistanceMeters(PathPoints[4], PathPoints[5]));

			TurnUntil(Right, finalHeading);
			StraightLine(mapTools->GetDistanceMeters(PathPoints[4], PathPoints[5]));
			TurnUntil(Right, FinalYaw);
		}
		else if (dubinsPath == RSL)
		{
			this->initialPosition = InitialPosition;
			this->initialYaw = InitialYaw;

			double slope = mapTools->GetAngleMeassuredFromNord(PathPoints[4], PathPoints[5]);
			double angle = acos(turnRadius * 2 / minDistance);
			double finalHeading = slope - angle + M_PI / 2;

			this->initialPitch = FindPitch(InitialPosition, FinalPosition, InitialYaw, finalHeading, FinalYaw, sqrt(pow(minDistance, 2) - pow(turnRadius * 2, 2)));

			TurnUntil(Right, finalHeading);
			StraightLine(sqrt(pow(minDistance, 2) - pow(turnRadius * 2, 2)));
			TurnUntil(Left, FinalYaw);
		}


		return PathPoints;


	}

	double PathGenerator4D::FindPitch(PointLatLngAlt *Ip, PointLatLngAlt *Fp, double IYaw, double FHeading, double FYaw, double d2)
	{
		double a1 = IYaw + 2 * M_PI;
		double a2 = FHeading + 2 * M_PI;
		double a3 = FYaw + 2 * M_PI;
		double d1 = abs(a1 - a2) * 2 * turnRadius;
		//double d2 = mapTools.GetDistanceMeters(PathPoints[4], PathPoints[5]);
		double d3 = abs(a2 - a3) * 2 * turnRadius;
		double h = abs(Ip->Alt() - Fp->Alt());
		double dTotal = d1 + d2 + d3;
		double angle = atan2(h, dTotal);
		return (Ip->Alt() - Fp->Alt()) > 0 ? - atan2(h, dTotal) : atan2(h, dTotal);



	}

	void PathGenerator4D::Turn180(PointLatLngAlt *InitialPosition, double InitialHeading)
	{
		this->initialPosition = InitialPosition;
		this->initialYaw = InitialHeading;


		StraightLine(turnRadius * 2.2);

		GeneratePath(this->initialPosition, this->initialYaw, InitialPosition, InitialHeading - M_PI);



	}

	void PathGenerator4D::Turn180()
	{


		StraightLine(turnRadius * 4);

		GeneratePath(this->initialPosition, this->initialYaw, getInitialPosition(), getInitialYaw() - M_PI);



	}

	PointLatLngAlt *PathGenerator4D::getInitialPosition() const
	{
		return initialPosition;
	}

	void PathGenerator4D::setInitialPosition(PointLatLngAlt *value)
	{
		initialPosition = value;
	}

	const double &PathGenerator4D::getInitialYaw() const
	{
		return initialYaw;
	}

	void PathGenerator4D::setInitialYaw(const double &value)
	{
		initialYaw = value;
	}

	const double &PathGenerator4D::getInitialPitch() const
	{
		return initialPitch;
	}

	void PathGenerator4D::setInitialPitch(const double &value)
	{
		initialPitch = value;
	}

	const double &PathGenerator4D::getTurnRadius() const
	{
		return turnRadius;
	}

	void PathGenerator4D::setTurnRadius(const double &value)
	{
		turnRadius = value;
	}

	std::vector<PointLatLngAlt*> PathGenerator4D::getRoutePoints() const
	{
		return path->getPointList();
	}

	const std::vector<double> &PathGenerator4D::getcCurvature() const
	{
		return path->getCurvature();
	}

	const std::vector<double> &PathGenerator4D::getPsi_f() const
	{
		return path->getPsi_f();
	}

	const std::vector<double> &PathGenerator4D::getTheta_f() const
	{
		return path->getTheta_f();
	}

	const std::vector<double> &PathGenerator4D::getVelocity() const
	{
		return path->getVelocity();
	}

	const double &PathGenerator4D::getCurrentVelocity() const
	{
		return currentVelocity;
	}

	void PathGenerator4D::setCurrentVelocity(const double &value)
	{
		currentVelocity = value;
	}



	void PathGenerator4D::setInitialEnuPosition(PointLatLngAlt *value)
	{
		initialEnuPosition = value;
	}



	Navigation::Path4D *PathGenerator4D::getPath() const
	{
		return path;
	}

	void PathGenerator4D::setPath(Path4D *value)
	{
		path = value;
	}

	void PathGenerator4D::InitializeInstanceFields()
	{
		;
		turnRadius = 0;
		initialYaw = 0;
		initialPitch = 0;
		currentHeading = 0;
		currentVelocity = 0;
		deltaS = .1;
		mapTools = new MapTools();
		initialEnuPosition = new PointLatLngAlt();
	}
}

