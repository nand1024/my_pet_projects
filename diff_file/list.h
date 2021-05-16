 
#ifndef __LIST_H
#define __LIST_H

	struct listItem{
		struct fileObj *data;	//��������� �� ��������� �����
		struct listItem *next;	//��������� �� ��������� ������� ������
	};

	struct list{
		struct listItem *item;	//������� ������� ������
		struct listItem *head;	//������(������) ������
		int len;				//���-�� ��������� ������
	};



	struct  list* newList();							//����� ������ ������

	struct list* newItem(struct list*, struct fileObj*);//����� ������� ������

	struct list* nextItem(struct list*);				//��������� ������� ������

	struct list* headItem(struct list*);				//������� ������

	struct fileObj* getItem(struct list*);				//��������� �������� ������

	struct list* clearList(struct list*);				//������� ������

	void dellList(struct list*);						//������ �������� ������

#endif
