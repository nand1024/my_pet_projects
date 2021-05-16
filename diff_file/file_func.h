#ifndef __FILE_FUNC_H
#define __FILE_FUNC_H

	struct fileObj{
		char* path;			//���� � ��������
		char* name;			//��� ��������
	};



	bool isDir(char*);									//true ���� ���� �������

	unsigned long long getFileLen(char*);				//���������� ������ ����� � ������

	struct fileObj* newFileObj(char*, char*);			//������� � ��������� ������� ��������� fileObj

	struct fileObj* clearFileObj(struct fileObj*);		//������� ���������� fileObj

	void dellFileObj(struct fileObj*);					//������� ��������� fileObj

	struct list* getAllSourceList(char*, struct list*);	//�������� ������ ���� ������ � ������������ ��������

	bool file_cmp(const char*, const char*);			//���������� 2 ����� �� ������������

	bool src_cmp(char*, char*);							//���������� ���������� ���� ��������� �� ������ ������������

#endif

