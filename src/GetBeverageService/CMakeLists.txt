add_executable(
    GetBeverageService
    GetBeverageService.cpp
    ${THRIFT_GEN_CPP_DIR}/GetBeverageService.cpp
    ${THRIFT_GEN_CPP_DIR}/vending_machine_types.cpp

)

target_include_directories(
    GetBeverageService PRIVATE
)

target_link_libraries(
    GetBeverageService
    nlohmann_json::nlohmann_json
    ${THRIFT_LIB}
    ${CMAKE_THREAD_LIBS_INIT}
    ${Boost_LIBRARIES}
    Boost::log
    Boost::log_setup
)

install(TARGETS GetBeverageService DESTINATION ./)
