set(CMAKE_AUTOMOC ON)

include(cmake/qtdeploy.cmake)

find_package(Qt5 COMPONENTS Core Gui Widgets REQUIRED)
find_package(Eigen3 REQUIRED)
#find_package(Boost REQUIRED)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(
		GLOB_RECURSE
		fparser_src
		${CMAKE_CURRENT_SOURCE_DIR}/FParser/fparser.cc # *.cc *.hh
		${CMAKE_CURRENT_SOURCE_DIR}/FParser/fparser.hh
		${CMAKE_CURRENT_SOURCE_DIR}/FParser/fpconfig.hh
		${CMAKE_CURRENT_SOURCE_DIR}/FParser/fpoptimizer.cc
		${CMAKE_CURRENT_SOURCE_DIR}/FParser/extrasrc/*
)

file(
		GLOB_RECURSE
		src
		${CMAKE_CURRENT_SOURCE_DIR}/src/*
		${CMAKE_CURRENT_SOURCE_DIR}/src/BoxFilterConfigurationDialog.h
		${CMAKE_CURRENT_SOURCE_DIR}/src/BoxFilterConfigurationDialog.cpp
)
# message(STATUS ${src})

if (MSVC)
  add_compile_options(/bigobj)
  add_compile_definitions(_CRT_SECURE_NO_WARNINGS)
endif()

# FParser
add_compile_definitions(FP_SUPPORT_COMPLEX_DOUBLE_TYPE)
add_compile_definitions(FP_SUPPORT_OPTIMIZER)

add_executable(${PROJECT_NAME} ${src} ${fparser_src})
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/GeneratedFiles)

target_link_libraries(${PROJECT_NAME} Qt5::Core Qt5::Gui Qt5::Widgets Eigen3::Eigen) # boost::boost)

message(STATUS "Current config ${res}")
windeployqt(${PROJECT_NAME})

install(
	TARGETS ${PROJECT_NAME}
	RUNTIME DESTINATION "$<CONFIG>"
)

#file(GLOB_RECURSE include_dirs LIST_DIRECTORIES true
#    RELATIVE ${CMAKE_SOURCE_DIR} "include")
	
MACRO(SUBDIRLIST result curdir)
  #file(GLOB sources_list LIST_DIRECTORIES true YourGLOBPattern)
  FILE(GLOB_RECURSE children LIST_DIRECTORIES true RELATIVE "${CMAKE_CURRENT_BINARY_DIR}" "${CMAKE_CURRENT_BINARY_DIR}/*")
  SET(dirlist "")
  FOREACH(child ${children})
    IF(IS_DIRECTORY ${curdir}/${child})
      LIST(APPEND dirlist ${child})
    ENDIF()
  ENDFOREACH()
  SET(${result} ${dirlist})
ENDMACRO()

# install(DIRECTORY ${all_dirs}
        # DESTINATION "myDestination" 
        # FILES_MATCHING PATTERN "*.h" 
# )

# message(STATUS "P1 ${CMAKE_CURRENT_BINARY_DIR}")
# SUBDIRLIST(all_dirs ${CMAKE_CURRENT_BINARY_DIR})

# message(STATUS "PRINTING ${all_dirs}")

# install(DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
        # DESTINATION "$<CONFIG>"
# )

