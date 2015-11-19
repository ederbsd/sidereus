include_directories("${CMAKE_SOURCE_DIR}")

add_library(sidereus SHARED
  sidereus.cxx
  sidereus.hxx
  parallax.cxx
  parallax.hxx
  precession.cxx
  precession.hxx
  sidereal_time.cxx
  sidereal_time.hxx
  transform_coord.cxx
  transform_coord.hxx
  nutation.cxx
  nutation.hxx
  julian_day.cxx
  julian_day.hxx
)

if("${CMAKE_SYSTEM_NAME}" STREQUAL "Linux")
  target_link_libraries(sidereus dl)
endif()

target_link_libraries(sidereus pthread)
target_link_libraries(sidereus rt)
#target_link_libraries(sidereus genesis)
target_link_libraries(sidereus /usr/local/lib/libgenesis.so)

install(TARGETS sidereus
  RUNTIME DESTINATION "lib"
  ARCHIVE DESTINATION "lib"
  LIBRARY DESTINATION "lib")

install(FILES sidereus/sidereus.hpp
  DESTINATION "include/sidereus")

