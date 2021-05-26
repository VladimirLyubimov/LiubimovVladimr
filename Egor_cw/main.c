#include <stdio.h>
#include <stdlib.h>
#include "structs.h"
#include "file_io.h"
#include "plant_funcs.h"
#include "console_io.h"
#include "database_files.h"

int main() {
	database_files db;
	db.m_amount = 0;
	db.m_filenames = NULL;

	addFile(&db, "1.txt");
	addFile(&db, "2.txt");
	addFile(&db, "3.txt");
	addFile(&db, "2.txt");
	for(int i = 0; i < db.m_amount; i++){
		printf("%s ", db.m_filenames[i]);
	}
	printf("\n");
	deleteFile(&db, "1.txt");
	deleteFile(&db, "2.txt");
	deleteFile(&db, "3.txt");
	for(int i = 0; i < db.m_amount; i++){
		printf("%s ", db.m_filenames[i]);
	}
	printf("\n");
	return 0;
}
