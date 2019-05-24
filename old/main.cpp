#include "Interface.h"

int main()
{
    InterfacePrint();

    int ch;
    do
    {
        scanf("%d", &ch);
        InterfaceHandleCommand(ch);
    } while (ch != 0);
    return 0;
}
