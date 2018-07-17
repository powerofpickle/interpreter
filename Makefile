
OBJS = main node directory file link file_util vfs program
OBJS := $(patsubst %, build/%.o, $(OBJS))

build/%.o : %.cpp
	g++ $< -o $@ -c -std=c++17

build/interpreter : $(OBJS)
	g++ $(OBJS) -o $@ -lstdc++fs -std=c++17
