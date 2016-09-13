
 /* SizeLatLng.h
 *
 *  Created on: Nov 18, 2014
 *      Author: Logan
 */

#ifndef POINTLATLNG_H_
#define POINTLATLNG_H_

#include "SizeLatLng.h"
#include <string>


	   /// <summary>
	   /// the point of coordinates
	   /// </summary>
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//ORIGINAL LINE: [Serializable] public struct PointLatLng
class PointLatLng
{
public:
  static const PointLatLng Empty;
private:
  double lat;
  double lng;

  bool NotEmpty;

public:
  PointLatLng(double lat, double lng);

  /// <summary>
  /// returns true if coordinates wasn't assigned
  /// </summary>
 const bool &getIsEmpty() const;

 const double &getLat() const;
 void setLat(const double &value);

 const double &getLng() const;
 void setLng(const double &value);

  PointLatLng operator + (SizeLatLng sz);

  PointLatLng operator - (SizeLatLng sz);

  bool operator == (PointLatLng right);

  bool operator != (PointLatLng right);

  static PointLatLng Add(PointLatLng pt, SizeLatLng sz);

  static PointLatLng Subtract(PointLatLng pt, SizeLatLng sz);

  //virtual bool Equals(void *obj) override;

  void Offset(PointLatLng pos);

  void Offset(double lat, double lng);

  //virtual int GetHashCode() override;

  //virtual std::wstring ToString() override;
};

#endif /* SPOINTLATLNG_H_ */

