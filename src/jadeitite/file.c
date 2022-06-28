#include "file.h"
#include "jadeitite/log.h"
#include <stdio.h>
#include <stdlib.h>

//======================================
//          Public functions
//======================================

/**
 * Write any data type to file
 *
 * @param p_file_path File path with its file name and extension, e.g. data.dat
 * @param p_data Data
 * @param p_data_size Size of some data, e.g sizeof(my_struct)
 * @return Return RS_OK if write operation is successful, otherwise return RS_FAILED
 */
u8 file_write(const char *p_file_path, void *p_data, size_t p_data_size) {
  FILE* l_file = fopen(p_file_path, "w");
  if (l_file == NULL) {
    LOG_ERROR("Failed to open file [file_path=%s]!", p_file_path);
    return RS_FAILED;
  }

  size_t l_status = fwrite(p_data, p_data_size, 1, l_file);
  if (l_status == 0) {
    LOG_ERROR(
      "Failed to write data to file [file_path=%s; data_size=%ul]",
      p_file_path, p_data_size);
    return RS_FAILED;
  }

  fclose(l_file);
  return RS_OK;
}

/**
 * Read file and return any data type
 *
 * Be aware! This function read only one data type and return it
 * so for list of some structures will return only one entity,
 * make structure as root
 *
 * @param p_file_path File path with its file name and extension, e.g. data.dat
 * @param p_data_size Size of some data, e.g sizeof(my_struct)
 * @return Return any data type
 */
void *file_read(const char *p_file_path, size_t p_data_size) {
  FILE* l_file = fopen(p_file_path, "r");
  if (l_file == NULL) {
    LOG_ERROR("Failed to open file [file_path=%s]!", p_file_path);
    return NULL;
  }

  void *l_data = malloc(p_data_size);
  size_t l_status = fread(l_data, p_data_size, 1, l_file);
  if (l_status == 0) {
    LOG_ERROR(
      "Failed to read data from file [file_path=%s; data_size=%ul]",
      p_file_path, p_data_size);
    return NULL;
  }

  fclose(l_file);
  return l_data;
}
