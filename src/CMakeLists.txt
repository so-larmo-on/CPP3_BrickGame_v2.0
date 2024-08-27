cmake_minimum_required(VERSION 3.5)

project(snake_desktop VERSION 0.1 LANGUAGES CXX C)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


if(${SNAKE_MODE})
    message(SNAKe_MODE="${SNAKE_MODE}")
    set(
    CMAKE_CXX_FLAGS
    "${CMAKE_CXX_FLAGS} -Werror -fsanitize=address -D SNAKE_DESK -D SNAKE"
  )
    add_executable(

    snake_desktop
    snake.cpp
    brick_game/snake/model.h
    brick_game/snake/model.cpp
    brick_game/snake/controller.h
    brick_game/snake/controller.cpp
    gui/desktop/game.h
    gui/desktop/game.cpp
    gui/desktop/mainwindow.cpp
    gui/desktop/mainwindow.h
    gui/desktop/mainwindow.ui

    )
    target_link_libraries(snake_desktop PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

    set_target_properties(snake_desktop PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
    )
    find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
    find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

    if(QT_VERSION_MAJOR EQUAL 6)
     qt_finalize_executable(snake_desktop)
    endif()
    
else()
    message(SNAK_MODE="${SNAKE_MODE}")
    set(
    CMAKE_CXX_FLAGS
    "${CMAKE_CXX_FLAGS} -Werror -fsanitize=address -D TETRIS_DESK -D TETRIS"
    )
    set(
        CMAKE_C_FLAGS
        "${CMAKE_C_FLAGS} -Werror -fsanitize=address -D TETRIS_DESK -D TETRIS"
        )
    add_executable(

    tetris_desktop
    tetris.cpp
    brick_game/tetris/backend.h
    brick_game/tetris/backend.c
    brick_game/tetris/helper.c
    gui/desktop/game.h
    gui/desktop/game.cpp
    gui/desktop/mainwindow.cpp
    gui/desktop/mainwindow.h
    gui/desktop/mainwindow.ui

    )

    target_link_libraries(tetris_desktop PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

    set_target_properties(tetris_desktop PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
    )
    find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
    find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)
    if(QT_VERSION_MAJOR EQUAL 6)
     qt_finalize_executable(tetris_desktop)
    endif()
endif()













