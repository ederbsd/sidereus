/**
 * @file
 *
 * Implementation for an precession.
 *
 * SIDEREUS - Astronomy Librarie
 *
 * Copyright (c) 2009 Ederson de Moura
 *
 * @author Ederson de Moura
 *
 * $Id: Exp$
 */

#include <sidereus/precession.hxx>
#include <sidereus/julian_day.hxx>

namespace sidereus {

  void precession::get_equ_prec2( genesis::proto_geo::point_equ_posn* mean_pos,
   double fromJD, double toJD,
   genesis::proto_geo::point_equ_posn* position )
  {
    long double t = 0.0, t2 = 0.0, t3 = 0.0, A = 0.0, B = 0.0, 
                C = 0.0, zeta = 0.0, eta = 0.0, theta = 0.0, ra = 0.0, 
                dec = 0.0, mean_ra = 0.0, mean_dec = 0.0, T = 0.0, T2 = 0.0;

    // Change original ra and dec to radians.
    mean_ra = GEN_GEOMETRY_DEGTORAD( mean_pos->ra );
    mean_dec = GEN_GEOMETRY_DEGTORAD( mean_pos->dec );

    // Calc t, T, zeta, eta and theta Equ 20.2.
    T = (( long double )( fromJD - JULIAN_DAY_JD2000 )) / 36525.0;
    T *= 1.0 / 3600.0;
    t = (( long double )( toJD - fromJD )) / 36525.0;
    t *= 1.0 / 3600.0;

    T2 = T * T;
    t2 = t * t;
    t3 = t2 *t;

    zeta = ( 2306.2181 + 1.39656 * T - 0.000139 * T2 ) * t + 
           ( 0.30188 - 0.000344 * T ) * t2 + 0.017998 * t3;
    eta = ( 2306.2181 + 1.39656 * T - 0.000139 * T2 ) * t + 
          ( 1.09468 + 0.000066 * T ) * t2 + 0.018203 * t3;
    theta = ( 2004.3109 - 0.85330 * T - 0.000217 * T2 ) * t - 
            ( 0.42665 + 0.000217 * T ) * t2 - 0.041833 * t3;

    zeta = GEN_GEOMETRY_DEGTORAD( zeta );
    eta = GEN_GEOMETRY_DEGTORAD( eta );
    theta = GEN_GEOMETRY_DEGTORAD( theta );

    // Calc A,B,C equ 20.4.
    A = std::cos( mean_dec ) * std::sin( mean_ra + zeta );
    B = std::cos( theta ) * std::cos( mean_dec ) * 
        std::cos( mean_ra + zeta ) - std::sin( theta ) * 
        std::sin( mean_dec );
    C = std::sin( theta ) * std::cos( mean_dec ) * 
        std::cos( mean_ra + zeta ) + 
        std::cos( theta ) * std::sin( mean_dec );

    ra = std::atan2( A, B ) + eta;

    // Check for object near celestial pole.
    if( mean_dec > ( 0.4 * M_PI ) || mean_dec < ( -0.4 * M_PI ) ) {
      // Close to pole.
      dec = std::acos( std::sqrt( A * A + B * B ) );

      if( mean_dec < 0. ) {
        dec *= -1; // 0 <= acos() <= PI.
      } else {
        dec = std::asin( C ); // Not close to pole.
      }
    }

    // Change to degrees.
    position->ra = genesis::geometry::range_degrees( 
                    GEN_GEOMETRY_RADTODEG( ra ) );
    position->dec = GEN_GEOMETRY_RADTODEG( dec );
  }

}
