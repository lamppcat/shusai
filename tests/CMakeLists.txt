# 'tests/CMakeLists.txt': includes all subdirectories as tests

# Find all subdirectories
file(GLOB children *)
set(dirlist "")
foreach(child ${children})
	if(IS_DIRECTORY ${child})
		list(APPEND dirlist ${child})
	endif()
endforeach()

# Add all subdirectories as separate tests
foreach (dir ${dirlist})
	set(SOURCE_FILES "")
	add_subdirectory(${dir})
	foreach (file ${src})
		list(APPEND SOURCE_FILES ../src/${file})
	endforeach()

	foreach (file ${include})
		list(APPEND SOURCE_FILES ../include/${file})
	endforeach()

	foreach (file ${test})
		list(APPEND SOURCE_FILES ${dir}/${file})
	endforeach()

	add_executable(test-${name} ${SOURCE_FILES})
	target_link_libraries(test-${name} gtest)
	message("tests: Added test-${name} to targets")
endforeach()
