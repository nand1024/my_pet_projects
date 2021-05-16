#include "main.h"
#include "list.h"

extern struct fileObj* newFileObj(char*, char*);
extern struct fileObj* clearFileObj(struct fileObj*);
extern void dellFileObj(struct fileObj*);



struct  list* newList(){//����� ������ ������
	struct list *res; 
	res = (struct list*)malloc(sizeof(struct list));
	res->item = 0;
	res->head = 0;
	res->len = 0;
	return res;
}

struct list* newItem(struct list *point, struct fileObj *val){//����� ������� ������
	struct listItem *newElem;
	newElem = (struct listItem*)malloc(sizeof(struct listItem));
	newElem->data = (struct fileObj*)malloc(sizeof(struct fileObj));
	memcpy(newElem->data, val, sizeof(struct fileObj));
	newElem->next = 0;
	if(point->head == 0){
		point->item = newElem;
		point->head = newElem;
	}else{
		point->item->next = newElem;
		point->item = newElem;
	}
	point->len++;
	return point;
	
}

struct list* nextItem(struct list *point){//��������� ������� ������
	if(point->item->next != 0){
		point->item = point->item->next;
		return point;
	}else{
		return 0;
	}
	
}

struct list* headItem(struct list *point){//������� ������
	point->item = point->head;
	return point;
}

struct fileObj* getItem(struct list *point){//��������� �������� ������
	if(point->item != 0){
		return point->item->data;
	}else{
		return 0;
	}
}

struct list* clearList(struct list *point){//������� ������
	headItem(point);
	if(point->item != 0){//���� ������� �� ������
		while(1){
			if(point->item->data != 0){//���� ��������� ��������� �� ���������
				//����������� ���� ��������� �����
				dellFileObj(point->item->data);
			}
			if(point->item->next != 0){//���� ������ ���� ��� ��������
				point->head = point->item->next;//������ ��������� �� ��������� �������
				free(point->item);//����������� ������� �������
				point->item = point->head;//��������� �������
				point->len--;
			}else{//������� ��������� �������
				point->len--;
				free(point->item);//����������� ������� �������
				break;
			}
			
		}
	}
	return point;
}

void dellList(struct list *point){//������ �������� ������
	clearList(point);
	free(point);
}



