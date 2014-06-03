
vpasdir			=	.

bin_PROGRAMS		=	vpas

vpas_SOURCES		=	$(vpas_sources) $(vpas_headers)

vpas_CXXFLAGS		=	-std=c++11			\
				-I$(vpasdir)			\
				-I$(vpasdir)/crypto		\
				-I$(vpasdir)/network		\
				-I$(vpasdir)/parsers		\
				-I$(vpasdir)/queue		\
				-I$(vpasdir)/util

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
