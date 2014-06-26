set(name opentxs-auditor)

include_directories(SYSTEM
  ${OPENTXS_AUDITOR_SOURCE_DIR}/deps/jsonrpc-cpp
  ${OPENTXS_AUDITOR_SOURCE_DIR}/deps/websocketpp
)

set(sources
  BtcdWalletClient.cpp
  Auditor.cpp
  main.cpp
)

add_executable(${name} ${sources})

target_link_libraries(${name}
  ${Boost_LIBRARIES}
  ${OPENSSL_LIBRARIES}
  ${OPENTXS_AUDITOR_SYSTEM_LIBRARIES}
)
