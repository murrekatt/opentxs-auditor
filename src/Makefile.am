
vpasdir			=	.

bin_PROGRAMS		=	vpas

vpas_SOURCES		=	$(vpas_sources) $(vpas_headers)

vpas_CXXFLAGS		=	$(AM_CXXFLAGS)			\
				-I$(vpasdir)			\
				-I$(vpasdir)/crypto		\
				-I$(vpasdir)/network		\
				-I$(vpasdir)/parsers		\
				-I$(vpasdir)/queue		\
				-I$(vpasdir)/util               \
                                -I$(vpasdir)/parsers/jsoncpp

vpas_LDADD		=	-lxmlrpc_client++ -lxmlrpc++ -lxmlrpc -lboost_system -lboost_program_options

vpas_sources		=	main.cpp			\
				crypto/base64.cpp		\
				network/BitMessage.cpp		\
				network/Network.cpp		\
				network/XmlRPC.cpp		\
				parsers/MainConfigParser.cpp	\
				parsers/jsoncpp/jsoncpp.cpp	\
				queue/BitMessageQueue.cpp

vpas_headers		=	constants.h			\
				crypto/base64.h			\
				network/BitMessage.h		\
				network/Network.h		\
				network/XmlRPC.h		\
				parsers/MainConfigParser.h	\
				parsers/jsoncpp/json/json-forwards.h	\
				parsers/jsoncpp/json/json.h	\
				queue/BitMessageQueue.h		\
				queue/MsgQueue.h		\
				queue/WorkQueue.h		\
				util/VectorHelp.h
