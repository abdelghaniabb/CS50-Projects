# get the input text from the usr
text = input("Text: ")

letters = 0
words = 0
sentences = 0

for l in text:
    if (ord(l) >= ord('A') and ord(l) <= ord('Z')) or (ord(l) >= ord('a') and ord(l) <= ord('z')):
        letters = letters + 1
    if l == ' ':
        words = words + 1
    if l == '.' or l == '!' or l == '?':
        sentences = sentences + 1

if words != 0:
    words = words + 1

# the Coleman-Liau formula
L = (letters / words) * 100
S = (sentences / words) * 100
x = 0.0588 * L - 0.296 * S - 15.8
# print("letters {}\nwords {}\nsentences {}".format(letters, words, sentences))

if x < 1:
    print('Before Grade 1')
elif x >= 16:
    print('Grade 16+')
else:
    print("Grade {}".format(int(x + 0.5)))

