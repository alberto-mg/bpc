# Il linguaggio
Il linguaggio su cui lavora il compilatore è uno pseudo-codice che implementa tutti i costrutti della programmazione strutturata: sequenza, selezione, iterazione. Prevede come tipi di dato Intero (range degli int di C), Reale (range dei double di C), Carattere, Stringa, inoltre non supporta alcuno tipo di dato strutturato.

## BNF della grammatica
```
<statements> ::= <statement> "\n" | <statement> "\n" <statements>

<statement> ::= <type> <id> | <id> " <- " <val> | <io> | "MENTRE " <conditions> " ALLORA <!\n" <statements> "!>" | "SE " <conditions> " ALLORA <!\n" <statements> "!> " <else> |

<else> ::= "ALTRIMENTI <!\n" <statements> "!>" |

<conditions> ::= <condition> <logicop> <conditions> | <condition>

<condition> ::= <val> <compare> <val>

<operation> ::= <mathop> <val> <val>

<io> ::= "LEGGI -> " <id> | "STAMPA <- " <val>

<val> ::= <id> | <value> | <operation>

<id> ::= [a-zA-Z][_a-zA-Z0-9]*

<type> ::= "Intero" | "Reale" | "Carattere" | "Stringa"

<value> ::= 0|-?[1-9][0-9]* | (0|-?[1-9][0-9]*)\.?[0-9]* | ['].['] | ["][^"]*["] 

<compare> ::= "<" | "<=" | ">" | ">=" | "=" | "!="

<mathop> ::= "+" | "-" | "*" | "/" | "%"

<logicop> ::= "AND" | "OR"
```

### Esempio codice
```
Intero a
Intero b
Intero r
LEGGI -> a
LEGGI -> b
SE a < b ALLORA <!
	r <- a
	a <- b
	b <- r
!>
MENTRE b != 0 ALLORA <!
	r <- % a b
	a <- b
	b <- r
!>
STAMPA <- "L'MCD e' "
STAMPA <- a
```

## Funzionamento

### MENTRE
```
MENTRE <condition> ALLORA <!
	[blocco]
!>
```
Il costrutto equivale a un ciclo precondizionato, dove viene prima valutata la condizione e se vera viene eseguito il codice.

### SE-ALTRIMENTI
```
SE <condition> ALLORA <!
	[blocco true]
!> ALTRIMENTI <!
	[blocco false]
!>
```
Il costrutto equivale a un if-then-else, è presente anche if-then nel linguaggio, è sufficiente omettere "ALTRIMENTI".

### I/O
```
LEGGI -> <id>
STAMPA <- <val>
```
L'input viene fatto tramite la keyword "LEGGI", mentre l'output con "STAMPA", questa permette la concatenazione tramite l'operatore +, solo tra tipi Stringa e Carattere:
```
Stringa a
Stringa b
LEGGI -> a
LEGGI -> b
STAMPA <- + a b
```

### Condizioni
Si possono concatenare più condizioni nei MENTRE e nei SE, questo viene fatto tramite gli operatori logici "AND" e "OR". Non è possibile stabilire l'ordine tramite le parentesi, quindi si tratta sempre di una verifica short-circuit da sinsitra verso destra.
```
MENTRE a < 0 AND continua = 1 <!
	[blocco]
!>
```
Gli operatori di confronto disponibili sono: <, <=, >, >=, =, !=.

### Operatori aritmetici
Gli operatori aritmetici se utilizzati su Intero, Reale o Carattere hanno il loro classico funzinamento quindi:
- \+ : somma;
- \- : differenza;
- \* : prodotto;
- / : divisione;
- % : modulo;

Quando vengono utilizzati con tipi Stringa hanno un comportamento diverso:
- \+ : concatenazione
```
+ <val>.Carattere/<val>.Stringa <val>.Carattere/<val>.Stringa
```
- \- : restituisce la stringa con n caratteri rimossi dalla fine
```
- <val>.Stringa <val>.Intero
```
- \* : restituisce il carattere nella posizione specificata, se non è presente ritorna 0
```
* <val>.Stringa <val>.Intero
```
- / : restituisce la stringa con n caratteri rimossi dall'inizio
```
/ <val>.Stringa <val>.Intero
```
- % : restituisce 1 se la stringa o il carattere passato è una sottostringa
```
% <val>.Stringa <val>.Carattere/<val>.Stringa
```

### Compatibilità fra tipi

#### Assegnamenti
Gli assegnamenti validi, considerando il primo come tipo del left value e il secondo come tipo del right value, sono:
- Intero: Intero, Reale, Carattere;
- Reale: Intero, Reale, Carattere;
- Carattere: Intero, Reale, Carattere;
- Stringa: Carattere, Stringa.

#### Confronti
I confronti validi, considerando il primo come tipo del left value e il secondo come tipo del right value, sono:
- Intero: Intero, Reale, Carattere;
- Reale: Intero, Reale, Carattere;
- Carattere: Intero, Reale, Carattere;
- Stringa: Stringa.

#### Operazioni
Le operazioni definiscono il tipo dell'espressione finale quindi, considerando i casi in cui sono diversi:
- Intero-Carattere: valutato come Intero;
- Reale-Intero/Carattere : valutato come Reale;
- Stringa-Carattere: valutato come Stringa in caso di +, in caso di % come Intero;
- Stringa-Intero: valutato come Carattere in caso di \*, come Stringa in caso di - o /; 
