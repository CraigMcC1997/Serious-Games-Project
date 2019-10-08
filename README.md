# Serious-Games-Project
Repository for 4th Year Serious Games Project


  *** WIP ***

An app for teaching bartenders new cocktails

Current Build:
Cocktails are stored as files in a directory

At runtime:
 1. A random cocktail is chosen from the directory of cocktail text files
 2. A text file containing a list of cocktail ingredients is input and stored in the program
 3. The array of correct ingredients and the array of other ingredients are added together into one single array
 4. This new array is then checked for duplicates and the duplicates are "removed" (needs updated as ingredients are not actually removed)
 5. The array is then shuffled randomly so the correct ingredients are mixed in with the other ingredients
 6. The player then guesses the ingredients within the cocktail from the list dislayed
 7. If the player guesses correctly the ingredient is "removed" from the array and the player can guess again.
 
Two display functions exist:
 1. Displays the correct ingredients and name of the cocktail which the user will later guess
 2. Displays the final array of ingredients which the user will later use to pick from to guess which ingredients are in the correct           cocktail.
