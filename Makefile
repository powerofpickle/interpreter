
OBJS = main node directory file link file_util vfs program http
OBJS := $(patsubst %, build/%.o, $(OBJS))

build/%.o : %.cpp
	g++ $< -o $@ -c -std=c++17

build/interpreter : $(OBJS)
	g++ $(OBJS) -o $@ -lstdc++fs -lpthread -lboost_system -std=c++17

clean:
	rm build/* -f

all : build/interpreter
