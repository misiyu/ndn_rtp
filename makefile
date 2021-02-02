# create by wgh
INC_DIR= -I.
SRC_DIR = .
OBJ_DIR = ./objs

#SRC=$(wildcard $(SRC_DIR)/*.cpp)   

SRC=  pro.cpp \
	  ndn_rtpp.cpp 

SRC1= con.cpp \
	  ndn_rtpc.cpp \
	  recv_list.cpp


OBJS := $(patsubst %.cpp, %.o,$(SRC))
OBJS1 := $(patsubst %.cpp, %.o,$(SRC1))

CC := g++ 
CFLAGS := -g -std=c++14 ${INC_DIR}
LFLAGS := -lpthread -lpcap -lndn-cxx -lboost_system -ljsoncpp
TARGET := pro con

all: ${TARGET} 

pro: ${OBJS}
	$(CC) ${OBJS} -o pro  $(LFLAGS)

${OBJS} : %.o: %.cpp %.h
	${CC} ${CFLAGS} -c $< -o $@

con: ${OBJS1}
	$(CC) ${OBJS1} -o con  $(LFLAGS)

${OBJS1} : %.o: %.cpp %.h
	${CC} ${CFLAGS} -c $< -o $@

clean:  
	rm -rf $(TARGET) *.o ${OBJS} 

test:
	echo $(SRC)
	echo $(OBJS)
	echo $(CFLAGS)
