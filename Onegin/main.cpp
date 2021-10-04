#include <clocale>
#include <cstdlib>

#include "wide_text.h"
#include "sorting.h"
#include "unit_test.h"

struct CL_ARGS {
    const char* input_fn;
    const char* output_fn;
    int test_mode;
};

void read_args(int argc, char** argv, CL_ARGS* args);

void run_work_cycle(const char* input_fn, const char* output_fn);

void run_unit_tests();

int main(int argc, char** argv) {
    setlocale(LC_CTYPE, "ru_RU.UTF-8");

    CL_ARGS args = {};
    read_args(argc, argv, &args);

    if (args.test_mode)
        run_unit_tests();
    else
        run_work_cycle(args.input_fn, args.output_fn);

    return 0;
}

void read_args(int argc, char** argv, CL_ARGS* args) {
    const char* test_flag = "-t";
    int input_is_read  = 0;
    int output_is_read = 0;

    args->test_mode = 0;
    for (int i = 1; i < argc; i++) {
        char* command = argv[i];
        if (strcmp(command, test_flag) == 0) {
            args->test_mode = 1;
            continue;
        }
        if (!input_is_read) {
            args->input_fn = command;
            input_is_read = 1;
            continue;
        }
        if (!output_is_read) {
            args->output_fn = command;
            output_is_read = 1;
        }
    }
}

void run_unit_tests() {
    const size_t ntests = 2;

    unit_test test_inputs[ntests] = {
            {"abc\nbca\naab\nCBa", 15, FROM_LEFT_TO_RIGHT},
            {"abc\nabc\ncab\ncab", 15, FROM_RIGHT_TO_LEFT}
    };
    const wchar_t* test_expects[ntests] = {
            L"aab\nabc\nbca\ncba\n",
            L"cab\ncab\nabc\nabc\n"
    };
    for (size_t i = 0; i < ntests; i++) {
        run_unit_test(&test_inputs[i], test_expects[i]);
    }
}

void run_work_cycle(const char* input_fn, const char* output_fn) {
    operation_status status;
    wide_text text = {};

    status = fread_text(input_fn, &text);
    if (status != SUCCESS) {
        fprintf(stderr, "Error: %s on line %d!", error_description[status], __LINE__);
        return;
    }

    wide_filter text_filters[] = {iswalpha, iswcntrl, iswspace};
    status = use_symbols_text(&text, text_filters, array_size(text_filters));
    if (status != SUCCESS) {
        fprintf(stderr, "Error: %s on line %d!", error_description[status], __LINE__);
        return;
    }

    status = one_space_mode_text(&text);
    if (status != SUCCESS) {
        fprintf(stderr, "Error: %s on line %d!", error_description[status], __LINE__);
        return;
    }

    to_lower_text(&text);

    FILE* out_file = fopen(output_fn, "w");
    if (!out_file) {
        fprintf(stderr, "Error: can`t open the file on line %d", __LINE__);
        return;
    }

    qsort(text.lines, text.size, sizeof(*text.lines), comparator_string(FROM_LEFT_TO_RIGHT));
    status = fwrite_text(out_file, &text);
    if (status != SUCCESS) {
        fprintf(stderr, "Error: %s on line %d!", error_description[status], __LINE__);
        return;
    }

    mergesort(text.lines, text.size, sizeof(*text.lines), comparator_string(FROM_RIGHT_TO_LEFT));
    status = fwrite_text(out_file, &text);
    if (status != SUCCESS) {
        fprintf(stderr, "Error: %s on line %d!", error_description[status], __LINE__);
        return;
    }

    status = fwrite_text_origin(out_file, &text);
    if (status != SUCCESS) {
        fprintf(stderr, "Error: %s on line %d!", error_description[status], __LINE__);
        return;
    }

    if (fclose(out_file) == -1) {
        fprintf(stderr, "Error: can`t close the file on line %d", __LINE__);
        return;
    }

    destruct_text(&text);
}