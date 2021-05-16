 
#ifndef __LIST_H
#define __LIST_H

	struct listItem{
		struct fileObj *data;	//указатель на структуру файла
		struct listItem *next;	//указатель на следующий элемент списка
	};

	struct list{
		struct listItem *item;	//текущий элемент списка
		struct listItem *head;	//голова(начало) списка
		int len;				//кол-во єлементов списка
	};



	struct  list* newList();							//новый пустой список

	struct list* newItem(struct list*, struct fileObj*);//новый элемент списка

	struct list* nextItem(struct list*);				//следующий элемент списка

	struct list* headItem(struct list*);				//вначало списка

	struct fileObj* getItem(struct list*);				//получение элемента списка

	struct list* clearList(struct list*);				//очистка списка

	void dellList(struct list*);						//полное удаление списка

#endif
