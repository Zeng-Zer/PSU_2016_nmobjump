#! /bin/bash

diff <(./my_nm ~/.froot/lib/libsfml-graphics.so.2.3) <(nm ~/.froot/lib/libsfml-graphics.so.2.3)
diff <(./my_nm ~/.froot/lib/libsfml-system.so) <(nm ~/.froot/lib/libsfml-system.so)
diff <(./my_nm ~/.froot/lib/libsfml-audio.so) <(nm ~/.froot/lib/libsfml-audio.so)
diff <(./my_nm ~/.froot/lib/liblapin.a) <(nm ~/.froot/lib/liblapin.a)
diff <(./my_nm src/main.o) <(nm src/main.o)
diff <(./my_nm my_nm) <(nm my_nm)
diff <(./my_nm ~/rendu/PSU/PSU_2016_malloc/libmy_malloc.so) <(nm ~/rendu/PSU/PSU_2016_malloc/libmy_malloc.so)
