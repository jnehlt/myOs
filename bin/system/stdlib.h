/* stdlib implementation */

void
memset(void *destination, int c, unsigned int target_size)
{
    if(target_size)
    {
        char *dst = destination;
        do {
            *dst++ = c;
        } while(--target_size);
    }
}
