/*    This function flushes the stdio input buffer */
void flush_input(void)
{
    /* getchar returns an int */
    int ch;
    /* Read characters until there are none left */

    do
        ch = getchar();
    while (ch != EOF && ch != '\n');
    /* Clear EOF state */
    clearerr(stdin);
}