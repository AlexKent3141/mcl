
set(test_names da_test bt_test pq_test)

foreach(name ${test_names})
  add_executable(${name}
    "${CMAKE_CURRENT_SOURCE_DIR}/${name}.c")

  target_link_libraries(${name}
    PRIVATE
      mcl)

  set_target_properties(${name}
    PROPERTIES
      LANGUAGE C)

  target_compile_options(${name}
    PRIVATE
      -g)

  add_test(NAME ${name} COMMAND ${name})
endforeach()
