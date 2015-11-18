/**
 * @file
 *
 * Tests for an transform_coord class.
 *
 * SIDEREUS Astronomy Librarie.
 *
 * Copyright (c) 2009 Ederson de Moura
 *
 * @author Ederson de Moura
 *
 * @mainteiner: ederbsd@gmail.com
 *
 * $Id: Exp$
 */

#include <sidereus/transform_coord.hxx>
#include <sidereus/julian_day.hxx>

#include <genesis/logger.hxx>
#include <genesis/tests.hxx>

// Test for class Transformation Coord.
static int transform_coord_test( void )
{
  GEN_MSG( "Tests for class Transform Coord.\n" );

  genesis::proto_geo::point_nh_equ_posn hobject, hpollux;
  genesis::proto_geo::point_nh_lonlat_posn hobserver; 
  genesis::proto_geo::point_equ_posn object, pollux, equ;
  genesis::proto_geo::point_hrz_posn hrz;
  genesis::proto_geo::point_lon_lat_posn observer, ecl;

  genesis::proto_datetime::date date;

  // Observers position.
  hobserver.lon.neg = 0;
  hobserver.lon.degrees = 282;
  hobserver.lon.minutes = 56;
  hobserver.lon.seconds = 4;
  hobserver.lat.neg = 0;
  hobserver.lat.degrees = 38;
  hobserver.lat.minutes = 55;
  hobserver.lat.seconds = 17;

  // Object position.
  hobject.ra.hours = 23;
  hobject.ra.minutes = 9;
  hobject.ra.seconds = 16.641;
  hobject.dec.neg = 1;
  hobject.dec.degrees = 6;
  hobject.dec.minutes = 43;
  hobject.dec.seconds = 11.61;

  // Set for tests.      
  int failed = 0;

  // Datetime.
  date.years = 1987;
  date.months = 4;
  date.days = 10;
  date.hours = 19;
  date.minutes = 21;
  date.seconds = 0;

  sidereus::julian_day J;

  double JD = J.get_julian_day( &date );

  genesis::geometry::hequ_to_equ( &hobject, &object );
  genesis::geometry::hlnlat_to_lnlat( &hobserver, &observer );

  sidereus::transform_coord T;;

  T.get_hrz_from_equ( &object, &observer, JD, &hrz );

  failed += GEN_TEST_RESULT( "(Transforms) Equ to Horiz ALT ", hrz.alt, 
                             15.12426274, 0.00000001 );
  failed += GEN_TEST_RESULT( "(Transforms) Equ to Horiz AZ ", hrz.az, 
                             68.03429264, 0.00000001 );

  object.dec = 90;

  T.get_hrz_from_equ( &object, &observer, JD, &hrz );
  failed += GEN_TEST_RESULT( "(Transforms) Equ to Horiz ALT ", hrz.alt, 
                             38.92138889, 0.00000001 );
  failed += GEN_TEST_RESULT( "(Transforms) Equ to Horiz AZ ", hrz.az, 
                             180.0, 0.1 );

  object.dec = -90;

  T.get_hrz_from_equ( &object, &observer, JD, &hrz );
  failed += GEN_TEST_RESULT( "(Transforms) Equ to Horiz ALT ", hrz.alt, 
                             -38.92138889, 0.00000001 );
  failed += GEN_TEST_RESULT( "(Transforms) Equ to Horiz AZ ", hrz.az, 
                             0.0, 0.1 );

  observer.lat *= -1;

  T.get_hrz_from_equ( &object, &observer, JD, &hrz );
  failed +=  GEN_TEST_RESULT( "(Transforms) Equ to Horiz ALT ", hrz.alt, 
                              38.92138889, 0.00000001 );
  failed +=  GEN_TEST_RESULT( "(Transforms) Equ to Horiz AZ ", hrz.az, 
                              0.0, 0.1 );

  object.dec = 90;

  T.get_hrz_from_equ( &object, &observer, JD, &hrz );
  failed +=  GEN_TEST_RESULT( "(Transforms) Equ to Horiz ALT ", hrz.alt, 
                              -38.92138889, 0.00000001 );
  failed +=  GEN_TEST_RESULT( "(Transforms) Equ to Horiz AZ ", hrz.az, 
                              180.0, 0.1 );

  hpollux.ra.hours = 7;
  hpollux.ra.minutes = 45;
  hpollux.ra.seconds = 18.946;
  hpollux.dec.neg = 0;
  hpollux.dec.degrees = 28;
  hpollux.dec.minutes = 1;
  hpollux.dec.seconds = 34.26;

  genesis::geometry::hequ_to_equ( &hpollux, &pollux );
  T.get_ecl_from_equ( &pollux, JD, &ecl );

  /*
  genesis::geometry::lat_to_hlnlat( &ecl, &hecl );
  failed += GEN_TEST_RESULT( "(Transforms) Equ to Ecl longitude ", 
                             ecl.lon, 113.21542105, 0.00000001 );
  failed += GEN_TEST_RESULT( "(Transforms) Equ to Ecl latitude", 
                             ecl.lat, 6.68002727, 0.00000001 );
  */

  T.get_equ_from_ecl( &ecl, JD, &equ );
  failed += GEN_TEST_RESULT( "(Transforms) Ecl to Equ RA ", equ.ra, 
                             116.32894167, 0.00000001 );
  failed += GEN_TEST_RESULT( "(Transforms) Ecl to Equ DEC", equ.dec, 
                             28.02618333, 0.00000001 );

  GEN_MSG( "End: Tranformation Coord.\n" );

  return failed;
}

int main( int argc, char* argv[] ) 
{
  int failed = 0;

  failed += transform_coord_test();

  GEN_TEST_PRINT_RESULT( "tranformation_coord", failed );

  return( failed > 0 );
}
