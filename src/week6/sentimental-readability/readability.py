# TODO

def main():
    content = input("Text: ")
    letters_count = count_letters(content)
    words_count = count_words(content)
    sentences_count = count_sentences(content)
    L = 100 * letters_count / words_count
    S = 100 * sentences_count / words_count
    index = round(0.0588 * L - 0.296 * S - 15.8)

    if index < 1:
        print("Before Grade 1")
    elif index >= 16:
        print("Grade 16+")
    else:
        print(f"Grade {index}")


def count_letters(text):
    letters_count = 0
    for i in range(len(text)):
        if text[i].isalpha():
            letters_count += 1
    return letters_count


def count_words(text):
    words_count = len(text.split())
    return words_count


def count_sentences(text):
    sentences_count = 0
    for i in range(len(text)):
        if text[i] in ['.', '!', '?']:
            sentences_count += 1
    return sentences_count


if __name__ == "__main__":
    main()
