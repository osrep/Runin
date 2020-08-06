enable_testing()

#GTEST
configure_file(${PROJECT_SOURCE_DIR}/cmake/GoogleTestDownload.cmake googletest-download/CMakeLists.txt)

execute_process(
  COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
  RESULT_VARIABLE result
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/googletest-download )
if(result)
  message(FATAL_ERROR "CMake step for googletest failed: ${result}")
endif()
execute_process(
  COMMAND ${CMAKE_COMMAND} --build .
  RESULT_VARIABLE result
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/googletest-download )
if(result)
  message(FATAL_ERROR "Build step for googletest failed: ${result}")
endif()

# Add googletest directly to our build. This defines
# the gtest and gtest_main targets.
add_subdirectory(${CMAKE_CURRENT_BINARY_DIR}/googletest-src
                 ${CMAKE_CURRENT_BINARY_DIR}/googletest-build
                 EXCLUDE_FROM_ALL)

if($ENV{ITM_ENVIRONMENT_LOADED})
	set(TEST_SRC_FILES test_cpo.cpp)
	add_executable(RuninTests ${TEST_SRC_FILES})
	target_link_libraries(RuninTests runin gtest_main pthread)
else()
	set(TEST_SRC_FILES test_ids.cpp)
	add_executable(RuninTests ${TEST_SRC_FILES})
	target_link_libraries(RuninTests runin_imas gtest_main pthread)
endif()
