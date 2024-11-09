/**
 * Description:
 *
 * Сортировка массива структур.
 * Нужно реализовать функцию, которая сортирует массив структур.
 * Элемент структуры представляет собой информацию о видео.
 *
 * Ф-ия принимает на вход массив структур, ф-цию компаратора, копирования, аллокатор.
 * Ф-ия отдаёт на выход указатель на массив отсортированных структур.
 */
#include <stdio.h>

#include <stdlib.h>

#include <string.h>

typedef struct {
    char name[64];
    char codec[32];
    size_t size_bytes;
    size_t duration_sec;
    size_t width;
    size_t height;
} video_file_t;

typedef void* (*malloc_func_t)(unsigned long long bytes);
typedef int (*is_less_func_t)(const video_file_t*, const video_file_t*);
typedef void (*copy_func_t)(video_file_t* dst, const video_file_t* src);

video_file_t** sort_video_files(
    const video_file_t** files,
    is_less_func_t is_less_func,
    copy_func_t copy_func,
    malloc_func_t malloc_func)
{
    if (!files || !is_less_func || !copy_func || !malloc_func) {
        return NULL;
    }

    size_t files_num = 0;
    const video_file_t** files_iterator = files;
    while (*files_iterator++) {
        files_num++;
    }
    video_file_t tmp_files[files_num];
    for (size_t i = 0; i < files_num; i++) {
        copy_func(&tmp_files[i], files[i]);
    }

    video_file_t** s_files_p = malloc_func(sizeof(video_file_t*) * (files_num + 1));
    if (s_files_p == NULL) {
        return NULL;
    }
    for (size_t i = 0; i < files_num; i++) {
        size_t min_index = i;
        for (size_t j = i + 1; j < files_num; j++) {
            if (is_less_func(&tmp_files[j], &tmp_files[min_index])) {
                min_index = j;
            }
        }
        if (min_index != i) {
            video_file_t tmp_item = tmp_files[i];
            copy_func(&tmp_files[i], &tmp_files[min_index]);
            copy_func(&tmp_files[min_index], &tmp_item);
        }
        s_files_p[i] = malloc_func(sizeof(video_file_t));
        if (!s_files_p[i]) {
            while (i > 0) {
                free(s_files_p[--i]);
            }
            free(s_files_p);
            return NULL;
        }
        copy_func(s_files_p[i], &tmp_files[i]);
    }
    s_files_p[files_num] = NULL;

    return s_files_p;
}

int is_less_than(const video_file_t* a, const video_file_t* b)
{
    if (a->size_bytes < b->size_bytes) {
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

    video_file_t** sorted_video_files = sort_video_files(
        video_files,
        is_less_than,
        copy_func, my_malloc);

    for (video_file_t** it = sorted_video_files; *it != NULL; it++) {
        printf("%lu ", (*it)->size_bytes);
        free(*it);
    }
    free(sorted_video_files);
    printf("\n");

    return EXIT_SUCCESS;
}