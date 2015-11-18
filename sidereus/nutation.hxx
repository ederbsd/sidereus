/**
 * @file
 *
 * Definitions for an nutation.
 *
 * SIDEREUS - Astronomy Algoritms
 *
 * Copyright (c) 2009 Ederson de Moura
 *
 * @author Ederson de Moura
 *
 * $Id: Exp$
 */

#ifndef SIDEREUS_NUTATION_HPP
#define SIDEREUS_NUTATION_HPP

#include <genesis/datetime.hxx>
#include <genesis/geometry.hxx>

namespace sidereus {
  /**
   * Sidereus Nutation.
   */
  class nutation : public genesis::dynamical_time {
  public:
    /**
     * Contains Nutation in longitude, obliquity and 
     * ecliptic obliquity.
     */ 
    typedef struct nutation_ {
      double longitude; ///< Nutation in longitude.
      double obliquity; ///< Nutation in obliquity.
      double ecliptic;  ///< Obliquity of the ecliptic.
    } nut;

    /**
     * Constructor.
     *
     * Nutation is a period oscillation of the Earths rotational axis 
     * around it's mean position. All angles are expressed in degrees.
     * Calculate nutation of longitude and obliquity in degrees from 
     * Julian Ephemeris Day.
     *
     * @param JD - Julian day.
     * @param n - Pointer to store nutation.
     */ 
    explicit nutation( double JD, nut* n );

    /**
     * Constructor.
     */ 
    nutation() {};

    /**
     * Destructor.
     */ 
    ~nutation() {};

  };

}

#endif // SIDEREUS_NUTATION_HPP
