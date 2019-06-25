#include "cbuf.h"

#define NULL 0







void my_memcpy(unsigned char *tar, const unsigned char *src, u32 len)
{
  ASSERT(tar);
	ASSERT(src);
	if(len==0)
		return;
	while(len--)
		*tar++ = *src++;
}




u32 min(u32 data1, u32 data2)
{
    return (data1<data2)?(data1):(data2);
}
/*
** �� ������ д������
** ����ֵ��ʵ��д������
*/
u32 put_fifo(struct cbuf_t *cbuf, const u8* data_in, u32 len)
{
    if((cbuf == NULL)||(data_in == NULL)||(len==0)){
        return 0;
    }
    len = min(len, cbuf->size - (cbuf->in-cbuf->out));     			//��֤д�볤�� <= ���пռ��С
    u32 L = min(len, cbuf->size - (cbuf->in & (cbuf->size - 1)));       // size - in&(sie-1)in��������β���ľ���
    my_memcpy(cbuf->buffer + (cbuf->in&(cbuf->size-1)) , data_in, L);
    my_memcpy(cbuf->buffer, data_in+L, len-L);
    cbuf->in += len;
    return len;
}
/*
** ������
*/
u32 get_fifo(struct cbuf_t *cbuf,  u8* data_out, u32 len)
{
    if((cbuf == NULL)||(data_out == NULL)||(len==0)){
        return 0;
    }
     len = min(len , cbuf->in - cbuf->out);
     u32 L = min(len,cbuf->size - (cbuf->out &(cbuf->size - 1) ));

     my_memcpy(data_out , cbuf->buffer + (cbuf->out &(cbuf->size - 1)), L );
     my_memcpy(data_out+L , cbuf->buffer , len -L);
     cbuf->out += len;

     return len;
}


/**
** ѭ����ȡbuf�е�����  ��ɾ������
*/
u32 get_fifo_roll(struct cbuf_t *cbuf,  u8* data_out, u32 len)
{
    if((cbuf == NULL)||(data_out == NULL)||(len==0)){
        return 0;
    }
    u32 L = min(len,cbuf->size - cbuf->out);
    if((cbuf->out+1) >=  cbuf->size)
        cbuf->out = 0;
    my_memcpy(data_out , cbuf->buffer + cbuf->out, L );
    my_memcpy(data_out+L , cbuf->buffer , len -L);
    cbuf->out ++;
		return 0;
}


/*
 * size:ֻ����2�ļ�����
 */
u32 cbuffer_init(struct cbuf_t *cbuf,u8 *buf, u32 size)
{
    if((size&(size-1)) != 0){
			return 1;
    }
    cbuf->buffer = buf;
    cbuf->in = 0;
    cbuf->out = 0;
    cbuf->size = size;
		return 0;
}
