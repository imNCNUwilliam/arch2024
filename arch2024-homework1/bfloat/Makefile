
TARGET := bfloat

all: 
	$(CC) -o $(TARGET) $(TARGET).c

clean:
	$(RM) $(TARGET)
#	$(RM) out

PRINTF = env printf
PASS_COLOR = \e[32;01m
NO_COLOR = \e[0m
pass = $(PRINTF) "$(PASS_COLOR)$1 Passed [-]$(NO_COLOR)\n"

check: all
#	$(RM) out || true > /dev/null
#	./$(TARGET) m1.txt out
#	cat out

