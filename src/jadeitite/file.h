#ifndef JADEITITE_FILE_H
#define JADEITITE_FILE_H

#include "jadeitite/datatypes.h"

u8 file_write(const char *p_file_path, void *p_data, size_t p_data_size);
void *file_read(const char *p_file_path, size_t p_data_size);

#endif //JADEITITE_FILE_H
