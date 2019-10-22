#define MAX_WORDS 5

enum Word {
    ActionWord = 1,
    SubjectWord,
    ModifierWord,
    RemainingWords,
};

typedef struct Words {
    enum Word word[MAX_WORDS];
} Words;

Words *create_words(int count, ...) {
    va_list ap;
    va_start(ap, count);
    Words *words = malloc(sizeof(Words));
    for (int i = 0; i < count; i++) {
        words->word[i] = va_arg(ap, enum Word);
    }
    va_end(ap);
    return words;
}

Words *create_single_word() {
    return create_words(1, ActionWord);
}
