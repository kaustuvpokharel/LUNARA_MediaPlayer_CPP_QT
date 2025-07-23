qt_add_qml_module(themeLib
    URI themeLib
    VERSION 1.0

    SOURCES
        ThemeManager.cpp
        ThemeManager.hpp

    RESOURCES
        Theme.qrc
)

target_link_libraries(themeLib
    PRIVATE Qt6::Core
)
