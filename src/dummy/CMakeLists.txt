add_library(info_sec_dummy STATIC)
target_link_libraries(info_sec_dummy PRIVATE
    info_sec_include
)
target_sources(info_sec_dummy PRIVATE
    dummy.cpp
)
