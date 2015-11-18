/**
 * @file
 *
 * Tests for an julian_day class.
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

#include <sidereus/julian_day.hxx>

#include <genesis/logger.hxx>
#include <genesis/tests.hxx>

// Tests for class Julian Day.
static int julian_day_test( void )
{
  GEN_MSG( "Tests for class Julian Day.\n" );

  sidereus::julian_day J;

  double JD = 0.0;
  double JD2 = 0.0;

  int wday = 0; 
  int failed = 0;

  genesis::proto_datetime::date date;
  genesis::proto_datetime::date pdate;
  genesis::proto_datetime::zonedate zonedate;

  time_t now;
  time_t now_jd;

  // Get julian day for 04/10/1957 19:00:00.
  date.years = 1957;
  date.months = 10;
  date.days = 4; 
  date.hours = 19;
  date.minutes = 0;
  date.seconds = 0;
  JD = J.get_julian_day( &date );
  failed += GEN_TEST_RESULT( "(Julian Day) JD for 4/10/1957 19:00:00", 
                             JD, 2436116.29166667, 0.00001 );

  // Get julian day for 27/01/333 12:00:00.
  date.years = 333;
  date.months = 1;
  date.days = 27;
  date.hours = 12;
  JD = J.get_julian_day( &date );
  failed += GEN_TEST_RESULT( "(Julian Day) JD for 27/01/333 12:00:00",
                             JD, 1842713.0, 0.1 );

  // Get julian day for 30/06/1954 00:00:00.
  date.years = 1954;
  date.months = 6;
  date.days = 30;
  date.hours = 0;
  JD = J.get_julian_day( &date );
  failed += GEN_TEST_RESULT( "(Julian Day) JD for 30/06/1954 00:00:00",
                             JD, 2434923.5, 0.1 );

  wday = J.get_day_of_week( &date );
  failed += GEN_TEST_RESULT( "(Julian Day) Weekday No", wday, 3, 0.1 );

  // Test date_to_zonedate and back.
  J.date_to_zonedate( &date, &zonedate, 7200 );
  J.zonedate_to_date( &zonedate, &date );
  JD = J.get_julian_day( &date );
  failed += GEN_TEST_RESULT( "(Julian Day) date_to_zonedate and zonedate_to_date check "
                             "- JD for 30/06/1954 00:00:00", 
                             JD, 2434923.5, 0.1 );

  genesis::datetime::get_date( JD, &pdate );

  failed += GEN_TEST_RESULT( "(Julian Day) Day from JD for 30/06/1954 "
                             "00:00:00", pdate.days, 30, 0.1 );

  failed += GEN_TEST_RESULT( "(Julian Day) Month from JD for 30/06/1954 "
                             "00:00:00", pdate.months, 6, 0.1 );

  failed += GEN_TEST_RESULT( "(Julian Day) Year from JD for 30/06/1954 "
                             "00:00:00", pdate.years, 1954, 0.1 );

  failed += GEN_TEST_RESULT( "(Julian Day) Hour from JD for 30/06/1954 "
                             "00:00:00", pdate.hours, 0, 0.1 );

  failed += GEN_TEST_RESULT( "(Julian Day) Minute from JD for 30/06/1954 "
                             "00:00:00", pdate.minutes, 0, 0.1 );

  failed += GEN_TEST_RESULT( "(Julian Day) Second from JD for 30/06/1954 " 
                             "00:00:00", pdate.seconds, 0, 0.001 );

  JD = J.get_julian_from_sys();

  JD2 = J.get_julian_from_sys();
  failed += GEN_TEST_RESULT( "(Julian Day) Diferrence between two "
                             "sucessive get_julian_from_sys calls "
                             "it shall never be zero)", 
                             JD2 - JD, 1e-2/86400.0, .99e-1 );


  // Test that we get from JD same value as is in time_t
  // struct..was problem before introduction of zonedate (on
  // machines which doesn't run in UTC).
  std::time( &now );
  genesis::datetime::get_timet_from_julian( \
    genesis::datetime::get_julian_from_timet( &now ), &now_jd );

  failed += GEN_TEST_RESULT( "(Julian Day) Diferrence between time_t "
                             "from system and from JD", 
                             std::difftime( now, now_jd ), 0, 0 );

  GEN_MSG( "End: Julian Day.\n" );

  return failed;
}

int main( int argc, char* argv[] ) 
{
  int failed = 0;

  failed += julian_day_test();

  GEN_TEST_PRINT_RESULT( "julian_day", failed );

  return( failed > 0 );
}
