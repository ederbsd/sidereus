/**
 * @file
 *
 * Implementation for an julian_day.
 *
 * SIDEREUS - Astronomy Librarie
 *
 * Copyright (c) 2009 Ederson de Moura
 *
 * @author Ederson de Moura
 *
 * $Id: Exp$
 */

#include <sidereus/julian_day.hxx>
 
#include <cstring>

namespace sidereus {

  double julian_day::get_julian_day( genesis::proto_datetime::date* date )
  {
    double JD = 0.0;
    double days = 0.0;
    
    volatile register int a asm ("eax");
    volatile register int b asm ("eax");
    a = 0; b= 0; 

    // Ruct date local_date.
    genesis::proto_datetime::date local_date;
		
    // Create local copy.
    std::memcpy( &local_date, date, sizeof( genesis::proto_datetime::date ) );
		
    // Check for month = January or February.
    if( local_date.months < 3 ) {
      local_date.years--;
      local_date.months += 12;
    }
	
    a = local_date.years / 100;
	
    // Check for Julian or Gregorian calendar (starts Oct 4th 1582).
    if( local_date.years > 1582 || 
         ( local_date.years == 1582 && ( local_date.months > 10 || 
         ( local_date.months == 10 && local_date.days >= 4 )) )) {
      // Gregorian calendar.
      b = 2 - a + (a / 4);
    } else {
      // Julian calendar.
      b = 0;
    }
	
    // Add a fraction of hours, minutes and secs to days.
    days = local_date.days + ( double )( local_date.hours / 24.0 ) + 
                             ( double )( local_date.minutes / 1440.0 ) + 
                             ( double )( local_date.seconds / 86400.0 );

    // Now get the JD.
    JD = ( int )( 365.25 * ( local_date.years + 4716 )) + 
         ( int )( 30.6001 * ( local_date.months + 1 )) + days + b - 1524.5;
	
    return JD;
  }

  size_t julian_day::get_day_of_week( genesis::proto_datetime::date* date )
  {
    size_t day = 0;
    double JD = 0.;
    
    // Get julian day.
    JD = get_julian_day( date );
    JD += 1.5;
    day = ( int )JD % 7;
    
    return day;
  }	

  double julian_day::get_julian_from_sys()
  {
    double JD = 0.0;
    genesis::proto_datetime::date date;
		
    // Get sys date.
    genesis::datetime::get_date_from_sys( &date );
    JD = get_julian_day( &date );

    return JD;
  }

  double julian_day::get_julian_local_date( genesis::proto_datetime::zonedate* 
   zonedate )
  {
    genesis::proto_datetime::date date;
	
    zonedate_to_date( zonedate, &date );

    return get_julian_day( &date );
  }

  void julian_day::get_local_date( double JD, genesis::proto_datetime::zonedate* 
   zonedate )
  {
    genesis::proto_datetime::date date;

#ifndef __WIN32__
    //time_t curtime;
    //struct tm* loctime;
#endif
    long gmtoff = 0;

    genesis::datetime::get_date( JD, &date );

    // Add day light savings time and hour angle.
#ifdef __WIN32__
    _tzset();
    gmtoff = _timezone;
    if( _daylight ) {
      gmtoff += 3600;
    }
#else
#ifdef _BSD_SOURCE
    curtime = time( 0 );
    loctime = localtime(&curtime);
    gmtoff = loctime->tm_gmtoff;
#endif
#endif
    date_to_zonedate( &date, zonedate, gmtoff );
  }

  double julian_day::get_julian_from_mpc( char* mpc_date )
  {
    genesis::proto_datetime::date date;
    double JD = 0.;
	
    genesis::datetime::get_date_from_mpc( &date, mpc_date );

    JD = get_julian_day( &date );
    return JD;
  }

  void julian_day::date_to_zonedate( genesis::proto_datetime::date* date, 
   genesis::proto_datetime::zonedate* zonedate, long gmtoff )
  {
    double jd = 0.;
    genesis::proto_datetime::date dat;

    jd = get_julian_day( date );
    jd += gmtoff / 86400.0;
	
    genesis::datetime::get_date( jd, &dat );

    zonedate->years   = dat.years;
    zonedate->months  = dat.months;
    zonedate->days    = dat.days;
    zonedate->hours   = dat.hours;
    zonedate->minutes = dat.minutes;
    zonedate->seconds = dat.seconds;
    zonedate->gmtoff  = gmtoff;
  }

  void julian_day::zonedate_to_date( genesis::proto_datetime::zonedate* zonedate, 
                                     genesis::proto_datetime::date* date )
  {
    double jd = 0.;
    genesis::proto_datetime::date dat;

    dat.years   = zonedate->years;
    dat.months  = zonedate->months;
    dat.days    = zonedate->days;
    dat.hours   = zonedate->hours;
    dat.minutes = zonedate->minutes;
    dat.seconds = zonedate->seconds;

    jd = get_julian_day( &dat );
    jd -= zonedate->gmtoff / 86400.0;
    genesis::datetime::get_date( jd, date );
  }

}
