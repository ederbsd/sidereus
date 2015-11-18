/**
 * @file
 *
 * Definitions for an precession.
 *
 * SIDEREUS - Astronomy Librarie
 *
 * Copyright (c) 2009 Ederson de Moura
 *
 * @author Ederson de Moura
 *
 * $Id: Exp$
 */

#ifndef SIDEREUS_PRECESSION_HPP
#define SIDEREUS_PRECESSION_HPP

#include <genesis/geometry.hxx>

namespace sidereus {
  /**
   * Astro Precession.
   */
  class precession {
  public:
    /**
     * Constructor.
     */ 
    precession() {};

    /**
     * Destructor.
     */ 
    ~precession() {};

    /**
     * Calculate the effects of precession on equatorial coordinates, 
     * between arbitary Jxxxx epochs. Use fromJD and toJD parameters 
     * to specify required Jxxxx epochs.
     *
     * @param mean_pos - Mean object position.
     * @param fromJD - Julian day (start).
     * @param toJD - Julian day (end)
     * @param position - Pointer to store new object position
     */
    static void get_equ_prec2( genesis::proto_geo::point_equ_posn* mean_pos, 
                               double fromJD, double toJD, 
                               genesis::proto_geo::point_equ_posn* position );
  };

}

#endif // SIDEREUS_PRECESSION_HPP 
