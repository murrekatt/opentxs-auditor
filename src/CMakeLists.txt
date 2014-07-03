# Copyright (c) Monetas AG, 2014

set(name opentxs-auditor)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${PEDANTIC_CXX_FLAGS}")

set(sources
  wallet/WalletClient.cpp
  Auditor.cpp
  main.cpp
)

add_executable(${name} ${sources})

target_link_libraries(${name}
  ${Boost_LIBRARIES}
  ${OPENSSL_LIBRARIES}
  ${OPENTXS_AUDITOR_SYSTEM_LIBRARIES}
)
