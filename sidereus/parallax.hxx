/**
 * @file
 *
 * Definitions for an parallax.
 *
 * SIDEREUS - Astronomy Librarie
 *
 * Copyright (c) 2009 Ederson de Moura
 *
 * @author Ederson de Moura
 *
 * $Id: Exp$
 */

#ifndef SIDEREUS_PARALLAX_HPP
#define SIDEREUS_PARALLAX_HPP

#include <genesis/geometry.hxx>

namespace sidereus {
  /**
   * Astro Parallax.
   */
  class parallax {
  public:
    /**
     * Calculate body parallax, which is need to calculate topocentric
     * position of the body.
     *
     * @param object - Object geocentric coordinates.
     * @param au_distance - Distance of object from Earth in AU.
     * @param observer - Geographics observer positions.
     * @param height - Observer height in m.
     * @param JD - Julian day of observation.
     * @param parallax - RA and DEC parallax.
     */
    static void 
     get( genesis::proto_geo::point_equ_posn* object, 
          double au_distance,
          genesis::proto_geo::point_lon_lat_posn* observer,
          double height, double JD, 
          genesis::proto_geo::point_equ_posn* parallax );

    /**
     * Calculate body parallax, which is need to calculate topocentric 
     * position of the body.
     *
     * Uses hour angle as time reference handy in case we already compute it.
     *
     * @param object - Object geocentric coordinates.
     * @param au_distance - Distance of object from Earth in AU.
     * @param observer - Geographics observer positions.
     * @param height - Observer height in m.
     * @param H - Hour angle of object in hours.
     * @param parallax - RA and DEC parallax.
     */
    static void
     get_ha( genesis::proto_geo::point_equ_posn* object,
             double au_distance,
             genesis::proto_geo::point_lon_lat_posn* observer,
             double height,
             double H,
             genesis::proto_geo::point_equ_posn* parallax );

  private:
    /**
     *
     */
    static void 
     get_topocentric( genesis::proto_geo::point_lon_lat_posn* observer, 
                      double height, double* ro_sin, double* ro_cos );
  };

}

#endif // SIDEREUS_PARALLAX_HPP 
