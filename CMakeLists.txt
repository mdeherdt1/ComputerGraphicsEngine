cmake_minimum_required(VERSION 3.5)

project(engine)

############################################################
# Set compiler flags
############################################################
# If supported by your compiler, you can add the -Wall, -Wextra, –fstack-protector-all and -g3 flags here.
set(OWN_GXX_FLAGS "-std=c++14")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} ${OWN_GXX_FLAGS}")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} ${OWN_GXX_FLAGS}")
set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} ${OWN_GXX_FLAGS}")

############################################################
# List all sources
############################################################
set(engine_sources
        src/easy_image.cc
        src/engine.cc
        src/ini_configuration.cc
        src/Color1.cpp
        src/Color1.h
        src/Point2D.cpp
        src/Point2D.h
        src/Line2D.cpp
        src/Line2D.h
        src/introduction.cpp
        src/introduction.h
        src/l_parser.cc
        src/StochasticRule.cpp
        src/Figure.cpp
        src/Figure.h
        src/Face.cpp
        src/Face.h
        src/vector3d.cc
        src/PlatonischeLichamen.cpp
        src/PlatonischeLichamen.h
        src/translations.cpp
        src/translations.h
        src/draw3DLsystem.cpp
        src/Wireframes.cpp
        src/ZBuffer.cpp
        src/ZBuffering.cpp
        src/lightClass.cpp
        src/lightClass.h
        src/lightedZbuffering.cpp
        src/lightedZbuffering.h
)

############################################################
# Create an executable
############################################################
set(exe_name "engine")
add_executable( ${exe_name} ${engine_sources} )
install( TARGETS ${exe_name} DESTINATION ${PROJECT_SOURCE_DIR}/ )


