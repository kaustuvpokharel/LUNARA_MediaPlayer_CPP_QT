add_library(coreLib STATIC
    LoginAuthentication.hpp
    LoginAuthentication.cpp
)

target_link_libraries(coreLib
    PRIVATE Qt6::Core
    PRIVATE Qt6::Network
)
