# deo-interpreter
A program that interprets a language that I call Deo 
Here are all the following commands my program can interpret:
COM typeanythinghere. COM is basically a comment and you can write anything you want on the same line as COM.
START is the start of a nested block of code. It determines the scope of the variables defined within a START-FINISH block.
FINISH is the end of a nested block of code. Use it with START to define variables within the nested START/FINISH block.
VAR varName = valueHere. For ex you would use it like this: VAR SajidDeo = 100 
PRINT varName. For ex: PRINT SajidDeo. You can also perform operations within the PRINT statement such as: PRINT SajidDeo * 2 or PRINT SajidDeo + 2
varName ++ Increments the varName by 1
varName -- Decrements the varName by 1

This program was a learning experience for me to develop a hashtable so that I could search for the variable and it's value in O(1) time. It uses hash chaining collision resolution strategy. I would have had used linear probing instead but I wanted to work more with linear lists which is the reason why I opted for chaining.
