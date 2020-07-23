cmake_minimum_required(VERSION 3.1)

project(Runin VERSION 2.0.0
              LANGUAGES CXX)

#set(CMAKE_CXX_STANDARD 11)

set(CMAKE_CXX_FLAGS "-pthread -g -fPIC -std=gnu++11")

find_package(Threads)


set(RUNIN_HOME ${ITMWORK}/Runin/)
message("Runin home: ${RUNIN_HOME}")

#ITM Enviroment flags
if($ENV{ITM_ENVIRONMENT_LOADED})
	message("###Compiler set to ITM###")
	execute_process(COMMAND tcsh -c "eval-pkg-config --cflags ual-cpp-gnu --cflags itmconstants --cflags xmllib-$ITM_INTEL_OBJECTCODE"
			OUTPUT_VARIABLE shell_script1)	
	execute_process(COMMAND tcsh -c "eval-pkg-config --libs ual-cpp-gnu xmllib-$ITM_INTEL_OBJECTCODE"
			OUTPUT_VARIABLE shell_script2)
	include_directories($ENV{ITM_XMLLIB_DIR}/$ENV{ITM_XMLLIB_VERSION}/$ENV{DATAVERSION}/include/)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -lTreeShr")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -lTdiShr")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -lXTreeShr")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${shell_script1}")
	set(CMAKE_EXE_LINKER_FLAGS_INIT ${shell_script2})
	add_definitions(-DITM_CONSTANTS)

	include_directories("include")
	include_directories("ext/Runaphys/include")
	set(SOURCE_FILES src/runin.cpp
			 src/codeparams.cpp
			 src/cpo_utils.cpp
			 ext/Runaphys/src/critical_field.cpp
			 ext/Runaphys/src/growth_rate.cpp)
	add_library(runin ${SOURCE_FILES})	
elseif($ENV{IMAS_ENVIRONMENT_LOADED})
	message("###Compiler set to IMAS###")
	execute_process(COMMAND tcsh -c "pkg-config --cflags imas-cpp blitz imas-constants-cpp libxml-2.0 xmllib"
			OUTPUT_VARIABLE shell_script1)
	execute_process(COMMAND tcsh -c "pkg-config --libs imas-cpp blitz libxml-2.0 xmllib"
			OUTPUT_VARIABLE shell_script2)
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
else()
	message("###Compiler set to IMAS (no imas-constants)###")
	execute_process(COMMAND tcsh -c "pkg-config --cflags imas-cpp blitz libxml-2.0 xmllib"
			OUTPUT_VARIABLE shell_script1)
	execute_process(COMMAND tcsh -c "pkg-config --libs imas-cpp blitz libxml-2.0 xmllib"
			OUTPUT_VARIABLE shell_script2)
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
endif()