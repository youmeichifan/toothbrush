
/******************** (C) COPYRIGHT  ���iCreateǶ��ʽ���������� **************
 * �ļ���  ��uart1.c
 * ����    ��UART1�����ļ�   
 * ʵ��ƽ̨�����STM8������
 * ��汾  ��V2.1.0
 * ����    �����  QQ��779814207
 * ����    ��
 * �Ա�    ��http://shop71177993.taobao.com/
 *�޸�ʱ�� ��2012-10-28

  ���STM8������Ӳ������
    |------------------------|
    |  TXD - PA4(UART1->RX)  |
    |  RXD - PA5(UART1->TX)  |
    |------------------------|

*******************************************************************************/

/* ����ϵͳͷ�ļ� */
#include <stdarg.h>

/* �����Զ���ͷ�ļ� */
#include "uart1.h"

/* �Զ��������� */

/* �Զ���� */

/* ȫ�ֱ������� */

/*******************************************************************************
 * ����: Uart_Init
 * ����: UART1��ʼ������
 * �β�: ��
 * ����: ��
 * ˵��: �� 
 ******************************************************************************/
void Uart1_Init(void)
{
    UART1_DeInit();		/* ���Ĵ�����ֵ��λ */
	
	/*
	 * ��UART1����Ϊ��
	 * ������ = 115200
	 * ����λ = 8
	 * 1λֹͣλ
	 * ��У��λ
	 * ʹ�ܽ��պͷ���
	 * ʹ�ܽ����ж�
	 */
    UART1_Init((u32)115200, UART1_WORDLENGTH_8D, UART1_STOPBITS_1, \
    	UART1_PARITY_NO , UART1_SYNCMODE_CLOCK_DISABLE , UART1_MODE_TXRX_ENABLE);
    UART1_ITConfig(UART1_IT_RXNE_OR, ENABLE);
    UART1_Cmd(ENABLE);
}

/*******************************************************************************
 * ����: UART1_SendByte
 * ����: UART1����һ���ֽ�
 * �β�: data -> Ҫ���͵��ֽ�
 * ����: ��
 * ˵��: �� 
 ******************************************************************************/
void UART1_SendByte(uint8_t data)
{
	UART1_SendData8((unsigned char)data);
	
	/* �ȴ�������� */
	while (UART1_GetFlagStatus(UART1_FLAG_TXE) == RESET);
}

/*******************************************************************************
 * ����: UART1_SendData
 * ����: UART1����len���ַ�
 * �β�: data -> ָ��Ҫ���͵��ַ���
 *       len -> Ҫ���͵��ֽ���
 * ����: ��
 * ˵��: �� 
 ******************************************************************************/
void UART1_SendData(uint8_t* Data,uint16_t len)
{
	uint16_t i=0;
	for(; i < len; i++)
		UART1_SendByte(Data[i]);	/* ѭ�����÷���һ���ַ����� */
}

/*******************************************************************************
 * ����: UART1_ReceiveByte
 * ����: UART1����һ���ַ�
 * �β�: ��
 * ����: ���յ����ַ�
 * ˵��: �� 
 ******************************************************************************/
/*
uint8_t UART1_ReceiveByte(void)
{
	uint8_t USART1_RX_BUF; 
	
	while (UART1_GetFlagStatus(UART1_FLAG_RXNE) == RESET)
	  	;
	
	USART1_RX_BUF = UART1_ReceiveData8();
	
	return  USART1_RX_BUF;
}
*/
/*******************************************************************************
 * ����: fputc
 * ����: �ض���c�⺯��printf��UART1
 * �β�: ��
 * ����: Ҫ��ӡ���ַ�
 * ˵��: ��printf���� 
 ******************************************************************************/
/*
int fputc(int ch, FILE *f)
{  
	

	UART1_SendByte(ch);
	
	return (ch);
}
*/
/********************************************************
 * ��������itoa
 * ����  ������������ת�����ַ���
 * ����  ��-radix =10 ��ʾ10���ƣ��������Ϊ0
 *         -value Ҫת����������
 *         -buf ת������ַ���
 *         -radix = 10
 * ���  ����
 * ����  ����
 * ����  ����USART1_printf()����
 *******************************************************/

char *itoa(int value, char *string, int radix)
{
    int     i, d;
    int     flag = 0;
    char    *ptr = string;

   
    if (radix != 10)
    {
        *ptr = 0;
        return string;
    }

    if (!value)
    {
        *ptr++ = 0x30;
        *ptr = 0;
        return string;
    }

    // if this is a negative value insert the minus sign. 
    if (value < 0)
    {
        *ptr++ = '-';

        // Make the value positive. 
        value *= -1;
    }

    for (i = 10000; i > 0; i /= 10)
    {
        d = value / i;

        if (d || flag)
        {
            *ptr++ = (char)(d + 0x30);
            value -= (d * i);
            flag = 1;
        }
    }

    // Null terminate the string. 
    *ptr = 0;

    return string;

} /* NCL_Itoa */

/************************************************************************
 * ��������UART1_printf
 * ����  ����ʽ�������������C���е�printf��������û���õ�C��
 * ����  ��-UARTx ����ͨ��������ֻ�õ��˴���1����UART1
 *		     -Data   Ҫ���͵����ڵ����ݵ�ָ��
 *			   -...    ��������
 * ���  ����
 * ����  ���� 
 * ����  ���ⲿ����
 *         ����Ӧ��	 UART1_printf( "\r\n this is a demo \r\n" );
 *            		 UART1_printf(  "\r\n %d \r\n", i );
 *            		 UART1_printf(  "\r\n %s \r\n", j );
 ***************************************************************************/

void UART1_printf( uint8_t *Data,...)
{
	const char *s;
//	int d;   
        uint16_t d;
	char buf[16];
	va_list ap;
	va_start(ap, Data);
	
	while ( *Data != 0)     // �ж��Ƿ񵽴��ַ���������
	{				                          
		if ( *Data == 0x5c )  //'\'
		{									  
			switch ( *++Data )
			{
				case 'r':							          //�س���
					UART1_SendData8(0x0d);
					Data ++;
				break;
	
				case 'n':							          //���з�
					UART1_SendData8(0x0a);	
					Data ++;
				break;
	
				default:
					Data ++;
				break;
			}			 
		}
		else if ( *Data == '%')
		{					//
			switch ( *++Data )
			{				
				case 's':						//�ַ���
				s = va_arg(ap, const char *);
				for ( ; *s; s++) 
				{
					UART1_SendData8(*s);
					while (UART1_GetFlagStatus(UART1_FLAG_TXE) == RESET);
				}
				Data++;
				break;
	
				case 'd':	//ʮ����
					d = va_arg(ap, int);
					itoa(d, buf, 10);
				for (s = buf; *s; s++) 
				{
					UART1_SendData8(*s);
					while (UART1_GetFlagStatus(UART1_FLAG_TXE) == RESET);
				}
				Data++;
				break;
				
				default:
					Data++;
				break;
			}		 
		} // end of else if 
		else UART1_SendData8(*Data++);
	
		while (UART1_GetFlagStatus(UART1_FLAG_TXE) == RESET);
	}
}


/******************* (C) COPYRIGHT ���iCreateǶ��ʽ���������� *****END OF FILE****/