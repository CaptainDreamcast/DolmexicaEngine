TARGET = 1ST_READ

OPTFLAGS=-O3 -fomit-frame-pointer -fno-delayed-branch -DDREAMCAST

KOS_CFLAGS+= $(OPTFLAGS)

all: rm-elf $(TARGET).elf

KOS_ROMDISK_DIR = romdisk_boot
include $(KOS_BASE)/Makefile.rules

.SRCS	=	main.c \

OBJS = $(.SRCS:.c=.o)

clean:
	-rm -f $(TARGET).elf $(OBJS)
	-rm -f $(TARGET).BIN

dist:
	-rm -f $(OBJS)
	$(KOS_STRIP) $(TARGET).elf

rm-elf:
	-rm -f $(TARGET).elf $(OBJS)
	-rm -f $(TARGET).BIN

$(TARGET).elf: $(OBJS) 
	$(KOS_CC) $(KOS_CFLAGS) $(KOS_LDFLAGS) -o $(TARGET).elf $(KOS_START) \
	$(OBJS) -lkmg -lm $(OBJEXTRA) $(KOS_LIBS)
	sh-elf-objcopy -O binary $(TARGET).elf $(TARGET).BIN

romdisk_boot.img:
	$(KOS_GENROMFS) -f $@ -d romdisk_boot -v

romdisk_boot.o: romdisk_boot.img
	$(KOS_BASE)/utils/bin2o/bin2o $< romdisk_boot $@

run: $(TARGET).elf
	$(KOS_LOADER) $<


