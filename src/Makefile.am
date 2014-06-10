bin_PROGRAMS		= 	auditor

auditor_SOURCES		= 	$(auditor_sources) $(auditor_headers)

auditor_CXXFLAGS	= 	$(AM_CXXFLAGS) $(BOOST_CPPFLAGS)

auditor_LDFLAGS		=	$(BOOST_LDFLAGS)

auditor_LDADD 		=	$(DEPS_LIBS)

auditor_sources		= 	BtcdWalletClient.cpp \
				Auditor.cpp \
				main.cpp

auditor_headers		= 	WalletClient.hpp \
				BtcdWalletClient.hpp \
				Auditor.hpp
