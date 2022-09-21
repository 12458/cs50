text = input('Text: ')
# index = 0.0588 * L - 0.296 * S - 15.8
# where L is the average number of letters per 100 words in the text, and S is the average number of sentences per 100 words in the text.
words = text.split(' ')
word_count = len(words)
sentence_count = text.count('.') + text.count('!') + text.count('?')
L = le
index = 0.0588 * L - 0.296 * S - 15.8
