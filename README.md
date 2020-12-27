# Uzbek Spellchecker
This is our Data Structure project from 2020 Fall Semester. Our program makes use of multimap, and some linguistics features of Uzbek to do a basic spell-checking.

## Features
Currently our spellchecker checks words via blind-matching. Due to the agglutinative nature of Uzbek, words are formed by appending specifix affixes to the end. This feature makes the rules for chaining extremely complex and thus morphotactics of Uzbek is not yet defined. Moreover, according to the latest research in this area, around 100,000 lexemes for any verb exist in Uzbek. 

Our approach relies heavily on the amount of combinations of affixes, which are not necessarily grammatically or semantically correct - the only thing is that it agrees with language orthography.

## Example of Usage

In the example below, we made one typo in a phrase "to the cat", and got morpholigcally parsed and correct version of the word:

```
mushuggami
----------------
mushuk -> ga -> mi
```


Here we entered "qishgacha", which means "till the winter" without any typos, and the program returned parsed word:
```
qishgacha
----------------
qish -> ga -> cha
```
