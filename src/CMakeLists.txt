set(NAME opentxs-auditor)

include_directories(
  ${OPENTXS_AUDITOR_SOURCE_DIR}/deps/jsonrpc-cpp
  ${OPENTXS_AUDITOR_SOURCE_DIR}/deps/websocketpp
)

set(SRC
  BtcdWalletClient.cpp
  Auditor.cpp
  main.cpp
)

add_executable(${NAME} ${SRC})

target_link_libraries(${NAME}
  ${Boost_LIBRARIES}
  ${OPENSSL_LIBRARIES}
  ${OPENTXS_AUDITOR_SYSTEM_LIBRARIES}
)
