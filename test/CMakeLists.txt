include_directories("${CMAKE_SOURCE_DIR}")

#sidereus_test.cxx
#parallax_test.cxx
#nutation_test.cxx
#julian_day_test.cxx
#sidereal_time_test.cxx
#transform_coord_test.cxx

# Sidereus test.
add_executable(sidereus_test sidereus_test.cxx)
target_link_libraries(sidereus_test sidereus)
add_test(sidereus_test sidereus_test)

# Parallax test.
add_executable(parallax_test parallax_test.cxx)
target_link_libraries(parallax_test sidereus)
add_test(parallax_test parallay_test)

# Nutation test.
add_executable(nutation_test nutation_test.cxx)
target_link_libraries(nutation_test sidereus)
add_test(nutation_test nutation_test)

# Julian day test.
add_executable(julian_day_test julian_day_test.cxx)
target_link_libraries(julian_day_test sidereus)
add_test(julian_day_test julian_day_test)

# Sidereal time test.
add_executable(sidereal_time_test sidereal_time_test.cxx)
target_link_libraries(sidereal_time_test sidereus)
add_test(sidereal_time_test sidereal_time_test)

# Transformation coord test.
add_executable(transform_coord_test transform_coord_test.cxx)
target_link_libraries(transform_coord_test sidereus)
add_test(transform_coord_test transform_coord_test)

# Convex hull test.
#add_executable(convex_hull_test convex_hull_test.cxx)
#target_link_libraries(convex_hull_test genesis)
#add_test(convex_hull_test convex_hull_test)


