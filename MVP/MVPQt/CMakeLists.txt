cmake_minimum_required(VERSION 3.2)

project(CoursMVP LANGUAGES CXX VERSION 1.0.0 )

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)

if(WIN32)
    set(QT_VERSION "5.15.2")
    set(CMAKE_PREFIX_PATH J:/logiciels/QT/${QT_VERSION}/msvc2019_64)
endif(WIN32)

find_package( Qt5 ${QT_VERSION} COMPONENTS
    Core
    Widgets
    Gui
    REQUIRED
)

set (HEADER_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)
set (SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)

set (HEADERS
    ${HEADER_DIR}/BackgroundWorker.h
    ${HEADER_DIR}/ConcreteModel.h
    ${HEADER_DIR}/ConcretePresenter.h
    ${HEADER_DIR}/ConcreteView.h
    ${HEADER_DIR}/IModel.h
    ${HEADER_DIR}/IView.h
    ${HEADER_DIR}/IPresenter.h
    ${HEADER_DIR}/Threading.h
    ${HEADER_DIR}/Signal.h
    ${HEADER_DIR}/Trigger.h

    ${HEADER_DIR}/Dispatcher.h

)

set (SOURCES
    ${SOURCE_DIR}/BackgroundWorker.cpp
    ${SOURCE_DIR}/ConcreteView.cpp
    ${SOURCE_DIR}/ConcreteModel.cpp
    ${SOURCE_DIR}/ConcretePresenter.cpp
    ${SOURCE_DIR}/main.cpp
)

add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})
target_compile_features(${PROJECT_NAME} PRIVATE cxx_auto_type)
target_link_libraries(${PROJECT_NAME}
    PUBLIC
        ${Qt5Widgets_LIBRARIES}
        Qt5::Core
        Qt5::Widgets
        Qt5::Gui
)

target_include_directories(${PROJECT_NAME} PUBLIC
     "."
     ${HEADER_DIR}
 )

target_compile_definitions(${PROJECT_NAME}
    PUBLIC
        ${Qt5Widgets_DEFINITIONS}
        
    PRIVATE
        QT_NO_KEYWORDS
)
       
if(WIN32)
    add_custom_command(
        TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            $<TARGET_FILE:Qt5::Widgets>
            $<TARGET_FILE:Qt5::Core>
            $<TARGET_FILE:Qt5::Gui>
            $<TARGET_FILE_DIR:${PROJECT_NAME}>
    
    )
endif(WIN32)

