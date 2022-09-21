import re

VISA = "^4[0-9]{12}(?:[0-9]{3})?$"
MASTERCARD = "^(?:5[1-5][0-9]{2}|222[1-9]|22[3-9][0-9]|2[3-6][0-9]{2}|27[01][0-9]|2720)[0-9]{12}$"
AMEX = "^3[47][0-9]{13}$"


def is_luhn_valid(card_number):
    def luhn_checksum(card_number):
        def digits_of(n):
            return [int(d) for d in str(n)]
        digits = digits_of(card_number)
        odd_digits = digits[-1::-2]
        even_digits = digits[-2::-2]
        checksum = 0
        checksum += sum(odd_digits)
        for d in even_digits:
            checksum += sum(digits_of(d*2))
        return checksum % 10
    return luhn_checksum(card_number) == 0


card_num = input("Number: ").strip()

if re.search(VISA, card_num):
    if is_luhn_valid(card_num):
        print('VISA')
    else:
        print('INVALID')
elif re.search(MASTERCARD, card_num):
    if is_luhn_valid(card_num):
        print('MASTERCARD')
    else:
        print('INVALID')
elif re.search(AMEX, card_num):
    if is_luhn_valid(card_num):
        print('AMEX')
    else:
        print('INVALID')
else:
    print('INVALID')
