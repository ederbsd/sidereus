/**
 * @file
 *
 * Implementation for an parallax.
 *
 * SIDEREUS - Astronomy Librarie
 *
 * Copyright (c) 2009 Ederson de Moura
 *
 * @author Ederson de Moura
 *
 * $Id: Exp$
 */

#include <sidereus/parallax.hxx>
#include <sidereus/sidereal_time.hxx>

namespace sidereus {

  void parallax::get( genesis::proto_geo::point_equ_posn* object,
     double au_distance,
     genesis::proto_geo::point_lon_lat_posn* observer,
     double height, double JD,
     genesis::proto_geo::point_equ_posn* parallax )
  {
    double H = 0.;

    H = sidereus::sidereal_time::get_apparent( JD ) + 
        ( observer->lon - object->ra ) / 15.0;

    get_ha( object, au_distance, observer, height, H, parallax );

  }

  void parallax::get_ha( genesis::proto_geo::point_equ_posn* object,
   double au_distance,
   genesis::proto_geo::point_lon_lat_posn* observer,
   double height,
   double H,
   genesis::proto_geo::point_equ_posn* parallax )
  {
    double sin_pi, ro_sin, ro_cos, sin_H, cos_H, dec_rad, cos_dec;

    get_topocentric( observer, height, &ro_sin, &ro_cos );
    sin_pi = std::sin( GEN_GEOMETRY_DEGTORAD( ( 8.794 / au_distance ) / 3600.0 ) ); 

    // Change hour angle from hours to radians.
    H *= M_PI / 12.0;

    sin_H = std::sin( H );
    cos_H = std::cos( H );

    dec_rad = GEN_GEOMETRY_DEGTORAD( object->dec );
    cos_dec = std::cos( dec_rad );

    parallax->ra = std::atan2( -ro_cos * sin_pi * sin_H, cos_dec - 
                   ro_cos * sin_pi * cos_H );
    parallax->dec = std::atan2(( std::sin( dec_rad ) - ro_sin * sin_pi ) * 
                    std::cos( parallax->ra ), cos_dec - ro_cos * sin_pi * cos_H );

    parallax->ra = GEN_GEOMETRY_RADTODEG( parallax->ra );
    parallax->dec = GEN_GEOMETRY_RADTODEG( parallax->dec ) - object->dec;
  }

  void parallax::get_topocentric( 
   genesis::proto_geo::point_lon_lat_posn* observer,
   double height, double* ro_sin, double* ro_cos )
  {
    double u = 0.;
    double lat_rad = 0.;
 
    lat_rad = GEN_GEOMETRY_DEGTORAD( observer->lat );
    u = std::atan( 0.99664719 * tan ( lat_rad ) );
    *ro_sin = 0.99664719 * std::sin( u ) + 
     ( height / 6378140 ) * std::sin( lat_rad );
    *ro_cos = std::cos( u ) + ( height / 6378140 ) * std::cos( lat_rad );

    // The quantity ro_sin is positive in the northern hemisphere, 
    // negative in the southern one.
    if( observer->lat > 0 ) {
      *ro_sin = std::fabs( *ro_sin );
    } else {
      *ro_sin = std::fabs( *ro_sin ) * -1;
    }

    // ro_cos is always positive.
    *ro_cos = std::fabs( *ro_cos );
  }

}
