#include "catalog.h"

static const char* FILE_NAME   = "Catalog.txt";
static const char* FILE_ACCESS = "r,ccs=UTF-16LE";

typedef struct {
	wchar_t short_name[21];
	int total_hours;
	int classroom_hours;
	wchar_t full_name[295];
} Subject;

typedef struct {
	int k_wage;
	int k_accrual;
	int k_sfedu;

	int program_count;

	Subject* subjects;
} Catalog;

static Catalog* catalog = NULL;

int initCatalog() {
	if (catalog) {
		return -1;
	}

	catalog = (Catalog*)malloc(sizeof(Catalog));

	FILE* catalog_file = fopen(FILE_NAME, FILE_ACCESS);

	if (!catalog_file) {
		return -1;
	}

	int x = fwscanf(catalog_file, L"%d %d %d\n%d\n", &catalog->k_wage, 
										   &catalog->k_accrual, 
										   &catalog->k_sfedu, 
										   &catalog->program_count);
	
	catalog->subjects = (Subject*)malloc(sizeof(Subject) * catalog->program_count);

	Subject* subjects_ptr = catalog->subjects;
	for (int i = 0; i < catalog->program_count; ++i) {
		fwscanf(catalog_file, L"%ls %d %d ", &subjects_ptr[i].short_name, 
										  &subjects_ptr[i].total_hours, 
										  &subjects_ptr[i].classroom_hours);
		fgetws(subjects_ptr[i].full_name, 295, catalog_file);
	}

	fclose(catalog_file);

	return 0;
}

int deinitCatalog() {
	if (!catalog) {
		if (!catalog->subjects) {
			free(catalog->subjects);
		}
		free(catalog);
	}
}