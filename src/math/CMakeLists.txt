add_library(info_sec_math STATIC)
target_link_libraries(info_sec_math PRIVATE
    info_sec_include
)
target_sources(info_sec_math PRIVATE
    math.cpp
)
