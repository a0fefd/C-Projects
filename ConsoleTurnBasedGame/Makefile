UTILS_LIB_PATH = /mnt/d/nbigi0/My\ Documents/Coding/C/utils_lib
CONIO_LIB_PATH = /mnt/d/nbigi0/My\ Documents/Coding/C/conio

SOURCEFILES = main.c engine.c _err.c data.c $(CONIO_LIB_PATH)/conio.c $(UTILS_LIB_PATH)/utils.c

OPTIONS = -Wall -Wno-sizeof-pointer-div -Wno-incompatible-pointer-types -Wno-unused-variable -Werror 

LINUX_EXEC = gcc $(OPTIONS) -o CTBG_linux_build $(SOURCEFILES)
WIN32_EXEC = i686-w64-mingw32-gcc $(OPTIONS) -o CTBG_win32_build.exe $(SOURCEFILES)
WIN64_EXEC = x86_64-w64-mingw32-gcc $(OPTIONS) -o CTBG_win64_build.exe $(SOURCEFILES)

game: main.c engine.c _err.c 
	$(LINUX_EXEC)
	$(WIN32_EXEC)
	$(WIN64_EXEC)
