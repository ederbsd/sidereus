/**
 * @file
 *
 * Tests for an parallax class.
 *
 * SIDEREUS - Astronomy Librarie
 *
 * Copyright (c) 2009 Ederson de Moura
 *
 * @author Ederson de Moura
 *
 * @mainteiner: ederbsd@gmail.com
 *
 * $Id: Exp$
 */

#include <sidereus/parallax.hxx>
#include <sidereus/julian_day.hxx>

#include <genesis/logger.hxx>
#include <genesis/tests.hxx>

// Test for class Parallax.
static int parallax_test( void )
{
  GEN_MSG( "Tests for class Parallax.\n" );

  //genesis::proto_geo::point_equ_posn mars, parallax;
  genesis::proto_geo::point_lon_lat_posn observer;

  genesis::proto_datetime::dms dms;
  genesis::proto_datetime::date date;

  double JD = 0.;

  dms.neg = 0;
  dms.degrees = 33;
  dms.minutes = 21;
  dms.seconds = 22;

  observer.lat = genesis::datetime::dms_to_deg( &dms );

  dms.neg = 1;
  dms.degrees = 116;
  dms.minutes = 51;
  dms.seconds = 47;

  observer.lon = genesis::datetime::dms_to_deg( &dms );

  date.years = 2003;
  date.months = 8;
  date.days = 28;

  date.hours = 3;
  date.minutes = 17;
  date.seconds = 0;

  sidereus::julian_day J;

  JD = J.get_julian_day( &date );

  int failed = 0;

  /*
  ln_get_mars_equ_coords (jd, &mars);

  ln_get_parallax (&mars, ln_get_mars_earth_dist (jd), &observer, 1706, jd, &parallax);

  // Parallax is hard to calculate, so we allow relatively big errror.
  failed += GEN_TEST_RESULT( "Mars RA parallax for Palomar observatory at 2003/08/28 3:17 UT ", 
                             parallax.ra, 0.0053917, 0.00001 );
  failed += GEN_TEST_RESULT( "Mars DEC parallax for Palomar observatory at 2003/08/28 3:17 UT ",
                             parallax.dec, -14.1 / 3600.0,0.00002);

  return failed;
  */

  /////////////

  GEN_MSG( "End: Parallax.\n" );

  return failed;
}

int main( int argc, char* argv[] ) 
{
  int failed = 0;

  failed += parallax_test();

  GEN_TEST_PRINT_RESULT( "parallax", failed );

  return( failed > 0 );
}
