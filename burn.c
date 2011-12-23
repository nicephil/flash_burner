#include <stdio.h>
#include <string.h>

/* adjusting each MACRO refer to CHIP Manual */
/* assume 64Bit system and 16bit chip wide */

#define LOCK_LOCKER()
#define UNLOCK_LOCKER()
#define GET_CYCLE()
#define MALLOC(x) malloc(x)
#define FREE(x) free(x)
#define MEMCPY(d,s,z) memcpy(d,s,z)

#define uint8_t unsigned char
#define uint16_t unsigned short
#define uint32_t unsigned int
#define uint64_t unsigned long long
#define int32_t int
#define int64_t long long


#define FLASH_BASE_ADDR 0xFFFFFFFF90000000
#define WORD  volatile uint16_t
#define WORD_T volatile uint16_t
#define SIZE_T uint32_t
#define PRINTF(x...) printf(x)
#define SECTOR_SIZE 0x20000
#define MAX_BUFFER_WORD_COUNT 32

#define CMD_RESET_OFFSET 0x000
#define CMD_UNLOCK_1_OFFSET 0x555
#define CMD_UNLOCK_2_OFFSET 0x2AA
#define CMD_SETUP_OFFSET    0x555

#define CMD_RESET_DATA 0x00F0
#define CMD_UNLOCK_1_DATA 0x00AA
#define CMD_UNLOCK_2_DATA 0x0055
#define CMD_SETUP_DATA    0x0080
#define CMD_SECTOR_ERASE_DATA 0x0030
#define CMD_WRITE_BUFFER_LOAD_DATA 0x0025
#define CMD_WRITE_CONFIRM_DATA 0x0029

#define ERASE_TIMEOUT 3276800000
#define WRITE_TIMEOUT 409600 


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
            (~(SECTOR_SIZE-1)));
    SIZE_T extension1 = (uint64_t)dest_addr%SECTOR_SIZE; 
    SIZE_T extension2 = 0;
    void* fill1 = 0;
    void* fill2 = 0;

    /* number of sectors */
    int n = (size+extension1)/SECTOR_SIZE; 
    if ((size+extension1)%SECTOR_SIZE) {
        n++;
        extension2 = SECTOR_SIZE - ((size+extension1)%SECTOR_SIZE);
    }

    PRINTF ("0x%016llx - 0x%016llx\n", sector_base_addr, sector_base_addr+n*SECTOR_SIZE);
    PRINTF ("sector_base_addr:0x%08x, n:%d, extension1:0x%08x, extension2:0x%08x\n", 
            sector_base_addr, n, extension1, extension2);

    /* store old value */
    if (extension1) {
        fill1 = (void*)MALLOC(extension1);
        MEMCPY(fill1, sector_base_addr, extension1);
    }

    if (extension2) {
        fill2 = (void*)MALLOC(extension2);
        MEMCPY(fill2, (sector_base_addr+n*SECTOR_SIZE)-extension2, extension2);
    }

    /* erase sector */
    //erase_sector();


}

#if 0
/*
 * INPUT:
 * void *sector_addr[] - erased sector base addresses
 * int num - how many sector base addresses specifed in sector_addr[]
 * OUTPUT:
 * -1 - failed
 *  0 - success
 */
inline int sector_erase (void *sector_addr[], int num)
{
    int i = 0;
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
    
    for (i = 0; i < num; i ++) {
        /* write sector erase command */
        *(WORD_T*) (sector_addr[num]) = CMD_SECTOR_ERASE_DATA;
    }


    /* polling */
    WORD_T status = *(WORD_T*)(sector_addr[num-1]);
    int start_cycle = GET_CYCLE();
    while (1)
    {
        /* Read the status and xor it with the old status so we can
           find toggling bits */
        WORD_T old_status = status;
        status = *(WORD_T*)(sector_addr[num-1]);
        WORD_T toggle = status ^ old_status;

        /* Check if the erase in progress bit is toggling */
        if (toggle & (1<<6))
        {
            /* Check hardware timeout */
            if (status & (1<<5))
            {
                /* Chip has signalled a timeout. Reread the status */
                old_status = *(WORD_T*)(sector_addr[num-1]);
                status = *(WORD_T*)(sector_addr[num-1]);
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
 * void *dest_addr - destination address
 * void *data_addr - source address
 * int size - how many bytes
 * OUTPUT:
 * -1 - failed
 *  0 - succsse
 *
 */
inline int program_buffer (void *dest_addr, void *data_addr, int size)
{
    WORD_T* src = (WORD_T*) data_addr;
    WORD_T* dst = (WORD_T*) dest_addr;
    WORD_T wc = (size/sizeof(WORD)) - 1;
    int i = 0;
    LOCK_LOCKER();

    /* reset chip */
    *(WORD_T*) (FLASH_BASE_ADDR + CMD_RESET_OFFSET) = CMD_RESET_DATA;

    /* write unlock cycle 1 */
    *(WORD_T*)(FLASH_BASE_ADDR + CMD_UNLOCK_1_OFFSET) = CMD_UNLOCK_1_DATA;
    /* write unlock cycle 2 */
    *(WORD_T*)(FLASH_BASE_ADDR + CMD_UNLOCK_2_OFFSET) = CMD_UNLOCK_2_DATA;
    /* write write buffer load command */
    *(WORD_T*)(sector_addr) = CMD_WRITE_BUFFER_LOAD_DATA;
    /* write word count */
    *(WORD_T*)(sector_addr) = wc;
    for (i = 0; i < wc; i ++) {
        *dst ++ = *src ++;
    }
    /* write write confirm command */
    *(WORD_T*)(sector_addr) = CMD_WRITE_CONFIRM_DATA;

    /* polling */
    unsigned int start_cycle = GET_CYCLE();
    while (1)
    {
        WORD_T status = *(WORD_T*)sector_addr; 
        if (((status ^ *ptr) & (1<<7)) == 0)
            break;  /* Data matches, this byte is done */
        else if (status & (1<<5))
        {
            /* Hardware timeout, recheck status */
            status = *(WORD_T*)sector_addr;
            if (((status ^ *ptr) & (1<<7)) == 0)
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


    /* write buffer abort reset */
    /* write unlock cycle 1 */
    *(WORD_T*)(FLASH_BASE_ADDR + CMD_UNLOCK_1_OFFSET) = CMD_UNLOCK_1_DATA;
    /* write unlock cycle 2 */
    *(WORD_T*)(FLASH_BASE_ADDR + CMD_UNLOCK_2_OFFSET) = CMD_UNLOCK_2_DATA;
    /* reset chip */
    *(WORD_T*) (FLASH_BASE_ADDR + CMD_RESET_OFFSET) = CMD_RESET_DATA;
}
#endif
