cmake_minimum_required(VERSION 3.2)

project(RayTracer VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)

set (HEADER_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)
set (SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)

set (HEADERS
    ${HEADER_DIR}/ImageTypes.h
    ${HEADER_DIR}/Bitmap.h
    ${HEADER_DIR}/TVec3D.h
    ${HEADER_DIR}/TRay.h
    ${HEADER_DIR}/TPoint3D.h
    ${HEADER_DIR}/TCamera.h
    ${HEADER_DIR}/TLight.h
    ${HEADER_DIR}/Tools.h
    ${HEADER_DIR}/Color.h
    ${HEADER_DIR}/TSphere.h
    ${HEADER_DIR}/IObject.h
    ${HEADER_DIR}/TPlane.h
    ${HEADER_DIR}/ISource.h
)

set (SOURCES
    ${SOURCE_DIR}/Bitmap.cpp
    ${SOURCE_DIR}/Color.cpp
    main.cpp
)

add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})
target_compile_features(${PROJECT_NAME} PRIVATE cxx_auto_type)
target_include_directories(${PROJECT_NAME} PUBLIC
    "."
    ${HEADER_DIR}
)

add_subdirectory(Tests)
