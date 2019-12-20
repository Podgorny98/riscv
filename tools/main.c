
int main()
{
    int src = 1;
    int dst;   

    char buf[10];
    buf[11] = 5;

    /*
    asm ("mov %1, %0\n\t"
        "add $1, %0"
        : "=r" (dst) 
        : "r" (src));
    */
    return 0;
}
