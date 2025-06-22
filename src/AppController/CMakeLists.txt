add_executable(App
    main.cpp
)

target_include_directories(App
    PRIVATE ${CMAKE_SOURCE_DIR}/src/Core/LoginAuthentication)

target_link_libraries (App
    PRIVATE Qt6::Core
    PRIVATE Qt6::Quick
    coreLib
    UIModule
)
