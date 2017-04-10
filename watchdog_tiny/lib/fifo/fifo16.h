#ifndef FIFO16_H_
#define FIFO16_H_

//������ ������ ���� �������� ������: 4,8,16,32...128
#define FIFO16( size )\
struct {\
	uint16_t buf[size];\
	unsigned char tail;\
	unsigned char head;\
}

//���������� ��������� � �������
#define FIFO16_COUNT(fifo)     (fifo.head-fifo.tail)

//������ fifo
#define FIFO16_SIZE(fifo)      ( sizeof(fifo.buf)/sizeof(fifo.buf[0]) )

//fifo ���������?
#define FIFO16_IS_FULL(fifo)   (FIFO16_COUNT(fifo)==FIFO16_SIZE(fifo))

//fifo �����?
#define FIFO16_IS_EMPTY(fifo)  (fifo.tail==fifo.head)

//���������� ���������� ����� � fifo
#define FIFO16_SPACE(fifo)     (FIFO16_SIZE(fifo)-FIFO16_COUNT(fifo))

//��������� ������� � fifo
#define FIFO16_PUT(fifo, val) \
{\
	fifo.buf[fifo.head & (FIFO16_SIZE(fifo)-1)]=val;\
	fifo.head++;\
}

//����� ������ ������� �� fifo
#define FIFO16_PEEK(fifo) (fifo.buf[fifo.tail & (FIFO16_SIZE(fifo)-1)])

//����� ��������� ������� �� fifo
#define FIFO16_PEEK_LAST(fifo) (fifo.buf[(fifo.head - 1) & (FIFO16_SIZE(fifo)-1)])

//������� ��������� ������� �� fifo
#define FIFO16_REMOVE_LAST(fifo) {if (fifo.tail!=fifo.head) {fifo.head--;}}

//��������� ���������� ��������� � �������
#define FIFO16_POP(fifo)   \
{\
	fifo.tail++; \
}

#define FIFO16_GET(fifo) (fifo.buf[fifo.tail++ & (FIFO16_SIZE(fifo)-1)])

//�������� fifo
#define FIFO16_FLUSH(fifo)   \
{\
	fifo.tail=0;\
	fifo.head=0;\
}



#endif /* FIFO16_H_ */