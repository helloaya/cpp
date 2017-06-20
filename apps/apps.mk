#app

PATH_SRCS 		+= .
PATH_INCLUDES 	+=  ../../3rd/include
PATH_LIBS 		+= ../../3rd/lib
LIBS 			+=
CPPFLAGS 		+= -O2
CC 				 = g++

SRCS += $(foreach n, $(PATH_SRCS), $(wildcard $(n)/*.c)) $(foreach n, $(PATH_SRCS), $(wildcard $(n)/*.cpp))
OBJS  = $(patsubst %.c, .dep/%.c_obj, $(patsubst %.cpp, .dep/%.cpp_obj, $(SRCS)))

.PHONY:clean
.PHONY:prepare

all:prepare $(TARGET)

prepare:
	mkdir -p .dep

clean:
	@rm -rf .dep $(TARGET)

$(TARGET):$(OBJS)
	$(CC) -o $(TARGET) $(OBJS) $(foreach n, $(PATH_LIBS), -L$(n)) $(foreach n, $(LIBS), -l$(n))
	

.dep/%.cpp_obj:%.cpp
	$(CC) -c $(foreach n, $(PATH_INCLUDES), -I$(n)) $(CPPFLAGS) $< -o $@
