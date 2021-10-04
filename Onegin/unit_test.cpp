#include "unit_test.h"

UNIT_TEST_RESULT run_unit_test(unit_test* input, const wchar_t* expect) {
    operation_status status;
    wide_text text = {};

    status = construct_text(&text, input->buffer, input->length);
    if (status != SUCCESS) {
        destruct_text(&text);
        return ERROR_ON_RUN;
    }

    wide_filter text_filters[] = {iswalpha, iswcntrl, iswspace};
    status = use_symbols_text(&text, text_filters, array_size(text_filters));
    if (status != SUCCESS) {
        destruct_text(&text);
        return ERROR_ON_RUN;
    }

    status = one_space_mode_text(&text);
    if (status != SUCCESS) {
        destruct_text(&text);
        return ERROR_ON_RUN;
    }

    to_lower_text(&text);

    size_t output_size = 0;
    for (size_t i = 0; i < text.size; i++) {
        output_size += text.lines[i].length;
    }

    wchar_t *output = (wchar_t *) calloc(output_size+1, sizeof(wchar_t));
    if (!output) {
        destruct_text(&text);
        return ERROR_ON_RUN;
    }
    output[output_size] = L'\0';

    mergesort(text.lines, text.size, sizeof(*text.lines), comparator_string(input->type));

    size_t written = 0;
    for (size_t i = 0; i < text.size; i++) {
        if (swprintf(output + written, text.lines[i].length + 1, L"%ls", text.lines[i].symbols) == -1) {
            free(output);
            destruct_text(&text);
            return ERROR_ON_RUN;
        }
        written += text.lines[i].length;
    }

    if (wcscmp(output, expect) != 0) {
        free(output);
        destruct_text(&text);
        fwprintf(stderr, L"Output:\n%ls\nExpect:\n%ls", output, expect);
        return FAILED;
    }

    free(output);
    destruct_text(&text);

    wprintf(L"Test passed!\n");
    return PASSED;
}