Exact Cover - program which solves the problem of exact cover. </br>

Author: Arkadiusz Tomczak</br>
Version: 1.0</br>
Date: 12-01-2016</br>
Language:
 - Variable names: Polish
 - Comments: Polish

You can read more about the problem here: https://en.wikipedia.org/wiki/Exact_cover</br></br>
Program gets some rows which can contain any ASCI character. If there is a space (`' '` character) - program interpretes it as a hole in the row.
Program will take all of the rows and try to merge them (two rows can be merged if letters of one row fit in holes in the second one).
If one row is shorter than other, program assumes that they are the same size, but there are holes at the end of shorter row.
If it can merge some of the rows it will write it to stdout. This program creates every possible output (every possible match of rows).
