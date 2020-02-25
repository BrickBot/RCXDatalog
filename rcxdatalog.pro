TEMPLATE  =  app
CONFIG    =  qt debug
LIBS 	  += -lqwt
INCLUDEPATH = /usr/local/include/qwt
HEADERS   =  rcx.h send.h rcxdatalog.h rcxsensor.h rcxrealsensor.h rcxboolsensor.h rcxlight.h rcxbattery.h rcxwidget.h rcxcc.h qrcxsend.h qlmled.h gplbrowser.h rcxerrormessage.h
SOURCES   =  send.cpp rcx.cpp rcxdatalog.cpp rcxsensor.cpp rcxrealsensor.cpp rcxboolsensor.cpp rcxlight.cpp rcxbattery.cpp rcxwidget.cpp rcxcc.cpp qrcxsend.cpp qlmled.cpp main.cpp gplbrowser.cpp rcxerrormessage.cpp
TARGET    =  rcxdatalog
TMAKE_MOC       = /usr/lib/qt2/bin/moc      
