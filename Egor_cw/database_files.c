#include "database_files.h"

int isFileExist(database_files* database, const char* filename){
	int is_exist = -1; 
	for(int i = 0; i < database->m_amount; i++){
		if(strcmp(database->m_filenames[i], filename) == 0){
			is_exist = i;
		}
	}

	return is_exist;
}

int addFile(database_files* database, const char* filename){
	if(isFileExist(database, filename) != -1){
		return 1;
	}

	FILE* fin = fopen(filename, "w");
	fclose(fin);

	int last = database->m_amount;

	database->m_amount += 1;
	database->m_filenames = (char**)realloc(database->m_filenames, database->m_amount*sizeof(char*));

	database->m_filenames[last] = (char*)malloc(strlen(filename)+1);
	strcpy(database->m_filenames[last], filename);

	return 0;
}

int deleteFile(database_files* database, const char* filename){
	int file_pos = isFileExist(database, filename);
	if(file_pos == -1){
		return 1;
	}

	remove(filename);
	if(file_pos == database->m_amount-1){
		free(database->m_filenames[database->m_amount-1]);
		database->m_amount -= 1;
		database->m_filenames = (char**)realloc(database->m_filenames, database->m_amount*sizeof(char*));
		return 0;
	}

	for(int i = file_pos; i < database->m_amount-1; i++){
		free(database->m_filenames[i]);
		database->m_filenames[i] = (char*)malloc(strlen(database->m_filenames[i+1])+1);
		strcpy(database->m_filenames[i], database->m_filenames[i+1]);
	}

	free(database->m_filenames[database->m_amount-1]);
	database->m_amount -= 1;
	database->m_filenames = (char**)realloc(database->m_filenames, database->m_amount*sizeof(char*));
	
	return 0;
}