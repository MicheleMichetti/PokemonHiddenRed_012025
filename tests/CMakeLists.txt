find_package(PkgConfig REQUIRED)
find_package(fmt REQUIRED)
pkg_search_module(GTEST REQUIRED gtest_main)

add_executable(pokemon-tests)

file(GLOB TEST_FILES
    unit-tests/*.hpp
    unit-tests/*.cpp
    integration-tests/*.hpp
    integration-tests/*.cpp
)

pkg_check_modules(ALLEGRO REQUIRED allegro-5 allegro_font-5 allegro_ttf-5 allegro_image-5 allegro_primitives-5)
pkg_check_modules(JSONCPP REQUIRED jsoncpp)
pkg_check_modules(SPDLOG REQUIRED spdlog)
FIND_PACKAGE( Boost 1.74 COMPONENTS REQUIRED )

target_sources(pokemon-tests PRIVATE ${TEST_FILES})

target_link_libraries(pokemon-tests PRIVATE ${GTEST_LDFLAGS})
target_compile_options(pokemon-tests PRIVATE ${GTEST_CFLAGS})

enable_testing()
#[[include dirs for extra safety]]
target_include_directories(pokemon-tests PUBLIC ${JSONCPP_INCLUDE_DIRS})
target_include_directories(pokemon-tests PUBLIC ${ALLEGRO_INCLUDE_DIRS})
target_include_directories(pokemon-tests PUBLIC ${BOOST_INCLUDE_DIRS})
#[[linked libraries]]
target_link_libraries(pokemon-tests PRIVATE ${JSONCPP_LIBRARIES})
target_link_libraries(pokemon-tests PRIVATE ${ALLEGRO_LIBRARIES})
target_link_libraries(pokemon-tests PRIVATE ${BOOST_LIBRARIES})
target_link_libraries(pokemon-tests PRIVATE pokemon-lib)
target_link_libraries(pokemon-tests PRIVATE engine-lib)
target_link_libraries(pokemon-tests PRIVATE fmt::fmt)