TARGET = RAD_ADVENTURES_OF_CDC

OPTFLAGS=-O3 -fomit-frame-pointer -DDREAMCAST

KOS_CFLAGS+= -I$(KOS_BASE)/../kos-ports/include/SDL-1.2.9 $(OPTFLAGS)

all: rm-elf example.elf

include $(KOS_BASE)/Makefile.rules

.SRCS	=	example.c \

OBJS = example.o

clean:
	-rm -f $(TARGET).elf $(OBJS)
	-rm -f romdisk_boot.*

dist:
	-rm -f $(OBJS)
	-rm -f romdisk_boot.*
	$(KOS_STRIP) $(TARGET).elf

rm-elf:
	-rm -f $(TARGET).elf
	-rm -f romdisk_boot.*

$(TARGET).elf: $(OBJS) romdisk_boot.o
	$(KOS_CC) $(KOS_CFLAGS) $(KOS_LDFLAGS) -o $(TARGET).elf $(KOS_START) \
	$(OBJS) -lSDL_gfx -lSDL_129 -lm $(OBJEXTRA) $(KOS_LIBS)

romdisk_boot.img:
	$(KOS_GENROMFS) -f $@ -d romdisk_boot -v

romdisk_boot.o: romdisk_boot.img
	$(KOS_BASE)/utils/bin2o/bin2o $< romdisk_boot $@

run: $(TARGET).elf
	$(KOS_LOADER) $<


