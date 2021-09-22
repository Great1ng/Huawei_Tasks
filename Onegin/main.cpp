#include "textio.h"

void run_work_cycle();

int main() {
    setlocale(LC_ALL, "");

    run_work_cycle();

    return 0;
}

void run_work_cycle() {
    //todo Read main args and get input, output file, sort type and test

    const char* input_filename = "../Onegin.in";
    const char* output_filename = "../Onegin.out";

    ssize_t input_size = get_file_size(input_filename);
    if (input_size == -1) return;
    size_t byte_input_size = (size_t) input_size;

    char* byte_buffer = (char*) calloc(byte_input_size+1, sizeof(char));
    read_file(input_filename, byte_buffer, byte_input_size);
    byte_buffer[input_size] = '\0';

    const char* perm_byte_buffer = byte_buffer;

    size_t wbyte_input_size = mbsrtowcs(NULL, &perm_byte_buffer, 0, NULL);
    wchar_t* wbyte_buffer = (wchar_t *) calloc(wbyte_input_size, sizeof(wchar_t));
    mbsrtowcs(wbyte_buffer, &perm_byte_buffer, wbyte_input_size, NULL);

    size_t wbyte_output_size = 0;
    for (size_t i = 0; i <= wbyte_input_size; i++) {
        if (!iswalpha((wint_t)wbyte_buffer[i]) && !iswspace((wint_t)wbyte_buffer[i]) && wbyte_buffer[i] != L'\n') continue;
        if (i > 0 && iswspace((wint_t)wbyte_buffer[i-1]) && iswspace((wint_t)wbyte_buffer[i])) continue;
        wbyte_buffer[wbyte_output_size] = wbyte_buffer[i];
        wbyte_output_size++;
    }

    size_t n_lines = wcsnrplc(wbyte_buffer, L'\n', L'\0', wbyte_output_size);

    line* indexes = (line*)calloc(n_lines, sizeof(struct line));
    size_t line = 0;
    for (size_t i = 0; i < wbyte_output_size; i++) {
        indexes[line].text = &wbyte_buffer[i];
        indexes[line].size = 0;
        while (wbyte_buffer[i] != L'\0') {
            indexes[line].size++;
            i++;
        }
        line++;
    }

    FILE* output_file = fopen(output_filename, "w");
    if (output_filename == NULL) return;

    qsort(indexes, n_lines, sizeof(struct line), linecmp);

    for (size_t i = 0; i < n_lines; i++)
        fwprintf(output_file, L"%ls\n", indexes[i].text);

    fwprintf(output_file, L"\n");

    mergesort(indexes, n_lines, sizeof(struct line), linecmp_inv);
    for (size_t i = 0; i < n_lines; i++)
        fwprintf(output_file, L"%ls\n", indexes[i].text);

    fwprintf(output_file, L"\n");

    fclose(output_file);

    output_file = fopen(output_filename, "a");
    write(fileno(output_file), byte_buffer, byte_input_size);
    fclose(output_file);
}