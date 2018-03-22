# Add executable called "helloDemo" that is built from the source files
# "demo.cxx" and "demo_b.cxx". The extensions are automatically found.

file(GLOB lib_SRC
    "../lib/*.h"
    "../lib/*.cpp"
)

file(GLOB rapidjson_SRC
    "../rapidjson/*.h"
    "../rapidjson/*.cpp"
)

file(GLOB here_SRC
    "*.h"
    "*.cpp"
)

add_executable(LexicalAnalyzerGenerator ${here_SRC} ${lib_SRC} ${rapidjson_SRC} RulesHandler.cpp RulesHandler.h)