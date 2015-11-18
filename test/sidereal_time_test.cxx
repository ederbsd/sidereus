/**
 * @file
 *
 * Tests for an sidereal_time class.
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

#include <sidereus/sidereal_time.hxx>

#include <genesis/logger.hxx>
#include <genesis/tests.hxx>

// Test for class Sidereal Time.
static int sidereal_time_test( void )
{
  GEN_MSG( "Tests for class Sidereal Time.\n" );

  genesis::proto_datetime::date date;

  double sd = 0.0;
  double JD = 0.0;

  // Set for tests.
  int failed = 0;

  // 10/04/1987 19:21:00.
  date.years = 1987;
  date.months = 4;
  date.days = 10;
  date.hours = 19;
  date.minutes = 21;
  date.seconds = 0;

  JD = sidereus::sidereal_time().julian_day::get_julian_day( &date );

  sd = sidereus::sidereal_time::get_mean( JD );
  failed += GEN_TEST_RESULT( "(Sidereal) mean hours on 10/04/1987 19:21:00 ", 
                             sd, 8.58252488, 0.000001 );

  sd = sidereus::sidereal_time::get_apparent( JD );
  failed += GEN_TEST_RESULT( "(Sidereal) apparent hours on 10/04/1987 19:21:00 "
                             , sd, 8.58252060, 0.000001 );

  GEN_MSG( "End: Sidereal Time.\n" );

  return failed;
}

int main( int argc, char* argv[] ) 
{
  int failed = 0;

  failed += sidereal_time_test();

  GEN_TEST_PRINT_RESULT( "sidereal_time", failed );

  return( failed > 0 );
}
