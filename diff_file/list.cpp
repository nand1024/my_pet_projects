#include "main.h"
#include "list.h"

extern struct fileObj* newFileObj(char*, char*);
extern struct fileObj* clearFileObj(struct fileObj*);
extern void dellFileObj(struct fileObj*);



struct  list* newList(){//новый пустой список
	struct list *res; 
	res = (struct list*)malloc(sizeof(struct list));
	res->item = 0;
	res->head = 0;
	res->len = 0;
	return res;
}

struct list* newItem(struct list *point, struct fileObj *val){//новый элемент списка
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

struct list* nextItem(struct list *point){//следующий элемент списка
	if(point->item->next != 0){
		point->item = point->item->next;
		return point;
	}else{
		return 0;
	}
	
}

struct list* headItem(struct list *point){//вначало списка
	point->item = point->head;
	return point;
}

struct fileObj* getItem(struct list *point){//получение элемента списка
	if(point->item != 0){
		return point->item->data;
	}else{
		return 0;
	}
}

struct list* clearList(struct list *point){//очистка списка
	headItem(point);
	if(point->item != 0){//если элемент не пустой
		while(1){
			if(point->item->data != 0){//если указатель указывает на структуру
				//освобождаем поля структуры файла
				dellFileObj(point->item->data);
			}
			if(point->item->next != 0){//если дальше есть еще элементы
				point->head = point->item->next;//голова указывает на следующий элемент
				free(point->item);//освобождаем текущий элемент
				point->item = point->head;//переходим вначало
				point->len--;
			}else{//остался последний элемент
				point->len--;
				free(point->item);//освобождаем текущий элемент
				break;
			}
			
		}
	}
	return point;
}

void dellList(struct list *point){//полное удаление списка
	clearList(point);
	free(point);
}



