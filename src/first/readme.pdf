
First Part (100 points)

Your task in the first part is to write a C program called first that reads an input file, which contains
a list of dictionary and data file pairs, and generates statistics for each pair.
Each line in your input file contains the names of the dictionary and data files. You have to read the
files and generate the following statistics:

1. For every word w in the dictionary file, count the number of words w'
that occur in the data file
such that w'= w.
2. For every word w in the dictionary file, count the number of words w'
that occur in the data file
such that w is a proper prefix of w
(we shall say w' is a superword of w).

Write all the unique words in the dictionary along with these counts to the output file in lexicographical
(i.e. alphabetical) order.

Definition of a word: Any string of characters can be a word. For example in the sentence:

”a&ab&abc234 dfg”

the words are:

a, ab, abc, dfg

They do not need to be meaningful. Words, in both dictionary and data files, correspond to the longest
continuous sequence of letters read from the file. Another way to say this is that words are any sequence
of letters separated by non-letter characters (punctuation, numbers, whitespace, etc.). Each unique word
is case-insensitive. That is, “boOK”, “Book” and “bOOk” are all occurrences of the same (unique) word
“book”.

Case-insensitivity also applies when matching prefixes: for example, both “Boo” and ”bOo” are proper
prefixes of “bOOk”, which itself is a proper prefix of “booKING” (See the example below).
As an example, suppose the content of the dictionary file is:

boo22$Book5555bOoKiNg#bOo#TeX123tEXT(JOHN)

and that of the data file is:

John1TEXAN4isa1BOoRiSH%whohasa2bo3KING BOOKING bOoKIngs$12for a TEX-Text(BOOKS(textBOOKS)
Then, the various counts for the unique words in the dictionary file are:


Unique words 	No. of occurrences 	No. of superwords

boo 				0 	4

book 				0	3

booking 			1 	1

tex 				1 	3

text 				1 	1

john 				1 	0

Input/Output specification

Usage interface

The program first should have the following usage interface:

./first <mappingfile>

where <mappingFile> is the name of the mapping file. You can assume that the mapping file will exist
and that it is well structured. So, unlike assignment1, you don’t need to check the structure of the
mapping file

If no argument or more than one argument is provided, or the file names provided are
invalid, the program should print “invalid input” and abort.

Input specification

Here, and below, let m be the maximum number of words in either the dictionary or data files. Every
word is of length at most k. Let n be the number of unique words in the dictionary file.
Your input will be a mapping file, which contains lines of the form: hdictFilei hdataFilei, where
dictFile and dataFile are the dictionary and data files for your program, respectively. An example of a
mapping file is given below:

dict_1 data_1

dictm foom

The files: dict1.txt and dictm.txt are dictionary files and files: data1.txt and foom.txt are data files.
They are plain text files with no special structure.

Output specification

Your program should generate several output files outi.txt, where i is the line number in mapping
file. It means that you need to get mapping file as an argument to your program. Then each line in the
mapping file has information about the dictionary file and the data file.
For example suppose line j in the mapping file is dict j data j. In this case you should produce
outj.txt, which contains the described informations. Remember that you shouldn’t have any spaces at
the end of the lines in your output files. Also, you shouldn’t have any empty lines in your outputs files .
The program should write all the unique words (see definition above) that occur in the dictionary file
along with their various counts (See above), in lexicographical order, one word per line to the output
files i.e. the output should have exactly n lines:

<word1> <count11> <count12>

<word2> <count21> <count22>
.
.
.

<wordn> <countn1> <countn2>

such that

1. <word1>, <word2>, <word3> . . . <wordn> is the lexicographical ordering of the unique words
occurring in the dictionary,

2
. <counti1> denotes the number of occurrences of <wordi> in the data file,

3. <counti2> denotes the number of proper superwords of <wordi> in the data file,

4. Line i is <wordi><space><counti1><space><counti2>

Note that you can assume the dictionaries are non-empty.
Also note that if the mapping file has more than one line, you need to do same procedure
for each line and create the result file (outi.txt) of every line.
For example, running first on the input described above should produce the following output:

boo 0 4

book 0 3

booking 1 1

john 1 0

tex 1 3

text 1 1




The way my program works is as such:

first I open the map file and store the first char into a circular linked list. I read through the characters, adding them to my list with addEnd until I hit a space. I convert this CLL to a string and have it store said string to the dictionary name. I do the same to get the data file name.

After I have the file names, I use readDict to open the dict file, and read the file char by char while checking that it is a character or not. Everytime I find a non alpha char, I store the linked list into a string, this is my word.

I then insert the word into the trie (root)

once Im done inserting all the words I open the data file

for every alpha word in the dict file, I run an incrementing search which does superword++ whenever a search passes over that letter in the trie and occurance++, super -- whenever a search succesfully ends on a letter.

Then I read the dict file again, output the words into a linked list. Using buildAnswer

the words cary over the super and occ values from the last letter they had when they were in the trie.
I do quick sort on this answer list
Then I write the answer list with the values into the designated file with printResult();

I do this for every set of files until the end of the mapping file;