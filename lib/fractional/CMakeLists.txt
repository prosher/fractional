project(fractional)

add_library(${PROJECT_NAME}
        include/Fraction.h src/Fraction.cpp
        include/Expression.h src/Expression.cpp)

target_include_directories(${PROJECT_NAME} PUBLIC include)

#add_library(fractional::fractional ALIAS ${PROJECT_NAME})

enable_testing()
find_package(Catch2 3 REQUIRED)

include(CTest)
include(Catch)

add_executable(tests tests/test.cpp)
target_link_libraries(tests PRIVATE Catch2::Catch2WithMain fractional)
catch_discover_tests(tests)

if(COMPILE_OPTS)
    target_compile_options(${PROJECT_NAME} PUBLIC ${COMPILE_OPTS})
    target_link_options(${PROJECT_NAME} PUBLIC ${LINK_OPTS})

    target_compile_options(tests PUBLIC ${COMPILE_OPTS})
    target_link_options(tests PUBLIC ${LINK_OPTS})
endif()