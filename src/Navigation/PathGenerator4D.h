#pragma once

#define _USE_MATH_DEFINES
#include "Path4D.h"
#include "../Maps/MapTools.h"

#include <string>
#include <vector>
#include <cmath>




	namespace Navigation
	{
		class PathGenerator4D
		{
		public:
			enum Direction
			{
				Right,
				Left
			};

			enum DubinsPath
			{
				LSL,
				LSR,
				RSL,
				RSR,
				None
			};
		private:
			//Log *log;

			Path4D *path;

			PointLatLngAlt *initialPosition;
			PointLatLngAlt *currentPosition;
			double turnRadius;
			double initialYaw;
			double initialPitch;
			double currentHeading;
			double currentVelocity;

			double deltaS;
			MapTools *mapTools;
			//private List<PointLatLngAlt> pointsList = new List<PointLatLngAlt>();
			//private List<PointLatLng> _pointsList = new List<PointLatLng>();
			//private List<double> x_enu = new List<double>();
			//private List<double> y_enu = new List<double>();
			//private List<double> theta_f = new List<double>();
			//private List<double> psi_f = new List<double>();
			//private List<double> Cc = new List<double>();
			//private List<double> arcLength = new List<double>();
			//private List<double> velocity = new List<double>();
			PointLatLngAlt *initialEnuPosition;



		public:
			PathGenerator4D();

			void newPath();

			void AddPath(std::vector<PointLatLngAlt*> &Points, std::vector<double> &Velocity, std::vector<double> &Curvature, std::vector<double> &Psi_f, std::vector<double> &Theta_f);


			void StraightLine(double meters);

			void StraightLine(double Meters, double InitialVelocity, double FinalVelocity);

			void Turn(Direction direction, double angle);

			void TurnUntil(Direction direction, double angle);

			std::vector<PointLatLngAlt*> GeneratePath(PointLatLngAlt *FinalPosition, double FinalYaw);


			std::vector<PointLatLngAlt*> GeneratePath(PointLatLngAlt *InitialPosition, double InitialYaw, PointLatLngAlt *FinalPosition, double FinalYaw);

			double FindPitch(PointLatLngAlt *Ip, PointLatLngAlt *Fp, double IYaw, double FHeading, double FYaw, double d2);

			void Turn180(PointLatLngAlt *InitialPosition, double InitialHeading);

			void Turn180();

			PointLatLngAlt *getInitialPosition() const;
			void setInitialPosition(PointLatLngAlt *value);

			const double &getInitialYaw() const;
			void setInitialYaw(const double &value);

			const double &getInitialPitch() const;
			void setInitialPitch(const double &value);

			const double &getTurnRadius() const;
			void setTurnRadius(const double &value);

			std::vector<PointLatLngAlt*> getRoutePoints() const;

			const std::vector<double> &getcCurvature() const;



			const std::vector<double> &getPsi_f() const;
			const std::vector<double> &getTheta_f() const;


			const std::vector<double> &getVelocity() const;
			const double &getCurrentVelocity() const;
			void setCurrentVelocity(const double &value);

		private:


		public:
			void setInitialEnuPosition(PointLatLngAlt *value);



			Path4D *getPath() const;
			void setPath(Path4D *value);



		private:
			void InitializeInstanceFields();
		};
	}

