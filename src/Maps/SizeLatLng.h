/*
 * SizeLatLng.h
 *
 *  Created on: Nov 18, 2014
 *      Author: Logan
 */

#include <string>
#ifndef SIZELATLNG_H_
#define SIZELATLNG_H_

//#include "PointLatLng.h"
/// <summary>
/// the size of coordinates
/// </summary>
class SizeLatLng
{

private:
  double heightLat;
  double widthLng;

public:
  static const SizeLatLng Empty;
  //SizeLatLng(SizeLatLng *size);
  virtual ~SizeLatLng();

  //SizeLatLng(PointLatLng pt);

  SizeLatLng(double heightLat, double widthLng);

  SizeLatLng operator + (SizeLatLng sz2);

  SizeLatLng operator - (SizeLatLng sz2);

  bool operator == (SizeLatLng sz2);

  bool operator != (SizeLatLng sz2);

//explicit operator PointLatLng();

 const bool &getIsEmpty() const;

 const double &getWidthLng() const;
 void setWidthLng(const double &value);

 const double &getHeightLat() const;
 void setHeightLat(const double &value);

  static SizeLatLng Add(SizeLatLng sz1, SizeLatLng sz2);

  static SizeLatLng Subtract(SizeLatLng sz1, SizeLatLng sz2);

  //virtual bool Equals(void *obj);

  //virtual int GetHashCode();

  //PointLatLng ToPointLatLng();

  //virtual std::wstring ToString();

//C# TO C++ CONVERTER TODO TASK: Static constructors are not allowed in native C++:
  //static SizeLatLng();
};

#endif /* SIZELATLNG_H_ */


