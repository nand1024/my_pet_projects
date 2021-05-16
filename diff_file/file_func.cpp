#include "main.h"
#include "file_func.h"


bool isDir(char *path){//true если путь каталог
	struct stat fileStateBuf;
	stat (path, &fileStateBuf);
	if(S_ISDIR(fileStateBuf.st_mode)){
		return true;
	}else{
		return false;
	}
}

unsigned long long getFileLen(char *pathFile){//возвращаем размер файла в байтах
	unsigned long long  res = 0;
	FILE *x = fopen(pathFile, "rb");
	if(x != NULL){
		fseek(x, 0, SEEK_END);
		res = ftell(x);
		fclose(x);
	}
	return res;
}


struct fileObj* newFileObj(char *path_val, char *name_val){//создает и заполняет данными структуру fileObj
	struct fileObj* resFs;
	resFs = (struct fileObj*)malloc(sizeof(struct fileObj));
	resFs->name = (char*)calloc(strlen(name_val)+1, sizeof(char));
	resFs->path = (char*)calloc(strlen(path_val)+1, sizeof(char));
	strcat(resFs->name, name_val);
	strcat(resFs->path, path_val);
	return resFs;
}

struct fileObj* clearFileObj(struct fileObj* ptr){//очищает стркуктуру fileObj
	if(ptr->name)free(ptr->name);
	if(ptr->path)free(ptr->path);
	return ptr;
}

void dellFileObj(struct fileObj* ptr){//удаляет структуру fileObj
	clearFileObj(ptr);
	free(ptr);
}

struct list* getAllSourceList(char* path, struct list* ptrLst){//получает список всех файлов и подкаталогов каталога
	struct fileObj *flObjPtr;
	DIR *pointDir;
	dirent *res;
	pointDir = opendir(path);
	if(pointDir == 0){
		printf("error open path %s\n",path);
		exit(1);
	}
	const int lenPathSym = 4096;
	char fullpath[lenPathSym];
	while(res = readdir(pointDir)){
		if(	(strlen(res->d_name) == 2 && res->d_name[0] == '.' && res->d_name[1] == '.') ||
			(strlen(res->d_name) == 1 && res->d_name[0] == '.')){//элементы '.' '..' указывают на текущий и родительский каталог
			continue;
		}
		//добавляем элемент в список
		flObjPtr = newFileObj(path, res->d_name);
		newItem(ptrLst, flObjPtr);
		free(flObjPtr);
		//составляем полный путь к элементу
		for(int i = 0; i < lenPathSym; i++)fullpath[i]=0;
		strcat(fullpath, path);
		if(path[strlen(path)-1] != '\\')strcat(fullpath, "\\");
		strcat(fullpath, res->d_name);
		
		if(isDir(fullpath)){	//если данный элемент подкаталог	
			getAllSourceList(fullpath, ptrLst);		//заходим в него и продолжаем обход
		}
	}
	closedir(pointDir);
	return ptrLst;
}

bool file_cmp(char *pathFileA, char *pathFileB){//сравниваем 2 файла на идентичность
	FILE *A = fopen(pathFileA, "rb");
	FILE *B = fopen(pathFileB, "rb");
	unsigned long blokSizeRead = 1024*64;
	unsigned char bufferA[blokSizeRead];
	unsigned char bufferB[blokSizeRead];
	unsigned long sizeRead;
	unsigned long long  size_fl;
	if(A != NULL && B != NULL){//если файлы успешно открылись
		size_fl = getFileLen(pathFileA);
		if(size_fl != getFileLen(pathFileB)){//если файлы не одинакового размера
			goto cmp_false;
		}
		while(size_fl!=0){//читаем блоками по blokSizeRead байт пока не дойдем до конца файла
			sizeRead = fread(bufferA, 1, blokSizeRead, A);
			fread(bufferB, 1, blokSizeRead, B);
			if(memcmp(bufferA, bufferB, sizeRead)){//если блоки данных не идентичны
				goto cmp_false;
			}
			size_fl-=sizeRead;
		}
		goto cmp_true;
	}else{
		goto cmp_false;
	}
	
	cmp_true:
		fclose(A);
		fclose(B);
		return true;
		
	cmp_false:
		fclose(A);
		fclose(B);
		return false;

}



bool src_cmp(char *dirA, char *dirB){//сравнивает содержимое двух каталогов на полную идентичность
	bool findFile, result;
	struct list *ptrLstA = newList();
	struct list *ptrLstB = newList();
	struct fileObj *resFsA, *resFsB;
	char *pathCmpA, *pathCmpB, *cmpPathNameA, *cmpPathNameB;
	pathCmpA = pathCmpB = 0;
	int lenSrcA, lenSrcB, lenPathA, lenPathB;
	lenSrcA = strlen(dirA);
	lenSrcB = strlen(dirB);
	//получаем содержимое папок
	getAllSourceList(dirA, ptrLstA);
	getAllSourceList(dirB, ptrLstB);
	result = true;
	if(ptrLstA->len != ptrLstB->len){//если разное кол-во содержимого в папках
		//printf("different number of elements in compared paths\n");
		//printf("\t%s = %d elements\n\t%s = %d elements\n", dirA, ptrLstA->len,  dirB, ptrLstB->len);
		result = false;
	}
	headItem(ptrLstB);
	//ищем файлы с одинаковыми именами и сравниваем их содержимое
	do{//перебор элементов пути dirB
		//получаем элемент списка и строим полный путь к элементу
		resFsB= getItem(ptrLstB);
		pathCmpB = (char*)calloc(strlen(resFsB->path)+1+strlen(resFsB->name)+1, sizeof(char));
		strcat(pathCmpB, resFsB->path);
		if(resFsB->path[strlen(resFsB->path)-1] != '\\')strcat(pathCmpB, "\\");
		strcat(pathCmpB, resFsB->name);
		//формируем переменую для сравнения путей с игнорированием имен самих источников
		lenPathB = strlen(pathCmpB);
		cmpPathNameB = (char*)calloc(lenPathB-lenSrcB+1, sizeof(char));
		//урезаем лишний слеш если он есть
		if(pathCmpB[lenSrcB]!='\\'){
			memcpy(cmpPathNameB, &pathCmpB[lenSrcB], lenPathB-lenSrcB+1);
		}else{
			memcpy(cmpPathNameB, &pathCmpB[lenSrcB+1], lenPathB-lenSrcB+1);
		}
		headItem(ptrLstA);
		findFile = false;//сбрасываем флаг успешного поиска файла
		do{//перебор элементов пути dirA
			//получаем элемент списка и строим полный путь к элементу
			resFsA = getItem(ptrLstA);
			pathCmpA = (char*)calloc(strlen(resFsA->path)+1+strlen(resFsA->name)+1, sizeof(char));
			strcat(pathCmpA, resFsA->path);
			if(resFsA->path[strlen(resFsA->path)-1] != '\\')strcat(pathCmpA, "\\");
			strcat(pathCmpA, resFsA->name);	
			lenPathA = strlen(pathCmpA);
			//для сравнения путей с игнорированием имен самих источников
			cmpPathNameA = (char*)calloc(lenPathA-lenSrcA+1, sizeof(char));
			//урезаем лишний слеш если он есть
			if(pathCmpA[lenSrcA]!='\\'){
				memcpy(cmpPathNameA, &pathCmpA[lenSrcA], lenPathA-lenSrcA+1);
			}else{
				memcpy(cmpPathNameA, &pathCmpA[lenSrcA+1], lenPathA-lenSrcA+1);
			}
			//если найдены файлы с одинаковыми именами сравниваем содержимое
			if(strcmp(cmpPathNameB, cmpPathNameA) == 0 &&
			isDir(pathCmpB) == false && isDir(pathCmpA) == false ){
				if(!file_cmp(pathCmpA, pathCmpB)){					
						//printf("%s != %s\n", cmpPathNameA, cmpPathNameB);
						result = false;
						break;
				}
				findFile = true;
				break;
			}
			free(cmpPathNameA);
			free(pathCmpA);
		}while(nextItem(ptrLstA) && result);
		if(isDir(pathCmpB) == false && !findFile){//если искомый файл не найден
			//printf("not find file to compare with file %s\n", pathCmpB);
			result = false;
		}
		free(cmpPathNameB);
		free(pathCmpB);
	}while(nextItem(ptrLstB) && result);
	
	return result;
}
