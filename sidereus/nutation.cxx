/**
 * @file
 *
 * Implementation for an nutation.
 *
 * SIDEREUS - Astronomy Librarie
 *
 * Copyright (c) 2009 Ederson de Moura
 *
 * @author Ederson de Moura
 *
 * $Id: Exp$
 */

#include <sidereus/nutation.hxx>

#include <cmath>

static const int NUTATION_TERMS = 63;
static const double NUTATION_EPOCH_THRESHOLD = 0.1;

namespace sidereus {

  struct nutation_arguments {
    double D;
    double M;
    double MM;
    double F;
    double O;
  };

  struct nutation_coefficients {
    double longitude1;
    double longitude2;
    double obliquity1;
    double obliquity2;
  };

  const static struct nutation_arguments arguments[NUTATION_TERMS] = {
    {0.0,	0.0,	0.0,	0.0,	1.0},
    {-2.0,	0.0,	0.0,	2.0,	2.0},
    {0.0,	0.0,	0.0,	2.0,	2.0},
    {0.0,	0.0,	0.0,	0.0,	2.0},
    {0.0,	1.0,	0.0,	0.0,	0.0},
    {0.0,	0.0,	1.0,	0.0,	0.0},
    {-2.0,	1.0,	0.0,	2.0,	2.0},
    {0.0,	0.0,	0.0,	2.0,	1.0},
    {0.0,	0.0,	1.0,	2.0,	2.0},
    {-2.0,	-1.0,	0.0,	2.0,	2.0},
    {-2.0,	0.0,	1.0,	0.0,	0.0},
    {-2.0,	0.0,	0.0,	2.0,	1.0},
    {0.0,	0.0,	-1.0,	2.0,	2.0},
    {2.0,	0.0,	0.0,	0.0,	0.0},
    {0.0,	0.0,	1.0,	0.0,	1.0},
    {2.0,	0.0,	-1.0,	2.0,	2.0},
    {0.0,	0.0,	-1.0,	0.0,	1.0},
    {0.0,	0.0,	1.0,	2.0,	1.0},
    {-2.0,	0.0,	2.0,	0.0,	0.0},
    {0.0,	0.0,	-2.0,	2.0,	1.0},
    {2.0,	0.0,	0.0,	2.0,	2.0},
    {0.0,	0.0,	2.0,	2.0,	2.0},
    {0.0,	0.0,	2.0,	0.0,	0.0},
    {-2.0,	0.0,	1.0,	2.0,	2.0},
    {0.0,	0.0,	0.0,	2.0,	0.0},
    {-2.0,	0.0,	0.0,	2.0,	0.0},
    {0.0,	0.0,	-1.0,	2.0,	1.0},
    {0.0,	2.0,	0.0,	0.0,	0.0},
    {2.0,	0.0,	-1.0,	0.0,	1.0},
    {-2.0,	2.0,	0.0,	2.0,	2.0},
    {0.0,	1.0,	0.0,	0.0,	1.0},
    {-2.0,	0.0,	1.0,	0.0,	1.0},
    {0.0,	-1.0,	0.0,	0.0,	1.0},
    {0.0,	0.0,	2.0,	-2.0,	0.0},
    {2.0,	0.0,	-1.0,	2.0,	1.0},
    {2.0,	0.0,	1.0,	2.0,	2.0},
    {0.0,	1.0,	0.0,	2.0,	2.0},
    {-2.0,	1.0,	1.0,	0.0,	0.0},
    {0.0,	-1.0,	0.0,	2.0,	2.0},
    {2.0,	0.0,	0.0,	2.0,	1.0},
    {2.0,	0.0,	1.0,	0.0,	0.0},
    {-2.0,	0.0,	2.0,	2.0,	2.0},
    {-2.0,	0.0,	1.0,	2.0,	1.0},
    {2.0,	0.0,	-2.0,	0.0,	1.0},
    {2.0,	0.0,	0.0,	0.0,	1.0},
    {0.0,	-1.0,	1.0,	0.0,	0.0},
    {-2.0,	-1.0,	0.0,	2.0,	1.0},
    {-2.0,	0.0,	0.0,	0.0,	1.0},
    {0.0,	0.0,	2.0,	2.0,	1.0},
    {-2.0,	0.0,	2.0,	0.0,	1.0},
    {-2.0,	1.0,	0.0,	2.0,	1.0},
    {0.0,	0.0,	1.0,	-2.0,	0.0},
    {-1.0,	0.0,	1.0,	0.0,	0.0},
    {-2.0,	1.0,	0.0,	0.0,	0.0},
    {1.0,	0.0,	0.0,	0.0,	0.0},
    {0.0,	0.0,	1.0,	2.0,	0.0},
    {0.0,	0.0,	-2.0,	2.0,	2.0},
    {-1.0,	-1.0,	1.0,	0.0,	0.0},
    {0.0,	1.0,	1.0,	0.0,	0.0},
    {0.0,	-1.0,	1.0,	2.0,	2.0},
    {2.0,	-1.0,	-1.0,	2.0,	2.0},
    {0.0,	0.0,	3.0,	2.0,	2.0},
    {2.0,	-1.0,	0.0,	2.0,	2.0}
  };

  const static struct nutation_coefficients coefficients[NUTATION_TERMS] = {
    {-171996.0,	-174.2,	92025.0,8.9},
    {-13187.0,	-1.6,  	5736.0,	-3.1},
    {-2274.0, 	 0.2,  	977.0,	-0.5},
    {2062.0,   	0.2,    -895.0,    0.5},
    {1426.0,    -3.4,    54.0,    -0.1},
    {712.0,    0.1,    -7.0,    0.0},
    {-517.0,    1.2,    224.0,    -0.6},
    {-386.0,    -0.4,    200.0,    0.0},
    {-301.0,    0.0,    129.0,    -0.1},
    {217.0,    -0.5,    -95.0,    0.3},
    {-158.0,    0.0,    0.0,    0.0},
    {129.0,	0.1,	-70.0,	0.0},
    {123.0,	0.0,	-53.0,	0.0},
    {63.0,	0.0,	0.0,	0.0},
    {63.0,	1.0,	-33.0,	0.0},
    {-59.0,	0.0,	26.0,	0.0},
    {-58.0,	-0.1,	32.0,	0.0},
    {-51.0,	0.0,	27.0,	0.0},
    {48.0,	0.0,	0.0,	0.0},
    {46.0,	0.0,	-24.0,	0.0},
    {-38.0,	0.0,	16.0,	0.0},
    {-31.0,	0.0,	13.0,	0.0},
    {29.0,	0.0,	0.0,	0.0},
    {29.0,	0.0,	-12.0,	0.0},
    {26.0,	0.0,	0.0,	0.0},
    {-22.0,	0.0,	0.0,	0.0},
    {21.0,	0.0,	-10.0,	0.0},
    {17.0,	-0.1,	0.0,	0.0},
    {16.0,	0.0,	-8.0,	0.0},
    {-16.0,	0.1,	7.0,	0.0},
    {-15.0,	0.0,	9.0,	0.0},
    {-13.0,	0.0,	7.0,	0.0},
    {-12.0,	0.0,	6.0,	0.0},
    {11.0,	0.0,	0.0,	0.0},
    {-10.0,	0.0,	5.0,	0.0},
    {-8.0,	0.0,	3.0,	0.0},
    {7.0,	0.0,	-3.0,	0.0},
    {-7.0,	0.0,	0.0,	0.0},
    {-7.0,	0.0,	3.0,	0.0},
    {-7.0,	0.0,	3.0,	0.0},
    {6.0,	0.0,	0.0,	0.0},
    {6.0,	0.0,	-3.0,	0.0},
    {6.0,	0.0,	-3.0,	0.0},
    {-6.0,	0.0,	3.0,	0.0},
    {-6.0,	0.0,	3.0,	0.0},
    {5.0,	0.0,	0.0,	0.0},
    {-5.0,	0.0,	3.0,	0.0},
    {-5.0,	0.0,	3.0,	0.0},
    {-5.0,	0.0,	3.0,	0.0},
    {4.0,	0.0,	0.0,	0.0},
    {4.0,	0.0,	0.0,	0.0},
    {4.0,	0.0,	0.0,	0.0},
    {-4.0,	0.0,	0.0,	0.0},
    {-4.0,	0.0,	0.0,	0.0},
    {-4.0,	0.0,	0.0,	0.0},
    {3.0,	0.0,	0.0,	0.0},
    {-3.0,	0.0,	0.0,	0.0},
    {-3.0,	0.0,	0.0,	0.0},
    {-3.0,	0.0,	0.0,	0.0},
    {-3.0,	0.0,	0.0,	0.0},
    {-3.0,	0.0,	0.0,	0.0},
    {-3.0,	0.0,	0.0,	0.0},
    {-3.0,	0.0,	0.0,	0.0}
  };

  // Cache values.
  static long double c_JD = 0.0, c_longitude = 0.0, 
                     c_obliquity = 0.0, c_ecliptic = 0.0;

  nutation::nutation( double JD, nut* n )
  {  
    long double D = 0.0, M = 0.0, MM = 0.0, 
                F = 0.0, O = 0.0, T = 0.0, 
                T2 = 0.0, T3 = 0.0, JDE = 0.0;

    long double coeff_sine = 0.0,
                coeff_cos = 0.0;

    volatile register int i asm ("eax");
    i = 0;

    // Should we bother recalculating nutation.
    if( std::fabs( JD - c_JD ) > NUTATION_EPOCH_THRESHOLD ) {
      // Set the new epoch.
      c_JD = JD;

      // Set ecliptic.
      c_ecliptic = 23.0 + 26.0 / 60.0 + 27.407 / 3600.0;

      // Get julian ephemeris day.
      JDE = dynamical_time::get_jde( JD );

      // Calc T.
      T = ( JDE - 2451545.0 ) / 36525;
      T2 = T * T;
      T3 = T2 * T;

      // Calculate D,M,M',F and Omega.
      D = 297.85036 + 445267.111480 * T - 0.0019142 * T2 + T3 / 189474.0;
      M = 357.52772 + 35999.050340 * T - 0.0001603 * T2 - T3 / 300000.0;
      MM = 134.96298 + 477198.867398 * T + 0.0086972 * T2 + T3 / 56250.0;
      F = 93.2719100 + 483202.017538 * T - 0.0036825 * T2 + T3 / 327270.0;
      O = 125.04452 - 1934.136261 * T + 0.0020708 * T2 + T3 / 450000.0;
	
      // Convert to radians.
      D = GEN_GEOMETRY_DEGTORAD( D );
      M = GEN_GEOMETRY_DEGTORAD( M );
      MM = GEN_GEOMETRY_DEGTORAD( MM );
      F = GEN_GEOMETRY_DEGTORAD( F );
      O = GEN_GEOMETRY_DEGTORAD( O );

      // Calc sum of terms in table 21A.
      for( i = 0; i < NUTATION_TERMS; i++ ) {
        // Calc coefficients of sine and cosine.
        coeff_sine = ( coefficients[i].longitude1 + 
                     ( coefficients[i].longitude2 * T ) );
	coeff_cos = ( coefficients[i].obliquity1 + 
                    ( coefficients[i].obliquity2 * T ) );
			
	// Sum the arguments.
	if( arguments[i].D != 0 ) {
          c_longitude += coeff_sine * ( std::sin( arguments[i].D * D ) );
	  c_obliquity += coeff_cos * ( std::cos( arguments[i].D * D ) );
        }

	if( arguments[i].M != 0 ) {
          c_longitude += coeff_sine * ( std::sin( arguments[i].M * M ) );
	  c_obliquity += coeff_cos * ( std::cos( arguments[i].M * M ) );
	}

        if( arguments[i].MM != 0 ) {
          c_longitude += coeff_sine * ( std::sin( arguments[i].MM * MM ) );
	  c_obliquity += coeff_cos * ( std::cos( arguments[i].MM * MM ) );
        }

        if( arguments[i].F != 0 ) {
          c_longitude += coeff_sine * ( std::sin( arguments[i].F * F ) );
	  c_obliquity += coeff_cos * ( std::cos( arguments[i].F * F ) );
	}

        if( arguments[i].O != 0 ) {
          c_longitude += coeff_sine * ( std::sin( arguments[i].O * O ) );
	  c_obliquity += coeff_cos * ( std::cos( arguments[i].O * O ) );
	}
      }    

      // Change to arcsecs.
      c_longitude /= 10000;
      c_obliquity /= 10000;

      // Change to degrees.
      c_longitude /= ( 60 * 60 );
      c_obliquity /= ( 60 * 60 );
      c_ecliptic += c_obliquity;

    }

    // Return results.
    n->longitude = c_longitude;
    n->obliquity = c_obliquity;
    n->ecliptic = c_ecliptic;
  }

}
