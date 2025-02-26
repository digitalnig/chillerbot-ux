foreach(target ${TARGETS_OWN})
  if((CMAKE_VERSION VERSION_GREATER 3.1 OR CMAKE_VERSION VERSION_EQUAL 3.1))
    set_property(TARGET ${target} PROPERTY CXX_STANDARD 17)
    set_property(TARGET ${target} PROPERTY CXX_STANDARD_REQUIRED ON)
    set_property(TARGET ${target} PROPERTY CXX_EXTENSIONS OFF)
  endif()
  target_include_directories(${target} PRIVATE src/rust-bridge-chillerbot)
  if(CURSES_CLIENT)
    target_compile_definitions(${target} PRIVATE CONF_CURSES_CLIENT)
  endif()
endforeach()
