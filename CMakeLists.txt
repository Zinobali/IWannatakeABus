cmake_minimum_required(VERSION 3.19)
project(IWannatakeABus LANGUAGES CXX)

find_package(Qt6 6.5 REQUIRED COMPONENTS Core Widgets)

qt_standard_project_setup()

qt_add_executable(IWannatakeABus
    WIN32 MACOSX_BUNDLE
    main.cpp
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui
    res.qrc
    global.h
    global.cpp
    zoomablegraphicsview.h
    zoomablegraphicsview.cpp
)

qt_add_resources(IWannatakeABus_RESOURCES res.qrc)

INCLUDE_DIRECTORIES(
    ${PROJECT_SOURCE_DIR}
)

target_sources(IWannatakeABus PRIVATE ${IWannatakeABus_RESOURCES})

target_link_libraries(IWannatakeABus
    PRIVATE
        Qt::Core
        Qt::Widgets
)

include(GNUInstallDirs)

install(TARGETS IWannatakeABus
    BUNDLE  DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

qt_generate_deploy_app_script(
    TARGET IWannatakeABus
    OUTPUT_SCRIPT deploy_script
    NO_UNSUPPORTED_PLATFORM_ERROR
)
install(SCRIPT ${deploy_script})
