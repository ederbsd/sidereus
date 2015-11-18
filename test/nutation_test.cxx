/**
 * @file
 *
 * Tests for an nutation class.
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

#include <sidereus/nutation.hxx>

#include <genesis/logger.hxx>
#include <genesis/tests.hxx>

// Test for class Nutation.
static int nutation_test( void )
{
  GEN_MSG( "Tests for class Nutation.\n" );

  double JDE = 0.0; 
  double JD = 0.0;

  sidereus::nutation::nut nutation;
  
  // Set for tests.      
  int failed = 0;

  JD = 2446895.5;
  JDE = sidereus::nutation().dynamical_time::get_jde( JD );

  sidereus::nutation( JD, &nutation );

  failed += GEN_TEST_RESULT( "(Nutation) longitude (deg) for JD 2446895.5", 
                             nutation.longitude, -0.00100561, 0.00000001 );
  failed += GEN_TEST_RESULT( "(Nutation) obliquity (deg) for JD 2446895.5", 
                             nutation.obliquity, 0.00273297, 0.00000001 );
  failed += GEN_TEST_RESULT( "(Nutation) ecliptic (deg) for JD 2446895.5", 
                             nutation.ecliptic, 23.44367936, 0.00000001 );

  GEN_MSG( "End: Nutation.\n" );

  return failed;
}

int main( int argc, char* argv[] ) 
{
  int failed = 0;

  failed += nutation_test();

  GEN_TEST_PRINT_RESULT( "nutation", failed );

  return( failed > 0 );
}
