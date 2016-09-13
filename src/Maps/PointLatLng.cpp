/*
 * PointLatLng.cpp
 *
 *  Created on: Nov 18, 2014
 *      Author: Logan
 */

#include "PointLatLng.h"


//const PointLatLng PointLatLng::Empty = PointLatLng();

PointLatLng::PointLatLng(double lat, double lng)
{
   this->lat = lat;
   this->lng = lng;
   NotEmpty = true;
}

const bool &PointLatLng::getIsEmpty() const
{
   return !NotEmpty;
}

const double &PointLatLng::getLat() const
{
   return this->lat;
}

void PointLatLng::setLat(const double &value)
{
   this->lat = value;
   NotEmpty = true;
}

const double &PointLatLng::getLng() const
{
   return this->lng;
}

void PointLatLng::setLng(const double &value)
{
   this->lng = value;
   NotEmpty = true;
}

PointLatLng PointLatLng::operator + (SizeLatLng sz)
{
   return Add(*this, sz);
}

PointLatLng PointLatLng::operator - (SizeLatLng sz)
{
   return Subtract(*this, sz);
}

bool PointLatLng::operator == (PointLatLng right)
{
   return ((this->getLng() == right.getLng()) && (this->getLat() == right.getLat()));
}

bool PointLatLng::operator != (PointLatLng right)
{
   return !(*this == right);
}

PointLatLng PointLatLng::Add(PointLatLng pt, SizeLatLng sz)
{
   return PointLatLng(pt.getLat() - sz.getHeightLat(), pt.getLng() + sz.getWidthLng());
}

PointLatLng PointLatLng::Subtract(PointLatLng pt, SizeLatLng sz)
{
   return PointLatLng(pt.getLat() + sz.getHeightLat(), pt.getLng() - sz.getWidthLng());
}

/*bool PointLatLng::Equals(void *obj)
{
   if (!(dynamic_cast<PointLatLng>(obj) != nullptr))
   {
	  return false;
   }
   PointLatLng tf = static_cast<PointLatLng>(obj);
   return (((tf.getLng() == this->getLng()) && (tf.getLat() == this->getLat())) && tf.GetType()->Equals(__super::GetType()));
}*/

void PointLatLng::Offset(PointLatLng pos)
{
   this->Offset(pos.getLat(), pos.getLng());
}

void PointLatLng::Offset(double lat, double lng)
{
   this->setLng(this->getLng() + lng);
   this->setLat(this->getLat() - lat);
}

/*int PointLatLng::GetHashCode()
{
   return (this->getLng().GetHashCode() ^ this->getLat().GetHashCode());
}

/*std::wstring PointLatLng::ToString()
{
   return std::wstring::Format(CultureInfo::CurrentCulture, L"{{Lat={0}, Lng={1}}}", this->getLat(), this->getLng());
}*/

