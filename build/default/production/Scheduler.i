# 1 "Scheduler.c"
# 1 "<built-in>" 1
# 1 "<built-in>" 3
# 288 "<built-in>" 3
# 1 "<command line>" 1
# 1 "<built-in>" 2
# 1 "C:/Program Files (x86)/Microchip/MPLABX/v5.35/packs/Microchip/PIC16Fxxx_DFP/1.2.33/xc8\\pic\\include\\language_support.h" 1 3
# 2 "<built-in>" 2
# 1 "Scheduler.c" 2
# 1 "./Scheduler.h" 1



# 1 "./SchedulerConfig.h" 1





# 1 "C:\\Program Files\\Microchip\\xc8\\v2.20\\pic\\include\\c90\\stdio.h" 1 3



# 1 "C:/Program Files (x86)/Microchip/MPLABX/v5.35/packs/Microchip/PIC16Fxxx_DFP/1.2.33/xc8\\pic\\include\\__size_t.h" 1 3



typedef unsigned size_t;
# 4 "C:\\Program Files\\Microchip\\xc8\\v2.20\\pic\\include\\c90\\stdio.h" 2 3

# 1 "C:/Program Files (x86)/Microchip/MPLABX/v5.35/packs/Microchip/PIC16Fxxx_DFP/1.2.33/xc8\\pic\\include\\__null.h" 1 3
# 5 "C:\\Program Files\\Microchip\\xc8\\v2.20\\pic\\include\\c90\\stdio.h" 2 3






# 1 "C:\\Program Files\\Microchip\\xc8\\v2.20\\pic\\include\\c90\\stdarg.h" 1 3






typedef void * va_list[1];

#pragma intrinsic(__va_start)
extern void * __va_start(void);

#pragma intrinsic(__va_arg)
extern void * __va_arg(void *, ...);
# 11 "C:\\Program Files\\Microchip\\xc8\\v2.20\\pic\\include\\c90\\stdio.h" 2 3
# 43 "C:\\Program Files\\Microchip\\xc8\\v2.20\\pic\\include\\c90\\stdio.h" 3
struct __prbuf
{
 char * ptr;
 void (* func)(char);
};
# 85 "C:\\Program Files\\Microchip\\xc8\\v2.20\\pic\\include\\c90\\stdio.h" 3
# 1 "C:\\Program Files\\Microchip\\xc8\\v2.20\\pic\\include\\c90\\conio.h" 1 3







# 1 "C:\\Program Files\\Microchip\\xc8\\v2.20\\pic\\include\\c90\\errno.h" 1 3
# 29 "C:\\Program Files\\Microchip\\xc8\\v2.20\\pic\\include\\c90\\errno.h" 3
extern int errno;
# 8 "C:\\Program Files\\Microchip\\xc8\\v2.20\\pic\\include\\c90\\conio.h" 2 3




extern void init_uart(void);

extern char getch(void);
extern char getche(void);
extern void putch(char);
extern void ungetch(char);

extern __bit kbhit(void);



extern char * cgets(char *);
extern void cputs(const char *);
# 85 "C:\\Program Files\\Microchip\\xc8\\v2.20\\pic\\include\\c90\\stdio.h" 2 3



extern int cprintf(char *, ...);
#pragma printf_check(cprintf)



extern int _doprnt(struct __prbuf *, const register char *, register va_list);
# 180 "C:\\Program Files\\Microchip\\xc8\\v2.20\\pic\\include\\c90\\stdio.h" 3
#pragma printf_check(vprintf) const
#pragma printf_check(vsprintf) const

extern char * gets(char *);
extern int puts(const char *);
extern int scanf(const char *, ...) __attribute__((unsupported("scanf() is not supported by this compiler")));
extern int sscanf(const char *, const char *, ...) __attribute__((unsupported("sscanf() is not supported by this compiler")));
extern int vprintf(const char *, va_list) __attribute__((unsupported("vprintf() is not supported by this compiler")));
extern int vsprintf(char *, const char *, va_list) __attribute__((unsupported("vsprintf() is not supported by this compiler")));
extern int vscanf(const char *, va_list ap) __attribute__((unsupported("vscanf() is not supported by this compiler")));
extern int vsscanf(const char *, const char *, va_list) __attribute__((unsupported("vsscanf() is not supported by this compiler")));

#pragma printf_check(printf) const
#pragma printf_check(sprintf) const
extern int sprintf(char *, const char *, ...);
extern int printf(const char *, ...);
# 6 "./SchedulerConfig.h" 2

# 1 "C:\\Program Files\\Microchip\\xc8\\v2.20\\pic\\include\\c90\\stdint.h" 1 3
# 13 "C:\\Program Files\\Microchip\\xc8\\v2.20\\pic\\include\\c90\\stdint.h" 3
typedef signed char int8_t;






typedef signed int int16_t;







typedef __int24 int24_t;







typedef signed long int int32_t;
# 52 "C:\\Program Files\\Microchip\\xc8\\v2.20\\pic\\include\\c90\\stdint.h" 3
typedef unsigned char uint8_t;





typedef unsigned int uint16_t;






typedef __uint24 uint24_t;






typedef unsigned long int uint32_t;
# 88 "C:\\Program Files\\Microchip\\xc8\\v2.20\\pic\\include\\c90\\stdint.h" 3
typedef signed char int_least8_t;







typedef signed int int_least16_t;
# 109 "C:\\Program Files\\Microchip\\xc8\\v2.20\\pic\\include\\c90\\stdint.h" 3
typedef __int24 int_least24_t;
# 118 "C:\\Program Files\\Microchip\\xc8\\v2.20\\pic\\include\\c90\\stdint.h" 3
typedef signed long int int_least32_t;
# 136 "C:\\Program Files\\Microchip\\xc8\\v2.20\\pic\\include\\c90\\stdint.h" 3
typedef unsigned char uint_least8_t;






typedef unsigned int uint_least16_t;
# 154 "C:\\Program Files\\Microchip\\xc8\\v2.20\\pic\\include\\c90\\stdint.h" 3
typedef __uint24 uint_least24_t;







typedef unsigned long int uint_least32_t;
# 181 "C:\\Program Files\\Microchip\\xc8\\v2.20\\pic\\include\\c90\\stdint.h" 3
typedef signed char int_fast8_t;






typedef signed int int_fast16_t;
# 200 "C:\\Program Files\\Microchip\\xc8\\v2.20\\pic\\include\\c90\\stdint.h" 3
typedef __int24 int_fast24_t;







typedef signed long int int_fast32_t;
# 224 "C:\\Program Files\\Microchip\\xc8\\v2.20\\pic\\include\\c90\\stdint.h" 3
typedef unsigned char uint_fast8_t;





typedef unsigned int uint_fast16_t;
# 240 "C:\\Program Files\\Microchip\\xc8\\v2.20\\pic\\include\\c90\\stdint.h" 3
typedef __uint24 uint_fast24_t;






typedef unsigned long int uint_fast32_t;
# 268 "C:\\Program Files\\Microchip\\xc8\\v2.20\\pic\\include\\c90\\stdint.h" 3
typedef int32_t intmax_t;
# 282 "C:\\Program Files\\Microchip\\xc8\\v2.20\\pic\\include\\c90\\stdint.h" 3
typedef uint32_t uintmax_t;






typedef int16_t intptr_t;




typedef uint16_t uintptr_t;
# 7 "./SchedulerConfig.h" 2

# 1 "C:\\Program Files\\Microchip\\xc8\\v2.20\\pic\\include\\c90\\stdlib.h" 1 3






typedef unsigned short wchar_t;







typedef struct {
 int rem;
 int quot;
} div_t;
typedef struct {
 unsigned rem;
 unsigned quot;
} udiv_t;
typedef struct {
 long quot;
 long rem;
} ldiv_t;
typedef struct {
 unsigned long quot;
 unsigned long rem;
} uldiv_t;
# 65 "C:\\Program Files\\Microchip\\xc8\\v2.20\\pic\\include\\c90\\stdlib.h" 3
extern double atof(const char *);
extern double strtod(const char *, const char **);
extern int atoi(const char *);
extern unsigned xtoi(const char *);
extern long atol(const char *);



extern long strtol(const char *, char **, int);

extern int rand(void);
extern void srand(unsigned int);
extern void * calloc(size_t, size_t);
extern div_t div(int numer, int denom);
extern udiv_t udiv(unsigned numer, unsigned denom);
extern ldiv_t ldiv(long numer, long denom);
extern uldiv_t uldiv(unsigned long numer,unsigned long denom);



extern unsigned long _lrotl(unsigned long value, unsigned int shift);
extern unsigned long _lrotr(unsigned long value, unsigned int shift);
extern unsigned int _rotl(unsigned int value, unsigned int shift);
extern unsigned int _rotr(unsigned int value, unsigned int shift);




extern void * malloc(size_t);
extern void free(void *);
extern void * realloc(void *, size_t);




# 1 "C:\\Program Files\\Microchip\\xc8\\v2.20\\pic\\include\\c90\\xc8debug.h" 1 3
# 13 "C:\\Program Files\\Microchip\\xc8\\v2.20\\pic\\include\\c90\\xc8debug.h" 3
#pragma intrinsic(__builtin_software_breakpoint)
extern void __builtin_software_breakpoint(void);
# 99 "C:\\Program Files\\Microchip\\xc8\\v2.20\\pic\\include\\c90\\stdlib.h" 2 3





extern int atexit(void (*)(void));
extern char * getenv(const char *);
extern char ** environ;
extern int system(char *);
extern void qsort(void *, size_t, size_t, int (*)(const void *, const void *));
extern void * bsearch(const void *, void *, size_t, size_t, int(*)(const void *, const void *));
extern int abs(int);
extern long labs(long);

extern char * itoa(char * buf, int val, int base);
extern char * utoa(char * buf, unsigned val, int base);




extern char * ltoa(char * buf, long val, int base);
extern char * ultoa(char * buf, unsigned long val, int base);

extern char * ftoa(float f, int * status);
# 8 "./SchedulerConfig.h" 2

# 1 "C:\\Program Files\\Microchip\\xc8\\v2.20\\pic\\include\\c90\\string.h" 1 3
# 14 "C:\\Program Files\\Microchip\\xc8\\v2.20\\pic\\include\\c90\\string.h" 3
extern void * memcpy(void *, const void *, size_t);
extern void * memmove(void *, const void *, size_t);
extern void * memset(void *, int, size_t);
# 36 "C:\\Program Files\\Microchip\\xc8\\v2.20\\pic\\include\\c90\\string.h" 3
extern char * strcat(char *, const char *);
extern char * strcpy(char *, const char *);
extern char * strncat(char *, const char *, size_t);
extern char * strncpy(char *, const char *, size_t);
extern char * strdup(const char *);
extern char * strtok(char *, const char *);


extern int memcmp(const void *, const void *, size_t);
extern int strcmp(const char *, const char *);
extern int stricmp(const char *, const char *);
extern int strncmp(const char *, const char *, size_t);
extern int strnicmp(const char *, const char *, size_t);
extern void * memchr(const void *, int, size_t);
extern size_t strcspn(const char *, const char *);
extern char * strpbrk(const char *, const char *);
extern size_t strspn(const char *, const char *);
extern char * strstr(const char *, const char *);
extern char * stristr(const char *, const char *);
extern char * strerror(int);
extern size_t strlen(const char *);
extern char * strchr(const char *, int);
extern char * strichr(const char *, int);
extern char * strrchr(const char *, int);
extern char * strrichr(const char *, int);
# 9 "./SchedulerConfig.h" 2
# 56 "./SchedulerConfig.h"
typedef int8_t BaseType_t;
typedef uint8_t UBaseType_t;
typedef uint16_t TickType_t;

typedef union
{
    struct
    {
        UBaseType_t bit0:1;
        UBaseType_t bit1:1;
        UBaseType_t bit2:1;
        UBaseType_t bit3:1;
        UBaseType_t bit4:1;
        UBaseType_t bit5:1;
        UBaseType_t bit6:1;
        UBaseType_t bit7:1;
    }Bits_t;
    UBaseType_t reg:8;
}Reg_t;



void Scheduler_initSysTick( TickType_t msTicksPeriod );
void Scheduler_displayError( UBaseType_t errorCode );
void Scheduler_sleepHardware( void );
void Scheduler_delayHardwareMs( volatile uint32_t msDelay );
void Scheduler_delayHardwareUs( volatile uint32_t usDelay );
void Scheduler_delaySoftwareMs( volatile uint32_t msDelay );
void Scheduler_delaySoftwareUs( volatile uint32_t usDelay );
# 4 "./Scheduler.h" 2


void Scheduler_init( void );
UBaseType_t Scheduler_addTask( void (*task)( void *paramter ), void *paramter, UBaseType_t delay, UBaseType_t period );
UBaseType_t Scheduler_deleteTask( UBaseType_t index );
void Scheduler_start( void );
void Scheduler_update( void );
void Scheduler_dispatchTasks( void );
void Scheduler_reportStatus( void );
void Scheduler_goToSleep( void );
# 1 "Scheduler.c" 2


typedef struct
{
 void (*pointer)( void *paramter );
 void *paramter;
 UBaseType_t delay;
 UBaseType_t period;
 UBaseType_t runMe;
}Task_t;

typedef struct
{
 Task_t task[ ( ( UBaseType_t ) 10 ) ];
 UBaseType_t errorCode;
 UBaseType_t interruptFlag;
}Scheduler_t;

volatile static Scheduler_t scheduler;

void Scheduler_init( void )
{
 size_t index = 0;
 for( index = 0; index < ( ( UBaseType_t ) 10 ); index++ )
 {
  Scheduler_deleteTask( index );
 }
 scheduler.errorCode = 0;
 scheduler.interruptFlag = 0;
}

UBaseType_t Scheduler_addTask( void (*task)( void *paramter ), void *paramter, UBaseType_t delay, UBaseType_t period )
{
 size_t index = 0;
 for( index = 0; index < ( ( UBaseType_t ) 10 ); index++ )
 {
  if( scheduler.task[ index ].pointer == 0 )
  {
   break;
  }
 }
 if( index == ( ( UBaseType_t ) 10 ) )
 {
  return ( ( UBaseType_t ) 10 );
 }
 scheduler.task[ index ].pointer = task;
 scheduler.task[ index ].paramter = paramter;
 scheduler.task[ index ].delay = delay;
 scheduler.task[ index ].period = period;
 scheduler.task[ index ].runMe = 0;
 return index;
}

UBaseType_t Scheduler_deleteTask( UBaseType_t index )
{
 if( scheduler.task[ index ].pointer == 0 )
 {
  return ( 0 );
 }
 scheduler.task[ index ].pointer = 0x00000000;
 scheduler.task[ index ].paramter = 0x00000000;
 scheduler.task[ index ].delay = 0;
 scheduler.task[ index ].period = 0;
 scheduler.task[ index ].runMe = 0;
 return ( !( 0 ) );
}

void Scheduler_start( void )
{
 Scheduler_initSysTick( ( ( TickType_t ) 5 ) );
}

void Scheduler_reportStatus( void )
{
 if( scheduler.interruptFlag == 1 )
 {
  scheduler.errorCode = ( 1 );
 }
 Scheduler_displayError( scheduler.errorCode );
}

void Scheduler_goToSleep( void )
{
 if( scheduler.interruptFlag == 1 )
 {
  scheduler.interruptFlag = 0;
 }
 while( scheduler.interruptFlag == 0 )
 {
  Scheduler_sleepHardware();
 }
 scheduler.interruptFlag = 0;
}

void Scheduler_update( void )
{
 size_t index = 0;
 for( index = 0; index < ( ( UBaseType_t ) 10 ); index++ )
 {
  if( scheduler.task[ index ].pointer != 0 )
  {
   if( scheduler.task[ index ].delay == 0 )
   {
    scheduler.task[ index ].runMe = 1;
    scheduler.task[ index ].delay = scheduler.task[ index ].period;
   }
   if( scheduler.task[ index ].delay != 0 )
   {
    scheduler.task[ index ].delay--;
   }
  }
 }
 scheduler.interruptFlag = 1;
}

void Scheduler_dispatchTasks( void )
{
 size_t index = 0;
 for( index = 0; index < ( ( UBaseType_t ) 10 ); index++ )
 {
  if( scheduler.task[ index ].runMe != 0 )
  {
   (*scheduler.task[ index ].pointer)( scheduler.task[ index ].paramter );
   scheduler.task[ index ].runMe = 0;
   if( scheduler.task[ index ].period == 0 )
   {
    Scheduler_deleteTask( index );
   }
  }
 }
 Scheduler_reportStatus();
 Scheduler_goToSleep();
}
