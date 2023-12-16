cmake_minimum_required(VERSION 3.27)

PROJECT(JsonParser C)
set(CMAKE_C_STANDARD 17)

find_package(Iconv REQUIRED)
add_definitions(-DLOCALEDIR="\"${CMAKE_INSTALL_PREFIX}/share/locale\"")


add_library(jsonParserLib
        core/Json.h
        core/parser/parser.h
        core/types/JsonValue.h
        core/types/JsonArray.h
        core/types/JsonObject.h
        core/types/JsonString.h
        core/utils/outputer.h
        core/utils/outputer.c
        core/parser/parser.c
        core/types/JsonValue.c
        core/types/JsonArray.c
        core/types/JsonObject.c
        core/types/JsonString.c
)
target_link_libraries(jsonParserLib PRIVATE Iconv::Iconv)

add_executable(json
        cli/main.c
)
target_include_directories(json PRIVATE
        core
)
target_link_libraries(json PRIVATE
        jsonParserLib
)

add_library(cutest
        cutest/CuTest.h
        cutest/CuTest.c
)

add_executable(string_test
        test/stringTest.c
)

target_include_directories(string_test PRIVATE
        core
        cutest
)
target_link_libraries(string_test PRIVATE
        cutest
        jsonParserLib
)

enable_testing()
add_test(
        NAME "String Test"
        COMMAND string_test
)