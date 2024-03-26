import csv
import sys


def main():

    # TODO: Check for command-line usage
    n = len(sys.argv)
    if n != 3:
        print("Usage python dna.py file.csv file.txt")
        sys.exit

    # TODO: Read database file into a variable
    datarows = []
    with open(sys.argv[1]) as file:
        reader = csv.DictReader(file)
        for row in reader:
            datarows.append(row)

    # TODO: Read DNA sequence file into a variable
    with open(sys.argv[2]) as file:
        dna = file.read()

    # TODO: Find longest match of each STR in DNA sequence
    longest = []
    for x in datarows[0]:
        if x == "name":
            pass
        else:
            longest.append(longest_match(dna, x))

    # TODO: Check database for matching profiles
    for x in datarows:
        i = 0
        matches = 0
        for y in datarows[0]:
            if y == "name":
                pass
            elif int(x[y]) == longest[i]:
                matches += 1
                i += 1
            else:
                i += 1

        if matches == len(datarows[0]) - 1:
            print(x["name"])
            break
    else:
        print("No match")

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
