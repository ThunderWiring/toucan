WESTUDIO_PATH	=	C:\\Users/Bassam/AppData/Local/Arduino15/packages/WeActStudio
GNU_TOOLCHAIN_PATH = C:\\MyProjects/BlackPill/GNUARMEmbeddedToolchain/54_2016q3/bin
GXX_CC =  $(GNU_TOOLCHAIN_PATH)/arm-none-eabi-g++
GCC_CC =  $(GNU_TOOLCHAIN_PATH)/arm-none-eabi-gcc
ARM_CC =  $(GNU_TOOLCHAIN_PATH)/arm-none-eabi-ar
HEX_CC =  $(GNU_TOOLCHAIN_PATH)/arm-none-eabi-objcopy
SIZE_CC = $(GNU_TOOLCHAIN_PATH)/arm-none-eabi-size
WESTUDIO_HEX_UPLOADER = $(WESTUDIO_PATH)/tools/Artery_ISP_Console/0.0.1/WeAct Studio Download Tool.bat

DEFINES =	\
-DAT32F403ACGU7	\
-DAT_START_F403A_V1	\
-DF_CPU=80000000L	\

WARNINGS = -Wall -Wunused -Wuninitialized
MCU_FLAGS = -mthumb -mcpu=cortex-m4 -mfpu=fpv4-sp-d16 -O0  $(DEFINES)
FLAGS =  -MMD -MP -w -ffunction-sections -fno-exceptions $(MCU_FLAGS)
CFLAGS =  $(FLAGS) -std=c99 -xc
CXXFLAGS = -specs=nosys.specs  -std=gnu++11 -fno-rtti $(FLAGS)

ROOT_PATH = C:\\MyProjects/BlackPill/USBRobot/blackpill
AT32F403A = $(ROOT_PATH)/AT32F403A
FLASH_LD =        $(AT32F403A)/cmsis/cm4/device_support/startup/gcc/linker/AT32F403AxG_FLASH.ld
ENTRY_POINT_SRC	=	$(AT32F403A)/cmsis/cm4/device_support/startup/gcc/startup_at32f403a_407.s	\

####################################################
# Main Application sources and libraries           #
####################################################
SRCS	=	\
$(wildcard $(ROOT_PATH)/*.c)	\
$(wildcard $(ROOT_PATH)/*.cpp)	\
$(wildcard $(ROOT_PATH)/toucan/usb/*.cpp)	\
$(wildcard $(ROOT_PATH)/toucan/LCD/*.cpp)	\
$(wildcard $(ROOT_PATH)/toucan/gpio/*.cpp)	\
$(wildcard $(ROOT_PATH)/toucan/SPI/*.cpp)	\
$(wildcard $(ROOT_PATH)/toucan/robot/*.cpp)	\

CXX_LOCAL_LIBS	=	\
-I$(ROOT_PATH)	\
-I$(ROOT_PATH)/toucan/usb	\
-I$(ROOT_PATH)/toucan/LCD	\
-I$(ROOT_PATH)/toucan/gpio	\
-I$(ROOT_PATH)/toucan/SPI	\
-I$(ROOT_PATH)/toucan/robot	\

####################################################
# Firmaware - BSP (Board Support Pack)
####################################################
CMSIS_SRCS	=	\
$(wildcard $(AT32F403A)/cmsis/cm4/device_support/*.c)	\
$(wildcard $(AT32F403A)/drivers/src/*.c)	\

CMSIS_LIBS	=	\
-I$(AT32F403A)/cmsis/cm4/core_support	\
-I$(AT32F403A)/cmsis/cm4/device_support	\
-I$(AT32F403A)/drivers/inc	\

MIDDLEWARES_SRCS	=	\
$(wildcard $(AT32F403A)/Middlewares/usbd_class/custom_hid/*.c)	\
$(wildcard $(AT32F403A)/Middlewares/usbd_class/msc/*.c)	\
$(wildcard $(AT32F403A)/Middlewares/usbd_class/cdc/*.c)	\
$(wildcard $(AT32F403A)/Middlewares/usbd_class/mouse/*.c)	\
$(wildcard $(AT32F403A)/Middlewares/usbd_drivers/src/*.c)	\

MIDDLEWARES_LIBS	=	\
-I$(AT32F403A)/Middlewares/usbd_drivers/inc	\
-I$(AT32F403A)/Middlewares/usbd_class/custom_hid	\
-I$(AT32F403A)/Middlewares/usbd_class/cdc	\
-I$(AT32F403A)/Middlewares/usbd_class/msc	\
-I$(AT32F403A)/Middlewares/usbd_class/mouse	\

SYSTEM_SRC_C	=	\
$(CMSIS_SRCS)	\
$(MIDDLEWARES_SRCS)	\
$(wildcard $(AT32F403A)/Src/*.c)	\

SYSTEM_LIBS =	\
$(CMSIS_LIBS)	\
$(MIDDLEWARES_LIBS)	\
-I$(AT32F403A)/Inc	\

LIBS = \
$(SYSTEM_LIBS)	\
$(CXX_LOCAL_LIBS)	\

####################################################
# Build
####################################################
OUTFOLDER= out
C_CORE_OUT= c_out
PROG_OUT= prog_out
PROG_ENTRY_POINT = entry_point.S.o
ELF_OUT	=	pill.elf
HEX_OUT = pill.hex

#rules
PROG = pill
STARTUP_ENTRY_POINT = startup_entry_point
PROG_SYS_C = sys_out
ARM = arm_rcs
LINKING = linking
TO_HEX = to_hex
UPLOAD = upload

# targets to be built. Order is important.
# those rules $(PROG_SYS_C), $(PROG_SYS_CPP), $(ARM), are used to make the entry point 
# rule link properly in LINKING rule
# if UPLOAD target is enabled, make sure the blackpill board in DFU mode.
all: 	\
$(PROG_SYS_C)	\
$(ARM)	\
$(PROG)	\
$(STARTUP_ENTRY_POINT)	\
$(LINKING)	\
$(TO_HEX)	\
$(UPLOAD)	\

$(PROG_SYS_C):$(SYSTEM_SRC_C)
	$(GCC_CC)	$(CFLAGS)	$(SYSTEM_LIBS)	-c $(SYSTEM_SRC_C)	&\
	move *.o ./$(OUTFOLDER)/$(C_CORE_OUT) &\
	move *.d ./$(OUTFOLDER)/$(C_CORE_OUT)

# create static library from the AT32F403A firmware
$(ARM):
	$(ARM_CC) rcs $(OUTFOLDER)/core.a $(wildcard $(OUTFOLDER)/$(C_CORE_OUT)/*.o) 

$(PROG):$(SRCS)
	$(GXX_CC)	$(CXXFLAGS) -c $(LIBS) $?	&\
	move *.o ./$(OUTFOLDER)/$(PROG_OUT)	&\
	move *.d ./$(OUTFOLDER)/$(PROG_OUT)

$(STARTUP_ENTRY_POINT):$(ENTRY_POINT_SRC)
	$(GCC_CC)	-mthumb -Wall -g -Os -mcpu=cortex-m4 -c	$(ENTRY_POINT_SRC)	-o	$(OUTFOLDER)/$(PROG_ENTRY_POINT)	
	
$(LINKING):
	$(GXX_CC)	-mthumb -g -Wl,--gc-sections -Wall  -lm -mcpu=cortex-m4	\
	-T$(FLASH_LD)	\
	$(wildcard $(OUTFOLDER)/$(PROG_OUT)/*.o)	\
	$(wildcard $(OUTFOLDER)/$(C_CORE_OUT)/*.o)	\
	$(OUTFOLDER)/$(PROG_ENTRY_POINT)	\
	-L$(OUTFOLDER)/core.a	\
	-specs=nano.specs -specs=nosys.specs	\
	-u _sbrk -u link -u _close -u _fstat -u _isatty -u _lseek -u _read \
	-u _write -u _exit -u kill -u _getpid \
	-o $(OUTFOLDER)/$(ELF_OUT)

$(TO_HEX):
	$(HEX_CC)	-Oihex $(OUTFOLDER)/$(ELF_OUT)	$(OUTFOLDER)/$(HEX_OUT)	&\
	$(SIZE_CC) -A $(OUTFOLDER)/$(ELF_OUT)

$(UPLOAD):
	 $(WESTUDIO_HEX_UPLOADER)	$(ROOT_PATH)/$(OUTFOLDER)/$(HEX_OUT)