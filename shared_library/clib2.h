#ifndef _CLIB2_H
#define _CLIB2_H

uint32 LIB_Release(struct Interface *Self);
int LIB_Reserved(void);
uint32 LIB_Obtain(struct Interface *Self);

struct Library *LIB_Init(struct Library *Clib2Base, BPTR librarySegment, struct ExecIFace *const iexec);

int library_start(char *argstr,
                  int arglen,
                  struct Library **_DOSBase,
                  struct DOSIFace **_IDOS,
                  int (*start_main)(int, char **, char **),
                  void (*__CTOR_LIST__[])(void),
                  void (*__DTOR_LIST__[])(void));

int32 _start(char *args,
             int arglen,
             struct ExecBase *sysbase);

extern int _main(char *argstr,
                 int arglen,
                 struct Library **_DOSBase,
                 struct DOSIFace **_IDOS,
                 int (*start_main)(int, char **, char **),
                 void (*__CTOR_LIST__[])(void),
                 void (*__DTOR_LIST__[])(void));


#endif