##!nmake

!include <win32.mak>

OPENGL = glut32.lib glu32.lib opengl32.lib

CFILES  = test.c
TARGETS	= $(CFILES:.c=.exe)
LCFLAGS	= $(cflags) -DWIN32
LLDLIBS	= $(lflags) $(OPENGL) $(guilibs)

default	: $(TARGETS)

$(TARGETS): $*.obj
        $(link) -out:$@ $** $(LLDLIBS)

.c.obj	: 
	$(CC) $(LCFLAGS) $<

# dependencies (must come AFTER inference rules)
test.exe	: glf.obj

glf.obj	: glf.c
	$(CC) $(LCFLAGS) glf.c
