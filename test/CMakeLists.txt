

add_executable(darray_test
  "${CMAKE_CURRENT_SOURCE_DIR}/darray_test.c")

target_link_libraries(darray_test
  PRIVATE
    mcl)

set_target_properties(darray_test
  PROPERTIES
    LANGUAGE C)

add_test(NAME TestDynamicArray COMMAND darray_test)
