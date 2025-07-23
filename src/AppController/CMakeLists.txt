add_executable(App
    main.cpp
    App.cpp
    App.hpp
)

target_include_directories(App
    PRIVATE ${CMAKE_SOURCE_DIR}/src/Core/LoginAuthentication
    PRIVATE ${CMAKE_SOURCE_DIR}/src/Theme
)



target_link_libraries (App
    PRIVATE Qt6::Core
    PRIVATE Qt6::Quick
    coreLib
    UIModule
    themeLib
)
