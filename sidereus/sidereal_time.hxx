/**
 * @file
 *
 * Definitions for an sidereal_time.
 *
 * SIDEREUS - Astronomy Librarie
 *
 * Copyright (c) 2009 Ederson de Moura
 *
 * @author Ederson de Moura
 *
 * $Id: Exp$
 */

#ifndef  SIDEREUS_SIDEREAL_TIME_HPP
#define  SIDEREUS_SIDEREAL_TIME_HPP

#include <sidereus/julian_day.hxx>
#include <sidereus/nutation.hxx>

namespace sidereus {
  /**
   * Sidereus Sidereal Time.
   */
  class sidereal_time : public nutation, public julian_day {
  public:
    /**
     * Constructor.
     */ 
    sidereal_time() {};

    /**
     * Destructor.
     */ 
    ~sidereal_time() {};

    /**
     * Calculate the mean sidereal time at the meridian of
     * Greenwich of a given date.
     *
     * @param JD - Julian day.
     * @return Mean sidereal time.
     */ 
    static double get_mean( double JD );

    /**
     * Calculate the apparent sidereal time at the meridian of 
     * Greenwich of a given date.
     *
     * @param JD - Julian day.
     * @return Apparent sidereal time (hours).
     */ 
    static double get_apparent( double JD );

  };

}

#endif // SIDEREUS_SIDEREAL_TIME_HPP
