set(LIB_SOURCES
        some.cc
)

set(HEADERS
        ${CONFIG_HEADER}
        ps_containers.h
        ps_containersplus.h
)

add_library(containers_lib STATIC ${LIB_SOURCES} ${HEADERS})