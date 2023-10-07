

add_executable(da_test
  "${CMAKE_CURRENT_SOURCE_DIR}/da_test.c")

target_link_libraries(da_test
  PRIVATE
    mcl)

set_target_properties(da_test
  PROPERTIES
    LANGUAGE C)

add_test(NAME TestDynamicArray COMMAND da_test)
