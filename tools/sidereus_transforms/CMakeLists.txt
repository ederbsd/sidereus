include_directories("${CMAKE_SOURCE_DIR}")
add_executable(sidereus_transforms sidereus_transforms.cxx)
target_link_libraries(sidereus_transforms sidereus)
install(TARGETS sidereus_transforms DESTINATION "bin")

