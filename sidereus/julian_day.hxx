/**
 * @file
 *
 * Definitions for an julian_day.
 *
 * SIDEREUS - Astronomy Librarie
 *
 * Copyright (c) 2009 Ederson de Moura
 *
 * @author Ederson de Moura
 *
 * $Id: Exp$
 */

#ifndef SIDEREUS_JULIAN_DAY_HPP
#define SIDEREUS_JULIAN_DAY_HPP

#include <genesis/calendar.hxx>
#include <genesis/datetime.hxx>

namespace sidereus {
  /**
   * Astro Calendar Julian Day.
   */ 
  class julian_day : public genesis::calendar, public genesis::datetime {
  public:
    /**
     * Constructor.
     */ 
    julian_day() {};

    /**
     * Destructor.
     */ 
    ~julian_day() {};

    /**
     * Calculate the Julian Day from a calendar day.
     * Valid for positive and negative years but not for negative JD.
     *
     * @param date - Date required.
     * @return Julian date.
     */ 
    double get_julian_day( genesis::proto_datetime::date* date );

    /**
     * Calculate the day of the week. 
     * Returns 0 = Sunday .. 6 = Saturday.
     *
     * @param date - Date required.
     * @return Day of the week.
     */
    size_t get_day_of_week( genesis::proto_datetime::date* date );

    /**
     * Calculate the Julian day (UT) from the local system time.
     *
     * @return Julian day (UT).
     */ 
    double get_julian_from_sys();

    /**
     * Converts a ln_date (UT) to a ln_zonedate (local time).
     *
     * @param date - Pointer to date.
     * @param zonedate - Pointer to zonedate.
     * @param gmtoff - Offset in seconds from UT.
     */ 
    void date_to_zonedate( genesis::proto_datetime::date* date, 
                           genesis::proto_datetime::zonedate* zonedate, 
                           long gmtoff );

    /**
     * Converts a ln_zonedate (local time) to a ln_date (UT).
     *
     * @param zonedate - Pointer to zonedate.
     * @param date -  Pointer to date.
     */ 
    void zonedate_to_date( genesis::proto_datetime::zonedate* zonedate, 
                           genesis::proto_datetime::date* date );

  private:
    /**
     * Calculate Julian day (UT) from zone date.
     *
     * @param zonedate - Local date.
     * @return Julian day (UT).
     */
    double get_julian_local_date( genesis::proto_datetime::zonedate* zonedate );

    /**
     * Calculate the zone date from the Julian day (UT). Get zone info from
     * system using either "timezone" or tm_gmtoff fields.
     *
     * @param JD - Julian day.
     * @param zonedate - Pointer to new calendar date.
     */ 
    void get_local_date( double JD, genesis::proto_datetime::zonedate* zonedate );

    /**
     * Calculate the julian day from the a MPC packed date.
     * See http://cfa-www.harvard.edu/iau/info/PackedDates.html for info.
     *
     * @param mpc_date - MPC date.
     * @return Julian day.
     */ 
    double get_julian_from_mpc( char* mpc_date );
  };

// 1.1.2000 Julian Day & others.
#define JULIAN_DAY_JD2000 2451545.0
#define JULIAN_DAY_JD2050 2469807.50

#define JULIAN_DAY_B1900 2415020.3135
#define JULIAN_DAY_B1950 2433282.4235

}

#endif // SIDEREUS_JULIAN_DAY_HPP
