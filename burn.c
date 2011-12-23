#define WORD uint16_t
#define WORD_T volatile uint16_t
#define SECTOR_SIZE 128*1024
#define FLASH_BASE_ADDR 0xFFFFFFFF90000000
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

#define WRITE_TIMEOUT 409600 

#define LOCK_LOCKER()
#define UNLOCK_LOCKER()
#define GET_CYCLE()

/*
 * INPUT:
 * void *sector_addr[] - erased sector base addresses
 * int num - how many sector base addresses specifed in sector_addr[]
 * OUTPUT:
 * -1 - failed
 * 0 - success
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
        *(WORD_T*) (sector_addr[0]) = CMD_SECTOR_ERASE_DATA;
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
 *
 */
inline void program_buffer (void *dest_addr, void *data_addr, int size)
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

    /* write buffer abort reset */
    /* write unlock cycle 1 */
    *(WORD_T*)(FLASH_BASE_ADDR + CMD_UNLOCK_1_OFFSET) = CMD_UNLOCK_1_DATA;
    /* write unlock cycle 2 */
    *(WORD_T*)(FLASH_BASE_ADDR + CMD_UNLOCK_2_OFFSET) = CMD_UNLOCK_2_DATA;
    /* reset chip */
    *(WORD_T*) (FLASH_BASE_ADDR + CMD_RESET_OFFSET) = CMD_RESET_DATA;
}
