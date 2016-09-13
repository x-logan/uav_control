

 /* SizeLatLng.h
 *
 *  Created on: Sep 02, 2015
 *      Author: Logan
 */

#ifndef POINTLATLNGALT_H_
#define POINTLATLNGALT_H_

#include <string>
#include "PointLatLng.h"


class SizeLatLngAlt
{

	private:
		double heightLat;
		double widthLng;
		double alt;
	public:
		//static const SizeLatLngAlt Empty;
		//SizeLatLngAlt(const SizeLatLngAlt&);
		//SizeLatLngAlt(PointLatLngAlt pt);

		SizeLatLngAlt();
		SizeLatLngAlt(double heightLat, double widthLng, double alt);
		//virtual ~SizeLatLngAlt();
		SizeLatLngAlt operator + (SizeLatLngAlt sz2);
		SizeLatLngAlt operator - (SizeLatLngAlt sz2);
		bool operator == (SizeLatLngAlt sz2);
		bool operator != (SizeLatLngAlt sz2);
		//explicit operator PointLatLngAlt();
		const bool &IsEmpty() const;
		const double &WidthLng() const;
		void WidthLng(const double &value);
		const double &HeightLat() const;
		void HeightLat(const double &value);
		const double &Alt() const;
		void Alt(const double &value);
		static SizeLatLngAlt Add(SizeLatLngAlt sz1, SizeLatLngAlt sz2);
		static SizeLatLngAlt Subtract(SizeLatLngAlt sz1, SizeLatLngAlt sz2);
		//virtual bool Equals(void *obj);

		//virtual int GetHashCode() override;
		//PointLatLngAlt ToPointLatLng();
	//C# TO C++ CONVERTER TODO TASK: Static constructors are not allowed in native C++:
		//static SizeLatLngAlt();
};

		/// <summary>
		/// the point of coordinates
		/// </summary>
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//ORIGINAL LINE: [Serializable] public struct PointLatLngAlt
class PointLatLngAlt
{
	public:
		static const PointLatLngAlt Empty;
	private:
		double lat;
		double lng;
		double alt;
		bool NotEmpty;
	public:
		PointLatLngAlt(double lat, double lng, double alt);
		PointLatLngAlt();
		//virtual ~PointLatLngAlt();
		/// <summary>
		/// returns true if coordinates wasn't assigned
		/// </summary>
		const bool &IsEmpty() const;
		const double &Lat() const;
		void Lat(const double &value);
		const double &Lng() const;
		void Lng(const double &value);
		const double &Alt() const;
		void Alt(const double &value);
		PointLatLng *GetPointLatLng();


		PointLatLngAlt operator + (SizeLatLngAlt sz);
		PointLatLngAlt operator - (SizeLatLngAlt sz);
		bool operator == (PointLatLngAlt right);
		bool operator != (PointLatLngAlt right);
		static PointLatLngAlt Add(PointLatLngAlt pt, SizeLatLngAlt sz);
		static PointLatLngAlt Subtract(PointLatLngAlt pt, SizeLatLngAlt sz);
		//virtual bool Equals(void *obj);
		void Offset(PointLatLngAlt pos);
		void Offset(double lat, double lng, double alt);
		//virtual int GetHashCode() override;
		//virtual std::wstring ToString() override;
};


#endif /* SPOINTLATLNGALT_H_ */
