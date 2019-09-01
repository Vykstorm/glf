##!nmake

!include <win32.mak>

OPENGL = glut32.lib glu32.lib opengl32.lib

CFILES  = simply.c wired.c solid.c 3dtext.c demo1.c symtest.c textured.c \
          romkalogo.c console.c solid3d.c contour.c bitmap_text.c bitmap_text2.c \
          bitmap_sym.c bitmap_scale.c bitmap_mask.c bitmap_mult.c bitmap_centering.c \
          centering.c direction.c

TARGETS	= $(CFILES:.c=.exe)
LCFLAGS	= $(cflags) -DWIN32
LLDLIBS	= $(lflags) $(OPENGL) $(guilibs)

default	: $(TARGETS)

$(TARGETS): $*.obj
        $(link) -out:$@ $** $(LLDLIBS)

.c.obj	: 
	$(CC) $(LCFLAGS) $<

# dependencies (must come AFTER inference rules)
simply.exe	 : glf.obj
wired.exe	 : glf.obj
solid.exe	 : glf.obj
3dtext.exe	 : glf.obj
demo1.exe	 : glf.obj
symtest.exe	 : glf.obj
textured.exe	 : glf.obj texture.obj
romkalogo.exe	 : glf.obj
console.exe	 : glf.obj
solid3d.exe	 : glf.obj
contour.exe	 : glf.obj
bitmap_text.exe	 : glf.obj
bitmap_text2.exe : glf.obj
bitmap_sym.exe	 : glf.obj
bitmap_scale.exe : glf.obj
bitmap_mask.exe  : glf.obj texture.obj
bitmap_mult.exe  : glf.obj
bitmap_centering.exe  : glf.obj
centering.exe  : glf.obj
direction.exe  : glf.obj

glf.obj	: ../glf.c
	$(CC) $(LCFLAGS) ../glf.c
texture.obj	: texture.c
	$(CC) $(LCFLAGS) texture.c
