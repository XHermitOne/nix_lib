/**
 * Модуль функций работы с файлами
 * @author XHermit <xhermitone@gmail.com>
 * @file
 * @version 0.0.0.1
 */

#include "filefunc.h"

extern BOOL DebugMode;

char *get_home_path(void)
{
    return getenv("HOME");
}

/**
 * Проверить существует ли директория
 */
BOOL exists_dir(char *path)
{
    BOOL result = FALSE;
    struct stat st;

    if (!is_str_empty(path))
        result = (BOOL)(stat(path, &st) == 0);
    return result;
}

static int do_mkdir(const char *path, mode_t mode)
{
    struct stat st;
    int status = 0;

    if (stat(path, &st) != 0)
    {
        /* Directory does not exist. EEXIST for race condition */
        if (mkdir(path, mode) != 0) // && errno != EEXIST)
            status = -1;
    }
    else if (!S_ISDIR(st.st_mode))
    {
        if (DebugMode)
            add_log_line("ERROR: %s is not directory", path);
        status = -1;
    }

    return (status);
}

/**
 * mkpath - ensure all directories in path exist
 * Algorithm takes the pessimistic view and works top-down to ensure
 * each directory in path exists, rather than optimistically creating
 * the last element and working backwards.
 */
int mkpath(const char *path, mode_t mode)
{
    char *pp = NULL;
    char *sp = NULL;
    int status = 0;
    char *copy_path = create_str_clone(path);

    status = 0;
    pp = copy_path;
    while (status == 0 && (sp = strchr(pp, '/')) != 0)
    {
        if (sp != pp)
        {
            /* Neither root nor double slash in path */
            *sp = '\0';
            status = do_mkdir(copy_path, mode);
            *sp = '/';
        }
        pp = sp + 1;
    }
    if (status == 0)
        status = do_mkdir(path, mode);
    destroy_and_null_str(copy_path);
    return (status);
}

/**
 * Cуществует ли файл
 * @return TRUE  - exist / FALSE - don't exist
 */
BOOL exists_file(char *filename)
{
    BOOL exists = FALSE;
    if (!is_str_empty(filename))
    {
        FILE *in = fopen(filename, "rb");
        if (in != NULL)
        {
            exists = TRUE;
            fclose(in);
        }
    }
    return exists;
}

/**
 *   Удалить файл
 */
BOOL del_file(char *filename)
{
    if (unlink(filename) >= 0)
    {
        if (DebugMode)
            print_color_txt(YELLOW_COLOR_TEXT, "Delete file <%s>\n", filename);
        return TRUE;
    }
    else
    {
        if (DebugMode)
            print_color_txt(RED_COLOR_TEXT, "ERROR. Delete file <%s>\n", filename);
        return FALSE;
    }
}

/**
 *   Нормализация пути
 *   По умолчанию:
 *       src_len=-1
 */
char *create_norm_path(char *src, size_t src_len)
{
    char *res = NULL;
    size_t res_len;

    if (src_len < 0)
        src_len = strlen(src) - 1;

    const char *ptr = src;
    const char *end = &src[src_len];
    const char *next = NULL;

    if (src_len == 0 || src[0] != '/')
    {
        // relative path

        char pwd[PATH_MAX];
        size_t pwd_len;

        if (getcwd(pwd, sizeof(pwd)) == NULL)
        {
            return NULL;
        }

        pwd_len = strlen(pwd);
        res = (char *)malloc(pwd_len + 1 + src_len + 1);
        memcpy(res, pwd, pwd_len);
        res_len = pwd_len;
    }
    else
    {
        res = (char *)malloc((src_len > 0 ? src_len : 1) + 1);
        res_len = 0;
    }

    for (ptr = src; ptr < end; ptr = next + 1)
    {
        size_t len;
        next = (char *)memchr(ptr, '/', end - ptr);
        if (next == NULL)
        {
            next = end;
        }
        len = next - ptr;
        switch (len)
        {
        case 2:
            if (ptr[0] == '.' && ptr[1] == '.')
            {
                const char *slash = (char *)memrchr(res, '/', res_len);
                if (slash != NULL)
                {
                    res_len = slash - res;
                }
                continue;
            }
            break;
        case 1:
            if (ptr[0] == '.')
            {
                continue;
            }
            break;
        case 0:
            continue;
        }
        res[res_len++] = '/';
        memcpy(&res[res_len], ptr, len);
        res_len += len;
    }

    if (res_len == 0)
    {
        res[res_len++] = '/';
    }
    res[res_len] = '\0';

    return res;
}

/**
 *   Конвертация представления пути из dos(C:\\path\\) в unix(C:/path/)
 */
char *create_dos_to_unix_path(char *src)
{
    // Подразумевается что в unix все папки в нижнем регистре
    return str_lower_lat(create_str_replace(src, "\\", "/"));
}

/**
 *   Поменять расширение в имени файла
 */
char *create_change_filename_ext(char *filename, const char *new_ext)
{
    char *ext_filename = strrchr(filename, '.');
    char *result_filename = NULL;

    if (ext_filename != NULL)
    {
        char *base = create_str_begin(filename, ext_filename - filename);
        result_filename = create_str_printf("%s%s", base, new_ext);
        destroy_and_null_str(base);
    }
    else
        result_filename = create_str_printf("%s%s", filename, new_ext);

    return result_filename;
}

/**
 *   Проверка на то же самый файл
 */
BOOL is_same_file(const char *filename1, const char *filename2)
{
    struct stat st1, st2;

    if (stat(filename1, &st1) != 0 || stat(filename2, &st2) != 0)
        return FALSE;

    if (st1.st_dev != st2.st_dev || st1.st_ino != st2.st_ino)
        return FALSE;

    return TRUE;
}


char ProfilePath[] = PROFILE_DIRNAME; /**Папка профиля программы*/

static BOOL create_profile_path(char *path);

char *get_profile_path(void)
{
    char *profile_path = NULL;
    char *home_path = get_home_path();

    profile_path = (char *)calloc(strlen(home_path) + 1 + strlen(ProfilePath) + 1, sizeof(char));
    strcpy(profile_path, home_path);
    strcat(profile_path, "/");
    strcat(profile_path, ProfilePath);

    if (!exists_dir(profile_path))
        create_profile_path(profile_path);

    if (DebugMode)
        add_log_line("Profile path: %s\n", profile_path);

    return profile_path;
}

/**
 *   Сгенерировать путь к папке профиля.
 *   По умолчанию path = NULL
 */
static BOOL create_profile_path(char *path)
{
    BOOL do_free = FALSE;
    char *profile_path = path;

    if (profile_path == NULL)
    {
        profile_path = get_profile_path();
        do_free = TRUE;
    }

    BOOL result = (BOOL)mkpath(profile_path, S_IRWXU | S_IRGRP | S_IXGRP | S_IROTH | S_IXOTH);
    if (DebugMode)
        add_log_line("Create profile path: %s\n", profile_path);

    if (do_free)
        free(profile_path);

    return result;
}
