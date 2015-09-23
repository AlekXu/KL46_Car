
#include "printf.h"

#if (  __UART_DEBUG__  )
#include "UART/uart.h"
//#include "DMA/dma.h"

#define Printf_Struct       DEBUG_UART_Struct

int UART_printf(const char *fmt, ...)
{
    static char init_flag = 0;
    va_list args;
    int count;
    char buffer[PRINTF_BUFFER_SIZE];

    va_start(args, fmt);
    count = vsnprintf(buffer, sizeof(buffer), fmt, args);
    va_end(args);

    if (!init_flag)
        UART_Init(&Printf_Struct);
    /*
        DMA_Struct_TypeDef Printf_DMA_Struct =
        {
            DMAMUX0_UART0_TX,
            DMA_CH0,
            count,
            DMA_Simply,
            DMA_CS_Default,
            {(unsigned long)buffer, DMA_Size_8b, DMA_ADDR_INC, Buffer_Default},
            {(unsigned long)&UART0_D, DMA_Size_8b, DMA_ADDR_DIS, Buffer_Default},
        };

        DMA_Init(&Printf_DMA_Struct);
        UART_TX_DMA_Enable(&Printf_Struct);
        DMA_Start(&Printf_DMA_Struct);

        return(0);
    */
    UART_SendNBytes(&Printf_Struct, buffer, count);

    return (count);
}

int UART_scanf(const char *fmt, ...)
{
    static char init_flag = 0;
    char ch;
    va_list args;
    int count = 0;
    char buffer[PRINTF_BUFFER_SIZE];

    if (!init_flag)
        UART_Init(&Printf_Struct);

    while (1)
    {
        ch = __UART_RecvByte(&Printf_Struct);
        UART_SendByte(&Printf_Struct, ch);
        if ((ch == 0x0d) || (ch == 0x0a))
        {
            buffer[count] = '\0';
            break;
        }
        else
        {
            buffer[count++] = ch;
        }
    }

    va_start(args, fmt);
    count = vsnprintf(buffer, sizeof(buffer), fmt, args);
    va_end(args);

    UART_SendByte(&Printf_Struct, '\r');
    UART_SendByte(&Printf_Struct, '\n');

    return (count);
}

#else

inline int UART_printf(const char *fmt, ...)
{
    return (0);
}

inline int UART_scanf(const char *fmt, ...)
{
    return (0);
}

#endif


#if ( __DISPLAY_DEBUG__ )

#include "SSD130x/ssd130x.h"

#define DISPLAY_FONT_WIDTH     6
#define DISPLAY_LINE_NUM       SSD130x_LINE_NUM
#define DISPLAY_COLUMN_NUM     (SSD130x_COLUMN_NUM / DISPLAY_FONT_WIDTH)
static char Displaybuf[DISPLAY_LINE_NUM][DISPLAY_COLUMN_NUM];
static unsigned int Display_FontLine = 0;
static unsigned int Display_FontColumn = 0;
static unsigned char Display_FlagOut = 0;
static unsigned char Display_OutLine = 0;
int Display_printf(const char *fmt, ...)
{
    static char init_flag = 0;
    unsigned int tmpnum, fpoint;
    va_list args;
    int count;
    char buffer[PRINTF_BUFFER_SIZE];

    if (!init_flag)
        SSD130x_Init();

    va_start(args, fmt);
    count = vsnprintf(buffer, sizeof(buffer), fmt, args);
    va_end(args);

    for (fpoint = 0; fpoint < count; fpoint++)
    {
        switch (buffer[fpoint])
        {
        case '\n':
        case '\r':
            Displaybuf[Display_FontLine][Display_FontColumn] = '\0';
            Display_FontColumn = 0;
            if (++Display_FontLine >= DISPLAY_LINE_NUM)
            {
                Display_FontLine = 0;
                Display_FlagOut = 1;
            }
            if (Display_FlagOut)
                Display_OutLine = (Display_OutLine + 1) % DISPLAY_LINE_NUM;
            Displaybuf[Display_FontLine][Display_FontColumn] = '\0';
            break;

        case '\t':
            tmpnum = (((Display_FontColumn >> 2) + 1) << 2) - Display_FontColumn;
            while (tmpnum--)
            {
                Displaybuf[Display_FontLine][Display_FontColumn] = ' ';
                if (++Display_FontColumn >= DISPLAY_COLUMN_NUM)
                {
                    Display_FontColumn = 0;
                    if (++Display_FontLine >= DISPLAY_LINE_NUM)
                    {
                        Display_FontLine = 0;
                        Display_FlagOut = 1;
                    }
                    if (Display_FlagOut)
                        Display_OutLine = (Display_OutLine + 1) % DISPLAY_LINE_NUM;
                }
                Displaybuf[Display_FontLine][Display_FontColumn] = '\0';
            }
            break;

        default:
            Displaybuf[Display_FontLine][Display_FontColumn] = buffer[fpoint];
            if (++Display_FontColumn >= DISPLAY_COLUMN_NUM)
            {
                Display_FontColumn = 0;
                if (++Display_FontLine >= DISPLAY_LINE_NUM)
                {
                    Display_FontLine = 0;
                    Display_FlagOut = 1;
                }
                if (Display_FlagOut)
                    Display_OutLine = (Display_OutLine + 1) % DISPLAY_LINE_NUM;
            }
            Displaybuf[Display_FontLine][Display_FontColumn] = '\0';
        }
    }

    for (tmpnum = 0; tmpnum < DISPLAY_LINE_NUM; tmpnum++)
    {
        SSD130x_PLineClr(tmpnum);
        SSD130x_PStr6x8(tmpnum, 0, Displaybuf[(tmpnum + Display_OutLine) % DISPLAY_LINE_NUM]);
    }

    return (count);
}

void Display_CLS(void)
{
    static char init_flag = 0;

    if (!init_flag)
        SSD130x_Init();

    Display_FontColumn = 0;
    for (Display_FontLine = 0; Display_FontLine < DISPLAY_LINE_NUM; Display_FontLine++)
    {
        Displaybuf[Display_FontLine][Display_FontColumn] = '\0';
        SSD130x_PLineClr(Display_FontLine);
    }

    Display_FontLine = 0;
    Display_FlagOut = 0;
    Display_OutLine = 0;
}

#else

inline int Display_printf(const char *fmt, ...)
{
    return (0);
}

inline void Display_CLS(void)
{
	return ;
}

#endif



