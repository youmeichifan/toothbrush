#ifndef __UART1_H_
#define __UART1_H_

/* ����ϵͳͷ�ļ� */
#include <stdio.h>

/* �����Զ���ͷ�ļ� */
#include "stm8s.h"

/* �Զ����������� */

/* �Զ��峣����ͱ���ʽ�� */
#define countof(a)   (sizeof(a) / sizeof(*(a)))
#define RxBufferSize 64

/* �������ⲿʹ�õı��� */

/* �������ⲿʹ�õĺ��� */

/*******************************************************************************
 * ����: Uart_Init
 * ����: UART1��ʼ������
 * �β�: ��
 * ����: ��
 * ˵��: �� 
 ******************************************************************************/
void Uart1_Init(void);

/*******************************************************************************
 * ����: UART1_SendByte
 * ����: UART1����һ���ֽ�
 * �β�: data -> Ҫ���͵��ֽ�
 * ����: ��
 * ˵��: �� 
 ******************************************************************************/
void UART1_SendByte(uint8_t data);

/*******************************************************************************
 * ����: UART1_SendData
 * ����: UART1����len���ַ�
 * �β�: data -> ָ��Ҫ���͵��ַ���
 *       len -> Ҫ���͵��ֽ���
 * ����: ��
 * ˵��: �� 
 ******************************************************************************/
void UART1_SendData(uint8_t* Data,uint16_t len);

/*******************************************************************************
 * ����: UART1_ReceiveByte
 * ����: UART1����һ���ַ�
 * �β�: ��
 * ����: ���յ����ַ�
 * ˵��: �� 
 ******************************************************************************/
//uint8_t UART1_ReceiveByte(void);

/*******************************************************************************
 * ����: fputc
 * ����: �ض���c�⺯��printf��UART1
 * �β�: ��
 * ����: Ҫ��ӡ���ַ�
 * ˵��: ��printf���� 
 ******************************************************************************/
//int fputc(int ch, FILE *f);

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
char *itoa(int value, char *string, int radix);

/************************************************************************
 * ��������USART1_printf
 * ����  ����ʽ�������������C���е�printf��������û���õ�C��
 * ����  ��-USARTx ����ͨ��������ֻ�õ��˴���1����USART1
 *		     -Data   Ҫ���͵����ڵ����ݵ�ָ��
 *			   -...    ��������
 * ���  ����
 * ����  ���� 
 * ����  ���ⲿ����
 *         ����Ӧ��	 USART1_printf( "\r\n this is a demo \r\n" );
 *            		 USART1_printf(  "\r\n %d \r\n", i );
 *            		 USART1_printf(  "\r\n %s \r\n", j );
 ***************************************************************************/
void UART1_printf( uint8_t *Data,...);


#endif