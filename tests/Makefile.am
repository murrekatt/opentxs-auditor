noinst_PROGRAMS = unittests_as

unittests_as_SOURCES = Test_Example.cpp

unittests_as_CXXFLAGS = $(AM_CXXFLAGS) \
			-I../gtest/include

unittests_as_LDADD = -L../gtest/build \
			-lgtest_main -lgtest

TESTS = $(noinst_PROGRAMS)
