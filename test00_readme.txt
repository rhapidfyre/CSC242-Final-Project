## Controlled Test

- Place 5B.exe and these files in the same directory.

- In a terminal run:
CSC242_Assignment5B.exe -e -kFEATHER test00_in.txt test00_out.txt
fc /b test00_out.txt test00_test.txt
- EXPECT: "FC: no differences encountered"

- Then run:
CSC242_Assignment5B.exe -d -kFEATHER test00_out.txt test00_final.txt
fc /b test00_in.txt test00_final.txt
- EXPECT: "FC: no differences encountered"

PLAIN:  ABCDEFGHIJKLMNOPQRSTUVWXYZ
CIPHER: FEATHRZYXWVUSQPONMLKJIGDCB