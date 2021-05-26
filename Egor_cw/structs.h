#pragma once

typedef struct {
	char m_name[31];
	int m_time;
	int m_amount;
	int m_price;
} plant;

typedef struct {
	char** m_filenames;
	int m_amount;
} database_files;

typedef struct {
	plant* m_data;
	int m_amount;
} database_content;