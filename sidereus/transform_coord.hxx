/**
 * @file
 *
 * Definitions for an transform_coord.
 *
 * SIDEREUS - Astronomy Librarie
 *
 * Copyright (c) 2009 Ederson de Moura
 *
 * @author Ederson de Moura
 *
 * $Id: Exp$
 */

#ifndef SIDEREUS_TRANSFORM_COORD_HPP
#define SIDEREUS_TRANSFORM_COORD_HPP

#include <genesis/geometry.hxx>

namespace sidereus {
  /**
   * Sidereus
   */
  class transform_coord {
  public:
    /**
     * Constructor.
     */
    transform_coord() {};

    /**
     * Destructor.
     */
    ~transform_coord() {};

    /**
     * Transform an objects equatorial coordinates into horizontal 
     * coordinates for the given julian day and observers position.
     *
     * 0 deg azimuth = south, 90 deg = west.
     *
     * @param object - Object coordinates.
     * @param observer - Observer coordinates.
     * @param JD - Julian Day.
     * @param position - Pointer to store new positions.
     */
    void get_hrz_from_equ( genesis::proto_geo::point_equ_posn* object, 
                           genesis::proto_geo::point_lon_lat_posn* observer,
                           double JD,
                           genesis::proto_geo::point_hrz_posn* position );

    /**
     * Calculate horizontal coordinates from equatorial coordinates,
     * using mean sidereal time.
     *
     * @param object - Object coordinates.
     * @param observer - Observer coordinates.
     * @param sidereal - Sidereal Time.
     * @param position - Pointer to store new positions.
     */
    void get_hrz_from_equ_sidereal_time( 
      genesis::proto_geo::point_equ_posn* object, 
      genesis::proto_geo::point_lon_lat_posn* observer, 
      double sidereal,
      genesis::proto_geo::point_hrz_posn* position );

    /**
     * Transform an objects horizontal coordinates into equatorial 
     * coordinates for the given Julian Day and observers position.
     *
     * @param object - Object coordinates.
     * @param observer - Observer coordinates.
     * @param JD - Julian Day.
     * @param position - Pointer to store new position.
     */
    void get_equ_from_hrz( genesis::proto_geo::point_hrz_posn* object, 
                           genesis::proto_geo::point_lon_lat_posn* observer, 
                           double JD,
                           genesis::proto_geo::point_equ_posn* position );

    /**
     * Transform an objects ecliptical coordinates into equatorial
     * coordinates for the given Julian Day.
     *
     * @param object - Object coordinates.
     * @param JD - Julian Day.
     * @param position - Pointer to store new position.
     */
    void get_equ_from_ecl( genesis::proto_geo::point_lon_lat_posn* object, 
                           double JD, 
                           genesis::proto_geo::point_equ_posn* position );

    /**
     * Transform an objects equatorial cordinates into ecliptical 
     * coordinates for the given Julian Day.
     *
     * @param object - Object coordinates.
     * @param JD - Julian Day.
     * @param position - Pointer to store new position.
     */
    void get_ecl_from_equ( genesis::proto_geo::point_equ_posn* object,
                           double JD,
                           genesis::proto_geo::point_lon_lat_posn* position );

    /**
     * Transform an objects rectangular coordinates into ecliptical 
     * coordinates.
     *
     * @param rect - Rectangular coordinates.
     * @param position - Pointer to store new position.
     */
    void get_ecl_from_rect( genesis::proto_geo::point_rect_coord* rect,
                            genesis::proto_geo::point_lon_lat_posn* position );

    /**
     * Transform an object galactic coordinates into B1950 equatorial 
     * coordinate.
     *
     * @param gal - Galactic coordinates.
     * @param equ - B1950 equatorial coordinates.
     */
    void get_equ_from_gal( genesis::proto_geo::point_gal_posn* gal, 
                           genesis::proto_geo::point_equ_posn* equ );

    /**
     * Transform an object galactic coordinates into equatorial
     * coordinate.
     *
     * @param gal - Galactic coordinates.
     * @param equ - J2000 equatorial coordinates.
     */
    void get_equ2000_from_gal( genesis::proto_geo::point_gal_posn* gal, 
                               genesis::proto_geo::point_equ_posn* equ );

    /**
     * Transform an object B1950 equatorial coordinate into 
     * galactic coordinates.
     *
     * @param equ - B1950 equatorial coordinates.
     * @param gal - Galactic coordinates.
     */
    void get_gal_from_equ( genesis::proto_geo::point_equ_posn *equ, 
                           genesis::proto_geo::point_gal_posn* gal );

    /**
     * Transform an object J2000 equatorial coordinate into 
     * galactic coordinates.
     *
     * @param equ - J2000 equatorial coordinates.
     * @param gal - Galactic coordinates.
     */
    void get_gal_from_equ2000( genesis::proto_geo::point_equ_posn* equ, 
                               genesis::proto_geo::point_gal_posn* gal );

  };

}

#endif // ASTRO_TRANSFORM_COORD_HPP
