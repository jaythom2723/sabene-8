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

#define VIDEO_DATA_SEGMENT_BASE                 0xD602
#define VIDEO_DATA_SEGMENT_LIMIT                0xE602

#define FREE_SEGMENT_BASE                       0xE603
#define FREE_SEGMENT_LIMIT                      0xFFFF

#define BOOT_SEGMENT_SIZE                       (BOOT_SEGMENT_LIMIT - BOOT_SEGMENT_BASE)
#define DATA_SEGMENT_SIZE                       (DATA_SEGMENT_LIMIT - DATA_SEGMENT_BASE)
#define PROGRAM_SEGMENT_SIZE                    (PROGRAM_SEGMENT_LIMIT - PROGRAM_SEGMENT_BASE)
#define VIDEO_MEMORY_SEGMENT_SIZE               (VIDEO_MEMORY_SEGMENT_LIMIT - VIDEO_MEMORY_SEGMENT_BASE)
#define DISK_SEGMENT_SIZE                       (DISK_SEGMENT_LIMIT - DISK_SEGMENT_BASE)
#define STACK_SEGMENT_SIZE                      (STACK_SEGMENT_LIMIT - STACK_SEGMENT_BASE)
#define VGA_COLOR_SEGMENT_SIZE                  (VGA_COLOR_SEGMENT_LIMIT - VGA_COLOR_SEGMENT_BASE)
#define VIDEO_DATA_SEGMENT_SIZE                 (VIDEO_DATA_SEGMENT_LIMIT - VIDEO_DATA_SEGMENT_BASE)
#define FREE_SEGMENT_SIZE                       (FREE_SEGMENT_LIMIT - FREE_SEGMENT_BASE)

typedef char vram[VIDEO_MEMORY_SEGMENT_SIZE + VGA_COLOR_SEGMENT_SIZE + VIDEO_DATA_SEGMENT_SIZE];
typedef char disk[DISK_SEGMENT_SIZE];
typedef char obram[DATA_SEGMENT_SIZE + STACK_SEGMENT_SIZE];
typedef char rom[PROGRAM_SEGMENT_SIZE];
typedef char bootrom[BOOT_SEGMENT_SIZE];

typedef char sprogram_t[DATA_SEGMENT_SIZE + PROGRAM_SEGMENT_SIZE];

#endif /* SAB_MEM_H */