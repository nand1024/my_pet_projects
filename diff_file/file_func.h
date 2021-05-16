#ifndef __FILE_FUNC_H
#define __FILE_FUNC_H

	struct fileObj{
		char* path;			//путь к элементу
		char* name;			//имя элемента
	};



	bool isDir(char*);									//true если путь каталог

	unsigned long long getFileLen(char*);				//возвращаем размер файла в байтах

	struct fileObj* newFileObj(char*, char*);			//создает и заполняет данными структуру fileObj

	struct fileObj* clearFileObj(struct fileObj*);		//очищает стркуктуру fileObj

	void dellFileObj(struct fileObj*);					//удаляет структуру fileObj

	struct list* getAllSourceList(char*, struct list*);	//получает список всех файлов и подкаталогов каталога

	bool file_cmp(const char*, const char*);			//сравниваем 2 файла на идентичность

	bool src_cmp(char*, char*);							//сравнивает содержимое двух каталогов на полную идентичность

#endif

