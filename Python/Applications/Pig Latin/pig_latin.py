#!/usr/bin/env python3

def translate_to_pig_latin(sentence):
    words = sentence.split()
    translated_words = []

    for word in words:
        if word[0] in 'aeiou':
            translated_words.append(word + 'way')
        else:
            translated_words.append(word[1:] + word[0] + 'ay')

    return ' '.join(translated_words)

sentence = input("Enter a sentence: ")
print(translate_to_pig_latin(sentence.lower()))