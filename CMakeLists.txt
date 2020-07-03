cmake_minimum_required(VERSION 3.1)

project(Runin VERSION 2.0.0
              LANGUAGES CXX)

#set(CMAKE_CXX_STANDARD 11)

set(CMAKE_CXX_FLAGS "-pthread -g -fPIC -std=gnu++11")

find_package(Threads)


set(RUNIN_HOME ${ITMWORK}/Runin/)
message("Runin home: ${RUNIN_HOME}")

if($ENV{ITM_ENVIRONMENT_LOADED})
	execute_process(COMMAND tcsh -c "eval-pkg-config --cflags ual-cpp-gnu --cflags itmconstants --cflags xmllib-$ITM_INTEL_OBJECTCODE"
			OUTPUT_VARIABLE git_ver)
	
	execute_process(COMMAND tcsh -c "eval-pkg-config --libs ual-cpp-gnu xmllib-$ITM_INTEL_OBJECTCODE"
			OUTPUT_VARIABLE git_ver2)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DITM_CONSTANTS  " )
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -I$ENV{ITM_XMLLIB_DIR}/$ENV{ITM_XMLLIB_VERSION}/$ENV{DATAVERSION}/include/")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -lTreeShr")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -lTdiShr")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -lXTreeShr")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${git_ver}")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${git_ver3}")
	set(CMAKE_EXE_LINKER_FLAGS_INIT ${git_ver2})
	#add_compile_options(-DITM_CONSTANTS APPEND -I$ENV{ITM_XMLLIB_DIR}/$ENV{ITM_XMLLIB_VERSION}/$ENV{DATAVERSION}/include/ APPEND ${git_ver} APPEND ${git_ver3} APPEND -lTreeShr -lTdiShr -lXTreeShr)
	set(SOURCE_FILES src/runin.cpp
			 src/codeparams.cpp
			 src/cpo_utils.cpp
			 ext/Runaphys/src/critical_field.cpp
			 ext/Runaphys/src/growth_rate.cpp)
	add_library(runin ${SOURCE_FILES})		
endif()