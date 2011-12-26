#include <stdio.h>
#include <string.h>
#include <cvmx.h>

/* adjusting each MACRO refer to CHIP Manual */
/* assume 64Bit system and 16bit chip wide */

#define LOCK_LOCKER()
#define UNLOCK_LOCKER()
#define GET_CYCLE() cvmx_get_cycle()
#define MALLOC(x) malloc(x)
#define FREE(x) free(x)
#define MEMCPY(d,s,z) memcpy(d,s,z)

#define uint8_t unsigned char
#define uint16_t unsigned short
#define uint32_t unsigned int
#define uint64_t unsigned long long
#define int32_t int
#define int64_t long long


#define FLASH_BASE_ADDR 0xFFFFFFFF90000000ULL
#define WORD  volatile uint16_t
#define WORD_T volatile uint16_t
#define SIZE_T uint64_t
#define PRINTF(x...) printf(x)
#define SECTOR_SIZE 0x20000
#define MAX_BUFFER_WORD_COUNT 32

#define CMD_RESET_OFFSET (0x000<<1)
#define CMD_UNLOCK_1_OFFSET (0x555<<1)
#define CMD_UNLOCK_2_OFFSET (0x2AA<<1)
#define CMD_SETUP_OFFSET    (0x555<<1)

#define CMD_RESET_DATA 0x00FF
#define CMD_UNLOCK_1_DATA 0x00AA
#define CMD_UNLOCK_2_DATA 0x0055
#define CMD_SETUP_DATA    0x0080
#define CMD_SECTOR_ERASE_DATA 0x0030
#define CMD_WRITE_BUFFER_LOAD_DATA 0x0025
#define CMD_WRITE_CONFIRM_DATA 0x0029

#define ERASE_TIMEOUT 3276800000ULL
#define WRITE_TIMEOUT 409600 


inline int sector_erase (void *sector_addr);
inline int program_sector_by_buffer (void *sector_addr, void *data_addr);

/*
 * INPUT:
 * void *dest_addr - destination address
 * void *src_addr - source address
 * SIZE_T size - how many bytes
 * OUTPUT:
 * -1 - failed
 *  0 - succsse
 *
 */
inline int memcpy2flash (void *dest_addr, void *src_addr, SIZE_T size)
{
    uint64_t sector_base_addr = ((uint64_t)dest_addr&
            (~(SECTOR_SIZE-1))); /* SECTOR_SIZE align */
    SIZE_T extension1 = (uint64_t)dest_addr%SECTOR_SIZE; /* beginning extension size */ 
    SIZE_T extension2 = 0;
    int i = 0;
    void* fill = (void *)MALLOC(SECTOR_SIZE*2); /* reserve two sectors size */

    /* number of sectors */
    int n = (size+extension1)/SECTOR_SIZE; 
    if ((size+extension1)%SECTOR_SIZE) {
        n++;
        extension2 = SECTOR_SIZE - ((size+extension1)%SECTOR_SIZE); /* last extension size */
    }

    PRINTF ("0x%016llx - 0x%016llx\n", sector_base_addr, sector_base_addr+n*SECTOR_SIZE);
    PRINTF ("sector_base_addr:0x%016llx, n:%d, extension1:0x%016llx, extension2:0x%016llx\n", 
            sector_base_addr, n, extension1, extension2);

    /* store old content at beginning and last two sectors */
    MEMCPY(fill, (void*)(sector_base_addr), SECTOR_SIZE);
    MEMCPY((uint8_t*)fill+SECTOR_SIZE, (void*)((uint8_t*)sector_base_addr+(n-1)*SECTOR_SIZE), SECTOR_SIZE);
    *(uint64_t*)fill = 0xFF12FF34FF56FF78ULL;
    *((uint64_t*)fill+5) = 0xFF12FF34FF56FF78ULL;
    *(uint64_t*)((uint8_t*)fill+SECTOR_SIZE) = 0xFF12FF34FF56FF78ULL;
    *((uint64_t*)((uint8_t*)fill+SECTOR_SIZE)+5) = 0xFF12FF34FF56FF78ULL;


    /* erase sector */

    /* verify content */
    for (i = 0; i < 10; i ++) {
        printf ("0x%016llx\n", *((uint64_t*)sector_base_addr+i));
    }
    printf ("=====================\n");
    for (i = 0; i < 10; i ++) {
        printf ("0x%016llx\n", *((uint64_t*)((uint8_t*)sector_base_addr+(n-1)*SECTOR_SIZE)+i));
    }

    for (i = 0; i < n; i ++) {
        sector_erase((void*)((uint8_t*)sector_base_addr+i*SECTOR_SIZE));
        program_sector_by_buffer((void*)((uint8_t*)sector_base_addr+i*SECTOR_SIZE), (void*)((uint8_t*)fill+i*SECTOR_SIZE));
    }

    printf ("after erase\n");

    /* verify content */
    for (i = 0; i < 10; i ++) {
        printf ("0x%016llx\n", *((uint64_t*)sector_base_addr+i));
    }
    printf ("=====================\n");
    for (i = 0; i < 10; i ++) {
        printf ("0x%016llx\n", *((uint64_t*)((uint8_t*)sector_base_addr+(n-1)*SECTOR_SIZE)+i));
    }

__cleanup:
    if (fill) {
        FREE(fill);
    }

    return 0;
}

/*
 * INPUT:
 * void *sector_addr - erased sector base addresses
 * OUTPUT:
 * -1 - failed
 *  0 - success
 */
inline int sector_erase (void *sector_addr)
{
    LOCK_LOCKER();

    /* reset chip */
    *(WORD_T*) (FLASH_BASE_ADDR + CMD_RESET_OFFSET) = CMD_RESET_DATA;


    /* write unlock cycle 1 */
    *(WORD_T*) (FLASH_BASE_ADDR + CMD_UNLOCK_1_OFFSET) = CMD_UNLOCK_1_DATA;
    /* write unlock cycle 2 */
    *(WORD_T*) (FLASH_BASE_ADDR + CMD_UNLOCK_2_OFFSET) = CMD_UNLOCK_2_DATA;

    /* write setup command */
    *(WORD_T*) (FLASH_BASE_ADDR + CMD_SETUP_OFFSET) = CMD_SETUP_DATA;
    /* write additional cycle 1 */
    *(WORD_T*) (FLASH_BASE_ADDR + CMD_UNLOCK_1_OFFSET) = CMD_UNLOCK_1_DATA;
    /* write additional cycle 2 */
    *(WORD_T*) (FLASH_BASE_ADDR + CMD_UNLOCK_2_OFFSET) = CMD_UNLOCK_2_DATA;
    /* write sector erase command */
    *(WORD_T*) (sector_addr) = CMD_SECTOR_ERASE_DATA;


    /* polling */
    WORD_T status = *(WORD_T*)(sector_addr);
    uint64_t start_cycle = GET_CYCLE();
    while (1)
    {
        /* Read the status and xor it with the old status so we can
           find toggling bits */
        WORD_T old_status = status;
        status = *(WORD_T*)(sector_addr);
        WORD_T toggle = status ^ old_status;

        /* Check if the erase in progress bit is toggling */
        if (toggle & (1<<6))
        {
            /* Check hardware timeout */
            if (status & (1<<5))
            {
                /* Chip has signalled a timeout. Reread the status */
                old_status = *(WORD_T*)(sector_addr);
                status = *(WORD_T*)(sector_addr);
                toggle = status ^ old_status;

                /* Check if the erase in progress bit is toggling */
                if (toggle & (1<<6))
                {
                    printf ("Hardware timeout erasing sector\n");
                    UNLOCK_LOCKER();
                    return -1;
                }
                else
                    break;  /* Not toggling, erase complete */
            }
        }
        else
            break;  /* Not toggling, erase complete */

        if (GET_CYCLE() > start_cycle + ERASE_TIMEOUT)
        {
            printf ("Timeout erasing block\n");
            UNLOCK_LOCKER();
            return -1;
        }
    }

    /* reset chip */
    *(WORD_T*) (FLASH_BASE_ADDR + CMD_RESET_OFFSET) = CMD_RESET_DATA;
    UNLOCK_LOCKER();
    return 0;
}


/*
 * INPUT:
 * void *sector_addr - destination address
 * void *data_addr - source address
 * OUTPUT:
 * -1 - failed
 *  0 - succsse
 *
 */
inline int program_sector_by_buffer (void *sector_addr, void *data_addr)
{
    WORD_T* src = (WORD_T*) data_addr;
    WORD_T* dst = (WORD_T*) sector_addr;
    int num = SECTOR_SIZE/(MAX_BUFFER_WORD_COUNT*2);
    int i = 0;
    LOCK_LOCKER();

    /* reset chip */
    *(WORD_T*) (FLASH_BASE_ADDR + CMD_RESET_OFFSET) = CMD_RESET_DATA;

    for (i = 0; i < num; i ++) {
        /* write unlock cycle 1 */
        *(WORD_T*)(FLASH_BASE_ADDR + CMD_UNLOCK_1_OFFSET) = CMD_UNLOCK_1_DATA;
        /* write unlock cycle 2 */
        *(WORD_T*)(FLASH_BASE_ADDR + CMD_UNLOCK_2_OFFSET) = CMD_UNLOCK_2_DATA;
        /* write write buffer load command */
        *(WORD_T*)(sector_addr) = CMD_WRITE_BUFFER_LOAD_DATA;
        /* write word count */
        *(WORD_T*)(sector_addr) = MAX_BUFFER_WORD_COUNT-1;
        for (i = 0; i < MAX_BUFFER_WORD_COUNT; i ++) {
            *dst ++ = *src ++;
        }
        /* write write confirm command */
        *(WORD_T*)(sector_addr) = CMD_WRITE_CONFIRM_DATA;

        /* polling */
        unsigned int start_cycle = GET_CYCLE();
        while (1)
        {
            WORD_T status = *(WORD_T*)sector_addr; 
            if (((status ^ *src) & (1<<7)) == 0)
                break;  /* Data matches, this byte is done */
            else if (status & (1<<5))
            {
                /* Hardware timeout, recheck status */
                status = *(WORD_T*)sector_addr;
                if (((status ^ *src) & (1<<7)) == 0)
                    break;  /* Data matches, this byte is done */
                else
                {
                    printf ("Hardware write timeout\n");
                    UNLOCK_LOCKER();
                    return -1;
                }
            }

            if (GET_CYCLE() > start_cycle + WRITE_TIMEOUT)
            {
                printf ("Timeout writing block\n");
                UNLOCK_LOCKER();
                return -1;
            }
        }
        src += MAX_BUFFER_WORD_COUNT;
        dst += MAX_BUFFER_WORD_COUNT;
    }


    /* write buffer abort reset */
    /* write unlock cycle 1 */
    *(WORD_T*)(FLASH_BASE_ADDR + CMD_UNLOCK_1_OFFSET) = CMD_UNLOCK_1_DATA;
    /* write unlock cycle 2 */
    *(WORD_T*)(FLASH_BASE_ADDR + CMD_UNLOCK_2_OFFSET) = CMD_UNLOCK_2_DATA;
    /* reset chip */
    *(WORD_T*) (FLASH_BASE_ADDR + CMD_RESET_OFFSET) = CMD_RESET_DATA;
    return 0;
}
