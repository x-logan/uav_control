/*
 * PointLatLng.cpp
 *
 *  Created on: Nov 18, 2014
 *      Author: Logan
 */

#include "PointLatLngAlt.h"

//const PointLatLngAlt PointLatLngAlt::Empty = PointLatLngAlt();

PointLatLngAlt::PointLatLngAlt(double lat, double lng, double alt)
{
	this->lat = lat;
	this->lng = lng;
	this->alt = alt;
	NotEmpty = true;
}

PointLatLngAlt::PointLatLngAlt()
{
	this->lat = 0;
	this->lng = 0;
	this->alt = 0;
	NotEmpty = false;
}

const bool &PointLatLngAlt::IsEmpty() const
{
	return !NotEmpty;
}

const double &PointLatLngAlt::Lat() const
{
	return this->lat;
}

void PointLatLngAlt::Lat(const double &value)
{
	this->lat = value;
	NotEmpty = true;
}

const double &PointLatLngAlt::Lng() const
{
	return this->lng;
}

void PointLatLngAlt::Lng(const double &value)
{
	this->lng = value;
	NotEmpty = true;
}

const double &PointLatLngAlt::Alt() const
{
	return this->alt;
}

void PointLatLngAlt::Alt(const double &value)
{
	this->alt = value;
	NotEmpty = true;
}

PointLatLng *PointLatLngAlt::GetPointLatLng()
{
	return new PointLatLng(this->lat, this->lng);
}

PointLatLngAlt PointLatLngAlt::operator + (SizeLatLngAlt sz)
{
	return Add(*this, sz);
}

PointLatLngAlt PointLatLngAlt::operator - (SizeLatLngAlt sz)
{
	return Subtract(*this, sz);
}

bool PointLatLngAlt::operator == (PointLatLngAlt right)
{
	return ((this->Lng() == right.Lng()) && (this->Lat() == right.Lat()) && (this->Alt() == right.Alt()));
}

bool PointLatLngAlt::operator != (PointLatLngAlt right)
{
	return !(*this == right);
}

PointLatLngAlt PointLatLngAlt::Add(PointLatLngAlt pt, SizeLatLngAlt sz)
{
	return PointLatLngAlt(pt.Lat() - sz.HeightLat(), pt.Lng() + sz.WidthLng(), pt.Alt() + sz.Alt());
}

PointLatLngAlt PointLatLngAlt::Subtract(PointLatLngAlt pt, SizeLatLngAlt sz)
{
	return PointLatLngAlt(pt.Lat() + sz.HeightLat(), pt.Lng() - sz.WidthLng(), pt.Alt() - sz.Alt());
}

void PointLatLngAlt::Offset(PointLatLngAlt pos)
{
	this->Offset(pos.Lat(), pos.Lng(), pos.Alt());
}

void PointLatLngAlt::Offset(double lat, double lng, double alt)
{
	this->Lng(this->Lng() + lng);
	this->Lat(this->Lat() - lat);
	this->Alt(this->Alt() + alt);
}





/*SizeLatLngAlt::SizeLatLngAlt(SizeLatLngAlt size)
{

	this->widthLng = size.widthLng;
	this->heightLat = size.heightLat;
	this->alt = size.alt;
}

SizeLatLngAlt::SizeLatLngAlt(PointLatLngAlt pt)
{

	this->heightLat = pt.getLat();
	this->widthLng = pt.getLng();
	this->alt = pt.getAlt();
}*/

SizeLatLngAlt::SizeLatLngAlt(double heightLat, double widthLng, double alt)
{

	this->heightLat = heightLat;
	this->widthLng = widthLng;
	this->alt = alt;

}

SizeLatLngAlt SizeLatLngAlt::operator + (SizeLatLngAlt sz2)
{
	return Add(*this, sz2);
}

SizeLatLngAlt SizeLatLngAlt::operator - (SizeLatLngAlt sz2)
{
	return Subtract(*this, sz2);
}

bool SizeLatLngAlt::operator == (SizeLatLngAlt sz2)
{
	return ((this->WidthLng() == sz2.WidthLng()) && (this->HeightLat() == sz2.HeightLat()) && (this->alt == sz2.alt));
}

bool SizeLatLngAlt::operator != (SizeLatLngAlt sz2)
{
	return !(*this == sz2);
}

/*explicit SizeLatLngAlt::operator PointLatLngAlt()
{
	return PointLatLngAlt(this->HeightLat(), this->getWidthLng(), this->alt);
}*/

const bool &SizeLatLngAlt::IsEmpty() const
{
	return ((this->widthLng == 0) && (this->heightLat == 0) && (this->alt == 0));
}

const double &SizeLatLngAlt::WidthLng() const
{
	return this->widthLng;
}

void SizeLatLngAlt::WidthLng(const double &value)
{
	this->widthLng = value;
}

const double &SizeLatLngAlt::HeightLat() const
{
	return this->heightLat;
}

void SizeLatLngAlt::HeightLat(const double &value)
{
	this->heightLat = value;
}

const double &SizeLatLngAlt::Alt() const
{
	return this->alt;
}

void SizeLatLngAlt::Alt(const double &value)
{
	this->alt = value;
}

SizeLatLngAlt SizeLatLngAlt::Add(SizeLatLngAlt sz1, SizeLatLngAlt sz2)
{
	return SizeLatLngAlt(sz1.HeightLat() + sz2.HeightLat(), sz1.WidthLng() + sz2.WidthLng(), sz1.alt + sz2.alt);
}

SizeLatLngAlt SizeLatLngAlt::Subtract(SizeLatLngAlt sz1, SizeLatLngAlt sz2)
{
	return SizeLatLngAlt(sz1.HeightLat() - sz2.HeightLat(), sz1.WidthLng() - sz2.WidthLng(), sz1.alt - sz2.alt);
}


/*PointLatLngAlt SizeLatLngAlt::ToPointLatLng()
{
	return (PointLatLngAlt) *this;
}*/

//C# TO C++ CONVERTER TODO TASK: Static constructors are not allowed in native C++:
/*SizeLatLngAlt::SizeLatLngAlt()
{
	Empty = SizeLatLngAlt();
}*/
