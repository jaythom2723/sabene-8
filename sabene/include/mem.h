#ifndef SAB_MEM_H
#define SAB_MEM_H

#define BOOT_SEGMENT_BASE                       0x0000
#define BOOT_SEGMENT_LIMIT                      0x0200
#define DATA_SEGMENT_BASE                       0x0201
#define DATA_SEGMENT_LIMIT                      0x0FFF
#define PROGRAM_SEGMENT_BASE                    0x1000
#define PROGRAM_SEGMENT_LIMIT                   0x1FFF
#define VIDEO_MEMORY_SEGMENT_BASE               0x2000
#define VIDEO_MEMORY_SEGMENT_LIMIT              0x6B00
#define DISK_SEGMENT_BASE                       0x6B01
#define DISK_SEGMENT_LIMIT                      0x7B00
#define STACK_SEGMENT_BASE                      0x7B01
#define STACK_SEGMENT_LIMIT                     0x8B00
#define VGA_COLOR_SEGMENT_BASE                  0x8B01
#define VGA_COLOR_SEGMENT_LIMIT                 0xD601
#define FREE_SEGMENT_BASE                       0xD602
#define FREE_SEGMENT_LIMIT                      0xFFFF

typedef char obram[DATA_SEGMENT_LIMIT + (STACK_SEGMENT_LIMIT - STACK_SEGMENT_BASE)];
typedef char rom[PROGRAM_SEGMENT_LIMIT - PROGRAM_SEGMENT_BASE];

#endif /* SAB_MEM_H */