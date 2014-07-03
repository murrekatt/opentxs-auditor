set(NAME unittests-opentxs-auditor)

include_directories(
  ${OPENTXS_AUDITOR_SOURCE_DIR}/deps/gtest/include
  ${OPENTXS_AUDITOR_SOURCE_DIR}/src
)

set(SRC
  Test_Example.cpp
)

add_executable(${NAME} ${SRC})

target_link_libraries(${NAME}
  ${GTEST_BOTH_LIBRARIES}
  ${OPENTXS_AUDITOR_SYSTEM_LIBRARIES}
)

set_target_properties(${NAME}
                      PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${OPENTXS_AUDITOR_BINARY_DIR}/tests
)

add_test(${NAME} ${OPENTXS_AUDITOR_BINARY_DIR}/tests/${NAME} --gtest_output=xml:gtestresults.xml)
