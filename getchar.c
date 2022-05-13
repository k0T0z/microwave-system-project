
// implements a debouncing algorithm
//  to solve problems with get key function

unsigned char getchar(void)

{
    unsigned char key;

    // wait until previous key is released
    //  getkey() returns 0 when no key is pressed
    do
    {
        while (getkey() != 0) // previous key pressed
            ;
        delayms(20); // wait for debounce
    } while (getkey() != 0);

    do
    {
        key = getkey();
        
        delayms(20); // wait for debounce
    } while (getkey() != key);

    return key;
}