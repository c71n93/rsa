add_library(info_sec_testif INTERFACE)
target_link_libraries(info_sec_testif INTERFACE
        info_sec_include
        info_sec_dummy
        info_sec_rsa
        info_sec_math
        gmock_main
        gmock
        gtest
)

function(info_sec_test SOURCE_NAME)
    get_filename_component(TARGET_NAME ${SOURCE_NAME} NAME_WE)
    add_executable(${TARGET_NAME})
    target_sources(${TARGET_NAME} PRIVATE ${SOURCE_NAME})
    target_link_libraries(${TARGET_NAME} PRIVATE info_sec_testif)
    add_test(NAME ${TARGET_NAME} COMMAND ./${TARGET_NAME})
endfunction(info_sec_test)

include(CTest)

set(DIRS dummy-test rsa-test math-test)
foreach(DIR ${DIRS})
    add_subdirectory(${DIR})
endforeach()
