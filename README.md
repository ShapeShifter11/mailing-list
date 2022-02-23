# mailing-list

## mailing list routine using doubly linked lists

when started, the program displays a menu of options from which the user can chose:

``` c
    "1. Enter a name"
    "2. Delete a name"
    "3. List the file"
    "4. Search"
    "5. Save the file"
    "6. Load the file"
    "7. Quit" 
    
```
- `enter a name` option creates a new antry and prompts the user to fill in the reqiered information.
- `delete a name` option deletes an existing entry.
-  `list the file` option displays the contents of the mailing list.
-  `search` option searches the database by name. If no match is found it displays an appropriate message
- while active the program saves the entries on dinamicly allocated memmory. 
If the `save` option is chosen from the menu it will create a binary file on which the entries will be saved.
`load` is the other file function which will load an already existing binary disk file.
- `quit` option exits the program.
