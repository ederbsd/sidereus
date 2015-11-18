/**
 * @file
 *
 * Implementation for an transform_coord.
 *
 * SIDEREUS - Astronomy Librarie
 *
 * Copyright (c) 2009 Ederson de Moura
 *
 * @author Ederson de Moura
 *
 * $Id: Exp$
 */

#include <sidereus/transform_coord.hxx>
#include <sidereus/precession.hxx>
#include <sidereus/sidereal_time.hxx>

namespace sidereus {

  void transform_coord::get_hrz_from_equ( 
   genesis::proto_geo::point_equ_posn* object,
   genesis::proto_geo::point_lon_lat_posn* observer, double JD,
   genesis::proto_geo::point_hrz_posn* position )
  {
    /// todo: OBS Transform horizontal coordinates to 
    /// galactic coordinates.
    double sidereal = 0.;

    // Get mean sidereal time in hours.
    sidereal = sidereus::sidereal_time::get_mean( JD );
    get_hrz_from_equ_sidereal_time( object, observer, sidereal, position );
  }

  void transform_coord::get_hrz_from_equ_sidereal_time( 
   genesis::proto_geo::point_equ_posn* object, 
   genesis::proto_geo::point_lon_lat_posn* observer,
   double sidereal,
   genesis::proto_geo::point_hrz_posn* position )
  {
    long double H = 0.0, ra = 0.0, latitude = 0.0, 
                declination = 0.0, A = 0.0, Ac = 0.0, 
                As = 0.0, h = 0.0, Z = 0.0, Zs = 0.0;

    // Change sidereal time from hours to radians.
    sidereal *= 2.0 * M_PI / 24.0;

    // Calculate hour angle of object at observers position.
    ra =  GEN_GEOMETRY_DEGTORAD( object->ra );
    H = sidereal + GEN_GEOMETRY_DEGTORAD( observer->lon ) - ra;

    // Convert to radians - hour angle, observers latitude, 
    // object declination.
    latitude = GEN_GEOMETRY_DEGTORAD( observer->lat );
    declination = GEN_GEOMETRY_DEGTORAD( object->dec );

    // Missuse of A (you have been warned).
    A = std::sin( latitude ) * std::sin( declination ) + 
        std::cos( latitude ) * std::cos( declination ) * std::cos( H );
    h = std::asin( A );

    // Convert back to degrees.
    position->alt = GEN_GEOMETRY_RADTODEG( h );

    // Zenith distance, Telescope Control 6.8a.
    Z = std::acos( A );

    // Is'n there better way to compute that?.
    Zs = std::sin( Z );

    // Sane check for zenith distance. Don't try to divide by 0.
    if( std::fabs( Zs ) < 1e-5 ) {
      if( object->dec > 0 ) {
        position->az = 180;
      } else {
        position->az = 0;
      }

      if(( object->dec > 0 && observer->lat > 0 ) || 
           ( object->dec < 0 && observer->lat < 0 )) {
        position->alt = 90;
      } else {
        position->alt = -90;
      }

      return;
    }

    // Formulas TC 6.8d Taff 1991, pp. 2 and 13 - vector transformations.
    As = ( std::cos( declination ) * std::sin( H ) ) / Zs;
    Ac = ( std::sin( latitude ) * std::cos( declination ) * 
         std::cos( H ) - std::cos( latitude ) * std::sin( declination ) ) / Zs;

    // Don't blom at atan2.
    if( Ac == 0 && As == 0 ) {
      if( object->dec > 0 ) {
        position->az = 180.0;
      } else {
        position->az = 0.0;
      }
      return;
    }

    A = std::atan2( As, Ac );

    // Convert back to degrees.
    position->az = genesis::geometry::range_degrees( GEN_GEOMETRY_RADTODEG( A ) );
  }

  void transform_coord::get_equ_from_hrz( 
   genesis::proto_geo::point_hrz_posn* object,
   genesis::proto_geo::point_lon_lat_posn* observer,
   double JD,
   genesis::proto_geo::point_equ_posn* position )
  {
    long double H = 0.0, longitude = 0.0, declination = 0.0,
                latitude = 0.0, A = 0.0, h = 0.0, sidereal = 0.0;

    // Change observer/object position into radians.
    // object alt/az:
    A = GEN_GEOMETRY_DEGTORAD( object->az );
    h = GEN_GEOMETRY_DEGTORAD( object->alt );

    // Observer long / lat:
    longitude = GEN_GEOMETRY_DEGTORAD( observer->lon );
    latitude = GEN_GEOMETRY_DEGTORAD( observer->lat );

    // Equ on pg89!
    H = std::atan2( std::sin( A ), ( std::cos( A ) * 
        std::sin( latitude ) + std::tan( h ) * std::cos( latitude ) ));
    declination = std::sin( latitude ) * std::sin( h ) - 
                  std::cos( latitude ) * std::cos( h ) * std::cos( A );
    declination = std::asin( declination );

    // Get ra = sidereal - longitude + H and change sidereal to radians.
    sidereal = sidereus::sidereal_time::get_apparent( JD );
    sidereal *= 2.0 * M_PI / 24.0;

    // Store in position.
    position->ra = genesis::geometry::range_degrees( 
                    GEN_GEOMETRY_RADTODEG( sidereal - H + longitude ) );

    position->dec = GEN_GEOMETRY_RADTODEG( declination );
  }

  void transform_coord::get_equ_from_ecl( 
   genesis::proto_geo::point_lon_lat_posn* object,
   double JD,
   genesis::proto_geo::point_equ_posn* position )
  {
    double ra = 0.0, declination = 0.0, 
           longitude = 0.0, latitude = 0.0;

    sidereus::nutation::nut nutation;

    // Get obliquity of ecliptic and change it to rads.
    sidereus::nutation( JD, &nutation );
    nutation.ecliptic = GEN_GEOMETRY_DEGTORAD( nutation.ecliptic );

    // Change object's position into radians.
    // objects:
    longitude = GEN_GEOMETRY_DEGTORAD( object->lon );
    latitude = GEN_GEOMETRY_DEGTORAD( object->lat );

    // Equ 12.3, 12.4.
    ra = std::atan2(( std::sin( longitude ) * std::cos( nutation.ecliptic ) -
         std::tan( latitude ) * std::sin( nutation.ecliptic )), 
         std::cos ( longitude ) );
    declination = std::sin( latitude ) * std::cos( nutation.ecliptic ) + 
                  std::cos( latitude ) * std::sin( nutation.ecliptic ) * 
                  std::sin( longitude );
    declination = std::asin( declination );

    // Store in position.
    position->ra = genesis::geometry::range_degrees(
                    GEN_GEOMETRY_RADTODEG( ra ) );

    position->dec = GEN_GEOMETRY_RADTODEG( declination );
  }

  void transform_coord::get_ecl_from_equ( 
    genesis::proto_geo::point_equ_posn* object,
    double JD,
    genesis::proto_geo::point_lon_lat_posn* position )
  {
    double ra = 0.0, declination = 0.0,
           longitude = 0.0, latitude = 0.0;

    sidereus::nutation::nut nutation;

    // Object position:
    ra = GEN_GEOMETRY_DEGTORAD( object->ra );
    declination = GEN_GEOMETRY_DEGTORAD( object->dec );

    sidereus::nutation( JD, &nutation );
    nutation.ecliptic = GEN_GEOMETRY_DEGTORAD( nutation.ecliptic );

    // Equ 12.1, 12.2.
    longitude = std::atan2(( std::sin( ra ) * std::cos( nutation.ecliptic ) + 
                std::tan( declination ) * std::sin( nutation.ecliptic )), 
                std::cos( ra ));
    latitude = std::sin( declination ) * std::cos( nutation.ecliptic ) - 
               std::cos( declination ) * std::sin( nutation.ecliptic ) * 
               std::sin( ra );
    latitude = std::asin( latitude );

    // Store in position.
    position->lat = GEN_GEOMETRY_RADTODEG( latitude );
    position->lon = genesis::geometry::range_degrees( 
                     GEN_GEOMETRY_RADTODEG( longitude ) );
  }
 
  void transform_coord::get_ecl_from_rect( 
   genesis::proto_geo::point_rect_coord* rect,
   genesis::proto_geo::point_lon_lat_posn* position )
  {
    double t = std::sqrt( rect->x * rect->x + rect->y * rect->y );

    position->lon = genesis::geometry::range_degrees( 
                     GEN_GEOMETRY_RADTODEG( std::atan2( rect->x, rect->y ) ));
    position->lat = GEN_GEOMETRY_RADTODEG( std::atan2( t, rect->z ));
  }

  void transform_coord::get_equ_from_gal( 
   genesis::proto_geo::point_gal_posn* gal,
   genesis::proto_geo::point_equ_posn* equ )
  {
    double RAD_27_4 = 0.0, SIN_27_4 = 0.0, COS_27_4 = 0.0;

    double l_123 = 0.0, cos_l_123 = 0.0;
    double sin_b = 0.0, cos_b = 0.0, rad_gal_b = 0.0;
    double y = 0.0;

    RAD_27_4 = GEN_GEOMETRY_DEGTORAD( 27.4 );
    SIN_27_4 = std::sin( RAD_27_4 );
    COS_27_4 = std::cos( RAD_27_4 );

    l_123 = GEN_GEOMETRY_DEGTORAD( gal->lon - 123 );
    cos_l_123 = std::cos( l_123 );

    rad_gal_b = GEN_GEOMETRY_DEGTORAD( gal->lat );

    sin_b = std::sin( rad_gal_b );
    cos_b = std::cos( rad_gal_b );

    y = std::atan2( std::sin( l_123 ), cos_l_123 *
                    SIN_27_4 - ( sin_b / cos_b ) * COS_27_4 );

    equ->ra = genesis::geometry::range_degrees( 
               GEN_GEOMETRY_RADTODEG( y ) + 12.25 );

    equ->dec = GEN_GEOMETRY_RADTODEG( 
                std::asin( sin_b * SIN_27_4 + cos_b * COS_27_4 * cos_l_123 ) );
  }

  void transform_coord::get_equ2000_from_gal( 
   genesis::proto_geo::point_gal_posn* gal,
   genesis::proto_geo::point_equ_posn* equ )
  {
    get_equ_from_gal( gal, equ );
    sidereus::precession::get_equ_prec2( equ, JULIAN_DAY_B1950, 
                                         JULIAN_DAY_JD2000, equ );
  }

  void transform_coord::get_gal_from_equ( 
   genesis::proto_geo::point_equ_posn *equ,
   genesis::proto_geo::point_gal_posn* gal )
  {
    double RAD_27_4 = 0.0, SIN_27_4 = 0.0, COS_27_4 = 0.0;

    double ra_192_25 = 0.0, cos_ra_192_25 = 0.0;
    double rad_equ_dec = 0.0;
    double cos_dec = 0.0, sin_dec = 0.0;
    double x = 0.0;

    RAD_27_4 = GEN_GEOMETRY_DEGTORAD( 27.4 );
    SIN_27_4 = std::sin( RAD_27_4 );
    COS_27_4 = std::cos( RAD_27_4 );

    ra_192_25 = GEN_GEOMETRY_DEGTORAD( 192.25 - equ->ra );
    cos_ra_192_25 = std::cos( ra_192_25 );

    rad_equ_dec = GEN_GEOMETRY_DEGTORAD( equ->dec );

    sin_dec = std::sin( rad_equ_dec );
    cos_dec = std::cos( rad_equ_dec );

    x = std::atan2( std::sin( ra_192_25 ), cos_ra_192_25 * SIN_27_4 - 
                    ( sin_dec / cos_dec ) * COS_27_4 );

    gal->lon = genesis::geometry::range_degrees( 303 - 
                                                  GEN_GEOMETRY_RADTODEG( x ) );
    gal->lat = GEN_GEOMETRY_RADTODEG( 
                std::asin( sin_dec * SIN_27_4 + cos_dec * COS_27_4 * cos_ra_192_25 ) );
  }

  void transform_coord::get_gal_from_equ2000( 
   genesis::proto_geo::point_equ_posn* equ,
   genesis::proto_geo::point_gal_posn* gal )
  {
    genesis::proto_geo::point_equ_posn equ_1950;
    sidereus::precession::get_equ_prec2( equ, JULIAN_DAY_JD2000, 
                                         JULIAN_DAY_B1950, &equ_1950 );
    get_gal_from_equ( &equ_1950, gal );
  }
  
}
