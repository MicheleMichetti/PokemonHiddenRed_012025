find_package(PkgConfig REQUIRED)
find_package(fmt REQUIRED)

file(GLOB ENGINE_FILES
    src/*.cpp
    include/*.hpp
)

add_library(
    engine-lib SHARED
    ${ENGINE_FILES}
)

set_target_properties(engine-lib PROPERTIES LINKER_LANGUAGE CXX)

pkg_check_modules(ALLEGRO REQUIRED allegro-5 allegro_font-5 allegro_ttf-5 allegro_image-5 allegro_primitives-5)
pkg_check_modules(JSONCPP REQUIRED jsoncpp)
pkg_check_modules(SPDLOG REQUIRED spdlog)
FIND_PACKAGE( Boost 1.74 COMPONENTS REQUIRED )

target_include_directories(engine-lib PUBLIC include)
target_include_directories(engine-lib PUBLIC ${JSONCPP_INCLUDE_DIRS})
target_include_directories(engine-lib PUBLIC ${BOOST_INCLUDE_DIRS})

target_link_libraries(engine-lib PRIVATE ${JSONCPP_LIBRARIES})
target_link_libraries(engine-lib PRIVATE ${ALLEGRO_LIBRARIES})
target_link_libraries(engine-lib PRIVATE ${BOOST_LIBRARIES})
target_link_libraries(engine-lib PRIVATE fmt::fmt)