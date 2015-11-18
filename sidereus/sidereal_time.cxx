/**
 * @file
 *
 * Implementation for an sidereal_time.
 *
 * SIDEREUS - Astronomy Librarie
 *
 * Copyright (c) 2009 Ederson de Moura
 *
 * @author Ederson de Moura
 *
 * $Id: Exp$
 */

#include <sidereus/sidereal_time.hxx>

namespace sidereus {

  double sidereal_time::get_mean( double JD )
  {
    long double sidereal = 0.0;
    long double T = 0.0;

    T = ( JD - 2451545.0 ) / 36525.0;

    // Calc mean angle.
    sidereal = 280.46061837 + ( 360.98564736629 * ( JD - 2451545.0 )) + 
               ( 0.000387933 * T * T ) - ( T * T * T / 38710000.0 );

    // Add a convenient multiple of 360 degrees.
    sidereal = genesis::geometry::range_degrees( sidereal );

    // Change to hours.
    sidereal *= 24.0 / 360.0;

    return sidereal;
  }

  double sidereal_time::get_apparent( double JD )
  {
     double correction = 0.0;
     double hours = 0.0;
     double sidereal = 0.0;

     // Nutation
     nut nutation;

     // Get the mean sidereal time.
     sidereal = get_mean( JD );

     // Add corrections for nutation in longitude and for 
     // the true obliquity of the ecliptic.
     sidereus::nutation( JD, &nutation );

     correction = ( nutation.longitude / 15.0 * 
                    std::cos( GEN_GEOMETRY_DEGTORAD( nutation.obliquity ) ));

     // Value is in degrees so change it to hours and 
     // add to mean sidereal time.
     hours = ( 24.0 / 360.0 ) * correction;

     sidereal += hours;

     return sidereal;
  }

}
