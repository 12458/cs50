import csv
import sys


def main():

    # TODO: Check for command-line usage
    if len(sys.argv) != 3:
        print('Usage: python dna.py database.csv sequence.csv')

    # TODO: Read database file into a variable
    with open(sys.argv[1], 'r') as f:
        database = list(csv.reader(f))

    # TODO: Read DNA sequence file into a variable
    with open(sys.argv[2], 'r') as f:
        sequence = f.read().strip()

    # TODO: Find longest match of each STR in DNA sequence
    matches = {}

    for db_STR in database[0][1:]:
        matches[db_STR] = longest_match(sequence, db_STR)

    matches = list(matches.values())

    # TODO: Check database for matching profiles
    for record in database[1:]:
        if all([int(record[i + 1]) == matches[i] for i in range(len(database[0][1:]))]):
            print(record[0])
            return
    print('No Match')
    return


def longest_match(sequence, subsequence):
    """Returns length of longest run of subsequence in sequence."""

    # Initialize variables
    longest_run = 0
    subsequence_length = len(subsequence)
    sequence_length = len(sequence)

    # Check each character in sequence for most consecutive runs of subsequence
    for i in range(sequence_length):

        # Initialize count of consecutive runs
        count = 0

        # Check for a subsequence match in a "substring" (a subset of characters) within sequence
        # If a match, move substring to next potential match in sequence
        # Continue moving substring and checking for matches until out of consecutive matches
        while True:

            # Adjust substring start and end
            start = i + count * subsequence_length
            end = start + subsequence_length

            # If there is a match in the substring
            if sequence[start:end] == subsequence:
                count += 1

            # If there is no match in the substring
            else:
                break

        # Update most consecutive matches found
        longest_run = max(longest_run, count)

    # After checking for runs at each character in seqeuence, return longest run found
    return longest_run


main()
