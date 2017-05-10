# Ft_printf (Printf's refactoring)

## Project Overview
Ft_printf is a 42 Project that aims to mimic the printf function (included in <stdio.h>).<br /><br />
<img align="center" src="http://i.imgur.com/NlFm0FB.png" width="100%" />
<br /><br />Bonus :
1) <strong>~ at 175% faster than original printf (included in <stdio.h>)!</strong>.
2) Handles multiple file descriptor (use ft_dprintf(int fd, char const format, ...) instead of ft_printf).
3) All flags stored on only 14 bits.
4) Wildcard Length_modifier (%*) : replaces precision and field_width with parameter in va_list ap.
5) print_len with %n.
6) displaying errno with %m.
7) colors with '%{' (%{red}).
8) %f and %F to handle double and float numbers.

## How to use it

### Download and compile the library

```
git clone https://github.com/BenjaminSouchet/Ft_printf.git ~/Ft_printf
cd ~/Ft_printf
make
```

### Compile with your files

If you want to create a quick prog with the static library created before :
Add the include in your header.h or in your file ⇣
```
#include "ft_printf.h"
```
Then compile just like that ⇣
```
gcc -I include -o prog yourfile1.c yourfile2.c -L. -lftprintf
```
And execute it easily ⇣
```
./prog
```

## Credits

This project was done in collaboration with <strong>Agav</strong> a.k.a [Antonin Gavrel](https://github.com/agavrel)

## Contact or contribute

If you want to contact me, or fix / improve this project, just send me a mail at **bsouchet@student.42.fr**
