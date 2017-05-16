# Warehouse
A C++ project. Create a database using a 2D.

The project
Desc: a multi demiensional array that is representing the length and width of a ware house. 
    Each coord will store item name or be left blank.
    string warehouse [x_coords][y_coords] = item_name; 
    The warehouse is able to store "items" in a x and y graph format. 
    The program will start with [some] already assigned "items" in the coordinates of the warehouse. 
    
Menu: The menu should offer the user the option to 
    1)add another item and to either 
        A) assign an automatic location in the warehouse
        B) allow the user to choose the coordinates of where the itesm should be placed 
    2)delete an item
    3)locate an item using one or two keys if necessary
    4)write data to a filein same format as input file (data file has to automaticly saved when program is closed)
    5)quit the programm
    
Error: If the user places an item in an already alloted space an error can occur 'Error: warehouse[0][0] is occupied!' and:
    A) offer to assign the item systematically
    B) give the user another chance to assign the coordinates. 
            
Features: The codes menu should also ask the user if they want to show the current inventory
    A) it can be organized to show open spaces(avaible room for the item)
    B) show the items based off another catergory wether that be alphabetically or by part number or by the rows and columns itself.
    C) Display occupied inventory.
    
