cmake_minimum_required(VERSION 3.27)

PROJECT(JsonParser C)
set(CMAKE_C_STANDARD 17)

add_library(jsonParserLib
        core/Json.h
        core/parser.h
        core/JsonValue.h
        core/JsonArray.h
        core/JsonObject.h
        core/JsonString.h
        core/outputer.h
        core/parser.c
        core/JsonValue.c
        core/JsonArray.c
        core/JsonObject.c
        core/JsonString.c
        core/outputer.c
)

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