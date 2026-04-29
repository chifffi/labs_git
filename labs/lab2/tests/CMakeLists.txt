enable_testing()

# Список имен тестов
set(TEST_FILES
    test_basefile
    test_base32file
    test_rlefile
    test_base32file2
    test_rlefile2
    test_composition
)

foreach(TEST ${TEST_FILES})
    add_executable(${TEST} ${CMAKE_CURRENT_SOURCE_DIR}/${TEST}.cpp)
    target_link_libraries(${TEST} core)
    add_test(NAME ${TEST} COMMAND ${TEST})
endforeach()