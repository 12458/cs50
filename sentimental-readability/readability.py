import string


text = input('Text: ')

# index = 0.0588 * L - 0.296 * S - 15.8
# where L is the average number of letters per 100 words in the text, and S is the average number of sentences per 100 words in the text.
words = text.split(' ')
word_count = len(words)
sentence_count = text.count('.') + text.count('!') + text.count('?')
letter_count = len([i for i in text if i in string.ascii_letters])
L = letter_count / (word_count / 100)
S = sentence_count / (word_count / 100)
index = 0.0588 * L - 0.296 * S - 15.8

if index < 1:
    print('Before Grade 1')
elif index > 16:
    print('Grade 16+')
else:
    print(f'Grade {round(index)}')
