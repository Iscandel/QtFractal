find_package(Qt5Core REQUIRED)

# get absolute path to qmake, then use it to find windeployqt executable

get_target_property(_qmake_executable Qt5::qmake IMPORTED_LOCATION)
get_filename_component(_qt_bin_dir "${_qmake_executable}" DIRECTORY)

function(windeployqt target)

	# Can also use CMAKE_BUILD_TYPE for single project generators and 
	# VS Studio variables like $(ConfigurationName)
	# to determine the current build type
	
    # POST_BUILD step
    # - after build, we have a bin/lib for analyzing qt dependencies
    # - we run windeployqt on target and deploy Qt libs

    add_custom_command(TARGET ${target} POST_BUILD
        COMMAND "${_qt_bin_dir}/windeployqt.exe"         
                --verbose 1
                --$<$<CONFIG:DEBUG>:debug>$<$<CONFIG:RELEASE>:release>
                --no-svg
                --no-angle
                --no-opengl
                --no-opengl-sw
                --no-compiler-runtime
                --no-system-d3d-compiler
				--dir "${CMAKE_INSTALL_PREFIX}/$<CONFIG>"
                \"$<TARGET_FILE:${target}>\"
        COMMENT "Deploying Qt libraries using windeployqt for compilation target '${target}' ..."
    )

	# We can also use COMMAND ${CMAKE_COMMAND} -E copy_directory <source> <dest>

endfunction()