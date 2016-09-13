/*
 * SizeLatLng.cpp
 *
 *  Created on: Nov 18, 2014
 *      Author: Logan
 */

#include "SizeLatLng.h"


/*SizeLatLng::SizeLatLng(SizeLatLng size)
{
   //InitializeInstanceFields();
   this->widthLng = size.widthLng;
   this->heightLat = size.heightLat;
}*/

SizeLatLng::~SizeLatLng() {
	// TODO Auto-generated destructor stub
}

/*SizeLatLng::SizeLatLng(PointLatLng pt)
{
   InitializeInstanceFields();
   this->heightLat = pt.getLat();
   this->widthLng = pt.getLng();
}
*/
SizeLatLng::SizeLatLng(double heightLat, double widthLng)
{
   this->heightLat = heightLat;
   this->widthLng = widthLng;
}

SizeLatLng SizeLatLng::operator + (SizeLatLng sz2)
{
   return Add(*this, sz2);
}

SizeLatLng SizeLatLng::operator - (SizeLatLng sz2)
{
   return Subtract(*this, sz2);
}

bool SizeLatLng::operator == (SizeLatLng sz2)
{
   return ((this->getWidthLng() == sz2.getWidthLng()) && (this->getHeightLat() == sz2.getHeightLat()));
}

bool SizeLatLng::operator != (SizeLatLng sz2)
{
   return !(*this == sz2);
}

/*explicit SizeLatLng::operator PointLatLng()
{
   return PointLatLng(this->getHeightLat(), this->getWidthLng());
}*/

const bool &SizeLatLng::getIsEmpty() const
{
   return ((this->widthLng == 0) && (this->heightLat == 0));
}

const double &SizeLatLng::getWidthLng() const
{
   return this->widthLng;
}

void SizeLatLng::setWidthLng(const double &value)
{
   this->widthLng = value;
}

const double &SizeLatLng::getHeightLat() const
{
   return this->heightLat;
}

void SizeLatLng::setHeightLat(const double &value)
{
   this->heightLat = value;
}

SizeLatLng SizeLatLng::Add(SizeLatLng sz1, SizeLatLng sz2)
{
   return SizeLatLng(sz1.getHeightLat() + sz2.getHeightLat(), sz1.getWidthLng() + sz2.getWidthLng());
}

SizeLatLng SizeLatLng::Subtract(SizeLatLng sz1, SizeLatLng sz2)
{
   return SizeLatLng(sz1.getHeightLat() - sz2.getHeightLat(), sz1.getWidthLng() - sz2.getWidthLng());
}

/*bool SizeLatLng::Equals(void *obj)
{
   if (!(dynamic_cast<SizeLatLng>(obj) != NULL))
   {
	  return false;
   }
   SizeLatLng ef = static_cast<SizeLatLng>(obj);
   return (((ef.getWidthLng() == this->getWidthLng()) && (ef.getHeightLat() == this->getHeightLat())) && ef.GetType()->Equals(__super::GetType()));
}*/

/*int SizeLatLng::GetHashCode()
{
   if (this->getIsEmpty())
   {
	  return 0;
   }
   return (this->getWidthLng().GetHashCode() ^ this->getHeightLat().GetHashCode());
}*/

/*GMap::NET::PointLatLng SizeLatLng::ToPointLatLng()
{
   return (PointLatLng) *this;
}*/

/*std::wstring SizeLatLng::ToString()
{
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'ToString':
   return (std::wstring(L"{WidthLng=") + this->widthLng.ToString(CultureInfo::CurrentCulture) + std::wstring(L", HeightLng=") + this->heightLat.ToString(CultureInfo::CurrentCulture) + std::wstring(L"}"));
}*/



