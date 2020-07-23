cmake_minimum_required(VERSION 3.1)

project(Runin VERSION 2.0.0
              LANGUAGES CXX)

#set(CMAKE_CXX_STANDARD 11)

set(CMAKE_CXX_FLAGS "-pthread -g -fPIC -std=gnu++11")

find_package(Threads)

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

#ITM Enviroment flags
if($ENV{ITM_ENVIRONMENT_LOADED})
	message("###Compiler set to ITM###")
	execute_process(COMMAND tcsh -c "eval-pkg-config --cflags ual-cpp-gnu --cflags itmconstants --cflags xmllib-$ITM_INTEL_OBJECTCODE"
			OUTPUT_VARIABLE shell_script1)	
	string(LENGTH ${shell_script1} str_len)
	math(EXPR str_new_len ${str_len}-1)
	string(SUBSTRING ${shell_script1} 0 ${str_new_len} shell_script4)
	execute_process(COMMAND tcsh -c "eval-pkg-config --libs ual-cpp-gnu xmllib-$ITM_INTEL_OBJECTCODE"
			OUTPUT_VARIABLE shell_script2)
	string(LENGTH ${shell_script2} str_len)
	math(EXPR str_new_len ${str_len}-1)
	string(SUBSTRING ${shell_script2} 0 ${str_new_len} shell_script3)
	message("${shell_script4}")
	message("${shell_script3}")
	include_directories($ENV{ITM_XMLLIB_DIR}/$ENV{ITM_XMLLIB_VERSION}/$ENV{DATAVERSION}/include/)
	#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -lTreeShr")
	#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -lTdiShr")
	#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -lXTreeShr")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DITM_CONSTANTS")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${shell_script4}")
	set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${shell_script3}")
	include_directories("include")
	include_directories("ext/Runaphys/include")
	set(SOURCE_FILES src/runin.cpp
			 src/codeparams.cpp
			 src/cpo_utils.cpp
			 ext/Runaphys/src/critical_field.cpp
			 ext/Runaphys/src/growth_rate.cpp)
	add_library(runin ${SOURCE_FILES})	
	if(TESTING_ENABLED)
		set(TEST_SRC_FILES test/test_cpo.cpp)
		add_executable(RuninTests ${TEST_SRC_FILES})
		target_link_libraries(RuninTests runin gtest_main pthread)
	endif()
elseif($ENV{IMAS_ENVIRONMENT_LOADED})
	message("###Compiler set to IMAS###")
	execute_process(COMMAND tcsh -c "pkg-config --cflags imas-cpp blitz imas-constants-cpp libxml-2.0 xmllib"
			OUTPUT_VARIABLE shell_script1)
	string(LENGTH ${shell_script1} str_len)
	math(EXPR str_new_len ${str_len}-1)
	string(SUBSTRING ${shell_script1} 0 ${str_new_len} shell_script3)
	execute_process(COMMAND tcsh -c "pkg-config --libs imas-cpp blitz libxml-2.0 xmllib"
			OUTPUT_VARIABLE shell_script2)
	string(LENGTH ${shell_script2} str_len2)
	math(EXPR str_new_len2 ${str_len2}-1)
	string(SUBSTRING ${shell_script2} 0 ${str_new_len2} shell_script4)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${shell_script3}")
	set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${shell_script4}")
	message("${shell_script3}")
	message("${shell_script4}")
	set(SOURCE_FILES src/runin_imas.cpp
			 src/codeparams_imas.cpp
			 src/ids_utils.cpp
			 ext/Runaphys/src/critical_field.cpp
			 ext/Runaphys/src/growth_rate.cpp)
	include_directories("include")
	include_directories("ext/Runaphys/include")
	add_library(runin_imas ${SOURCE_FILES})
	if(TESTING_ENABLED)
		set(TEST_SRC_FILES test/test_ids.cpp)
		add_executable(RuninTests ${TEST_SRC_FILES})
		target_link_libraries(RuninTests runin_imas gtest_main pthread)
	endif()
else()
	message("###Compiler set to IMAS (no imas-constants)###")
	execute_process(COMMAND tcsh -c "pkg-config --cflags imas-cpp blitz libxml-2.0 xmllib"
			OUTPUT_VARIABLE shell_script1)
	string(LENGTH ${shell_script1} str_len)
	math(EXPR str_new_len ${str_len}-1)
	string(SUBSTRING ${shell_script1} 0 ${str_new_len} shell_script3)
	execute_process(COMMAND tcsh -c "pkg-config --libs imas-cpp blitz libxml-2.0 xmllib"
			OUTPUT_VARIABLE shell_script2)
	string(LENGTH ${shell_script2} str_len)
	math(EXPR str_new_len ${str_len}-1)
	string(SUBSTRING ${shell_script2} 0 ${str_new_len} shell_script3)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${shell_script1}")
	set(CMAKE_EXE_LINKER_FLAGS_INIT "${shell_script2}")
	set(SOURCE_FILES src/runin_imas.cpp
			 src/codeparams_imas.cpp
			 src/ids_utils.cpp
			 ext/Runaphys/src/critical_field.cpp
			 ext/Runaphys/src/growth_rate.cpp)
	include_directories("include")
	include_directories("ext/Runaphys/include")
	add_library(runin_imas ${SOURCE_FILES})
	if(TESTING_ENABLED)
		set(TEST_SRC_FILES test/test_ids.cpp)
		add_executable(RuninTests ${TEST_SRC_FILES})
		target_link_libraries(RuninTests runin gtest_main pthread)
	endif()
endif()