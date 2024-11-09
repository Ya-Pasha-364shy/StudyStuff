/**
 * Description:
 *
 * Нужно реализовать функцию:
 * video_file_t** filter_video_files(const video_file_t** files,
 *                                   filter_func_t filter_func,
 *                                   copy_func_t copy_func,
 *                                   malloc_func_t malloc_func);
 *
 * Какие-либо #include запрещены. Перед компиляция всё сделается автоматически.
 *
 * Идея функции заключается в том, что она принимает массив структур,
 * функцию фильтр и функцию копирования.
 * На основе "фильтра" она определяет какие элементы ожидаются в результате.
 * То есть, она создаёт новый массив, затем копирует через функцию копирования
 * те структуры, для которых фильтр вернул не 0.
 * Ниже более подробное описание входных и выходных значений.
 *
 * const video_file_t** files - массив указателей на структуры ([0x123, 0x124, ..., 0])
 * Последний указатель массива будет 0, он обозначает конец массива (как '\0' у строки).
 *
 * Возвращаемое значение:
 * Указатель на новый массив.
 * Этот массив содержит указатели на новые структуры,
 * которые будут являться копиями тех, для которых фильтр вернул не 0.
 * Массив должен заканчиваться нулевым указателям (по аналогии с входным).
 */

#include <stdio.h>

#include <stdlib.h>

#include <string.h>

typedef void* (*malloc_func_t)(unsigned long long bytes);

typedef struct {
    char name[64];
    char codec[32];
    size_t size_bytes;
    size_t duration_sec;
    size_t width;
    size_t height;
} video_file_t;

typedef int (*filter_func_t)(const video_file_t*);
typedef void (*copy_func_t)(video_file_t* dst, const video_file_t* src);

typedef struct file_ptr_list {
    video_file_t* payload;
    struct file_ptr_list* next;
} file_ptr_list_t, *file_ptr_list_p;

video_file_t** filter_video_files(
    const video_file_t** files,
    filter_func_t filter_func,
    copy_func_t copy_func,
    malloc_func_t malloc_func)
{
    file_ptr_list_p next_file = NULL;
    file_ptr_list_p list_root_item = NULL;
    file_ptr_list_p list_current_item = NULL;
    unsigned list_length = 0;

    for (const video_file_t** current_file = files; *current_file != NULL; current_file++) {
        if (filter_func(*current_file)) {
            file_ptr_list_p list_new_item = (file_ptr_list_p)malloc_func(sizeof(file_ptr_list_t));
            if (!list_new_item) {
                goto error2;
            }

            list_new_item->next = NULL;
            list_new_item->payload = (video_file_t*)(*current_file);

            if (!list_root_item) {
                list_root_item = list_new_item;
            } else {
                list_current_item->next = list_new_item;
            }
            list_current_item = list_new_item;
            list_length++;
        }
    }

    video_file_t** filtered_files_array = (video_file_t**)malloc_func(sizeof(video_file_t*) * (list_length + 1));
    if (!filtered_files_array) {
        goto error2;
    }

    list_current_item = list_root_item;
    for (unsigned i = 0; list_current_item; list_current_item = list_current_item->next, i++) {
        video_file_t* current_file = (video_file_t*)malloc_func(sizeof(video_file_t));
        if (!current_file) {
            list_length = i;
            goto error1;
        }
        copy_func(current_file, list_current_item->payload);
        filtered_files_array[i] = current_file;
    }
    filtered_files_array[list_length] = NULL;

    for (file_ptr_list_p list_file = list_root_item; list_file; list_file = next_file) {
        next_file = list_file->next;
        free(list_file);
    }

    return filtered_files_array;

error1:
    for (unsigned i = 0; i < list_length; i++) {
        free(filtered_files_array[i]);
    }
    free(filtered_files_array);

error2:
    for (file_ptr_list_p list_file = list_root_item; list_file; list_file = next_file) {
        next_file = list_file->next;
        free(list_file);
    }

    return NULL;
}

int filter(const video_file_t* a)
{
    if (a->duration_sec >= 10) {
        return 1;
    } else {
        return 0;
    }
}

void copy_func(video_file_t* dst, const video_file_t* src)
{
    (void)memcpy(dst, src, sizeof(video_file_t));
}

void* my_malloc(unsigned long long size)
{
    return malloc(size);
}

int main(void)
{
    video_file_t a = {
        .name = "a",
        .codec = "aaa",
        .size_bytes = 1024,
        .duration_sec = 5,
        .width = 800,
        .height = 600
    };

    video_file_t b = {
        .name = "b",
        .codec = "bbb",
        .size_bytes = 2048,
        .duration_sec = 10,
        .width = 800,
        .height = 600
    };

    video_file_t c = {
        .name = "c",
        .codec = "ccc",
        .size_bytes = 3072,
        .duration_sec = 15,
        .width = 800,
        .height = 600
    };

    const video_file_t* video_files[] = { &c, &b, &a, NULL };

    video_file_t** filtered_video_files = filter_video_files(
        video_files,
        filter,
        copy_func, my_malloc);

    for (video_file_t** it = filtered_video_files; *it != NULL; it++) {
        printf("%s ", (*it)->name);
        free(*it);
    }
    free(filtered_video_files);
    printf("\n");

    return EXIT_SUCCESS;
}