TARGET = 1ST_READ
OBJS = main.o
OPTFLAGS=-O3 -fomit-frame-pointer -fno-delayed-branch -DDREAMCAST
KOS_CFLAGS+= $(OPTFLAGS)
DOLMEXICA_FLAGS = -LLIBS

all: rm-elf $(TARGET).elf

clean:
	-rm -f $(TARGET).elf $(OBJS)
	-rm -f $(TARGET).BIN

rm-elf:
	-rm -f $(TARGET).elf $(OBJS)
	-rm -f $(TARGET).BIN

$(TARGET).elf: $(OBJS) 
	$(KOS_CC) $(KOS_CFLAGS) -I$(KOS_BASE)/addons/lua/include $(KOS_LDFLAGS) $(DOLMEXICA_FLAGS) \
	-o $(TARGET).elf $(KOS_START) \
	$(OBJS) -lkmg $(OPTIONAL_LIBS) -lm -ltremor $(OBJEXTRA) $(KOS_LIBS)
	$(KOS_OBJCOPY) -O binary $(TARGET).elf $(TARGET).BIN

include $(KOS_BASE)/Makefile.rules
include CONFIG.MAKEFILE
