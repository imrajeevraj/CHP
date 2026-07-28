# Read the length of the string (not actually needed in the logic,
# but it is part of the input format).
n = int(input())

# Read the input string.
s = input().strip()

# Initialize the smallest character seen so far from the right.
mn = s[-1]

# Store the position of the smallest character.
pos = n - 1

# Traverse the string from right to left.
for i in range(n - 2, -1, -1):

    # If the current character is greater than the smallest character
    # on its right, reversing the substring [i, pos] will make the
    # string lexicographically smaller.
    if s[i] > mn:
        print("YES")
        # Convert to 1-based indexing.
        print(i + 1, pos + 1)
        break

    # Update the smallest character and its position.
    if s[i] < mn:
        mn = s[i]
        pos = i

# If no valid pair was found, it is impossible.
else:
    print("NO")