ifeq (,$(findstring nosanitize, $(MAKECMDGOALS)))
	SANITIZE= -fsanitize=address
else
	CFLAGS += -D VALGRIND
endif

TARGET = test_sep
OBJS = test_sep.o digit_sep.o
DEPS=$(OBJS:.o=.d)

CFLAGS += -g3
CFLAGS += -O0
CFLAGS += -Wall -MMD -MP
CFLAGS += -Iinclude
#CFLAGS += --pedantic
#CFLAGS += -S -save-temps
CXXFLAGS += $(CFLAGS) 
LDFLAGS = -lstdc++ -g 

.PHONY: all clean memcheck nosanitize

all : $(TARGET)
	
nosanitize : $(TARGET)

memcheck: clean
	make nosanitize
	echo "cannot use with SANITIZE option on valgrind"
	valgrind --tool=memcheck --leak-check=full --track-origins=yes --show-leak-kinds=all ./$(TARGET)


clean:
	$(RM) $(OBJS) $(TARGET) $(DEPS) 

$(TARGET) : $(OBJS)
	$(LINK.cc) -o $@ $^
	
-include $(DEPS)
