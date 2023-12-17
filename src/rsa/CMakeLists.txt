add_library(info_sec_rsa STATIC)
target_link_libraries(info_sec_rsa PRIVATE
    info_sec_include
)
target_sources(info_sec_rsa PRIVATE
    rsa.cpp
)
