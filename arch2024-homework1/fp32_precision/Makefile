
TARGET1 := analysis
TARGET2 := sum

all: 
	$(CC) -o $(TARGET1) $(TARGET1).c
	$(CC) -o $(TARGET2) $(TARGET2).c

clean:
	$(RM) $(TARGET1)
	$(RM) $(TARGET2)
#	$(RM) out

PRINTF = env printf
PASS_COLOR = \e[32;01m
NO_COLOR = \e[0m
pass = $(PRINTF) "$(PASS_COLOR)$1 Passed [-]$(NO_COLOR)\n"

check: all
#	$(RM) out || true > /dev/null
	./$(TARGET1)
	./$(TARGET2)
#	cat out

