/**
 * @file
 *
 * Transform Coord.
 *
 * Copyright (c) 2009 Ederson de Moura
 *
 * @author Ederson de Moura
 *
 * $Id: Exp$
 */

#include <sidereus/transform_coord.hxx>
#include <sidereus/julian_day.hxx>

#include <genesis/application.hxx>
#include <genesis/logger.hxx>
#include <genesis/string_util.hxx>

class sidereus_transforms : public genesis::application {
  public:
    /// Constructor.
    sidereus_transforms() {};

  private:
    // Override.
    int main( int argc, char* argv[] );

    /// Print usage message to console.
    void usage();

    /// Print version message to console.
    void version() const;

  protected:
    void hrz_to_hhrz( genesis::proto_geo::point_hrz_posn* pos,
                      genesis::proto_geo::point_nh_hrz_posn* hpos );

    void equ_to_hequ( genesis::proto_geo::point_equ_posn* pos,
                      genesis::proto_geo::point_nh_equ_posn* hpos );

    /**
     * Computing distances between points on Earth.
     */
    void compute_trans();

    /// Transformation of Coordinates.
    sidereus::transform_coord trans_;

    /// Julian day.
    sidereus::julian_day julian_;
};

void sidereus_transforms::usage()
{
  add_usage( "Description:" );
  add_usage( "   This application ....\n" );
  add_usage( "Usage: " );
  add_usage( "   [<OPTIONS>] [<LAT1>] [<LON1>] [<LAT2>] [<LON2>]\n" );
  add_usage( "Options:" );
  print_usage();
}

void sidereus_transforms::version() const
{
  std::cout << "\n" << genesis::string_util::to_uppercase( name() )
            << ":\n\n"
            << "      Version " << VERSION << "." << " Part of the "
            << genesis::string_util::to_uppercase( PACKAGE )
            << " package.\n\n"
            << "Copyright (C) 2009 "
            << "Ederson de Moura.\n"
            << std::endl;
}

void sidereus_transforms::hrz_to_hhrz( genesis::proto_geo::point_hrz_posn* pos,
 genesis::proto_geo::point_nh_hrz_posn* hpos )
{
  genesis::datetime::deg_to_dms( pos->alt, &hpos->alt );
  genesis::datetime::deg_to_dms( pos->az, &hpos->az );
}

void sidereus_transforms::equ_to_hequ( genesis::proto_geo::point_equ_posn* pos,
 genesis::proto_geo::point_nh_equ_posn* hpos )
{
  genesis::datetime::deg_to_hms( pos->ra, &hpos->ra );
  genesis::datetime::deg_to_dms( pos->dec, &hpos->dec );
}

void sidereus_transforms::compute_trans()
{
  genesis::proto_geo::point_nh_equ_posn hobject, hequ;
  genesis::proto_geo::point_nh_lonlat_posn hobserver;
  genesis::proto_geo::point_equ_posn object, equ;
  genesis::proto_geo::point_hrz_posn hrz;
  genesis::proto_geo::point_nh_hrz_posn hhrz;
  genesis::proto_geo::point_lon_lat_posn observer;

  double JD = 0.0;
  genesis::proto_datetime::date date;

  // Observers position. 
  hobserver.lon.degrees = -5;
  hobserver.lon.minutes = 36;
  hobserver.lon.seconds = 30;
  hobserver.lat.degrees = 42;
  hobserver.lat.minutes = 35;
  hobserver.lat.seconds = 40;

  // Alnilam.
  hobject.ra.hours = 5;
  hobject.ra.minutes = 36;
  hobject.ra.seconds = 27;
  hobject.dec.neg = 1;
  hobject.dec.degrees = 1;
  hobject.dec.minutes = 12;
  hobject.dec.seconds = 0;

  // UT date and time.
  date.years = 2004;
  date.months = 4;
  date.days = 25;
  date.hours = 12;
  date.minutes = 18;
  date.seconds = 49;

  JD = julian_.get_julian_day( &date );

  genesis::geometry::hequ_to_equ( &hobject, &object );
  genesis::geometry::hlnlat_to_lnlat( &hobserver, &observer );

  GEN_MSG( "\nComputing Altitude and Azimuth\n" );

  trans_.get_hrz_from_equ( &object, &observer, JD, &hrz );

  fprintf( stdout, "( Alnilam ) Equ to Horiz Altitude: %f\n", hrz.alt );
  fprintf( stdout, "( Alnilam ) Equ to Horiz Azimuth: %f\n", hrz.az );

  hrz_to_hhrz( &hrz, &hhrz );

  fprintf( stdout, "Altitude = %d:%d:%f\n", hhrz.alt.degrees, 
                   hhrz.alt.minutes, hhrz.alt.seconds );

  fprintf( stdout, "Azimuth = %d:%d:%f\n\n", hhrz.az.degrees, 
                   hhrz.az.minutes, hhrz.az.seconds );

  trans_.get_equ_from_hrz( &hrz, &observer, JD, &equ );

  fprintf( stdout, "( Alnilam ) Horiz to Equ Right Ascension: %f\n", equ.ra );
  fprintf( stdout, "( Alnilam ) Horiz to Equ Declination: %f\n", equ.dec );

  equ_to_hequ( &equ, &hequ );

  fprintf( stdout, "Right Ascension = %d:%d:%f\n", hequ.ra.hours, 
                   hequ.ra.minutes, hequ.ra.seconds );

  fprintf( stdout, "Declination = %d:%d:%f\n\n", hequ.dec.degrees, 
                   hequ.dec.minutes, hequ.dec.seconds );
}

int sidereus_transforms::main( int argc, char* argv[] )
{
  set_verbose();

  set_flag( "version", 'v' );

  set_flag( "help", 'h' );
  set_flag( "log", 'l' );

  set_option( "lat1", 'a' );

  bool ok = false;

  process_command_args( argc, argv );

  if( !has_options() ) {
    usage();
    return ok;
  }

  if( get_flag( "version" ) || get_flag( 'v' ) ) {
    version();
    return ok;
  }

  if( get_flag( "help" ) || get_flag( 'h' ) ) {
    usage();
    return ok;
  }

  if( get_flag( "log" ) || get_flag( 'l' ) ) {
    GEN_LOG( "Log Enabled" );
    return ok;
  }

  std::string lat1;
  if( get_value( "lat1" ) != 0 || get_value( 'a' ) != 0 ) {
    lat1 = get_value( 'a' );
  }

  compute_trans();

  return 0;
}

int main( int argc, char* argv[] )
{
  return sidereus_transforms().run( argc, argv );
}
