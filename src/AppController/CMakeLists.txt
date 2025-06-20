add_executable(App
    main.cpp
)

target_link_libraries (App
    PRIVATE Qt6::Core
    PRIVATE Qt6::Quick
    UIModule
)
