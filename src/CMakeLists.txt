set(DIRS dummy rsa math)
foreach(DIR ${DIRS})
    add_subdirectory(${DIR})
endforeach()
